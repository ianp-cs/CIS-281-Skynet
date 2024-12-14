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
#include <array>
#include "Account.h"
#include "Administrator.h"
#include "Lab.h"
#include "Observer.h"
#include "Member.h"
using namespace std;

#define MEMBER_ARR_SIZE 100
#define LAB_ARR_SIZE 20

static int memberListSize{ 0 };
static int observerListSize{ 0 };
static int labListSize{ 0 };

// Startup
void userLogin();
void initializeLists(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList, 
    array<Lab*, LAB_ARR_SIZE>& labList);

// Main Menu Functions
void memberMenu(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList,
    array<Lab*, LAB_ARR_SIZE>& labList);
void labMenu(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList, 
    array<Lab*, LAB_ARR_SIZE>& labList);
void reportMenu(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList, 
    array<Lab*, LAB_ARR_SIZE>& labList);

// Member Menu Functions
void printMembersList(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList);
void addMember(array<Member*, MEMBER_ARR_SIZE>& memberList);
void editMember(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList);
void removeMember(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList);
void toggleObserverStatus(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList);
void addMemberLabHours(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList);
void spendMemberLabHours(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList);
void refundMemberLabHours(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList);

// Lab Menu Functions
void printLabList(array<Lab*, LAB_ARR_SIZE>& labList);
void addLab(array<Lab*, LAB_ARR_SIZE>& labList);
void editLab(array<Lab*, LAB_ARR_SIZE>& labList);
void removeLab(array<Lab*, LAB_ARR_SIZE>& labList);
void assignObserverToLab(array<Observer*, LAB_ARR_SIZE>& observerList, array<Lab*, LAB_ARR_SIZE>& labList);
void unassignObserver(array<Observer*, LAB_ARR_SIZE>& observerList);
void assignMemberToLab(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList,
    array<Lab*, LAB_ARR_SIZE>& labList);
void unassignMemberFromLab(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList,
    array<Lab*, LAB_ARR_SIZE>& labList);

// Report Menu Functions
void pullMemberReport(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList);
void pullLabReport(array<Lab*, LAB_ARR_SIZE>& labList);
void pullAllMembersReport(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList);
void pullAllLabsReport(array<Lab*, LAB_ARR_SIZE>& labList);

// Processing Functions
void clearBuffer(FILE* fp);
void shiftMemberListElements(array<Member*, MEMBER_ARR_SIZE>& memberList, const int& pos);
void shiftObserverListElements(array<Observer*, LAB_ARR_SIZE>& observerList, const int& pos);
void shiftLabListElements(array<Lab*, LAB_ARR_SIZE>& labList, const int& pos);
void attachMemberToLab(Member* member, Lab* lab);
void detachMemberFromLab(Member* member, Lab* lab);
void detachMember(Member* member);
void attachObserverToLab(Observer* observer, Lab* lab);
void deallocateLists(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList,
    array<Lab*, LAB_ARR_SIZE>& labList);

int main() {
    array<Member*, MEMBER_ARR_SIZE> memberList;
    memberList.fill(nullptr);
    array<Observer*, LAB_ARR_SIZE> observerList;
    observerList.fill(nullptr);
    array<Lab*, LAB_ARR_SIZE> labList;
    labList.fill(nullptr);

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
            memberMenu(memberList, observerList, labList);
            break;
        case 2:
            labMenu(memberList, observerList, labList);
            break;
        case 3:
            reportMenu(memberList, observerList, labList);
            break;
        case 4:
            validInput = true;
            cout << "Closing the program..." << endl;
            deallocateLists(memberList, observerList, labList);
            break;
        default:
            validInput = false;
            cout << "Invalid input. Please try again." << endl;
        }
    }
}

