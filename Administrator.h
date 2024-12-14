#pragma once

#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <iostream>
using namespace std;

class Administrator {

	/* This class contains the details for an administrator account and is used to login into the program. */

public:
	Administrator() = delete;

	Administrator(int adminID, string name, string userName, string password, string email);

	string getName() const;

	/*
	This method is called to allow access into the program. The user must input the name and password for the admin
	account to gain access. The name and password are case sensitive.
	Preconditions:	None
	Postconditions:	If name and password match the account's, the user is able to access the program. Otherwise, it is
					denied.
	*/
	bool login(string userName, string password) const;

private:
	/* Data Members */
	int adminID;
	string name;
	string userName;
	string password;
	string email;
};

#endif