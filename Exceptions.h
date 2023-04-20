#pragma once
#include <stdexcept>
using std::exception;
#include <string>
using std::string;


class TableExceptions : public exception {
public:
	virtual const string& get_key() const noexcept = 0;
};


class Table_DuplicateKey : public TableExceptions {
private:
	string key;
public:
	Table_DuplicateKey(const string key) noexcept {
		this->key = key;
	}
	virtual const string& get_key() const noexcept override {
		return this->key;
	}
};



class TreeExceptions : public exception {
public:
	virtual const string& get_key() const noexcept = 0;
};


class Tree_DuplicateKey : public TreeExceptions {
private:
	string key;
public:
	Tree_DuplicateKey(const string key) noexcept {
		this->key = key;
	}
	virtual const string& get_key() const noexcept override {
		return this->key;
	}
};



class InputExceptions : public exception {
public:
	virtual const string& get_more() const noexcept = 0;
};

class UncorrectPassport : public InputExceptions {
private:
	string passport;
public:
	UncorrectPassport(const string passport) noexcept {
		this->passport = passport;
	}
	virtual const string& get_more() const noexcept override {
		return this->passport;
	}
};

class UncorrectDate : public InputExceptions {
private:
	string date;
public:
	UncorrectDate(const string date) noexcept {
		this->date = date;
	}
	virtual const string& get_more() const noexcept override {
		return this->date;
	}
};

class UncorrectSIM : public InputExceptions {
private:
	string SIM;
public:
	UncorrectSIM(const string SIM) noexcept {
		this->SIM = SIM;
	}
	virtual const string& get_more() const noexcept override {
		return this->SIM;
	}
};