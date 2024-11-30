#include "Account.h"

Account::Account() {
	this->setID(0);
	this->setName("NO NAME");
	this->setEmail("NO EMAIL");
	this->setAddress("NO ADDRESS");
	this->setPhoneNum(0);
}

Account::Account(int accountID, string name, string email, string address, int phoneNum) {
	this->setID(accountID);
	this->setName(name);
	this->setEmail(email);
	this->setAddress(address);
	this->setPhoneNum(phoneNum);
}

int Account::getID() const {
	return this->accountID;
}

void Account::setID(int accountID) {
	this->accountID = accountID;
}

string Account::getName() const {
	return this->name;
}

void Account::setName(string name) {
	this->name = name;
}

string Account::getEmail() const {
	return this->email;
}

void Account::setEmail(string email) {
	this->email = email;
}

string Account::getAddress() const {
	return this->address;
}

void Account::setAddress(string address) {
	this->address = address;
}

int Account::getPhoneNum() const {
	return this->phoneNum;
}

void Account::setPhoneNum(int phoneNum) {
	this->phoneNum = phoneNum;
}

