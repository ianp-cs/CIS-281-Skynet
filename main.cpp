/*
Program: Old Pueblo Lapidary Club Records Management
Created By: Ian Penrose, Marie Perez, Lyes Attalah
Date Created: 11/29/2024
Description: 

CHANGE HISTORY
---------------------------------------------
Programmer	Date		Description of Change
---------------------------------------------
Ian			11/29/2024	Created Administrator, Account, Member, Observer, and Lab classes
Marie       12/02/2024  Created main
Ian         12/06/2024  Added further functionality to memberMenu.
*/

#include <iostream>
#include <list>
#include "Account.h"
#include "Administrator.h"
#include "Lab.h"
#include "Observer.h"
#include "Member.h"
using namespace std;

// Startup
void userLogin();
void initializeLists(list<Member>& memberList, list<Observer>& observerList, list<Lab>& labList);
void memberMenu(list<Member>& memberList, list<Observer>& observerList);

// Main Menu Functions
void labMenu(list<Member>& memberList, list<Observer>& observerList, list<Lab>& labList);
void reportMenu(list<Member>& memberList, list<Observer>& observerList, list<Lab>& labList);

// Member Menu Functions
void printMembersList(list<Member>& memberList, list<Observer>& observerList);
void addMember(list<Member>& memberList);

// Lab Menu Functions


// Report Menu Functions
void pullMemberReport(list<Member>& memberList, list<Observer>& observerList);
void pullLabReport(list<Lab>& labList);
void pullAllMembersReport(list<Member>& memberList, list<Observer>& observerList);
void pullAllLabsReport(list<Lab>& labList);

// Processing Functions
void addMemberToLab(Member& member, Lab& lab);
void assignObserverToLab(Observer& observer, Lab& lab);

int main() {
    list<Member> memberList;
    list<Observer> observerList;
    list<Lab> labList;
    int userInput;
    bool validInput{ false };

    userLogin();
    initializeLists(memberList, observerList, labList);

    while (validInput == false) {
        cout << "Main Menu" << endl;
        cout << "----------------" << endl;
        cout << "1) Edit Member Data" << endl;
        cout << "2) Edit Lab Data" << endl;
        cout << "3) Pull Reports" << endl;
        cout << "4) Exit Program" << endl << endl;

        cout << "Enter a menu option: ";
        cin >> userInput;

        cout << endl;

        switch (userInput) {
        case 1:
            memberMenu(memberList, observerList);
            break;
        case 2:
            labMenu(memberList, observerList, labList);
            break;
        case 3:
            reportMenu(memberList, observerList, labList);
            break;
        case 4:
            validInput = true;
            cout << "Closing the program..." << endl << endl;
            break;
        default:
            validInput = false;
            cout << "Invalid input. Please try again." << endl << endl;
        }
    }
}

/*
This function authenticates the user's login information. If successful, the user gains access to the program, 
otherwise they are prompted to try again.

TO DO: Administrator information should be pulled from an encrypted file, it should not be hard-coded.
*/
void userLogin() {
    Administrator admin(1, "Bill", "BillyBob123", "BabyBilly@gmail.com"); //create an admin
    bool loginSuccess{ false };

    while (loginSuccess == false) {
        string name, password;

        cout << "Administrator Login" << endl;
        cout << "Enter Username: ";
        cin >> name;
        cout << "Enter Password: ";
        cin >> password;
        cout << endl;

        if (!admin.login(name, password)) {
            loginSuccess = false;
            cout << "Login failed, try again " << endl << endl;
        }
        else {
            loginSuccess = true;
            cout << "Login Successful!" << endl << endl;
        }
    }
}

