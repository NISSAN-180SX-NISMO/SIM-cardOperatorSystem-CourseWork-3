#pragma once
#include <string>
using std::string;
namespace Entity {
	class client {
	public:
		string		passport;	// Серия и номер паспорта. Формат NNNN-NNNNNN
		string		given;		// Место и дата выдачи
		string		name;		// ФИО
		uint16_t	year;		// Год рождения (16-битный беззнаковый инт)
		string		address;	// Адрес
	};

	class SIM {
	public:
		string		number;		// Номе SIM-карты. Формат NNN-NNNNNNN
		string		tariff;		// Тариф
		uint16_t	year;		// Год выдачи (16-битный беззнаковый инт)
		bool		in_stock;	// Есть ли симкарта в наличии
	};

	class trade {
	public:
		enum class TRADE : bool {SALE, REFUND};
		TRADE		Trade;
		string		passport;	// Серия и номер паспорта. Формат NNNN-NNNNNN
		string		number;		// Номе SIM-карты. Формат NNN-NNNNNNN
		string		dateON;		// Дата выдачи
		string		dateOFF;	// Дата окончания действия

	};
}