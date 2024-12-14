#pragma once

#ifndef DEFINES_H
#define DEFINES_H

/*
This file contains macros and global variables used and shared by other files in the program.
*/

// Sets the max size of the adminList std::array
#define ADMIN_ARR_SIZE 10

// Sets the max size of the memberList std::array
#define MEMBER_ARR_SIZE 100

// Sets the max size of the observerList and labList std::arrays
#define LAB_ARR_SIZE 20

// Sets the file used to pull Administrator data needed to generate Administrator Objects
#define ADMIN_FILE "administratordata.dat"

// Sets the file used to pull Member data needed to generate Member Objects
#define MEMBER_FILE "memberdata.dat"

// Sets the file used to pull Observer data needed to generate Observer Objects
#define OBSERVER_FILE "observerdata.dat"

// Sets the file used to pull Lab data needed to generate Lab Objects
#define LAB_FILE "labdata.dat"

// Sets the file used to pull list link data needed to link Members, Observers, and Labs
#define LIST_LINK_FILE "listlinkdata.dat"

extern int memberListSize;		// Tracks the size of the memberList std::array
extern int observerListSize;	// Tracks the size of the observerList std::array
extern int labListSize;			// Tracks the size of the labList std::array

#endif