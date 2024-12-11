#pragma once

/*
TODO!!!

- Adjust formatting of output as necessary.
*/

#ifndef OBSERVER_H
#define OBSERVER_H

#include <iostream>
#include <string>
#include "Member.h"
using namespace std;

class Observer : public Member {

	/* 
	This class represents a Observer of the Old Pueblo Lapidary Club. It stores the Observer's contact information, a 
	list  of the Labs they are registered in, the amout of lab hours they have available, and the Lab that they're
	assigned to observe.
	*/

public:
/* CONSTRUCTORS + DESTRUCTORS*/
	Observer();

	Observer(const int& accountID, const string& name, const string& email, const string& address, const int& phoneNum, 
		const double& labHours);

	Observer(const Observer& observer);

	~Observer();

/* GETTERS + SETTERS */
	
	// Returns the assignedLab data member
	Lab* getAssignedLab() const;

	// Sets the assignedLab data member
	void setAssignedLab(Lab* lab);

/* OTHER METHODS */

	/*
	This method returns some data members of the Observer as a string. It is intended to be used whenever the 
	Observer's details need to be printed to a file or to the console/UI.
	Preconditions:	None
	Postconditions:	A string containing all of the data members of the Observer is returned.
	*/
	string toString() const;

	/*
	This method prints the Observer's formatted information, including their personal details, labList, and assigned 
	lab, to the console/UI.
	Preconditions:	None
	Postconditions:	The Observer's report is printed to the console/UI.
	*/
	void pullReport() const;

	Observer& operator=(const Observer& otherObserver);

private:
	Lab* assignedLab;
};

#endif