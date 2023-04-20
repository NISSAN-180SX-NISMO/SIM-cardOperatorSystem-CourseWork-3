#pragma once
#include <iostream>
using std::cout;
using std::endl;
#include "fstream"
using std::ofstream;
#include <string>
using std::string;
#include "Entities.h"
#include "Validators.h"
#include "Manager.h"
#include "AutoEntitiesCreator.h"

class Menu {
private:
	static string				TreePath;
	static string				TablePath;
	static string				ListPath;
public:							
	static const uint8_t		inputUserChoise() {
		string UserChoise;
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		cout << endl << "\t������� ��������: ";
		std::getline(std::cin, UserChoise);
		cout << endl;
		return atoi(UserChoise.c_str());
	}
	static void					missCase() {
		cout << "\t������ ������ ���� ���!!!" << endl;
		pause();
	}
public:
	static void					setClient(const string & extpass = "") {
		auto Client = Manager::CreateClient(extpass);
		Manager::setClient(*Client);
		cout << "\t������ ������� ��������!" << endl;
		pause();
	}
	static void					popClient(const string& extpass = "") {
		string passport;
		if (extpass == "")
			passport = Manager::input("\t������� ������� � ������� << 1234-123456 >> : ", PassportValidator);
		else passport = extpass;
		auto Client = Manager::findClient(passport);
		if (!Client) {
			cout << "\t������ �� ������!!!" << endl;
			pause(); return;
		}
		if (Manager::isDebtorClient(*Client)) {
			cout << "\t������ �� ������ ��� �����! �� �� ������ ��� �������!" << endl;
			if (extpass == "") { pause(); return; }
		}
		else {
			Manager::popClient(*Client);
			cout << "\t������ ������� �����" << endl;
			if (extpass == "") pause();
		}
	}
	static void					printClients() {
		ofstream fout(TreePath);
		Manager::print(fout, Manager::FOR::CLIENTS);
		fout.close();
		string start = "start " + TreePath;
		system(start.c_str());
	}
	static void					clearClients() {
		while (Manager::size(Manager::FOR::CLIENTS))
			popClient(Manager::getTopClient()->passport);
		cout << "\t������ �������� ������!" << endl;
		pause(); return;
	}
	static void					createClients() {
		//cout << "������� �������� ����������: ";
		uint16_t size = inputUserChoise();
		for (uint16_t i = 0; i < size; ++i)
			Manager::setClient(*AutoEntitiesCreator::CreateClient());
		cout << "\t" << size << " �������� ������� ����������������!" << endl;
		pause();
	}
	static void					findClient() {
		string passport = Manager::input("\t������� ����� ��������: ", PassportValidator);
		auto Client = Manager::findClient(passport);
		if (!Client) {
			cout << "\t������ �� ������!!!" << endl;
			pause(); return;
		}
		Manager::print(cout, Client);
		pause(); return;
	}
	static void					findClients() {
		string SubString = Manager::input("\t������� ��������: ");
		toUpperString(SubString);
		auto Clients = Manager::findClients(SubString);
		if (!Clients.size()) {
			cout << "\t������� �� ������!!!" << endl;
			pause(); return;
		}
		Manager::print(cout, Clients);
		pause(); return;
	}
public:
	static void					setSIM(const string & extnum = "") {
		auto SIM = Manager::CreateSIM(extnum);
		Manager::setSIM(*SIM);
		cout << "\tSIM-����� ������� ���������!" << endl;
		pause();
	}
	static void					popSIM(const string extnum = "") {
		string number; 
		if (extnum == "")
			number = Manager::input("\t������� ����� SIM - ����� � ������� << 123-1234567 >> : ", SIMValidator);
		else number = extnum;
		auto SIM = Manager::findSIM(number);
		if (!SIM) {
			cout << "\tSIM-����� �� �������!!!" << endl;
			pause(); return;
		}
		if (!SIM->in_stock) {
			cout << "\t���-�� �� ������ SIM-����� � " << SIM->number << "! �� �� ������ � �������!!!" << endl;
			if (extnum == "") { pause(); return; }
		}
		else {
			Manager::popSIM(*SIM);
			cout << "\tSIM-����� ������� ������" << endl;
			if (extnum == "") {
				cout << "\tSIM-����� ������� ������" << endl; pause();
			}
		}
	}
	static void					printSIM() {
		ofstream fout(TablePath);
		Manager::print(fout, Manager::FOR::SIMS);
		fout.close();
		string start = "start " + TablePath;
		system(start.c_str());
	}
	static void					clearSIMS() {
		for (uint16_t index = 0; index < Manager::getSIMSVolume(); ++index) {
			Entity::SIM* sim = Manager::getSIM(index);
			if (!sim) continue;
			popSIM(eraseDash(sim->number));
		}
		cout << "\t������ SIM-���� ������!" << endl;
		pause(); return;
	}
	static void					createSIMS(){
		//cout << "������� �������� ����������: ";
		uint16_t size = inputUserChoise();
		for (uint16_t i = 0; i < size; ++i)
			Manager::setSIM(*AutoEntitiesCreator::CreateSIM());
		cout << "\t" << size << " SIM-���� ������� ����������������!" << endl;
		pause();
	}
	static void					findSIM() {
		string number = Manager::input("\t������� �����: ", SIMValidator);
		auto sim = Manager::findSIM(number);
		if (!sim) {
			cout << "\tSIM-����� �� �������!!!" << endl;
			pause(); return;
		}
		Manager::print(cout, sim);
		if (sim->in_stock) {
			cout << "\tSIM-����� �� ������ ������ �� ��������!" << endl;
			pause(); return;
		}
		else
			Manager::print(cout, Manager::findClient(Manager::findTrades_byNumber(number)[0]->passport));
		pause(); return;
	}
	static void					findSIMS() {
		string tariff = Manager::input("\t������� �������� ������: ");
		toUpperString(tariff);
		auto SIMS = Manager::findSIMS(tariff);
		if (!SIMS.size()) {
			cout << "\tSIM-����� �� �������!!!" << endl;
			pause(); return;
		}
		Manager::print(cout, SIMS);
		pause(); return;
	}	
public:
	static void					giveOutSIM(){
		string passport = Manager::input("\t������� ����� �������� �������: ", PassportValidator);
		if (!Manager::findClient(passport)) {
			cout << "\t�������, ������ ������� ���!" << endl;
			cout << "\t1) ���������������� �������" << endl;
			cout << "\t2) �������� �������� ������" << endl;
			while (!Manager::findClient(passport)) {
				switch (inputUserChoise()) {
				case 1: setClient(passport); break;
				case 2: return;
				default: missCase(); break;
				}
			}
		}
		while (true) {
			string number = Manager::input("\t������� ����� SIM-�����: ", SIMValidator);
			while (!Manager::findSIM(number)) {
				cout << "\tSIM-����� � ����� ������� �� �������!" << endl;
				cout << "\t1) ���������������� ��� SIM-�����" << endl;
				cout << "\t2) �������� ��������� ������" << endl;
				switch (inputUserChoise()) {
				case 1: setSIM(number); break;
				case 2: return;
				default: missCase(); break;
				}
			}
			if (!Manager::findSIM(number)->in_stock) {
				cout << "������ SIM-����� ��� � �������!!!" << endl;
				cout << "1) ������� ������ SIM-�����" << endl;
				cout << "2) �������� �������� ������" << endl;
				switch (inputUserChoise()) {
				case 1: break;
				case 2: return;
				default: missCase(); break;
				}
			}
			else {
				Manager::findSIM(number)->in_stock = false;
				Manager::COASC_incr();
				auto Trade = Manager::CreateTrade(Entity::trade::TRADE::SALE, passport, number);
				Manager::setTrade(*Trade);
				cout << "SIM-����� ������� ������!\n���� ���������!" << endl;
				pause(); return;
			}
		}
	}
	static void					giveRefundSIM() {
		string number = Manager::input("\t������� ����� SIM-�����: ", SIMValidator);
		auto Trades = Manager::findTrades_byNumber(number);
		auto Trade = FindUnique(Trades);
		if (!Trade) {
			cout << "\t�������, ������ �� �������!!!" << endl;
			pause(); return;
		}
		else {
			Manager::findSIM(number)->in_stock = true;
			auto RefundTrade = Trade;
			RefundTrade->Trade = Entity::trade::TRADE::REFUND;
			Manager::setTrade(*RefundTrade);
		}
		
	}
	static void					printTrades() {
		ofstream fout(ListPath);
		Manager::print(fout, Manager::FOR::TRADES);
		fout.close();
		string start = "start " + ListPath;
		system(start.c_str());
	}
};

string Menu::TreePath = "printTree.txt";
string Menu::TablePath = "printTable.txt";
string Menu::ListPath = "printList.txt";