#include "Administrator.h"

Administrator::Administrator(int adminID, string name, string userName, string password, string email) {
	this->adminID = adminID;
	this->name = name;
	this->userName = userName;
	this->password = password;
	this->email = email;
}

string Administrator::getName() const {
	return this->name;
}

bool Administrator::login(string userName, string password) const {
	return this->userName == userName && this->password == password;
}