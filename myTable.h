#pragma once
#include <cstdint>
#include <vector>
using std::vector;
#include "fstream"
using std::ofstream;
#include "Exceptions.h"
#include "Entities.h"


class myTable {
public:
    static uint16_t VOLUME;
    static const uint16_t HashFunction1(const std::string& key) {
        uint16_t hash = 5381;   // начальное значение хеша
        for (char c : key) {    // побитовые операции
            hash = ((hash << 5) + hash) + c;
        }
        return hash % VOLUME;   // модуль от размера
    }
    static const uint16_t HashFunction2(const std::string& key) {
        uint16_t hash_val = 0;
        const uint16_t A = 2833;  // Простое число A
        const uint16_t B = 9421;  // Простое число B
        const uint16_t C = 5209;  // Простое число C
        const uint16_t FIRST_HASH = 37; // Начальное значение хеша

        for (auto &c : key)          // Посимвольный подсчет значения хеша
            hash_val = (hash_val * A + static_cast<uint16_t>(c)) % C;

        return (FIRST_HASH * hash_val) % VOLUME;
    }
private:
    struct node {
        string key;             // ключ
        Entity::SIM value;      // значение
        bool removed;           // была ли ячейка удалена
        node(bool removed = false) {
            this->removed = removed;
        }
        node(string key, Entity::SIM value) {
            this->key = key;
            this->value = value;
            this->removed = false;
        }
    };
    vector<node*> Table;
    uint16_t Size = 0;
    void remove_node(node*& current) {  // удаляет ячейку по указателю
        if (!current) return;                  // создает пустую ячейку
        delete current;                        // с тегом "удалена" 
        current = new node(true);
        --Size;
    }
public:
    void show_head(std::ostream& fout) {
        fout << " "; draw(69, '-', fout); fout << std::endl;
        fout << "| НОМЕР SIM-КАРТЫ ";
        fout << "| ТАРИФ";  draw(20, ' ', fout);
        fout << "| ГОД ВЫДАЧИ ";  
        fout << "| В НАЛИЧИИ |" << endl;
        fout << " "; draw(69, '-', fout); fout << std::endl;
    }
    void show_node(std::ostream& fout, Entity::SIM* current) {
        fout << "| " << current->number; draw(5, ' ', fout);
        fout << "| " << current->tariff; draw(25 - current->tariff.size(), ' ', fout);
        fout << "| " << current->year; draw(7, ' ', fout);
        fout << "| " << (current->in_stock ? "ЕСТЬ" : "НЕТ "); draw(6, ' ', fout);
        fout << "|" << std::endl;
        fout << " "; draw(69, '-', fout); fout << std::endl; 
    }
    myTable(){ 
        Table.resize(VOLUME, nullptr); 
    }
    ~myTable() { clear(); }
    node* operator[](const uint16_t index) {
        return Table[index] ? Table[index] : nullptr;
    }
    void resize(static uint16_t NEW_VOLUME) {   // увеличивает размер таблицы
        VOLUME = NEW_VOLUME;                    // если она занята более чем на 70%
        std::vector<node*> tmp = Table;
        Table.clear(); Table.resize(NEW_VOLUME, nullptr);
        Size = 0;
        for (node*& el : tmp)
            if (el) set(el->key, el->value);    // все ключи хешируются заново
        tmp.clear();
    }
    void set(const string& key, const Entity::SIM& value) {
        if (Size >= 0.7 * VOLUME) resize(VOLUME <<= 2);
        uint16_t index = HashFunction1(key);
        uint64_t i = 0;
        while (true) {
            if (!Table[index] || Table[index]->removed) {
                Table[index] = new node(key, value);
                Table[index]->removed = false;
                ++Size;            // если ячейка пуста или удалена
                break;             // добавляетм данные
            }
            else {
                if (Table[index]->key == key) throw Table_DuplicateKey(key); // проверка на дубликат
                ++i; index += i * HashFunction2(key); // двойное хеширование
                index = std::abs(int(index % VOLUME));
            }
        }
    }
    void remove(const string& key) {
        uint16_t index = HashFunction1(key);
        uint64_t i = 0;
        while (true) {
            if (Table[index] || Table[index]->removed) {
                if (Table[index]->key == key) {     // если ячейка занята или удалена
                    remove_node(Table[index]);      // удаляем или продолжаем поиск
                    break;
                }
                ++i; index += i * HashFunction2(key); // двойное хеширование
                index = std::abs(int(index % VOLUME));
            }
            else break;
        }
    }
    void clear() { // очистка таблицы
        for (auto& Node : Table) {
            remove_node(Node);
        }
    }
    Entity::SIM* find(const string& key) {
        uint16_t index = HashFunction1(key);
        uint64_t i = 0;
        while (true) {
            if (Table[index]) {
                if (Table[index]->key == key)      // если ячейка занята или удалена
                    return &Table[index]->value;           // возвращаем или продолжаем поиск
                ++i; index += i * HashFunction2(key); // двойное хеширование
                index = std::abs(int(index % VOLUME));
            }
            else return nullptr;
        }
    }
    vector<Entity::SIM*> findAll(const string& value) {
        vector<Entity::SIM*> buff;
        
        for (auto& Node : Table) {
            if (Node && Node->value.tariff == value)
                buff.push_back(&Node->value);
        }
        return buff;
    }
    void print(std::ostream& fout) {
        show_head(fout);
        for (auto& Node : Table)
            if (Node && !Node->removed) show_node(fout, &Node->value);
    }
    uint16_t size() { return this->Size; }
};

uint16_t myTable::VOLUME = 1367;