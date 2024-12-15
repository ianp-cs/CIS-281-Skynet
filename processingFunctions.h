#pragma once

#ifndef PROCESSINGFUNCTIONS_H
#define PROCESSINGFUNCTIONS_H

/*
This file includes miscellaneous functions that aid other files and functions in the program in processing user
commands.
*/

#include <array>
#include "Lab.h"
#include "Observer.h"
#include "Member.h"
#include "defines.h"

/*
This function clears the input buffer of the stream parameter.
Preconditions:  None
Postconditions: The buffer is cleared of any remaining characters.
*/
void clearBuffer(FILE* fp);

/*
This function deallocates the memory of the memberList element at pos and shift every element to the right of it back
to the left, if there are any.
Preconditions:  memberList has been intialized with data and pos is within the bounds of memberList.
Postconditions: The memberList element at pos is set to a nullptr or has been overwritten with the element to its
                right. Every element to the right of pos, if any, are shifted to the left. The memory allocated for
                the element is deallocated.
*/
void shiftMemberListElements(array<Member*, MEMBER_ARR_SIZE>& memberList, const int& pos);

/*
This function deallocates the memory of the observerList element at pos and shift every element to the right of it back
to the left, if there are any.
Preconditions:  observerList has been intialized with data and pos is within the bounds of observerList.
Postconditions: The observerList element at pos is set to a nullptr or has been overwritten with the element to its
                right. Every element to the right of pos, if any, are shifted to the left. The memory allocated for
                the element is deallocated.
*/
void shiftObserverListElements(array<Observer*, LAB_ARR_SIZE>& observerList, const int& pos);

/*
This function deallocates the memory of the labList element at pos and shift every element to the right of it back to
the left, if there are any.
Preconditions:  labList has been intialized with data and pos is within the bounds of labList.
Postconditions: The labList element at pos is set to a nullptr or has been overwritten with the element to its right.
                Every element to the right of pos, if any, are shifted to the left. The memory allocated for
                the element is deallocated.
*/
void shiftLabListElements(array<Lab*, LAB_ARR_SIZE>& labList, const int& pos);

/*
This function takes the member and lab parameter and adds them to each others' respective lists.
Preconditions:  None
Postconditions: member has been added to lab's memberList and lab has been added to member's labsList.
*/
void attachMemberToLab(Member* member, Lab* lab);

/*
This function takes the member and lab parameter and removes them to each others' respective lists. Verification that
they are in each others' lists is performed before this function is called.
Preconditions:  member is in lab's memberList and lab is in member's labsList.
Postconditions: member has been removed lab's memberList and lab has been removed from member's labsList.
*/
void detachMemberFromLab(Member* member, Lab* lab);

/*
This function takes the member parameter and removes it from all of the Labs in its labList.
Preconditions:  None
Postconditions: Every Lab in member's labsList do not have member in their memberLists.
*/
void detachMember(Member* member);

/*
This function sets observer to be lab's Observer and lab to be observer's assignedLab.
Preconditions:  None
Postconditions: observer is lab's Observer and lab is observer's assignedLab.
*/
void attachObserverToLab(Observer* observer, Lab* lab);

/*
This function checks if memberID is already an ID for an existing Member or Observer.
Preconditions:  None
Postconditions: It the ID is already taken, false is returned; otherwise, true is returned.
*/
bool checkIDAvailability(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList,
    const int& memberID);

/*
This function checks if labID is already an ID for an existing Lab.
Preconditions:  None
Postconditions: It the ID is already taken, false is returned; otherwise, true is returned.
*/
bool checkIDAvailability(array<Lab*, LAB_ARR_SIZE>& labList, const int& labID);

#endif