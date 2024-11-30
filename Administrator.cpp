#include "Administrator.h"

Administrator::Administrator(int adminID, string name, string password, string email) {
	this->adminID = adminID;
	this->name = name;
	this->password = password;
	this->email = email;
}

bool Administrator::login(string name, string password) {
	return this->name == name && this->password == password;
}