#pragma once

/*
TODO!!!

- Add error detection and error handling to this class' methods! But we don't need this for the prototype.
- Adjust formatting of output as necessary.
*/

#ifndef LAB_H
#define LAB_H

#include <iostream>
#include <list>
#include <string>
#include "Member.h"
#include "Observer.h"
using namespace std;

class Lab {

	/*  */

public:
/* CONSTRUCTORS + DESTRUCTORS*/
	Lab();

	Lab(int labID, string type, double totalHours, Observer observer);

/* GETTERS + SETTERS */
	
	// Returns the labID data member
	int getID() const;

	// Sets the labID data member
	void setID(int id);

	// Returns the type data member
	string getType() const;

	// Sets the type data member
	void setType(string type);

	// Returns the totalHours data member
	double getTotalHours() const;

	// Returns the Observer data member
	Observer getObserver() const;

	// Sets the Observer data member
	void setObserver(Observer observer);

	// Returns the memberList data member
	list<Member> getMemberList() const;

/* OTHER METHODS */

	/*
	This method adds hours to the Lab's totalHours data member.
	Precondition:	The hours parameter should be a positive value.
	Postcondition:	The Lab's totalHours has the hours parameter added to it.
	*/
	void addHours(double hours);

	/*
	This method subtracts hours from the Lab's totalHours data member.
	Precondition:	The hours parameter should be a positive value.
	Postcondition:	The Lab's totalHours has the hours parameter subtracted from it.
	*/
	void refundHours(double hours);

	/*
	This method resets the Lab's totalHours to 0. This should only be called at the beginning of each month.
	Precondition:	It is the beginning of the month.
	Postcondition:	The Lab's totalHours is set to 0.
	*/
	void resetHours();

	/*
	This method adds a Member to the Lab's memberList, if they aren't already in the memberList.
	Preconditions:	The Member is not already in this Lab's memberList.
	Postconditions:	The Lab's memberList contains the added Member.
	*/
	void addMember(Member member);

	/*
	This method removes a Member from the Lab's memberList, if they are in the memberList.
	Preconditions:	The Member is in this Lab's memberList.
	Postconditions:	The Member is no longer in the Lab's memberList.
	*/
	void removeMember(Member member);

	/*
	This method returns some data members of the Lab as a string. It is intended to be used whenever the Lab's details 
	need to be printed to a file or to the console/UI.
	Preconditions:	None
	Postconditions:	A string containing all of the data members of the Lab is returned.
	*/
	string toString();

	/*
	This method prints the Lab's formatted information, including the ID, type, total hours, Observer, and memberList, to 
	the console/UI.
	Preconditions:	None
	Postconditions:	The Lab's report is printed to the console/UI.
	*/
	void pullReport();

private:
	int labID;
	string type;
	double totalHours;
	Observer observer;
	list<Member> memberList;
};

#endif