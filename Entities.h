#pragma once
#include <string>
using std::string;
namespace Entity {
	class client {
	public:
		string		passport;	// ����� � ����� ��������. ������ NNNN-NNNNNN
		string		given;		// ����� � ���� ������
		string		name;		// ���
		uint16_t	year;		// ��� �������� (16-������ ����������� ���)
		string		address;	// �����
	};

	class SIM {
	public:
		string		number;		// ���� SIM-�����. ������ NNN-NNNNNNN
		string		tariff;		// �����
		uint16_t	year;		// ��� ������ (16-������ ����������� ���)
		bool		in_stock;	// ���� �� �������� � �������
	};

	class trade {
	public:
		enum class TRADE : bool {SALE, REFUND};
		TRADE		Trade;
		string		passport;	// ����� � ����� ��������. ������ NNNN-NNNNNN
		string		number;		// ���� SIM-�����. ������ NNN-NNNNNNN
		string		dateON;		// ���� ������
		string		dateOFF;	// ���� ��������� ��������

	};
}