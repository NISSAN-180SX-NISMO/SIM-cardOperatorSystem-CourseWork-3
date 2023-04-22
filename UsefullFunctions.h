#pragma once
#include <iostream>
using std::cout;
using std::endl;
#include <conio.h>
#include <string>
using std::string;

void toUpperString(std::string& str) {
	std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return c == 'я' ? 'Я' : std::toupper(c); });
}

void draw(int count, char what, std::ostream& fout) {
	for (int i = 0; i < std::abs(count); i++)
		fout << what;
}

void pause() {
	cout << "\tНажмите любую кнопку..." << endl;
	_getch();
}

void cls() {
	system("cls");
}

string eraseDash(string key) {
	key.erase(std::find(key.begin(), key.end(), '-'));
	return key;
}

vector<int> DateToVector(string date) { 
	// разделяет строку на массив из дд/мм/гггг
	std::vector<int> DATE;
	std::string buff = "";
	for (auto i = date.begin(); i <= date.end(); ++i) {
		if (i == date.end()) { DATE.push_back(atoi(buff.c_str())); break; }
		else if (*i == '/') { DATE.push_back(atoi(buff.c_str())); buff = ""; }
		else { buff += *i; }
	}
	return DATE;
}

bool LeftDateIsBigger(string LeftDate, string RightDate) {
	// сравнивает даты (нужно для проверки на ввод)
	constexpr auto DAY = 0;
	constexpr auto MONTH = 1;
	constexpr auto YEAR = 2;
	std::vector<int> L = DateToVector(LeftDate);
	std::vector<int> R = DateToVector(RightDate);

	if (L[YEAR] < R[YEAR]) return false;
	if (L[YEAR] > R[YEAR]) return true;
	else
		if (L[MONTH] < R[MONTH]) return false;
	if (L[MONTH] > R[MONTH]) return true;
	else
		if (L[DAY] < R[DAY]) return false;
		else return true;
}

bool FindSubString(std::string String, std::string SubString) {
	int stringSize = String.size();
	int subStringSize = SubString.size();

	for (int i = 0; i <= stringSize - subStringSize; i++) {
		int j;
		for (j = 0; j < subStringSize; j++)
			if (String[i + j] != SubString[j])
				break;
		if (j == subStringSize)
			return true;
	}
	return false;
}

Entity::trade* FindUnique(vector<Entity::trade*> buff) {
	if (!buff.size()) return nullptr;
	if (buff.size() == 1) return buff[0];
	for (size_t i =	0; i < buff.size(); ++i) {
		for (size_t j = 0; j < buff.size(); ++j) {
			if (i == j) continue;
			if (buff[i]->passport == buff[j]->passport)
				break;
			if (j == buff.size() - 1) return buff[i];
		}
	}
	return nullptr;
}