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
		case 0: department = "ОТДЕЛОМ УФМС РОССИИ"; break;
		case 1: department = "ОТДЕЛОМ УФМС"; break;
		case 2: department = "МВД РОССИИ"; break;
		case 3: department = "ОТДЕЛОМ МИЛИЦИИ"; break;
		}
		switch (rand() % 4) {
		case 0: region = "ПО СВЕРЛОВСКОЙ ОБЛАСТИ Г ЕКАТЕРИНБУРГ"; break;
		case 1: region = "ПО ЛЕНИНГРАДСКОЙ ОБЛАСТИ Г САНКТ-ПЕТЕРБУРГ"; break;
		case 2: region = "ПО МОСКОВСКОЙ ОБЛАСТИ Г МОСКВА"; break;
		case 3: region = "ПО ТУЛЬСТКОЙ ОБЛАСТИ Г ТУЛА"; break;
		}
		return department + " " + region + " " + getRandAddress() + " " + getRandDate();
	}
	static string	getRandName(){
		vector<string> NAMES{ "никита", "дмитрий", "артём", "владислав", "артемий",
			"михаил", "александр", "иван", "максим", "матвей", "григорий", "георгий",
			"станислав", "вячеслав", "тимофей", "евгений", "олег", "сергей", "илья",
			"роман", "кирилл", "василий", "арсений", "тимур", "даниил", "анатолий",
			"глеб", "андрей", "денис", "алексей"
		};
		vector<string> SURNAMES{ "смирнов", "белов", "лебедев", "волков", "зайцев",
			"голубев", "елисеев", "костев", "емельянов", "савин", "авдеев", "носов",
			"мишин", "миронов", "фадеев", "дементьев", "игнатьев", "молчанов",
			"глазатов", "мухин", "бобырев", "бледных", "красилов", "гарин", "беркутов",
			"ларкин", "аверин", "златов", "вихрев", "анохин"
		};
		vector<string> FATHERNAMES{ "фёдорович", "романович", "александрович", "алексеевич",
			"станиславович", "ильич", "евгеньевич", "денисович", "сергеевич", "андреевич",
			"иванович", "владиславович", "васильевич", "вячеславович", "григорьевич",
			"николаевич", "борисович", "олегович", "владимирович", "валерьевич", "юрьевич",
			"генадьевич", "павлович", "степанович", "дмитриевич", "игоревич", "ренатович",
			"тимурович", "георгиевич", "львович"
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
		vector<string> STREET{ "УЛ.", "ПР-КТ", "ПЕР.", "ПРОЕЗД" };
		vector<string> STREET_NAME{ "ГАГАРИНА", "ОДУВАНЧИКОВ", "ЛЕНИНА", "КАМЕНОЛОМНЯ",
			"ГРУСТНЯКА", "ПУШКИНА", "СТАЧЕК", "КРУТЫХ ТАЧЕК", "ПРОФСОЮЗОВ"
		};
		return STREET[rand() % STREET.size()] + " " + STREET_NAME[rand() % STREET_NAME.size()] + " д. " + std::to_string(1 + rand() % 199);
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
		case 0: return "БЕЗЛИМИТИЩЕ";
		case 1: return "ДЛЯ БАБУШЕК";
		case 2: return "ЛИМИТИЩЕ";
		case 3: return "ДЛЯ РАЗДАЧИ";
		case 4: return "ИНТЕРНЕТ + ТВ";
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