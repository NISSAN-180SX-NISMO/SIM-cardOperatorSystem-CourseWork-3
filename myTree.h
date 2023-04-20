#pragma once
#include <string>
using std::string;
#include <vector>
using std::vector;
#include "fstream"
using std::ofstream;
#include "Exceptions.h"
#include "Entities.h"

class myTree {
public:
	static uint64_t getInt(string key) {
		return std::stod(key.c_str());
	}
private:
	struct node {
		uint64_t key;
		Entity::client value;
		node* left, * right;
		int8_t height;
		node() { left = right = nullptr; height = 1; }
		node(const string& key, const Entity::client& value, node* left = nullptr, node* right = nullptr) {
			this->value = value;
			this->key = getInt(key);
			this->left = left;
			this->right = right;
			height = 1;
		}
	};
	node* Head = nullptr;
	uint16_t Size = 0;
	int8_t height(node* current) 
	{ return current ? current->height : 0; } // получает текущую разность высот
	int8_t bfactor(node* current) 
	{ return height(current->right) - height(current->left); } // вычисляет новую разность высот
	void fixheight(node* current) { // фиксит разность высот после вращений
		uint8_t hLeft = height(current->left);
		uint8_t hRight = height(current->right);
		current->height = (hLeft > hRight ? hLeft : hRight) + 1;
	}
	node* rotateright(node* current) {
		node* temp = current->left;
		current->left = temp->right;
		temp->right = current;
		fixheight(current);
		fixheight(temp);
		return temp;
	}
	node* rotateleft(node* current) {
		node* temp = current->right;
		current->right = temp->left;
		temp->left = current;
		fixheight(current);
		fixheight(temp);
		return temp;
	}
	node* balance(node* current) // балансировка узла current
	{
		fixheight(current);
		if (bfactor(current) == 2)
		{
			if (bfactor(current->right) < 0)
				current->right = rotateright(current->right);
			return rotateleft(current);
		}
		if (bfactor(current) == -2)
		{
			if (bfactor(current->left) > 0)
				current->left = rotateleft(current->left);
			return rotateright(current);
		}
		return current; // балансировка не нужна
	}
	node* findmin(node* current) // поиск узла с минимальным ключом в дереве current
	{
		return current->left ? findmin(current->left) : current;
	}
	node* removemin(node* current) // удаление узла с минимальным ключом из дерева current
	{
		if (current->left == nullptr) return current->right;
		current->left = removemin(current->left);
		return balance(current);
	}
	node* remove(int64_t key, node* current) // удаление ключа key из дерева current
	{
		if (current == nullptr) return 0;
		if (key < current->key) current->left = remove(key, current->left);
		else if (key > current->key) current->right = remove(key, current->right);
		else //  key == current->key 
		{
			node* left_copy = current->left;
			node* right_copy = current->right;
			delete current;
			if (right_copy == nullptr) {
				--Size;
				return left_copy;
			}
			node* min = findmin(right_copy);
			min->right = removemin(right_copy);
			min->left = left_copy;
			--Size;
			return balance(min);

		}
		return balance(current);
	}
	node* set(const string& key, const Entity::client& value, node* current) { // добавление
		if (!current) { ++Size; return new node(key, value); }
		if (current->key == getInt(key)) throw Tree_DuplicateKey(key);
		if (getInt(key) < current->key) { current->left = set(key, value, current->left); }
		else { current->right = set(key, value, current->right); }
		return balance(current);
	}
	Entity::client* find(const string& key, node* current) {
		if (!current) return nullptr;
		if (current->key == getInt(key)) return &current->value;
		if (getInt(key) < current->key) return find(key, current->left);
		else return find(key, current->right);
	}
	void findAll(const string& value, vector<Entity::client*>& buff, node* current) {
		if (!current) return;		// прямой обход 
		if (FindSubString(current->value.name, value) || FindSubString(current->value.address, value)) 
			buff.push_back(&current->value);
		if(current->left) findAll(value, buff, current->left);
		if (current->right) findAll(value, buff, current->right);
	}
	void print(std::ostream& fout, node* current) {
		if (!current) return;
		if (current) show_node(fout, &current->value);
		if (current->left) print(fout, current->left);
		if (current->right) print(fout, current->right);
	}
	void getAll(vector<Entity::client*> &all, node* current) {
		if (!current) return;
		if (current) all.push_back(&current->value);
		if (current->left) getAll(all, current->left);
		if (current->right) getAll(all, current->right);
	}
public:
	void show_head(std::ostream& fout) {
		fout << " "; draw(222, '-', fout); fout << std::endl;
		fout << "| ПАСПОРТ"; draw(5, ' ', fout); 
		fout << "| ВЫДАН";  draw(96, ' ', fout); 
		fout << "| ФИО";  draw(35, ' ', fout); 
		fout << "| ГОД РОЖДЕНИЯ ";
		fout << "| АДРЕС";  draw(44, ' ', fout); fout << "|"  << std::endl;
		fout << " "; draw(222, '-', fout); fout << std::endl;
	}
	void show_node(std::ostream& fout, Entity::client* current) {
		fout << "| " << current->passport << " ";
		fout << "| " << current->given; draw(101 - current->given.size(), ' ', fout);
		fout << "| " << current->name; draw(38 - current->name.size(), ' ', fout);
		fout << "| " << current->year; draw(9, ' ', fout);
		fout << "| " << current->address; draw(49 - current->address.size(), ' ', fout); 
		fout << "|" << std::endl;
		fout << " "; draw(222, '-', fout); fout << std::endl;
	}
	~myTree() { clear(); }
	Entity::client* getHead() { return &Head->value; }
	void set(const string& key, const Entity::client& value) {
		Head = set(key, value, Head);
	}
	void remove(int64_t key) {
		Head = remove(key, Head);
	}
	void clear() {
		while (Size) {
			remove(Head->key, Head);
		}
	}
	vector<Entity::client*> getAll() {
		vector<Entity::client*> All;
		getAll(All, Head);
		return All;
	}
	Entity::client* find(const string& key) {
		return find(key, Head);
	}
	vector<Entity::client*> findAll(const string& value) {
		vector<Entity::client*> buff;
		findAll(value, buff, Head);
		return buff;
	}
	void print(std::ostream& fout) { show_head(fout); print(fout, Head); }
	uint16_t& size() { return this->Size; }
};