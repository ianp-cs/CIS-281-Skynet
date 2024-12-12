#pragma once

/*
TODO!!!

- Add error detection and error handling to this class' methods! But we don't need this for the prototype.
- Adjust formatting of output as necessary.
*/

#ifndef LAB_H
#define LAB_H

#include <iostream>
#include <string>
using namespace std;

class Member;
class Observer;
#define MAX_MEMBERS 10

class Lab {

	/* 
	This class represents a Lab run by the Old Pueblo Lapidary Club that is attended by Members and overseen by an
	Observer. It stores data about the Lab including the type of Lab, the total hours spent at the Lab by members, the
	Observer assigned to the Lab, and the list of Members scheduled to attend the Lab.
	*/

public:
/* CONSTRUCTORS + DESTRUCTORS*/

	// Default Constructor
	Lab();

	// Constructor with parameters
	Lab(const int& labID, const string& type, const double& totalHours, Observer* observer);

	// Copy Constructor
	Lab(const Lab& lab);

	// Destructor
	~Lab();

/* GETTERS + SETTERS */
	
	// Returns the labID data member
	int getID() const;

	// Sets the labID data member
	void setID(const int& id);

	// Returns the type data member
	string getType() const;

	// Sets the type data member
	void setType(const string& type);

	// Returns the totalHours data member
	double getTotalHours() const;

	// Returns the Observer data member
	Observer* getObserver() const;

	// Sets the Observer data member
	void setObserver(Observer* observer);

	// Returns the memberList data member
	Member* getMemberList() const;

/* OTHER METHODS */

	/*
	This method adds hours to the Lab's totalHours data member.
	Precondition:	The hours parameter should be a positive value.
	Postcondition:	The Lab's totalHours has the hours parameter added to it.
	*/
	void addHours(const double& hours);

	/*
	This method subtracts hours from the Lab's totalHours data member.
	Precondition:	The hours parameter should be a positive value.
	Postcondition:	The Lab's totalHours has the hours parameter subtracted from it.
	*/
	void refundHours(const double& hours);

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
	void addMember(Member* member);

	/*
	This method removes a Member from the Lab's memberList, if they are in the memberList.
	Preconditions:	The Member is in this Lab's memberList.
	Postconditions:	The Member is no longer in the Lab's memberList.
	*/
	void removeMember(Member* member);

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

/* OVERLOADED OPERATORS */

	bool operator==(const Lab& otherLab) const;

	Lab& operator=(const Lab& otherLab);

private:
/* DATA MEMBERS */

	int labID;							// Unique identifier for the Lab
	string type;						// The type/name of the Lab (ex. Lapidary)
	double totalHours;					// The quantity of hours "spent" at the lab by all Members
	Observer* observer;					// The Observer assigned to the Lab
	Member* memberList[MAX_MEMBERS];	// The list of all Members scheduled to attend this Lab
	int listSize{ 0 };					// The size of memberList

/* OTHER METHODS*/

	/*
	This helper function is called to shift left all elements to the right of pos in the memberList array.
	Preconditions:	none
	Postconditions:	all elements to the right of pos in memberList are shifted left
	*/
	void shiftListElements(const int& pos);
};

#endif