/*
This function authenticates the user's login information. If successful, the user gains access to the program, 
otherwise they are prompted to try again.

TO DO: Administrator information should be pulled from an encrypted file, it should not be hard-coded.
*/
void userLogin() {
    Administrator admin(1, "a", "a", "BabyBilly@gmail.com"); //create an admin
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
void initializeLists(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList, 
    array<Lab*, LAB_ARR_SIZE>& labList) {

    // Initialize Members
    memberList[0] = new Member(11, "Phil Hartman", "Phartman@gmail.com", "123 Cropdust Ln", 3421243, 0.0);
    memberListSize++;
    memberList[1] = new Member(12, "Julia Kindly", "jewlzizkoolz@aol.com", "143 OakTree Ave", 3450989, 10.0);
    memberListSize++;
    memberList[2] = new Member(13, "Micheal Jordan", "theRealGooooaaat@gmail.com", "345 Rand Ave", 3094953, 12.2);
    memberListSize++;
    memberList[3] = new Member(14, "Mary Prescott", "Mprescott@gmail.com", "325 S Sunset Ln", 5989765, 20.5);
    memberListSize++;
    memberList[4] = new Member(15, "Robert Jackson", "MrJackson11@yahoo.com", "435 S Cherrywood Ln", 3453245, 7);
    memberListSize++;
    memberList[5] = new Member(16, "Boyd Crowder", "crawDaddy@yahoo.com", "643 Grizzly Lane", 4503495, 19);
    memberListSize++;

    // Initialize Members
    observerList[0] = new Observer(17, "Bob Sagot", "bsagot@aol.com", "123 N Main St", 1234567, 0);
    observerListSize++;
    observerList[1] = new Observer(18, "John Doe", "jdoe@yahoo.com", "987 N Uptown St", 1231234, 5.0);
    observerListSize++;
    observerList[2] = new Observer(19, "Hally Berry", "hberry@yahoo.com", "456 W Songify Rd", 8675309, 2.5);
    observerListSize++;

    // Initiailize Labs
    labList[0] = new Lab(1, "Faceting", 50, observerList[0]);
    labListSize++;
    labList[1] = new Lab(2, "Lapidary", 75.2, observerList[1]);
    labListSize++;
    labList[2] = new Lab(3, "Blacksmithing", 19.5, observerList[2]);
    labListSize++;

    // Add Members to Labs
    attachMemberToLab(memberList[0], labList[0]);
    attachMemberToLab(memberList[1], labList[0]);
    attachMemberToLab(memberList[1], labList[1]);
    attachMemberToLab(memberList[2], labList[0]);
    attachMemberToLab(memberList[4], labList[1]);
    attachMemberToLab(memberList[5], labList[1]);

    // Assign Labs to Observers
    attachObserverToLab(observerList[0], labList[0]);
    attachObserverToLab(observerList[1], labList[1]);
    attachObserverToLab(observerList[2], labList[2]);
}

/*
This function displays the Member Menu and accepts and verifies commands from the user. Valid commands call helper 
functions or return to the main menu.

TO DO: Make sure to add function calls for helper functions after they're made.
*/
void memberMenu(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList,
    array<Lab*, LAB_ARR_SIZE>& labList) {

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
        cout << "6) Add Lab Hours to Member" << endl;
        cout << "7) Spend Member's Lab Hours" << endl;
        cout << "8) Refund Member's lab Hours" << endl;
        cout << "9) Return to Main Menu" << endl << endl;

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
            addMemberLabHours(memberList, observerList);
            break;
        case 7:
            spendMemberLabHours(memberList, observerList);
            break;
        case 8:
            refundMemberLabHours(memberList, observerList);
            break;
        case 9:
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
void printMembersList(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList) {
    for (int i{ 0 }; i < observerListSize; i++) {
        cout << observerList[i]->toString() << endl;
    }

    for (int i{ 0 }; i < memberListSize; i++) {
        cout << memberList[i]->toString() << endl;
    }

    cout << endl;
}

/*
This helper function adds a user input Member to memberList.

TO DO: Add input verification and error handling.
*/
void addMember(array<Member*, MEMBER_ARR_SIZE>& memberList) {
    string userInput;
    int memberID;
    string name;
    string email;
    string address;
    int phoneNum;
    double labHours;

    clearBuffer(stdin);

    cout << "Adding new Club Member..." << endl;
    cout << "Enter the Member's ID or enter \"0\" to return: ";
    getline(cin, userInput);
    cout << endl;
    if (stoi(userInput) == 0) {
        cout << endl;
        return;
    }
    memberID = stoi(userInput);

    cout << "Enter the Member's name: ";
    getline(cin, userInput);
    cout << endl;
    name = userInput;

    cout << "Enter the Member's email address: ";
    getline(cin, userInput);
    cout << endl;
    email = userInput;

    cout << "Enter the Member's street address: ";
    getline(cin, userInput);
    cout << endl;
    address = userInput;

    cout << "Enter the Member's phone number (without special characters or spaces): ";
    getline(cin, userInput);
    cout << endl;
    phoneNum = stoi(userInput);

    cout << "Enter the Member's available lab hours: ";
    getline(cin, userInput);
    cout << endl;
    labHours = stod(userInput);

    cout << endl;

    memberList[memberListSize] = new Member(memberID, name, email, address, phoneNum, labHours);
    memberListSize++;
}

void editMember(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList) {
    int memberID;
    Member* target{ nullptr };
    string userInput;

    cout << "Enter the Member's ID to edit or enter \"0\" to return: ";
    cin >> memberID;

    cout << endl;

    if (memberID == 0) {
        return;
    }

    for (int i{ 0 }; i < memberListSize; i++) {
        if (memberList[i]->getID() == memberID) {
            target = memberList[i];
            break;
        }
    }

    if (target == nullptr) {
        for (int i{ 0 }; i < observerListSize; i++) {
            if (observerList[i]->getID() == memberID) {
                target = observerList[i];
                break;
            }
        }
    }
    
    if (target != nullptr) {
        clearBuffer(stdin);

        cout << "For the following prompts, enter a new value if the data needs to be changed, otherwise hit ENTER to skip." << endl << endl;

        cout << "Enter the Member's ID: ";
        getline(cin, userInput);
        cout << endl;
        if (userInput != "") {
            target->setID(stoi(userInput));
        }

        cout << "Enter the Member's name: ";
        getline(cin, userInput);
        cout << endl;
        if (userInput != "") {
            target->setName(userInput);
        }

        cout << "Enter the Member's email address: ";
        getline(cin, userInput);
        cout << endl;
        if (userInput != "") {
            target->setEmail(userInput);
        }

        cout << "Enter the Member's street address: ";
        getline(cin, userInput);
        cout << endl;
        if (userInput != "") {
            target->setAddress(userInput);
        }

        cout << "Enter the Member's phone number (without special characters or spaces): ";
        getline(cin, userInput);
        cout << endl;
        if (userInput != "") {
            target->setPhoneNum(stoi(userInput));
        }

        cout << "Enter the Member's available lab hours: ";
        getline(cin, userInput);
        cout << endl;
        if (userInput != "") {
            target->setLabHours(stod(userInput));
        }
    }
    else {
        cout << "There is no Member with ID \"" << memberID << "\". Returning to previous menu..." << endl << endl;
    }
}

void removeMember(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList) {
    int memberID;

    cout << "Enter the ID of the Member to remove them or enter \"0\" to return: ";
    cin >> memberID;

    cout << endl;

    if (memberID == 0) {
        return;
    }
    else {
        for (int i{ 0 }; i < memberListSize; i++) {
            if (memberList[i]->getID() == memberID) {
                detachMember(memberList[i]);
                shiftMemberListElements(memberList, i);
                cout << "Member " << memberID << " successfully removed from the database." << endl << endl;
                return;
            }
        }

        for (int i{ 0 }; i < memberListSize; i++) {
            if (observerList[i]->getID() == memberID) {
                observerList[i]->getAssignedLab()->setObserver(nullptr); // Detach observer from assigned Lab first.
                detachMember(observerList[i]);
                shiftObserverListElements(observerList, i);
                cout << "Member " << memberID << " successfully removed from the database." << endl << endl;
                return;
            }
        }

        cout << "There is no Member with ID \"" << memberID << "\". Returning to previous menu..." << endl << endl;
    }
}

void toggleObserverStatus(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList) {
    int memberID;

    cout << "Entering the ID of a Member will promote them to Observer, if they are not already one. Otherwise, if " <<
        "the ID is of an Observer, they will be demoted to Member. Enter \"0\" to return to the previous menu." << endl << endl;

    cout << "Enter a Member's ID to promote/demote them: ";
    cin >> memberID;

    cout << endl;

    if (memberID == 0) {
        return;
    }
    else {
        for (int i{ 0 }; i < memberListSize; i++) {
            if (memberList[i]->getID() == memberID) {
                observerList[observerListSize] = new Observer(*memberList[i]);
                observerListSize++;

                shiftMemberListElements(memberList, i);

                cout << "Member " << memberID << " successfully promoted to Observer." << endl << endl;
                return;
            }
        }

        for (int i{ 0 }; i < observerListSize; i++) {
            if (observerList[i]->getID() == memberID) {
                memberList[memberListSize] = new Member(*observerList[i]);
                memberListSize++;

                observerList[i]->getAssignedLab()->setObserver(nullptr);
                shiftObserverListElements(observerList, i);

                cout << "Member " << memberID << " successfully demoted toMember." << endl << endl;
                return;
            }
        }

        cout << "There is no Member with ID \"" << memberID << "\". Returning to previous menu..." << endl << endl;
    }
}

void addMemberLabHours(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList) {
    int memberID;
    Member* target{ nullptr };
    double labHours;

    cout << "Enter a Member's ID to add Lab hours or enter \"0\" to return: ";
    cin >> memberID;

    cout << endl;

    if (memberID == 0) {
        return;
    }

    for (int i{ 0 }; i < memberListSize; i++) {
        if (memberList[i]->getID() == memberID) {
            target = memberList[i];
            break;
        }
    }

    if (target == nullptr) {
        for (int i{ 0 }; i < observerListSize; i++) {
            if (observerList[i]->getID() == memberID) {
                target = observerList[i];
                break;
            }
        }
    }

    if (target != nullptr) {
        cout << "Enter the number of hours to add to Member " << memberID << " total Lab hours: ";
        cin >> labHours;

        cout << endl;

        target->refundLabHours(labHours);
        cout << fixed << setprecision(2);
        cout << "Successfully added " << labHours << " hours to Member " << memberID << "\'s balance." << endl << endl;
    }

    cout << "There is no Member with ID \"" << memberID << "\". Returning to previous menu..." << endl << endl;
}

void spendMemberLabHours(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList) {
    int memberID, labID;
    Member* memberTarget{ nullptr };
    Lab* labTarget{ nullptr };
    string userInput;
    double labHours;

    cout << "Enter a Member's ID to spend Lab hours or enter \"0\" to return: ";
    cin >> memberID;

    cout << endl;

    if (memberID == 0) {
        return;
    }

    for (int i{ 0 }; i < memberListSize; i++) {
        if (memberList[i]->getID() == memberID) {
            memberTarget = memberList[i];
            break;
        }
    }

    if (memberTarget == nullptr) {
        for (int i{ 0 }; i < observerListSize; i++) {
            if (observerList[i]->getID() == memberID) {
                memberTarget = observerList[i];
                break;
            }
        }
    }

    if (memberTarget == nullptr) {
        cout << "There is no Member with ID \"" << memberID << "\". Returning to previous menu..." << endl << endl;
        return;
    }

    cout << "Enter the ID of the Lab where the Lab hours are spent: ";
    cin >> labID;

    cout << endl;

    for (int i{ 0 }; i < memberTarget->getLabsListSize(); i++) {
        if (memberTarget->getLabsList()[i]->getID() == labID) {
            labTarget = memberTarget->getLabsList()[i];
        }
    }

    if (labTarget == nullptr) {
        cout << "Member " << memberID << " does not have Lab " << labID << " in their Lab list. Returning to previous " 
            "menu..." << endl << endl;
        return;
    }

    cout << "Enter the number of hours to be spent by Member " << memberID << " for Lab " << labID << ": ";
    cin >> labHours;

    cout << endl;

    memberTarget->spendLabHours(labHours);
    labTarget->addHours(labHours);
    cout << "Successfully spent " << labHours << " of Member " << memberID << "\'s Lab hours for Lab " << labID << "." 
        << endl << endl;
}

void refundMemberLabHours(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList) {
    int memberID, labID;
    Member* memberTarget{ nullptr };
    Lab* labTarget{ nullptr };
    string userInput;
    double labHours;

    cout << "Enter a Member's ID to refund Lab hours or enter \"0\" to return: ";
    cin >> memberID;

    cout << endl;

    if (memberID == 0) {
        return;
    }

    for (int i{ 0 }; i < memberListSize; i++) {
        if (memberList[i]->getID() == memberID) {
            memberTarget = memberList[i];
            break;
        }
    }

    if (memberTarget == nullptr) {
        for (int i{ 0 }; i < observerListSize; i++) {
            if (observerList[i]->getID() == memberID) {
                memberTarget = observerList[i];
                break;
            }
        }
    }

    if (memberTarget == nullptr) {
        cout << "There is no Member with ID \"" << memberID << "\". Returning to previous menu..." << endl << endl;
        return;
    }

    cout << "Enter the ID of the Lab where the Lab hours are refunded from: ";
    cin >> labID;

    cout << endl;

    for (int i{ 0 }; i < memberTarget->getLabsListSize(); i++) {
        if (memberTarget->getLabsList()[i]->getID() == labID) {
            labTarget = memberTarget->getLabsList()[i];
        }
    }

    if (labTarget == nullptr) {
        cout << "Member " << memberID << " does not have Lab " << labID << " in their Lab list. Returning to previous "
            "menu..." << endl << endl;
        return;
    }

    cout << "Enter the number of hours to be refunded to Member " << memberID << " from Lab " << labID << ": ";
    cin >> labHours;

    cout << endl;

    memberTarget->refundLabHours(labHours);
    labTarget->refundHours(labHours);
    cout << "Successfully refunded " << labHours << " hours to Member " << memberID << "\'s balance from Lab " << 
        labID << "." << endl << endl;
}

/*
This function displays the Lab Menu and accepts and verifies commands from the user. Valid commands call helper
functions or return to the main menu.

TO DO: Make sure to add function calls for helper functions after they're made.
*/
void labMenu(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList, array<Lab*, LAB_ARR_SIZE>& labList) {
    int userInput;
    bool validInput{ false };

    while (validInput == false) {
        cout << "Lab Data Menu" << endl;
        cout << "----------------" << endl;
        cout << "1) View Labs List" << endl;
        cout << "2) Add a Lab" << endl;
        cout << "3) Edit a Lab" << endl;
        cout << "4) Remove a Lab" << endl;
        cout << "5) Assign Observer to Lab" << endl;
        cout << "6) Remove Observer from lab" << endl;
        cout << "7) Add Member to Lab" << endl;
        cout << "8) Remove Member from lab" << endl;
        cout << "9) Return to Main Menu" << endl << endl;

        cout << "Enter a menu option: ";
        cin >> userInput;

        cout << endl;

        switch (userInput) {
        case 1:
            printLabList(labList);
            break;
        case 2:
            addLab(labList);
            break;
        case 3:
            editLab(labList);
            break;
        case 4:
            removeLab(labList);
            break;
        case 5:
            assignObserverToLab(observerList, labList);
            break;
        case 6:
            unassignObserver(observerList);
            break;
        case 7:
            assignMemberToLab(memberList, observerList, labList);
            break;
        case 8:
            unassignMemberFromLab(memberList, observerList, labList);
            break;
        case 9:
            validInput = true;
            cout << "Returning to main menu..." << endl << endl;
            break;
        default:
            validInput = false;
            cout << "Invalid input. Please try again." << endl << endl;
        }
    }
}

void printLabList(array<Lab*, LAB_ARR_SIZE>& labList) {
    for (int i{ 0 }; i < labListSize; i++) {
        cout << labList[i]->toString() << endl;
    }

    cout << endl;
}

void addLab(array<Lab*, LAB_ARR_SIZE>& labList) {
    string userInput;
    int labID;
    string type;

    clearBuffer(stdin);

    cout << "Adding new Lab..." << endl;
    cout << "Enter the Lab's ID or enter \"0\" to return: ";
    getline(cin, userInput);
    cout << endl;
    if (stoi(userInput) == 0) {
        cout << endl;
        return;
    }
    labID = stoi(userInput);

    cout << "Enter the Lab's ID: ";
    getline(cin, userInput);
    cout << endl;
    type = userInput;

    cout << endl;

    labList[labListSize] = new Lab(labID, type, 0, nullptr);
    labListSize++;
}

void editLab(array<Lab*, LAB_ARR_SIZE>& labList) {
    int labID;
    Lab* target{ nullptr };
    string userInput;

    cout << "Enter the Lab's ID to edit or enter \"0\" to return: ";
    cin >> labID;

    cout << endl;

    if (labID == 0) {
        return;
    }

    for (int i{ 0 }; i < labListSize; i++) {
        if (labList[i]->getID() == labID) {
            target = labList[i];
            break;
        }
    }

    if (target != nullptr) {
        clearBuffer(stdin);

        cout << "For the following prompts, enter a new value if the data needs to be changed, otherwise hit ENTER to "
            "skip." << endl << endl;

        cout << "Enter the Lab's ID: ";
        getline(cin, userInput);
        cout << endl;
        if (userInput != "") {
            target->setID(stoi(userInput));
        }

        cout << "Enter the Lab's type: ";
        getline(cin, userInput);
        cout << endl;
        if (userInput != "") {
            target->setType(userInput);
        }

        cout << "Enter the Lab's total hours: ";
        getline(cin, userInput);
        cout << endl;
        if (userInput != "") {
            target->setTotalHours(stod(userInput));
        }
    }
    else {
        cout << "There is no Lab with ID \"" << labID << "\". Returning to previous menu..." << endl << endl;
    }
}

void removeLab(array<Lab*, LAB_ARR_SIZE>& labList) {
    int labID;

    cout << "Enter the ID of the Lab to remove them or enter \"0\" to return: ";
    cin >> labID;

    cout << endl;

    if (labID == 0) {
        return;
    }
    else {
        for (int i{ 0 }; i < labListSize; i++) {
            if (labList[i]->getID() == labID) {
                shiftLabListElements(labList, i);
                cout << "Lab " << labID << " successfully removed from the database." << endl << endl;
                return;
            }
        }

        cout << "There is no Lab with ID \"" << labID << "\". Returning to previous menu..." << endl << endl;
    }
}

void assignObserverToLab(array<Observer*, LAB_ARR_SIZE>& observerList, array<Lab*, LAB_ARR_SIZE>& labList) {
    int observerID, labID;
    Observer* observerTarget = nullptr;
    Lab* labTarget = nullptr;
    
    cout << "Enter the ID of the Observer to be assigned or enter \"0\" to return";
    cin >> observerID;

    cout << endl;

    if (observerID == 0) {
        return;
    }
    else {
        for (int i{ 0 }; i < memberListSize; i++) {
            if (observerList[i]->getID() == observerID) {
                observerTarget = observerList[i];
                break;
            }
        }

        if (observerTarget == nullptr) {
            cout << "There is no Observer with ID \"" << observerID << "\". Returning to previous menu..." << endl << endl;
            return;
        }
    }

    cout << "Enter the ID of the Lab that Observer " << observerID << " should be assigned to: ";
    cin >> labID;

    cout << endl;

    for (int i{ 0 }; i < labListSize; i++) {
        if (labList[i]->getID() == labID) {
            labTarget = labList[i];
            break;
        }
    }

    if (labTarget == nullptr) {
        cout << "There is no Lab with ID \"" << labID << "\". Returning to previous menu..." << endl << endl;
        return;
    }
    else if (observerTarget->getAssignedLab() == labTarget) {
        cout << "Observer " << observerID << " is already assigned to Lab " << labID << ". Returning to previous menu..."
            << endl << endl;
    }
    else {
        // If the Lab already has an Observer, detach the Lab from the Observer
        if (labTarget->getObserver() != nullptr) {
            labTarget->getObserver()->setAssignedLab(nullptr);
        }
        // If the Observer already has an assigned Lab, detach the Observer from the Lab
        if (observerTarget->getAssignedLab() != nullptr) {
            observerTarget->getAssignedLab()->setObserver(nullptr);
        }
        attachObserverToLab(observerTarget, labTarget);
        cout << "Observer " << observerID << " successfully assigned to Lab " << labID << "." << endl << endl;
    }
}

void unassignObserver(array<Observer*, LAB_ARR_SIZE>& observerList) {
    int observerID;
    Observer* observerTarget = nullptr;

    cout << "Enter the ID of the Observer to be unassigned or enter \"0\" to return";
    cin >> observerID;

    cout << endl;

    if (observerID == 0) {
        return;
    }
    else {
        for (int i{ 0 }; i < observerListSize; i++) {
            if (observerList[i]->getID() == observerID) {
                observerTarget = observerList[i];
                break;
            }
        }

        if (observerTarget == nullptr) {
            cout << "There is no Observer with ID \"" << observerID << "\". Returning to previous menu..." << endl << endl;
            return;
        }
        else if (observerTarget->getAssignedLab() == nullptr) {
            cout << "Observer " << observerID << " is not assigned to any Lab. Returning to previous menu..." << endl << endl;
        }
        else {
            observerTarget->setAssignedLab(nullptr);
            cout << "Successfully unassigned Observer " << observerID << " from their assigned Lab." << endl << endl;
        }
    }
}

void assignMemberToLab(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList,
    array<Lab*, LAB_ARR_SIZE>& labList) {

    int memberID, labID;
    Member* memberTarget = nullptr;
    Lab* labTarget = nullptr;

    cout << "Enter the ID of the Member to be assigned or enter \"0\" to return";
    cin >> memberID;

    cout << endl;

    if (memberID == 0) {
        return;
    }
    else {
        for (int i{ 0 }; i < memberListSize; i++) {
            if (memberList[i]->getID() == memberID) {
                memberTarget = memberList[i];
                break;
            }
        }

        if (memberTarget == nullptr) {
            for (int i{ 0 }; i < observerListSize; i++) {
                if (observerList[i]->getID() == memberID) {
                    memberTarget = observerList[i];
                    break;
                }
            }
        }

        if (memberTarget == nullptr) {
            cout << "There is no Member with ID \"" << memberID << "\". Returning to previous menu..." << endl << endl;
            return; 
        }
    }
    
    cout << "Enter the ID of the Lab that Member " << memberID << " should be assigned to: ";
    cin >> labID;

    cout << endl;

    for (int i{ 0 }; i < labListSize; i++) {
        if (labList[i]->getID() == labID) {
            labTarget = labList[i];
            break;
        }
    }

    if (labTarget == nullptr) {
        cout << "There is no Lab with ID \"" << labID << "\". Returning to previous menu..." << endl << endl;
        return;
    }
    else if (memberTarget->hasLab(labTarget)) {
        cout << "Member " << memberID << " is already assigned to Lab " << labID << ". Returning to previous menu..." 
            << endl << endl;
    }
    else {
        attachMemberToLab(memberTarget, labTarget);
        cout << "Member " << memberID << " successfully assigned to Lab " << labID << "." << endl << endl;
    }
}

void unassignMemberFromLab(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList,
    array<Lab*, LAB_ARR_SIZE>& labList) {

    int memberID, labID;
    Member* memberTarget = nullptr;
    Lab* labTarget = nullptr;

    cout << "Enter the ID of the Member to be assigned or enter \"0\" to return";
    cin >> memberID;

    cout << endl;

    if (memberID == 0) {
        return;
    }
    else {
        for (int i{ 0 }; i < memberListSize; i++) {
            if (memberList[i]->getID() == memberID) {
                memberTarget = memberList[i];
                break;
            }
        }

        if (memberTarget == nullptr) {
            for (int i{ 0 }; i < observerListSize; i++) {
                if (observerList[i]->getID() == memberID) {
                    memberTarget = observerList[i];
                    break;
                }
            }
        }

        if (memberTarget == nullptr) {
            cout << "There is no Member with ID \"" << memberID << "\". Returning to previous menu..." << endl << endl;
            return;
        }
    }

    cout << "Enter the ID of the Lab that Member " << memberID << " should be removed from: ";
    cin >> labID;

    cout << endl;

    for (int i{ 0 }; i < labListSize; i++) {
        if (labList[i]->getID() == labID) {
            labTarget = labList[i];
            break;
        }
    }

    if (labTarget == nullptr) {
        cout << "There is no Lab with ID \"" << labID << "\". Returning to previous menu..." << endl << endl;
        return;
    }
    else if (!memberTarget->hasLab(labTarget)) {
        cout << "Member " << memberID << " is not assigned to Lab " << labID << ". Returning to previous menu..."
            << endl << endl;
    }
    else {
        detachMemberFromLab(memberTarget, labTarget);
        cout << "Member " << memberID << " successfully removed from Lab " << labID << "." << endl << endl;
    }
}

/*
This function displays the Pull Reports Menu and accepts and verifies commands from the user. Valid commands call 
helper functions or return to the main menu.

TO DO: This function and its helper functions will likely need to be changed if a Report class is added to the program
*/
void reportMenu(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList, array<Lab*, LAB_ARR_SIZE>& labList) {
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
void pullMemberReport(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList) {
    int memberID;

    cout << "Enter the Member's ID to pull their report: ";
    cin >> memberID;

    cout << endl;

    for (int i{ 0 }; i < memberListSize; i++) {
        if (memberList[i]->getID() == memberID) {
            cout << "Member Report" << endl;
            memberList[i]->pullReport();
            return;
        }
    }

    for (int i{ 0 }; i < observerListSize; i++) {
        if (observerList[i]->getID() == memberID) {
            cout << "Member Report" << endl;
            observerList[i]->pullReport();
            return;
        }
    }

    cout << "That Member ID doesn't exist. Returning to previous menu..." << endl << endl;
}

/*
This helper function takes a user input Lab ID and uses it to print the Lab's Report to the console.

TO DO: Add input verification and error handling.
*/
void pullLabReport(array<Lab*, LAB_ARR_SIZE>& labList) {
    Lab target;
    int labID;
    bool validInput{ false };

    cout << "Enter the Lab's ID to pull their report: ";
    cin >> labID;

    cout << endl;

    for (int i{ 0 }; i < labListSize; i++) {
        if (labList[i]->getID() == labID) {
            cout << "Lab Report" << endl;
            labList[i]->pullReport();
            return;
        }
    }

    cout << "That Lab ID doesn't exist. Returning to previous menu..." << endl << endl;
}

/*
This helper function prints out ever Member report from memberList and observerList.
Preconditions:  memberList and observerList have been initialized with Members
Postconditions: the Reports of all Members in memberList and observerList are printed to the console.
*/
void pullAllMembersReport(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList) {
    int count{ 1 };

    for (int i{ 0 }; i < memberListSize; i++) {
        cout << "Member " << count << " Report:" << endl;
        memberList[i]->pullReport();
        count++;
    }

    for (int i{ 0 }; i < observerListSize; i++) {
        cout << "Member " << count << " Report:" << endl;
        observerList[i]->pullReport();
        count++;
    }
}

/*
This helper function prints out ever Lab report from labList.
Preconditions:  labList has been initialized with Labs
Postconditions: the Reports of all Labs in labList are printed to the console.
*/
void pullAllLabsReport(array<Lab*, LAB_ARR_SIZE>& labList) {
    cout << "Lab Reports:" << endl;

    for (int i{ 0 }; i < labListSize; i++) {
        labList[i]->pullReport();
    }
}

/*
This function clears the input buffer of the stream parameter.
Input: FILE pointer fp
Output: none
*/
void clearBuffer(FILE* fp) {
    char ch;
    while ((ch = getc(fp)) != '\n' && ch != EOF);
}

void shiftMemberListElements(array<Member*, MEMBER_ARR_SIZE>& memberList, const int& pos) {
    int listSize = memberListSize;

    if (pos == memberList.max_size() - 1) { // If pos is the last element in labsList
        memberList[pos] = nullptr;
    }
    else if (listSize == 1) { // If pos is the only element in the list
        memberList[pos] = nullptr;
    }
    else {
        for (int i{ pos }; i < listSize - 1; i++) {
            memberList[i] = memberList[i + 1];
        }

        memberList[listSize - 1] = nullptr;
    }

    memberListSize--;
}

void shiftObserverListElements(array<Observer*, LAB_ARR_SIZE>& observerList, const int& pos) {
    int listSize = observerListSize;

    if (pos == observerList.max_size() - 1) { // If pos is the last element in labsList
        observerList[pos] = nullptr;
    }
    else if (listSize == 1) { // If pos is the only element in the list
        observerList[pos] = nullptr;
    }
    else {
        for (int i{ pos }; i < listSize - 1; i++) {
            observerList[i] = observerList[i + 1];
        }

        observerList[listSize - 1] = nullptr;
    }

    observerListSize--;
}

void shiftLabListElements(array<Lab*, LAB_ARR_SIZE>& labList, const int& pos) {
    int listSize = labListSize;

    if (pos == labList.max_size() - 1) { // If pos is the last element in labsList
        labList[pos] = nullptr;
    }
    else if (listSize == 1) { // If pos is the only element in the list
        labList[pos] = nullptr;
    }
    else {
        for (int i{ pos }; i < listSize - 1; i++) {
            labList[i] = labList[i + 1];
        }

        labList[listSize - 1] = nullptr;
    }

    labListSize--;
}

/*
This function takes the member and lab parameter and adds them to each others' respective lists.
Preconditions:  none
Postconditions: member has been added to lab's memberList and lab has been added to member's labsList
*/
void attachMemberToLab(Member* member, Lab* lab) {
    member->addLab(lab);
    lab->addMember(member);
}

void detachMemberFromLab(Member* member, Lab* lab) {
    member->removeLab(lab);
    lab->removeMember(member);
}

void detachMember(Member* member) {
    for (int i{ 0 }; i < member->getLabsListSize(); i++) {
        member->getLabsList()[i]->removeMember(member);
    }
}

void attachObserverToLab(Observer* observer, Lab* lab) {
    observer->setAssignedLab(lab);
    lab->setObserver(observer);
}

void deallocateLists(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList,
    array<Lab*, LAB_ARR_SIZE>& labList) {

    for (int i{ 0 }; i < memberListSize; i++) {
        delete memberList[i];
    }

    for (int i{ 0 }; i < observerListSize; i++) {
        delete observerList[i];
    }

    for (int i{ 0 }; i < labListSize; i++) {
        delete labList[i];
    }
}