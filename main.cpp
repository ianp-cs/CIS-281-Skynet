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
#include <string>
#include <list>
#include <fstream>
#include <sstream>

#include "Account.h"
#include "Administrator.h"
#include "Lab.h"
#include "Observer.h"
#include "Member.h"

using namespace std;

// Startup
void userLogin();
void initializeLists(list<Member>& memberList, list<Observer>& observerList, list<Lab>& labList);
void saveData()
// Main Menu
void memberMenu(list<Member>& memberList, list<Observer>& observerList);
void labMenu(list<Member>& memberList, list<Observer>& observerList, list<Lab>& labList);
void reportMenu(list<Member>& memberList, list<Observer>& observerList, list<Lab>& labList);

// Member Menu
void printMembersList(list<Member>& memberList, list<Observer>& observerList);
void addMember(list<Member>& memberList);

// Lab Menu
void printLabsList()

// Report Menu
void pullMemberReport(list<Member>& memberList, list<Observer>& observerList);
void pullLabReport(list<Lab>& labList);
void pullAllMembersReport(list<Member>& memberList, list<Observer>& observerList);
void pullAllLabsReport(list<Lab>& labList);

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
            cout << "Closing the program..." << endl << endl;
            break;
        default:
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

    // Initialize files
    ifstream memberFile("member.txt");
    ifstream observerFile("observer.txt");
    ifstream labFile("lab.txt");
    
    // Initialize Members
    if (memberFile.is_open())
    {    
        string line;
        while (getline(memberFile, line)) {
            istringstream ss(line);
            int id, phoneNum;
            string name, email, address;
            double labHours;
            ss >> id >> name >> address >> phoneNum >> labHours;
            memberList.push_back(id, name, email, address, phoneNum, labHours);
        }
        memberFile.close();
    } else {
      cout << "Error, could not open  member file!!" << endl; 
    }
    
    // Initiailize Labs
   if(labFile.is_open()){
    string line;
        while (getline(labFile, line)){
            istringstream ss(line);
            int id;
            string type;
            double totalHours;
            ss >> id >> type >> totalHours;
            labList.push_back(id, type, totalHours);}
        labFile.close();}
           else {
        cout << "Error, could not open lab file" << endl;
   }
}
    if (observerFile.is_open())
    {
        string line;
        while (getline(observerFile, line)) {
            istringstream ss(line);
            int id, phoneNum;
            string name, email, address;
            doublelabHours;

            ss >> id >> name >> address >> phoneNum >> labHours;
            observerList.push_back(id, name, email, address, phoneNum, labHours); }
        observerFile.close(); 
    }    else {
            cout << "Error, could not open observer file!"; 
    } 
}
*/ This function writes data to the file /*
void writeData(const list<Member>& memberList, const list<Observer>& observerList, const list<Lab>& labList) {
   
    ofstream memberFile("member.txt");
    ofstream observerFile("observer.txt");
    ofstream labFile("labs.txt");
    
    if (memberFile.is_open()){
        for (const auto& member:memberList) {
            memberFile << member.getID() << " " << member.getName() " " << member.getEmail() << " " 
             << member.getAddress() << " " << member.getPhoneNum() << " " << member.getLabHours() << " " << endl;
        }
        memberFile.close();
    } else {
        cout << "Error, could not open file!" << endl;}
        
        }
    if (observerFile.is_open()) {
        for (const auto& observer:observerList) {
            observerFile << observer.getID() << " " << observer.getName() << " " << observer.getEmail() << " " 
                << observer.getAddress() << " " << observer.getLabHours() << " " ; }
        observerFile.close();
        } else {
            cout << "Error, could not open file!!"}
            }
    if (labFile.is_open()) { 
        for (const auto& lab:labList() {
        labFile << lab.getID() " " lab.getType() << " " << lab.getTotalHours() << " " << endl; 
        } 
        labFile.close();
            } else { 
                cout << "Error: could not open file! " << endl; }
                }
}


*/ This function displays the Member Menu and accepts and verifies commands from the user. Valid commands call helper 
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
            editMember(memberList, observerList);
            break;
        case 4:
            removeMember(memberList, observerList);
            break;
        case 5:
            toggleObserverStatus(memberList, observerList);
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
        cout << "5) Return to Main Menu" << endl << endl;

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
    Member target;
    int memberID;
    bool validInput{ false };

    cout << "Enter the Member's ID to pull their report: ";
    cin >> memberID;

    cout << endl;

    for (Member member : memberList) {
        if (member.getID() == memberID) {
            target = member;
            validInput = true;
            break;
        }
    }

    if (validInput == false) {
        for (Observer observer : observerList) {
            if (observer.getID() == memberID) {
                target = observer;
                validInput = true;
                break;
            }
        }
    }

    if (validInput == true) {
        cout << "Member Report" << endl;
        target.pullReport();
    }
    else {
        cout << "That Member ID doesn't exist. Returning to previous menu..." << endl << endl;
    }
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