/*
This function initializes various objects to demo the program.

TO DO: This function should be replaced with one that pulls data from all files to initialize the lists.
*/
void initializeLists(list<Member>& memberList, list<Observer>& observerList, list<Lab>& labList) {

    // Initialize Members
    Member member1(11, "Phil Hartman", "Phartman@gmail.com", "123 Cropdust Ln", 3421243, 0.0);  
    Member member2(12, "Julia Kindly", "jewlzizkoolz@aol.com", "143 OakTree Ave", 3450989, 10.0);
    Member member3(13, "Micheal Jordan", "theRealGooooaaat@gmail.com", "345 Rand Ave", 3094953, 12.2);
    Member member4(14, "Mary Prescott", "Mprescott@gmail.com", "325 S Sunset Ln", 5989765, 20.5);
    Member member5(15, "Robert Jackson", "MrJackson11@yahoo.com", "435 S Cherrywood Ln", 3453245, 7);
    Member member6(16, "Boyd Crowder", "crawDaddy@yahoo.com", "643 Grizzly Lane", 4503495, 19);

    memberList.push_back(member1);
    memberList.push_back(member2);
    memberList.push_back(member3);
    memberList.push_back(member4);
    memberList.push_back(member5);
    memberList.push_back(member6);

    // Initialize Members
    Observer observer1(17, "Julia Kindly", "jewlzizkoolz@aol.com", "143 OakTree Ave", 3450989, 0);
    Observer observer2(18, "Robert Jackson", "MrJackson11@yahoo.com", "435 S Cherrywood Ln", 3453245, 5.0);
    Observer observer3(19, "Boyd Crowder", "crawDaddy@yahoo.com", "643 Grizzly Lane", 4503495, 2.5);

    observerList.push_back(observer1);
    observerList.push_back(observer2);
    observerList.push_back(observer3);

    // Initiailize Labs
    Lab lab1(1, "Faceting", 50, nullptr); 
    Lab lab2(2, "Lapidary", 75.2, nullptr);
    Lab lab3(3, "Blacksmithing", 19.5, nullptr);

    // Assign Observers to Labs
    auto itr1 = observerList.begin();

    // Observer1 -> Lab1
    lab1.setObserver(&*itr1);

    // Observer2 -> Lab2
    itr1++;
    lab2.setObserver(&*itr1);

    // Observer3 -> Lab3
    itr1++;
    lab3.setObserver(&*itr1);

    // Add Members to Labs
    auto itr2 = memberList.begin();

    // Member 1
    addMemberToLab(*itr2, lab1);

    // Member 2
    itr2++;
    addMemberToLab(*itr2, lab1);
    addMemberToLab(*itr2, lab2);

    // Member 3
    itr2++;
    addMemberToLab(*itr2, lab1);

    // Member 5
    itr2++;
    itr2++;
    addMemberToLab(*itr2, lab2);

    // Member 6
    itr2++;
    addMemberToLab(*itr2, lab2);

    labList.push_back(lab1);
    labList.push_back(lab2);
    labList.push_back(lab3);

    // Assign Labs to Observers
    itr1 = observerList.begin();
    auto itr3 = labList.begin();

    // Lab1 -> Observer 1
    assignObserverToLab(*itr1, *itr3);
    itr3++;
    addMemberToLab(*itr1, *itr3);

    // Lab2 -> Observer 2
    itr1++;
    assignObserverToLab(*itr1, *itr3);

    // Lab3 -> Observer 3
    itr1++;
    itr3++;
    assignObserverToLab(*itr1, *itr3);
}

/*
This function displays the Member Menu and accepts and verifies commands from the user. Valid commands call helper 
functions or return to the main menu.

TO DO: Make sure to add function calls for helper functions after they're made.
*/
void memberMenu(list<Member>& memberList, list<Observer>& observerList) {
    int userInput;
    bool validInput{ false };

    while (validInput == false) {
        cout << "Member Data Menu" << endl;
        cout << "----------------" << endl;
        cout << "1) View Members List" << endl;
        cout << "2) Add a Member" << endl;
        cout << "3) Edit a Member" << endl;
        cout << "4) Remove a Member" << endl;
        cout << "5) Promote/Demote to Observer" << endl;
        cout << "6) Return to Main Menu" << endl << endl;

        cout << "Enter a menu option: ";
        cin >> userInput;

        cout << endl;

        switch (userInput) {
        case 1:
            printMembersList(memberList, observerList);
            break;
        case 2:
            addMember(memberList);
            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;
        case 6:
            validInput = true;
            cout << "Returning to main menu..." << endl << endl;
            break;
        default:
            validInput = false;
            cout << "Invalid input. Please try again." << endl << endl;
        }
    }
}

/*
This helper function prints out every Member in the Member and Observer lists.
Preconditions:  memberList and observerList have been initialized with Members
Postconditions: all Members in memberList and observerList are printed to the console.
*/
void printMembersList(list<Member>& memberList, list<Observer>& observerList) {
    for (Observer observer : observerList) {
        cout << observer.toString() << endl;
    }

    for (Member member : memberList) {
        cout << member.toString() << endl;
    }

    cout << endl;
}

/*
This helper function adds a user input Member to memberList.

TO DO: Add input verification and error handling.
*/
void addMember(list<Member>& memberList) {
    int memberID;
    string name;
    string email;
    string address;
    int phoneNum;
    double labHours;

    cout << "Adding new Club Member..." << endl;
    cout << "Enter the Member's ID: ";
    cin >> memberID;
    cout << "Enter the Member's name: ";
    cin >> name;
    cout << "Enter the Member's email address: ";
    cin >> email;
    cout << "Enter the Member's street address: ";
    cin >> address;
    cout << "Enter the Member's phone number (without special characters or spaces): ";
    cin >> phoneNum;
    cout << "Enter the Member's available lab hours: ";
    cin >> labHours;

    Member member(memberID, name, email, address, phoneNum, labHours);
    memberList.push_back(member);
}

