#include <Windows.h>
#include "Menu.h"

void ClientsMenu() {
	cout << "\t1) Регистрация нового клиента" << endl;
	cout << "\t2) Снятие клиента с обслуживания" << endl;
	cout << "\t3) Просмотр всех клиентов" << endl;
	cout << "\t4) Очистка данных о клиентах" << endl;
	cout << "\t5) Сгенерировать несколько клиентов" << endl;
	cout << "\t6) Поиск клиента по номеру пасспорта" << endl;
	cout << "\t7) Поиск клиента по фрагментам ФИО/адреса" << endl;
	cout << "\t0) Назад" << endl;
	switch (Menu::inputUserChoise()) {
	case 0: return;
	case 1: Menu::setClient(); break;
	case 2: Menu::popClient(); break;
	case 3: Menu::printClients(); break;
	case 4: Menu::clearClients(); break;
	case 5: Menu::createClients(); break;
	case 6: Menu::findClient(); break;
	case 7: Menu::findClients(); break;
	default: Menu::missCase(); break;
	}
}

void SIMMenu(){
	cout << "\t1) Регистрация новой SIM-карты" << endl;
	cout << "\t2) Удаление SIM-карты" << endl;
	cout << "\t3) Просмотр всех SIM-карт" << endl;
	cout << "\t4) Очистка данных о SIM-картах" << endl;
	cout << "\t5) Сгенерировать несколько SIM-карт" << endl;
	cout << "\t6) Поиск SIM-карты по номеру" << endl;
	cout << "\t7) Поиск SIM-карт по тарифу" << endl;
	cout << "\t0) Назад" << endl;
	switch (Menu::inputUserChoise()) {
	case 0: return;
	case 1: Menu::setSIM(); break;
	case 2: Menu::popSIM(); break;
	case 3: Menu::printSIM(); break;
	case 4: Menu::clearSIMS(); break;
	case 5: Menu::createSIMS(); break;
	case 6: Menu::findSIM(); break;
	case 7: Menu::findSIMS(); break;
	default: Menu::missCase(); break;
	}
}

int main() {
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "");

	while (true) {
		cls();
		cout << " 1) Действия с клиентами" << endl;
		cout << " 2) Действия с SIM-картами" << endl;
		cout << " 3) Выдать SIM-карту" << endl;
		cout << " 4) Вернуть SIM-карту" << endl;
		cout << " 5) Показать логи" << endl;
		cout << " 0) Выход" << endl;
		switch (Menu::inputUserChoise()) {
		case 0: return 0;
		case 1: ClientsMenu(); break;
		case 2: SIMMenu(); break;
		case 3: Menu::giveOutSIM(); break;
		case 4: Menu::giveRefundSIM(); break;
		case 5: Menu::printTrades(); break;
		default: Menu::missCase(); break;
		}
	}
}