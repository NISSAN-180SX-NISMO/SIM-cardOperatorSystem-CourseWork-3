#pragma once
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <regex>
#include "Exceptions.h"
#include "UsefullFunctions.h"


bool TreeKeyValidator(string passport) {
	if (passport.size() != 10) throw UncorrectPassport(passport);
	if (regex_match(passport.c_str(), std::regex("[0-9]{10}"))) return true;
	else throw UncorrectPassport(passport);
}

bool PassportValidator(string passport) {
	if (passport.size() != 11) throw UncorrectPassport(passport);
	if (regex_match(passport.c_str(), std::regex("[0-9]{4}-[0-9]{6}"))) return true;
	else throw UncorrectPassport(passport);
}

bool YearValidator(string year) {
	if (year.size() != 4) throw UncorrectDate(year);
	if (regex_match(year.c_str(), std::regex("[0-9]{4}"))) return true;
	else throw UncorrectDate(year);
}

bool DateValidator(string date) {
	if (date.size() != 10) throw UncorrectPassport(date);
	if (regex_match(date.c_str(), std::regex("([0-9]{2}(\/)[0-9]{2}(\/)[0-9]{4})"))) return true;
	else throw UncorrectDate(date);
}

bool DateIsReal(string date) {
	enum  MONTHS { JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER };
	constexpr auto DAY = 0; constexpr auto MONTH = 1; constexpr auto YEAR = 2;
	int DAYS[]{ -1,31,29,31,30,31,30,31,31,30,31,30,31 };
	vector<int> DATE = DateToVector(date);
	if (DATE[MONTH] < 1 || DATE[MONTH] > 12) return false;
	if (DATE[DAY] < 1 || DATE[DAY] > DAYS[DATE[MONTH]]) return false;
	if (DATE[YEAR] < 1900 || DATE[YEAR] > 2023) return false;
	if (DATE[DAY] == 29 && DATE[MONTH] == int(MONTHS::FEBRUARY))
		if (!(DATE[YEAR] % 4 == 0 && ((DATE[YEAR] % 400 == 0 && DATE[YEAR] % 100 == 0) || (DATE[YEAR] % 100 != 0)))) return false;
	return true;
}

bool TableKeyValidator(string SIM) {
	if (SIM.size() != 10) throw UncorrectSIM(SIM);
	if (regex_match(SIM.c_str(), std::regex("[0-9]{10}"))) return true;
	else throw UncorrectSIM(SIM);
}

bool SIMValidator(string SIM) {
	if (SIM.size() != 11) throw UncorrectSIM(SIM);
	if (regex_match(SIM.c_str(), std::regex("[0-9]{3}-[0-9]{7}"))) return true;
	else throw UncorrectSIM(SIM);
}