/*
This function displays the Lab Menu and accepts and verifies commands from the user. Valid commands call helper
functions or return to the main menu.

TO DO: Make sure to add function calls for helper functions after they're made.
*/
void labMenu(list<Member>& memberList, list<Observer>& observerList, list<Lab>& labList) {
    int userInput;
    bool validInput{ false };

    while (validInput == false) {
        cout << "Lab Data Menu" << endl;
        cout << "----------------" << endl;
        cout << "1) View Labs List" << endl;
        cout << "2) Add a Lab" << endl;
        cout << "3) Edit a Lab" << endl;
        cout << "4) Remove a Lab" << endl;
        cout << "5) Add Member to Lab" << endl;
        cout << "6) Return to Main Menu" << endl << endl;

        cout << "Enter a menu option: ";
        cin >> userInput;

        cout << endl;

        switch (userInput) {
        case 1:
            
            break;
        case 2:
            
            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;
        case 6:
            validInput = true;
            cout << "Returning to main menu..." << endl << endl;
            break;
        default:
            validInput = false;
            cout << "Invalid input. Please try again." << endl << endl;
        }
    }
}

/*
This function displays the Pull Reports Menu and accepts and verifies commands from the user. Valid commands call 
helper functions or return to the main menu.

TO DO: This function and its helper functions will likely need to be changed if a Report class is added to the program
*/
void reportMenu(list<Member>& memberList, list<Observer>& observerList, list<Lab>& labList) {
    int userInput;
    bool validInput{ false };

    while (validInput == false) {
        cout << "Pull Reports Menu" << endl;
        cout << "----------------" << endl;
        cout << "1) Pull a Member's Report" << endl;
        cout << "2) Pull a Lab's Report" << endl;
        cout << "3) Pull ALL Member Reports" << endl;
        cout << "4) Pull ALL Lab Reports" << endl;
        cout << "5) Return to Main Menu" << endl << endl;

        cout << "Enter a menu option: ";
        cin >> userInput;

        cout << endl;

        switch (userInput) {
        case 1:
            pullMemberReport(memberList, observerList);
            break;
        case 2:
            pullLabReport(labList);
            break;
        case 3:
            pullAllMembersReport(memberList, observerList);
            break;
        case 4:
            pullAllLabsReport(labList);
            break;
        case 5:
            validInput = true;
            cout << "Returning to main menu..." << endl << endl;
            break;
        default:
            validInput = false;
            cout << "Invalid input. Please try again." << endl << endl;
        }
    }
}

/*
This helper function takes a user input Member ID and uses it to print the Member's Report to the console.

TO DO: Add input verification and error handling.
*/
void pullMemberReport(list<Member>& memberList, list<Observer>& observerList) {
    int memberID;

    cout << "Enter the Member's ID to pull their report: ";
    cin >> memberID;

    cout << endl;

    for (auto itr{ memberList.begin() }; itr != memberList.end(); ++itr) {
        if ((*itr).getID() == memberID) {
            cout << "Member Report" << endl;
            (*itr).pullReport();
            return;
        }
    }

    for (auto itr{ observerList.begin() }; itr != observerList.end(); ++itr) {
        if ((*itr).getID() == memberID) {
            cout << "Member Report" << endl;
            (*itr).pullReport();
            return;
        }
    }

    cout << "That Member ID doesn't exist. Returning to previous menu..." << endl << endl;
}

/*
This helper function takes a user input Lab ID and uses it to print the Lab's Report to the console.

TO DO: Add input verification and error handling.
*/
void pullLabReport(list<Lab>& labList) {
    Lab target;
    int labID;
    bool validInput{ false };

    cout << "Enter the Lab's ID to pull their report: ";
    cin >> labID;

    cout << endl;

    for (Lab lab : labList) {
        if (lab.getID() == labID) {
            target = lab;
            validInput = true;
            break;
        }
    }

    if (validInput == true) {
        cout << "Lab Report" << endl;
        target.pullReport();
    }
    else {
        cout << "That Lab ID doesn't exist. Returning to previous menu..." << endl << endl;
    }
}

/*
This helper function prints out ever Member report from memberList and observerList.
Preconditions:  memberList and observerList have been initialized with Members
Postconditions: the Reports of all Members in memberList and observerList are printed to the console.
*/
void pullAllMembersReport(list<Member>& memberList, list<Observer>& observerList) {
    int count{ 1 };

    for (Member member : memberList) {
        cout << "Member " << count << " Report:" << endl;
        member.pullReport();
        count++;
    }

    for (Observer observer : observerList) {
        cout << "Member " << count << " Report:" << endl;
        observer.pullReport();
        count++;
    }
}

/*
This helper function prints out ever Lab report from labList.
Preconditions:  labList has been initialized with Labs
Postconditions: the Reports of all Labs in labList are printed to the console.
*/
void pullAllLabsReport(list<Lab>& labList) {
    cout << "Lab Reports:" << endl;

    for (Lab lab : labList) {
        lab.pullReport();
    }
}

/*
This function takes the member and lab parameter and adds them to each others' respective lists.
Preconditions:  none
Postconditions: member has been added to lab's memberList and lab has been added to member's labsList
*/
void addMemberToLab(Member& member, Lab& lab) {
    member.addLab(&lab);
    lab.addMember(&member);
}

void assignObserverToLab(Observer& observer, Lab& lab) {
    observer.setAssignedLab(&lab);
    lab.setObserver(&observer);
}