#pragma once

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
using namespace std;

class Account {

	/* 
	This class represents a member of the Old Pueblo Lapidary Club. It contains contact information for the member and 
	their unique ID.
	*/

public:
/* CONSTRUCTORS + DESTRUCTORS*/

	// Default Constructor
	Account();

	// Constructor with parameters
	Account(const int& accountID, const string& name, const string& email, const string& address, const string& phoneNum);

	// Copy Constructor
	Account(const Account& account);

/* GETTERS + SETTERS */

	// Returns the accountID data member
	int getID() const;

	// Sets the accountID data member
	void setID(const int& accountID);

	// Returns the name data member
	string getName() const;

	// Sets the name data member
	void setName(const string& name);

	// Returns the email data member
	string getEmail() const;

	// Sets the email data member
	void setEmail(const string& email);

	// Returns the address data member
	string getAddress() const;
	
	// Sets the address data member
	void setAddress(const string& address);

	// Returns the phoneNum data member
	string getPhoneNum() const;

	// Sets the phoneNum data member
	void setPhoneNum(const string& phoneNum);

/* OTHER METHODS */

	/*
	This method returns the data members of the Account as a string. It is intended to be used whenever the Account's
	details need to be printed to a file or to the console/UI.
	Preconditions:	None
	Postconditions:	A string containing all of the data members of the account is returned.
	*/
	virtual void print() const = 0;

private:
/* DATA MEMBERS */

	int accountID;	// Unique identifier for account
	string name;	// Name of club member
	string email;	// Email for club member
	string address;	// Physical address of club member
	string phoneNum;	// Contact phone number for club member

};

#endif