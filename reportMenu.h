#pragma once

#ifndef REPORTMENU_H
#define REPORTMENU_H

/*
This file includes functions related to the reportMenu here users can enter commands to pull reports on Members, 
Observers, and Labs that include their key details.
*/

#include <iostream>
#include <array>
#include "Lab.h"
#include "Observer.h"
#include "Member.h"
#include "defines.h"
#include "processingFunctions.h"

/*
This function displays the Pull Reports Menu and accepts and verifies commands from the user. Valid commands call
helper functions or return to the main menu.
Preconditions:  memberList, observerList, and labList are initialized with data.
Postconditions: The command input by the user is processed.

TO DO: Add input verification and error handling.
*/
void reportMenu(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList,
    array<Lab*, LAB_ARR_SIZE>& labList);

/*
This helper function takes a user input Member ID and uses it to print the Member's Report to the console.
Preconditions:  The input Member exists in memberList or observerList.
Postconditions: Every Member's report is printed to the console.

TO DO: Add input verification and error handling.
*/
void pullMemberReport(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList);

/*
This helper function takes a user input Lab ID and uses it to print the Lab's Report to the console.
Preconditions:  The input Lab exists in labList.
Postconditions: Every Lab's report is printed to the console.

TO DO: Add input verification and error handling.
*/
void pullLabReport(array<Lab*, LAB_ARR_SIZE>& labList);

/*
This helper function prints out ever Member report from memberList and observerList.
Preconditions:  memberList and observerList have been initialized with Members
Postconditions: the Reports of all Members in memberList and observerList are printed to the console.
*/
void pullAllMembersReport(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList);

/*
This helper function prints out ever Lab report from labList.
Preconditions:  labList has been initialized with Labs
Postconditions: the Reports of all Labs in labList are printed to the console.
*/
void pullAllLabsReport(array<Lab*, LAB_ARR_SIZE>& labList);

#endif