#pragma once
#include <string>
using std::string;
#include <vector>
using std::vector;
#include "fstream"
using std::ofstream;
#include "Exceptions.h"
#include "Entities.h"
#include "UsefullFunctions.h"

static const uint8_t PARTS = 10;

class myList {
public:
	static uint64_t getInt(string key) {
		return std::stod(key.c_str());
	}
	static uint8_t getPart(string key) {
		return *key.begin() - uint8_t('0');
	}
private:
	struct node {
		uint64_t key = PARTS;
		Entity::trade value;
		node* next, * nextPart;
		node() {}
		node(const string& key, const Entity::trade& value, node* next = nullptr) {
			this->key = getInt(key);
			this->value = value;
			this->next = next;
			this->nextPart = nullptr;
		}
		bool empty() { return key == PARTS; }
	};
	vector<node*> Part;
	uint16_t Size = 0;
	void sorted_insert(const string& key, const Entity::trade& value, node*&current) {
		if (current->key > getInt(eraseDash(key))) {
			// если текущий больше нового, вставляем перед ним
			node* tmp = new node(std::to_string(current->key), current->value, current->next);
			current->next = tmp;
			current->key = getInt(eraseDash(key));
			current->value = value;
			++Size; return;
		}
		else if (current->next == Part[getPart(key)]->nextPart) {
			// если следующий уже из нового раздела, вставляем после текущего
			current->next = new node(key, value, current->next);
			++Size; return;
		}
		else (sorted_insert(key, value, current->next));
	}
public:
	void show_head(std::ostream& fout) {
		fout << " "; draw(73, '-', fout); fout << std::endl;
		fout << "| НОМЕР ПАСПОРТА ";
		fout << "| НОМЕР SIM-КАРТЫ ";
		fout << "| ВРЕМЯ ДЕЙСТВИЯ";  draw(13, ' ', fout);
		fout << "|"; draw(9, ' ', fout); fout << "|" << endl;
		fout << " "; draw(73, '-', fout); fout << std::endl;
	}
	void show_node(std::ostream& fout, Entity::trade* current) {
		fout << "| " << current->passport; draw(4, ' ', fout);
		fout << "| " << current->number; draw(5, ' ', fout);
		fout << "| с " << current->dateON << " до " << current->dateOFF << " ";
		fout << "| " << (current->Trade == Entity::trade::TRADE::SALE ? "ПРОДАЖА " : "ВОЗВРАТ ");
		fout << "|" << std::endl;
		fout << " "; draw(73, '-', fout); fout << std::endl;
	}
	myList() {
		for (uint8_t i = 0; i < PARTS; ++i) { Part.push_back(new node()); }
		for (uint8_t i = 0; i < PARTS; ++i) {
			if (i == PARTS - 1) {
				Part[i]->next = nullptr;
				Part[i]->nextPart = nullptr;
			}
			else {
				Part[i]->next = Part[i + 1];
				Part[i]->nextPart = Part[i + 1];
			}
		}
	}
	void set(const string& key, const Entity::trade& value) {
		uint8_t index = getPart(key);
		if (Part[index]->empty()) { 
			Part[index]->key = getInt(eraseDash(key)); 
			Part[index]->value = value; 
			++Size;
		} else sorted_insert(key, value, Part[index]);
	}
	vector<Entity::trade*> findAll_byKey(const string& key) {
		vector<Entity::trade*> buff;
		node* current = Part[getPart(key)];
		while (current != Part[getPart(key)]->nextPart) {
			if (current->key == getInt(key))
				buff.push_back(&current->value);
			current = current->next;
		}
		return buff;
	}
	vector<Entity::trade*> findAll_byValue(const string& value) {
		vector<Entity::trade*> buff;
		node* current = Part[0];
		while (current) {
			if (current->value.number == value)
				buff.push_back(&current->value);
			current = current->next;
		}
		return buff;
	}
	void print(std::ostream& fout) {
		show_head(fout);
		node* current = Part[0];
		while (current) {
			if(!current->empty())
				show_node(fout, &current->value);
			current = current->next;
		}
	}
	uint16_t size() { return this->Size; }
};