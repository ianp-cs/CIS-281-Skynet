#pragma once

#ifndef LABMENU_H
#define LABMENU_H

/*
This file includes functions related to the labMenu here users can enter commands to enact various processes on Lab 
data, including adding/removing/editing Labs and assigning/unassigning Members and Observers to/from Labs.
*/

#include <iostream>
#include <array>
#include "Lab.h"
#include "Observer.h"
#include "Member.h"
#include "defines.h"
#include "processingFunctions.h"

/*
This function displays the Lab Menu and accepts and verifies commands from the user. Valid commands call helper
functions or return to the main menu.
Preconditions:  memberList, observerList, and labList are initialized with data.
Postconditions: The command input by the user is processed.
*/
void labMenu(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList,
    array<Lab*, LAB_ARR_SIZE>& labList);

/*
This helper function prints out every Lab in labList.
Preconditions:  labList has been initialized with Labs
Postconditions: All Labs in labList are printed to the console.
*/
void printLabList(array<Lab*, LAB_ARR_SIZE>& labList);

/*
This helper function takes user input to create a new Lab and adds it to labList.
Preconditions:  The user input Lab is not already in labList.
Postconditions: If the user input data passes validation and the Lab does not already exist, the Lab is created and
                added to labList. Otherwise, a relevant error message is printed to the console and control is returned
                to the labMenu.
*/
void addLab(array<Lab*, LAB_ARR_SIZE>& labList);

/*
This helper function edits an existing member in labList using data input by the user.
Preconditions:  The Lab to be edited already exists and is in labList.
Postconditions: The Lab is updated with new data input by the user, if the input passes validation. Otherwise, a
                relevant error message is printed to the console and control is returned to labMenu.
*/
void editLab(array<Lab*, LAB_ARR_SIZE>& labList);

/*
This helper function removes an existing member from memberList.
Preconditions:  The Member to be removed exists and is in memberList.
Postconditions: The Member is removed from memberList and memberList's elements are shifted to the left to replace
                Member. If the Member does not exist, an error message is printed to the console.
*/
void removeLab(array<Lab*, LAB_ARR_SIZE>& labList);

/*
This helper function assigns the user input Observer to the user input Lab.
Preconditions:  The Observer and Lab exist and are in their respective lists.
Postconditions: The user input Observer has Lab as its assignedLab and Lab has Observer as its Observer. If the
                Observer already had an assignedLab, it is removed as that Lab's Observer. If the Lab already had an
                Observer, the Observer has Lab removed as its assignedLab.
*/
void assignObserverToLab(array<Observer*, LAB_ARR_SIZE>& observerList, array<Lab*, LAB_ARR_SIZE>& labList);

/*
This helper function removes the association between an Observer and their assignedLab, and vice-versa.
Preconditions:  The Observer exists and it has an assignedLab. The assignedLab has Observer as its Observer.
Postconditions: The user input Observer has no assignedLab and its prior assignedLab does not have Observer as its
                Observer.
*/
void unassignObserver(array<Observer*, LAB_ARR_SIZE>& observerList);

/*
This helper function assigns a user input Member to a user input Lab, linking the two together via their labsList and memberList.
Preconditions:  The user input Member and Lab both exist, and the Member is not in Lab's memberList and the Lab is not
                   in the Member's labList.
Postconditions: The user input Member is in the user input Lab's memberList and the Lab is in the Member's labsList.
*/
void assignMemberToLab(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList,
    array<Lab*, LAB_ARR_SIZE>& labList);

/*
This helper function unassigns a user input Member from a user input Lab, removing them from the others' labsList and
memberList, respectively.
Preconditions:  The user input Member and Lab both exist, and the Member is in Lab's memberList and the Lab is in the
                Member's labList.
Postconditions: The user input Member is in no longer in the user input Lab's memberList and the Lab is no longer in
                the Member's labsList.
*/
void unassignMemberFromLab(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList,
    array<Lab*, LAB_ARR_SIZE>& labList);

#endif