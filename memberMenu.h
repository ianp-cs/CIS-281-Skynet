#pragma once

#ifndef MEMBERMENU_H
#define MEMBERMENU_H

/*
This file includes functions related to the memberMenu where users can enter commands to enact various processes on
Member and Observer data, including adding/removing/editing Members, promoting Members to Observers (or demote them f
rom Observer), and add/charge/refund Member's available Lab hours.
*/

#include <iostream>
#include <array>
#include "Lab.h"
#include "Observer.h"
#include "Member.h"
#include "defines.h"
#include "processingFunctions.h"

/*
This function displays the Member Menu and accepts and verifies commands from the user. Valid commands call helper
functions or return to the main menu.
Preconditions:  memberList and observerList are initialized with data.
Postconditions: The command input by the user is processed.

TO DO: Add input verification and error handling.
*/
void memberMenu(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList);

/*
This helper function prints out every Member in the Member and Observer lists.
Preconditions:  memberList and observerList have been initialized with Members
Postconditions: All Members in memberList and observerList are printed to the console.
*/
void printMembersList(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList);

/*
This helper function takes user input to create a new Member and adds it to memberList.
Preconditions:  The user input Member is not already in memberList.
Postconditions: If the user input data passes validation and the Member does not already exist, the Member is created
                and added to memberList. Otherwise, a relevant error message is printed to the console and control is
                returned to the memberMenu.

TO DO: Add input verification and error handling.
*/
void addMember(array<Member*, MEMBER_ARR_SIZE>& memberList);

/*
This helper function edits an existing member in memberList using data input by the user.
Preconditions:  The Member to be edited already exists and is in memberList.
Postconditions: The Member is updated with new data input by the user, if the input passes validation. Otherwise, a
                relevant error message is printed to the console and control is returned to memberMenu.

TO DO: Add input verification and error handling.
*/
void editMember(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList);

/*
This helper function removes an existing member from memberList.
Preconditions:  The Member to be removed exists and is in memberList.
Postconditions: The Member is removed from memberList and memberList's elements are shifted to the left to replace
                Member. If the Member does not exist, an error message is printed to the console.

TO DO: Add input verification and error handling.
*/
void removeMember(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList);

/*
This helper function turns the input Member into an Observer, if the input is a Member, otherwise the input is an
Observer and they are converted into a Member. The Member/Observer is removed from their original list and added to
the respective list.
Preconditions:  The Member/Observer exists in their respective list.
Postconditions: If the input is a Member, the Member is removed from memberList and a new Observer is created using the
                Member's data and added to observerList. Otherwise, the input is an Observer, and they are removed from
                observerList and a new Member is created using the Observer's data and added to memberList.

TO DO: Add input verification and error handling.
*/
void toggleObserverStatus(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList);

/*
This helper function adds lab hours to a Member selected by the user. The number of lab hours added is specified by the
user.
Preconditions:  The Member exists in memberList or observerList. The input lab hours must be a postive value.
Postconditions: The input lab hours is added to the selected Member's total available lab hours. If the input lab hours
                are negative or the selected Member doesn't exist, a relevant error message is printed to the console.

TO DO: Add input verification and error handling.
*/
void addMemberLabHours(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList);

/*
This helper function takes a user input Member, Lab, and number of hours. The hours are subtracted from the Member's
lab hours balance and added to the Lab's total hours amount.
Preconditions:  The Member exists in memberList or observerList. The Lab exists and is in the Member's labList. The
                input lab hours must be a postive value.
Postconditions: The input lab hours are subtracted from the selected Member's total available lab hours and are added
                to the selected Lab's total hours. If the input lab hours are negative, or the selected Member or Lab
                don't exist, a relevant error message is printed to the console.

TO DO: Add input verification and error handling.
*/
void spendMemberLabHours(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList);

/*
This helper function takes a user input Member, Lab, and number of hours. The hours are added to the Member's lab hours
balance and subtracted from the Lab's total hours amount.
Preconditions:  The Member exists in memberList or observerList. The Lab exists and is in the Member's labList. The
                input lab hours must be a postive value.
Postconditions: The input lab hours are added to the selected Member's total available lab hours and are subtracted
                from the selected Lab's total hours. If the input lab hours are negative, or the selected Member or Lab
                don't exist, a relevant error message is printed to the console.

TO DO: Add input verification and error handling.
*/
void refundMemberLabHours(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList);

#endif
