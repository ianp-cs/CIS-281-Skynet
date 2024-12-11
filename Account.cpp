#include "Account.h"

Account::Account() {
	this->setID(0);
	this->setName("NO NAME");
	this->setEmail("NO EMAIL");
	this->setAddress("NO ADDRESS");
	this->setPhoneNum(0);
}

Account::Account(const int& accountID, const string& name, const string& email, const string& address, 
	const int& phoneNum) {

	this->setID(accountID);
	this->setName(name);
	this->setEmail(email);
	this->setAddress(address);
	this->setPhoneNum(phoneNum);
}

Account::Account(const Account& account) {
	this->setID(account.getID());
	this->setName(account.getName());
	this->setEmail(account.getEmail());
	this->setAddress(account.getAddress());
	this->setPhoneNum(account.getPhoneNum());
}

int Account::getID() const {
	return this->accountID;
}

void Account::setID(const int& accountID) {
	this->accountID = accountID;
}

string Account::getName() const {
	return this->name;
}

void Account::setName(const string& name) {
	this->name = name;
}

string Account::getEmail() const {
	return this->email;
}

void Account::setEmail(const string& email) {
	this->email = email;
}

string Account::getAddress() const {
	return this->address;
}

void Account::setAddress(const string& address) {
	this->address = address;
}

int Account::getPhoneNum() const {
	return this->phoneNum;
}

void Account::setPhoneNum(const int& phoneNum) {
	this->phoneNum = phoneNum;
}

