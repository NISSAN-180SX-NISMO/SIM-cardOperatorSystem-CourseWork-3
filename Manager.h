#pragma once
#include <iostream>
using std::cout;
using std::endl;
#include <functional>
using std::function;
#include <string>
using std::string;
#include "Validators.h"
#include "myList.h"
#include "myTable.h"
#include "myTree.h"

class Manager {
private:
	static myTree					Clients;
	static myTable					SIMCards;
	static myList					Trades;
	static string					UserInput;
public:						
	static string					input(const string& title, function<bool(string)> predicat = [](string) { return true; }) {
		while (true) {
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			cout << title; std::getline(std::cin, UserInput);
			toUpperString(UserInput);
			try { predicat(UserInput); break; }
			catch (UncorrectPassport& ex) { cout << "Некорректный ключ! " << ex.get_more() << " Повторите ввод!" << endl; }
			catch (UncorrectSIM& ex) { cout << "Некорректный ключ! " << ex.get_more() << " Повторите ввод!" << endl; }
			catch (UncorrectDate& ex) { cout << "Некорректный формат даты! " << ex.get_more() << " Повторите ввод!" << endl; }
		}
		return UserInput;
	}
	static Entity::client*			CreateClient(const string& extpass = "") {
		Entity::client* Client = new Entity::client;
		if (extpass == "")
			Client->passport = Manager::input("\tВведите паспорт в формате << 1234-123456 >> : ", PassportValidator);
		else Client->passport = extpass;
		Client->given = Manager::input("\tВведите место и дату выдачи: ");
		Client->name = Manager::input("\tВведите ФИО: ");
		Client->year = atoi(Manager::input("\tВведите год рождения: ", YearValidator).c_str());
		Client->address = Manager::input("\tВведите адрес проживания: ");
		return Client;
	}
	static Entity::SIM*				CreateSIM(string extnum = "") {
		Entity::SIM* sim = new Entity::SIM();
		if (extnum == "")
			sim->number = Manager::input("\tВведите номер SIM-карты в формате << 123-1234567 >> : ", SIMValidator);
		else sim->number = extnum;
		sim->tariff = Manager::input("\tВведите название тарифа: ");
		sim->year = atoi(Manager::input("\tВведите год выдачи: ", YearValidator).c_str());
		sim->in_stock = true;
		return sim;
	}
	static Entity::trade*			CreateTrade(Entity::trade::TRADE THIS_TRADE, string passport = "", string number = "") {
		Entity::trade* Trade = new Entity::trade;
		if (passport == "")
			Trade->passport = Manager::input("\tВведите паспорт в формате << NNNN-NNNNNN >> : ", PassportValidator);
		else Trade->passport = passport;
		if (number == "")
			Trade->number = Manager::input("\tВведите номер SIM-карты в формате << NNN-NNNNNNN >> : ", SIMValidator);
		else Trade->number = number;
		bool flag = false;
		do {
			start:
			if (flag) cout << "\tДата выдачи не может быть больше окончания!!! Повторите ввод!!!" << endl;
			Trade->dateON = Manager::input("\tВведите дату выдачи в формате << dd/mm/yyyy >>: ", DateValidator);
			if (!DateIsReal(Trade->dateON)) { cout << "Невозможная дата!!! Повторите ввод!" << endl; goto start; }
			Trade->dateOFF = Manager::input("\tВведите дату окончания в формате << dd/mm/yyyy >>: ", DateValidator);
			if (!DateIsReal(Trade->dateOFF)) { cout << "Невозможная дата!!! Повторите ввод!" << endl; goto start; }
			flag = true;
		} while (LeftDateIsBigger(Trade->dateON, Trade->dateOFF));
		Trade->Trade = THIS_TRADE;
		return Trade;
	}
	static bool						isDebtorClient(Entity::client &Client) {
		bool isDebtor = false;
		auto Trades = findTrades_byPassport(Client.passport);
		for (size_t i = 0; i < Trades.size(); i++)
		{
			isDebtor = true;
			for (size_t j = 0; j < Trades.size(); j++)
			{
				if (i == j) continue;
				if (Trades[i]->passport == Trades[j]->passport && Trades[i]->number == Trades[j]->number)
					isDebtor = false;
			}
		}
		return isDebtor;
	}
public:
	static myTree*					getTree() { return &Clients; }
	static Entity::SIM*				getSIM(const uint16_t index){ 
		if (!SIMCards[index]) return nullptr;
		if (SIMCards[index]->removed) return nullptr;
		return &SIMCards[index]->value; 
	}
	static const uint16_t			getSIMSVolume() { return myTable::VOLUME; }
public:
	static const void				setClient(Entity::client& Client) {
		Clients.set(eraseDash(Client.passport), Client);
	}
	static const void				popClient(Entity::client& Client) {
		Clients.remove(myTree::getInt(eraseDash(Client.passport)));
	}

	static const void				setSIM(Entity::SIM& sim) {
		SIMCards.set(eraseDash(sim.number), sim);
	}
	static const void				popSIM(Entity::SIM& sim) {
		SIMCards.remove(eraseDash(sim.number));
	}

	static const void				setTrade(Entity::trade& Trade) {
		Trades.set(eraseDash(Trade.passport), Trade);
	}
public:
	static enum class				FOR : uint8_t {CLIENTS, SIMS, TRADES};
	static const void				print(std::ostream& fout, FOR WHAT) { 
		switch (WHAT) {
		case FOR::CLIENTS: Clients.print(fout); break;
		case FOR::SIMS: SIMCards.print(fout); break;
		case FOR::TRADES: Trades.print(fout); break;
		}
	}
	static const void				print(std::ostream& fout, Entity::client* value) {
		Clients.show_head(fout);
		Clients.show_node(fout, value);
	}
	static const void				print(std::ostream& fout, vector<Entity::client*> values) {
		Clients.show_head(fout);
		for (auto& value : values)
			Clients.show_node(fout, value);
	}
	static const void				print(std::ostream& fout, Entity::SIM* value) {
		SIMCards.show_head(fout);
		SIMCards.show_node(fout, value);
	}
	static const void				print(std::ostream& fout, vector<Entity::SIM*> values) {
		SIMCards.show_head(fout);
		for (auto & value : values)
			SIMCards.show_node(fout, value);
	}
	static const void				print(std::ostream& fout, Entity::trade* value) {
		Trades.show_head(fout);
		Trades.show_node(fout, value);
	}
	static const uint16_t			size(const FOR& WHAT) {
		switch (WHAT) {
		case FOR::CLIENTS: return Clients.size();
		case FOR::SIMS: return SIMCards.size();
		case FOR::TRADES: return Trades.size();
		}
	}
public:
	static Entity::SIM*				findSIM(const string &number) { return SIMCards.find(eraseDash(number)); }
	static vector<Entity::SIM*>		findSIMS(const string &tariff) { return SIMCards.findAll(eraseDash(tariff)); }
	static Entity::client*			findClient(const string& passport) { return Clients.find(eraseDash(passport)); }
	static vector<Entity::client*>	findClients(const string& SubString) { return Clients.findAll(eraseDash(SubString)); }
	static vector<Entity::trade*>	findTrades_byNumber(const string& number) { return Trades.findAll_byValue(number); }
	static vector<Entity::trade*>	findTrades_byPassport(const string& passport) { return Trades.findAll_byKey(eraseDash(passport)); }
};

myTree Manager::Clients;
myTable Manager::SIMCards;
myList Manager::Trades;
string Manager::UserInput;