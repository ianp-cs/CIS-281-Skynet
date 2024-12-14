#pragma once

/*
TODO!!!

- Add error detection and error handling to this class' methods! But we don't need this for the prototype.
- Adjust formatting of output as necessary.
*/

#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <iomanip>
#include <string>
#include "Account.h"
using namespace std;

class Lab;
#define MAX_LABS 10

class Member : public Account {

	/* 
	This class represents a Member of the Old Pueblo Lapidary Club. It stores the Member's contact information, a list 
	of the Labs they are registered in, and the amout of lab hours they have available.
	*/

public:
/* CONSTRUCTORS + DESTRUCTORS*/

	// Default Constructor
	Member();

	// Constructor with parameters
	Member(const int& accountID, const string& name, const string& email, const string& address, 
		const string& phoneNum, const double& labHours);

	// Copy Constructor
	Member(const Member& member);

/* GETTERS + SETTERS */

	// Returns the labList data member
	Lab** getLabsList();

	// Returns the listSize data member
	int getLabsListSize() const;

	// Returns the labHours data member
	double getLabHours() const;

	// Sets the labHours data member
	void setLabHours(const double& labHours);

/* OTHER METHODS */

	/*
	This method adds the Lab parameter to this Member's labList, if it isn't already in the labList.
	Preconditions:	The Lab is not already in this Member's labList.
	Postconditions:	The Member's labList contains the added Lab.
	*/
	void addLab(Lab* lab);

	/*
	This method removes the input Lab paramter from the Member's lablist if it is in the labList.
	Precondition:	The Lab is in the Member's labList.
	Postcondition:	The Lab is no longer in the Member's labList.
	*/
	void removeLab(Lab* lab);

	/*
	This method returns true if the lab parameter is in this Member's labList.
	Precondition:	none
	Postcondition:	Returns true if the lab parameter is in this Member's labList.
	*/
	bool hasLab(Lab* lab);

	/*
	This method reduces the input amount of hours from this Member's labHours, so long as it doesn't bring their 
	remaining hours below 0.
	Precondition:	The input hours will not bring the Member's total labHours below 0. The hours parameter should be a
					positive value.
	Postcondition:	The Member's labHours has had hours subtracted from it.
	*/
	void spendLabHours(const double& hours);

	/*
	This method adds the input amount of hours to this Member's labHours.
	Precondition:	The hours parameter should be a positive value.
	Postcondition:	The Member's labHours has had hours added to it.
	*/
	void refundLabHours(const double& hours);

	/*
	This method returns some data members of the Member as a string. It is intended to be used whenever the Member's 
	details need to be printed to a file or to the console/UI.
	Preconditions:	None
	Postconditions:	A string containing all of the data members of the Member is returned.
	*/
	void print() const;

	/*
	This method prints the Member's formatted information, including their personal details and labList, to the
	console/UI.
	Preconditions:	None
	Postconditions:	The Member's report is printed to the console/UI.
	*/
	void pullReport() const;

/* OVERLOADED OPERATORS */

	bool operator==(const Member& otherMember) const;

	Member& operator=(const Member& otherMember);

protected:
/* DATA MEMBERS */

	double labHours;						// Available hours the Member has to "spend" on labs
	Lab* labsList[MAX_LABS]{ nullptr };		// The list of all Labs the Member is scheduled to attend
	int listSize{ 0 };						// The size of labsList

private:
/* OTHER METHODS */

	/*
	This helper function is called to shift left all elements to the right of pos in the labsList array.
	Preconditions:	none
	Postconditions:	all elements to the right of pos in labsList are shifted left
	*/
	void shiftListElements(const int& pos);
};

#endif