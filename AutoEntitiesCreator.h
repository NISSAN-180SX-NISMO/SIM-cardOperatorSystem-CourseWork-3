#pragma once
#include <string>
using std::string;
using std::to_string;
#include <vector>
using std::vector;
#include "Entities.h"
#include "Validators.h"
#include "UsefullFunctions.h"

class AutoEntitiesCreator {
private:
	static string	getRandPassport(){
		string number;
		for (int i = 0; i < 10; i++)
		{
			if (i == 4) number += '-';
			number += to_string(rand() % 10);
		}
		return number;
	}
	static string	getRandGiven(){
		string department, region;
		switch (rand() % 4) {
		case 0: department = "������� ���� ������"; break;
		case 1: department = "������� ����"; break;
		case 2: department = "��� ������"; break;
		case 3: department = "������� �������"; break;
		}
		switch (rand() % 4) {
		case 0: region = "�� ����������� ������� � ������������"; break;
		case 1: region = "�� ������������� ������� � �����-���������"; break;
		case 2: region = "�� ���������� ������� � ������"; break;
		case 3: region = "�� ��������� ������� � ����"; break;
		}
		return department + " " + region + " " + getRandAddress() + " " + getRandDate();
	}
	static string	getRandName(){
		vector<string> NAMES{ "������", "�������", "����", "���������", "�������",
			"������", "���������", "����", "������", "������", "��������", "�������",
			"���������", "��������", "�������", "�������", "����", "������", "����",
			"�����", "������", "�������", "�������", "�����", "������", "��������",
			"����", "������", "�����", "�������"
		};
		vector<string> SURNAMES{ "�������", "�����", "�������", "������", "������",
			"�������", "�������", "������", "���������", "�����", "������", "�����",
			"�����", "�������", "������", "���������", "��������", "��������",
			"��������", "�����", "�������", "�������", "��������", "�����", "��������",
			"������", "������", "������", "������", "������"
		};
		vector<string> FATHERNAMES{ "���������", "���������", "�������������", "����������",
			"�������������", "�����", "����������", "���������", "���������", "���������",
			"��������", "�������������", "����������", "������������", "�����������",
			"����������", "���������", "��������", "������������", "����������", "�������",
			"����������", "��������", "����������", "����������", "��������", "���������",
			"���������", "����������", "�������"
		};
		string surname = SURNAMES[rand() % SURNAMES.size()];
		toUpperString(surname);
		string name = NAMES[rand() % NAMES.size()];
		toUpperString(name);
		string fathername = FATHERNAMES[rand() % FATHERNAMES.size()];
		toUpperString(fathername);
		return surname + " " + name + " " + fathername;
	}
	static uint16_t getRandYear(uint16_t edge = 1950){
		return edge + rand() % std::abs(2020 - edge);
	}
	static string	getRandAddress(){
		vector<string> STREET{ "��.", "��-��", "���.", "������" };
		vector<string> STREET_NAME{ "��������", "�����������", "������", "�����������",
			"���������", "�������", "������", "������ �����", "����������"
		};
		return STREET[rand() % STREET.size()] + " " + STREET_NAME[rand() % STREET_NAME.size()] + " �. " + std::to_string(1 + rand() % 199);
	}
	static string	getRandNumber(){
		string number;
		for (int i = 0; i < 10; i++)
		{
			if (i == 3) number += '-';
			number += to_string(rand() % 10);
		}
		return number;
	}
	static string	getRandTariff(){
		switch (rand()%5) {
		case 0: return "�����������";
		case 1: return "��� �������";
		case 2: return "��������";
		case 3: return "��� �������";
		case 4: return "�������� + ��";
		}
	}
	static string	getRandDate(){
		string d, m, y;
		d = to_string(1 + rand() % 31);
		m = to_string(1 + rand() % 12);
		y = to_string(2020 + rand() % 4);
		if (d.size() == 1) d = "0" + d;
		if (m.size() == 1) m = "0" + m;
		return d + "/" + m + "/" + y;
	}
public:
	static Entity::client*	CreateClient(){
		Entity::client* Client = new Entity::client();
		Client->passport = getRandPassport();
		Client->given = getRandGiven();
		Client->name = getRandName();
		Client->year = getRandYear();
		Client->address = getRandAddress();
		return Client;
	}
	static Entity::SIM*		CreateSIM(){
		Entity::SIM* Sim = new Entity::SIM();
		Sim->number = getRandNumber();
		Sim->tariff = getRandTariff();
		Sim->year = getRandYear(2000);
		Sim->in_stock = true;
		return Sim;
	}
	static Entity::trade*	CreateTrade(const string& passport, const string& number) {
		Entity::trade* Trade = new Entity::trade();
		Trade->passport = passport;
		Trade->number = number;
		while (true) {
			Trade->dateON = getRandDate();
			Trade->dateOFF = getRandDate();
			if (!DateIsReal(Trade->dateON)) continue;
			if (!DateIsReal(Trade->dateOFF)) continue;
			if (LeftDateIsBigger(Trade->dateON, Trade->dateOFF)) continue;
			break;
		}
		Trade->Trade = Entity::trade::TRADE::SALE;
		return Trade;
	}

};