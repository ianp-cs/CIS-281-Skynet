/*
Program: Old Pueblo Lapidary Club Records Management
Created By: Ian Penrose, Marie Perez, Lyes Attalah
Date Created: 11/29/2024
Description: 
*/

#include <iostream>
#include <array>
#include <fstream>
#include <sstream>
#include "Account.h"
#include "Administrator.h"
#include "Lab.h"
#include "Observer.h"
#include "Member.h"
using namespace std;

#define ADMIN_ARR_SIZE 10
#define MEMBER_ARR_SIZE 100
#define LAB_ARR_SIZE 20
#define ADMIN_FILE "administratordata.dat"
#define MEMBER_FILE "memberdata.dat"
#define OBSERVER_FILE "observerdata.dat"
#define LAB_FILE "labdata.dat"
#define LIST_LINK_FILE "listlinkdata.dat"

static int memberListSize{ 0 };
static int observerListSize{ 0 };
static int labListSize{ 0 };

// Startup
void userLogin();
void initializeLists(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList, 
    array<Lab*, LAB_ARR_SIZE>& labList);
void readMemberFile(array<Member*, MEMBER_ARR_SIZE>& memberList, ifstream& memberFile);
void readObserverFile(array<Observer*, LAB_ARR_SIZE>& observerList, ifstream& observerFile);
void readLabFile(array<Lab*, LAB_ARR_SIZE>& labList, ifstream& labFile);
void readListLinkFile(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList,
    array<Lab*, LAB_ARR_SIZE>& labList, ifstream& listLinkFile);

// Main Menu Functions
void memberMenu(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList);
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
void writeToMemberFile(array<Member*, MEMBER_ARR_SIZE>& memberList);
void writeToObserverFile(array<Observer*, LAB_ARR_SIZE>& observerList);
void writeToLabFile(array<Lab*, LAB_ARR_SIZE>& labList);
void writeToListLinkFile(array<Lab*, LAB_ARR_SIZE>& labList);
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
            cout << "Closing the program..." << endl;
            writeToMemberFile(memberList);
            writeToObserverFile(observerList);
            writeToLabFile(labList);
            writeToListLinkFile(labList);
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

Preconditions:  ADMIN_FILE exists and holds at least one administrator entry.
Postconditions: The user gains access to the program.
*/
void userLogin() {
    ifstream adminFile(ADMIN_FILE);
    string line;
    int count = 0;
    array<Administrator*, ADMIN_ARR_SIZE> adminList;
    adminList.fill(nullptr);
    bool loginSuccess{ false };

    if (!adminFile.is_open()) {
        cout << "Failed to find or open Administrator file. Closing program..." << endl << endl;
        exit(1);
    }

    while (getline(adminFile, line) && count < ADMIN_ARR_SIZE) {
        string id, name, userName, password, email;

        istringstream iss(line);
        getline(iss, id, '~');
        getline(iss, name, '~');
        getline(iss, userName, '~');
        getline(iss, password, '~');
        getline(iss, email, '~');

        adminList[count] = new Administrator(stoi(id), name, userName, password, email);
        count++;
    }

    if (count == 0) {
        cout << "No Administrator data found. Closing program..." << endl << endl;
        exit(1);
    }

    cout << "Administrator Login" << endl;
    cout << "-------------------" << endl;

    while (loginSuccess == false) {
        string userName, password;

        cout << "Enter Username: ";
        cin >> userName;
        cout << "Enter Password: ";
        cin >> password;
        cout << endl;

        for (int i{ 0 }; i < count; i++) {
            if (adminList[i]->login(userName, password)) {
                cout << "Login Successful! Welcome, " << adminList[i]->getName() << "." << endl << endl;
                loginSuccess = true;
                break;
            }
        }

        if (loginSuccess == false) {
            cout << "Login failed, try again " << endl << endl;
        }
    }

    for (int i{ 0 }; i < count; i++) {
        delete adminList[i];
    }
    adminFile.close();
}

/*
This function initializes memberList, observerList, and labList with data from their respective files. Members' 
labsLists, Labs' memberLists, Observers' assignedLabs, and Labs' Observers are all attached with the data from the
listLinkData file.
Preconditions:  MEMBER_FILE, observerdata.dat, labdata.dat, and listlinkdata.dat exist and hold data in the correct
                format.
Postconditions: memberList, observerList, and labList are initialized and linked together as necessary.
*/
void initializeLists(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList,
    array<Lab*, LAB_ARR_SIZE>& labList) {

    // Open files
    ifstream memberFile(MEMBER_FILE);
    ifstream observerFile(OBSERVER_FILE);
    ifstream labFile(LAB_FILE);
    ifstream listLinkFile(LIST_LINK_FILE);

   // Verify files are open
    if (!memberFile.is_open()) {
        cout << "Failed to find or open Member file. Closing program..." << endl << endl;
        exit(1);
    }
    if (!observerFile.is_open()) {
        cout << "Failed to find or open Observer file. Closing program..." << endl << endl;
        exit(1);
    }
    if (!labFile.is_open()) {
        cout << "Failed to find or open Lab file. Closing program..." << endl << endl;
        exit(1);
    }
    if (!listLinkFile.is_open()) {
        cout << "Failed to find or open list link file. Closing program..." << endl << endl;
        exit(1);
    }

    // Process files
    readMemberFile(memberList, memberFile);
    readObserverFile(observerList, observerFile);
    readLabFile(labList, labFile);
    readListLinkFile(memberList, observerList, labList, listLinkFile);
    
    // Close files
    memberFile.close();
    observerFile.close();
    labFile.close();
    listLinkFile.close();
}

/*
This function reads the Member file and extracts its data to initialize new Members that are then added to memberList.
Preconditions:  memberFile was opened successfully.
Postconditions: memberList has been initialized.
*/
void readMemberFile(array<Member*, MEMBER_ARR_SIZE>& memberList, ifstream& memberFile) {
    string line;

    while (getline(memberFile, line) && memberListSize < MEMBER_ARR_SIZE) {
        string id, name, email, address, phone, hours;

        istringstream iss(line);
        getline(iss, id, '~');
        getline(iss, name, '~');
        getline(iss, email, '~');
        getline(iss, address, '~');
        getline(iss, phone, '~');
        getline(iss, hours, '~');

        memberList[memberListSize] = new Member(stoi(id), name, email, address, phone, stod(hours));
        memberListSize++;
    }
}

/*
This function reads the Observer file and extracts its data to initialize new Observers that are then added to 
observerList.
Preconditions:  observerFile was opened successfully.
Postconditions: observerList has been initialized.
*/
void readObserverFile(array<Observer*, LAB_ARR_SIZE>& observerList, ifstream& observerFile) {
    string line, id, name, email, address, phone, hours;
    
    while (getline(observerFile, line) && observerListSize < LAB_ARR_SIZE) {
        istringstream iss(line);

        getline(iss, id, '~');
        getline(iss, name, '~');
        getline(iss, email, '~');
        getline(iss, address, '~');
        getline(iss, phone, '~');
        getline(iss, hours, '~');

        observerList[observerListSize] = new Observer(stoi(id), name, email, address, phone, stod(hours));
        observerListSize++;
    }
}

/*
This function reads the Lab file and extracts its data to initialize new Labs that are then added to labList.
Preconditions:  labFile was opened successfully.
Postconditions: labList has been initialized.
*/
void readLabFile(array<Lab*, LAB_ARR_SIZE>& labList, ifstream& labFile) {
    string line, id, type, hours;
    
    while (getline(labFile, line) && labListSize < LAB_ARR_SIZE) {
        istringstream iss(line);

        getline(iss, id, '~');
        getline(iss, type, '~');
        getline(iss, hours, '~');

        labList[labListSize] = new Lab(stoi(id), type, stod(hours), nullptr);
        labListSize++;
    }
}

/*
This function reads the list link file and extracts its data to initialize every Member's labsList and every Lab's 
memberList. Every Observer's assignedLab is set, if they have one, and every Lab's Observer is set, if they have one.
Preconditions:  memberList, observerList, and labList are intialized. listLinkFile was opened successfully.
Postconditions: All Members' labLists are initalized. All Labs' memberLists are initialized. Each Observer with an
                assignedLab and every Lab with an Observer are attached together.
*/
void readListLinkFile(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList,
    array<Lab*, LAB_ARR_SIZE>& labList, ifstream& listLinkFile) {

    string line, labID, observerID, memberID;
    int count{ 0 };

    while (getline(listLinkFile, line) && count < labListSize) {
        Observer* observerTarget = nullptr;
        Member* memberTarget = nullptr;
        istringstream iss(line);

        getline(iss, labID, '~');
        getline(iss, observerID, '~');

        if (stoi(observerID) != 0) { // 0 means there is no Observer assigned to the Lab
            for (int i{ 0 }; i < observerListSize; i++) {
                if (observerList[i]->getID() == stoi(observerID)) {
                    observerTarget = observerList[i];
                    break;
                }
            }

            attachObserverToLab(observerTarget, labList[count]);
        }

        while (getline(iss, memberID, '~')) {
            for (int i{ 0 }; i < memberListSize; i++) {
                if (memberList[i]->getID() == stoi(memberID)) {
                    memberTarget = memberList[i];
                    break;
                }
            }

            attachMemberToLab(memberTarget, labList[count]);
        }

        count++;
    }
}

/*
This function displays the Member Menu and accepts and verifies commands from the user. Valid commands call helper 
functions or return to the main menu.
Preconditions:  memberList and observerList are initialized with data.
Postconditions: The command input by the user is processed.
*/
void memberMenu(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList) {

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
        cout << "8) Refund Member's Lab Hours" << endl;
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
Postconditions: All Members in memberList and observerList are printed to the console.
*/
void printMembersList(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList) {
    cout << "Member ID    Role      Name                  Email                         Address                       "
        " Phone" << endl;
    cout << "---------------------------------------------------------------------------------------------------------"
        "-----------" << endl;

    for (int i{ 0 }; i < observerListSize; i++) {
        observerList[i]->print();
    }

    for (int i{ 0 }; i < memberListSize; i++) {
        memberList[i]->print();
    }

    cout << endl;
}

/*
This helper function takes user input to create a new Member and adds it to memberList.
Preconditions:  The user input Member is not already in memberList.
Postconditions: If the user input data passes validation and the Member does not already exist, the Member is created
                and added to memberList. Otherwise, a relevant error message is printed to the console and control is
                returned to the memberMenu.

TO DO: Add input verification and error handling.
*/
void addMember(array<Member*, MEMBER_ARR_SIZE>& memberList) {
    string userInput;
    int memberID;
    string name;
    string email;
    string address;
    string phoneNum;
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
    phoneNum = userInput;

    cout << "Enter the Member's available lab hours: ";
    getline(cin, userInput);
    cout << endl;
    labHours = stod(userInput);

    memberList[memberListSize] = new Member(memberID, name, email, address, phoneNum, labHours);
    memberListSize++;
}

/*
This helper function edits an existing member in memberList using data input by the user.
Preconditions:  The Member to be edited already exists and is in memberList.
Postconditions: The Member is updated with new data input by the user, if the input passes validation. Otherwise, a 
                relevant error message is printed to the console and control is returned to memberMenu.

TO DO: Add input verification and error handling.
*/
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
            target->setPhoneNum(userInput);
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

/*
This helper function removes an existing member from memberList.
Preconditions:  The Member to be removed exists and is in memberList.
Postconditions: The Member is removed from memberList and memberList's elements are shifted to the left to replace 
                Member. If the Member does not exist, an error message is printed to the console.

TO DO: Add input verification and error handling.
*/
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

/*
This helper function adds lab hours to a Member selected by the user. The number of lab hours added is specified by the
user.
Preconditions:  The Member exists in memberList or observerList. The input lab hours must be a postive value.
Postconditions: The input lab hours is added to the selected Member's total available lab hours. If the input lab hours
                are negative or the selected Member doesn't exist, a relevant error message is printed to the console.

TO DO: Add input verification and error handling.
*/
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
Preconditions:  memberList, observerList, and labList are initialized with data.
Postconditions: The command input by the user is processed.
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

/*
This helper function prints out every Lab in labList.
Preconditions:  labList has been initialized with Labs
Postconditions: All Labs in labList are printed to the console.
*/
void printLabList(array<Lab*, LAB_ARR_SIZE>& labList) {
    cout << "Lab ID    Type                Observer" << endl;
    cout << "----------------------------------------------------" << endl;

    for (int i{ 0 }; i < labListSize; i++) {
        labList[i]->print();
    }

    cout << endl;
}

/*
This helper function takes user input to create a new Lab and adds it to labList.
Preconditions:  The user input Lab is not already in labList.
Postconditions: If the user input data passes validation and the Lab does not already exist, the Lab is created and 
                added to labList. Otherwise, a relevant error message is printed to the console and control is returned
                to the labMenu.

TO DO: Add input verification and error handling.
*/
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

    cout << "Enter the Lab's type: ";
    getline(cin, userInput);
    cout << endl;
    type = userInput;

    labList[labListSize] = new Lab(labID, type, 0, nullptr);
    labListSize++;
}

/*
This helper function edits an existing member in labList using data input by the user.
Preconditions:  The Lab to be edited already exists and is in labList.
Postconditions: The Lab is updated with new data input by the user, if the input passes validation. Otherwise, a
                relevant error message is printed to the console and control is returned to labMenu.

TO DO: Add input verification and error handling.
*/
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

/*
This helper function removes an existing member from memberList.
Preconditions:  The Member to be removed exists and is in memberList.
Postconditions: The Member is removed from memberList and memberList's elements are shifted to the left to replace
                Member. If the Member does not exist, an error message is printed to the console.

TO DO: Add input verification and error handling.
*/
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

/*
This helper function assigns the user input Observer to the user input Lab.
Preconditions:  The Observer and Lab exist and are in their respective lists.
Postconditions: The user input Observer has Lab as its assignedLab and Lab has Observer as its Observer. If the
                Observer already had an assignedLab, it is removed as that Lab's Observer. If the Lab already had an
                Observer, the Observer has Lab removed as its assignedLab.

TO DO: Add input verification and error handling.
*/
void assignObserverToLab(array<Observer*, LAB_ARR_SIZE>& observerList, array<Lab*, LAB_ARR_SIZE>& labList) {
    int observerID, labID;
    Observer* observerTarget = nullptr;
    Lab* labTarget = nullptr;
    
    cout << "Enter the ID of the Observer to be assigned or enter \"0\" to return: ";
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
            cout << "There is no Observer with ID \"" << observerID << "\". Returning to previous menu..." << endl 
                << endl;
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
        cout << "Observer " << observerID << " is already assigned to Lab " << labID << ". Returning to previous " 
            "menu..."  << endl << endl;
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

/*
This helper function removes the association between an Observer and their assignedLab, and vice-versa.
Preconditions:  The Observer exists and it has an assignedLab. The assignedLab has Observer as its Observer.
Postconditions: The user input Observer has no assignedLab and its prior assignedLab does not have Observer as its
                Observer.

TO DO: Add input verification and error handling.
*/
void unassignObserver(array<Observer*, LAB_ARR_SIZE>& observerList) {
    int observerID;
    Observer* observerTarget = nullptr;

    cout << "Enter the ID of the Observer to be unassigned or enter \"0\" to return: ";
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
            cout << "There is no Observer with ID \"" << observerID << "\". Returning to previous menu..." << endl 
                << endl;
            return;
        }
        else if (observerTarget->getAssignedLab() == nullptr) {
            cout << "Observer " << observerID << " is not assigned to any Lab. Returning to previous menu..." << endl 
                << endl;
        }
        else {
            observerTarget->getAssignedLab()->setObserver(nullptr);
            observerTarget->setAssignedLab(nullptr);
            cout << "Successfully unassigned Observer " << observerID << " from their assigned Lab." << endl << endl;
        }
    }
}

/*
This helper function assigns a user input Member to a user input Lab, linking the two together via their labsList and memberList.
Preconditions:  The user input Member and Lab both exist, and the Member is not in Lab's memberList and the Lab is not
                   in the Member's labList.
Postconditions: The user input Member is in the user input Lab's memberList and the Lab is in the Member's labsList.

TO DO: Add input verification and error handling.
*/
void assignMemberToLab(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList,
    array<Lab*, LAB_ARR_SIZE>& labList) {

    int memberID, labID;
    Member* memberTarget = nullptr;
    Lab* labTarget = nullptr;

    cout << "Enter the ID of the Member to be assigned or enter \"0\" to return: ";
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

/*
This helper function unassigns a user input Member from a user input Lab, removing them from the others' labsList and 
memberList, respectively.
Preconditions:  The user input Member and Lab both exist, and the Member is in Lab's memberList and the Lab is in the
                Member's labList.
Postconditions: The user input Member is in no longer in the user input Lab's memberList and the Lab is no longer in 
                the Member's labsList.

TO DO: Add input verification and error handling.
*/
void unassignMemberFromLab(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList,
    array<Lab*, LAB_ARR_SIZE>& labList) {

    int memberID, labID;
    Member* memberTarget = nullptr;
    Lab* labTarget = nullptr;

    cout << "Enter the ID of the Member to be assigned or enter \"0\" to return: ";
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
Preconditions:  memberList, observerList, and labList are initialized with data.
Postconditions: The command input by the user is processed.
*/
void reportMenu(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList, array<Lab*, 
    LAB_ARR_SIZE>& labList) {

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
Preconditions:  The input Member exists in memberList or observerList.
Postconditions: Every Member's report is printed to the console.

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
Preconditions:  The input Lab exists in labList.
Postconditions: Every Lab's report is printed to the console.

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
Preconditions:  None
Postconditions: The buffer is cleared of any remaining characters.
*/
void clearBuffer(FILE* fp) {
    char ch;
    while ((ch = getc(fp)) != '\n' && ch != EOF);
}

/*
This function deallocates the memory of the memberList element at pos and shift every element to the right of it back 
to the left, if there are any.
Preconditions:  memberList has been intialized with data and pos is within the bounds of memberList.
Postconditions: The memberList element at pos is set to a nullptr or has been overwritten with the element to its 
                right. Every element to the right of pos, if any, are shifted to the left. The memory allocated for 
                the element is deallocated.
*/
void shiftMemberListElements(array<Member*, MEMBER_ARR_SIZE>& memberList, const int& pos) {
    int listSize = memberListSize;

    if (pos == memberList.max_size() - 1) { // If pos is the last element in labsList
        delete memberList[pos];
        memberList[pos] = nullptr;
    }
    else if (listSize == 1) { // If pos is the only element in the list
        delete memberList[pos];
        memberList[pos] = nullptr;
    }
    else {
        delete memberList[pos];
        for (int i{ pos }; i < listSize - 1; i++) {
            memberList[i] = memberList[i + 1];
        }

        memberList[listSize - 1] = nullptr;
    }

    memberListSize--;
}

/*
This function deallocates the memory of the observerList element at pos and shift every element to the right of it back
to the left, if there are any.
Preconditions:  observerList has been intialized with data and pos is within the bounds of observerList.
Postconditions: The observerList element at pos is set to a nullptr or has been overwritten with the element to its
                right. Every element to the right of pos, if any, are shifted to the left. The memory allocated for
                the element is deallocated.
*/
void shiftObserverListElements(array<Observer*, LAB_ARR_SIZE>& observerList, const int& pos) {
    int listSize = observerListSize;

    if (pos == observerList.max_size() - 1) { // If pos is the last element in labsList
        delete observerList[pos];
        observerList[pos] = nullptr;
    }
    else if (listSize == 1) { // If pos is the only element in the list
        delete observerList[pos];
        observerList[pos] = nullptr;
    }
    else {
        delete observerList[pos];
        for (int i{ pos }; i < listSize - 1; i++) {
            observerList[i] = observerList[i + 1];
        }

        observerList[listSize - 1] = nullptr;
    }

    observerListSize--;
}

/*
This function deallocates the memory of the labList element at pos and shift every element to the right of it back to 
the left, if there are any.
Preconditions:  labList has been intialized with data and pos is within the bounds of labList.
Postconditions: The labList element at pos is set to a nullptr or has been overwritten with the element to its right. 
                Every element to the right of pos, if any, are shifted to the left. The memory allocated for
                the element is deallocated.
*/
void shiftLabListElements(array<Lab*, LAB_ARR_SIZE>& labList, const int& pos) {
    int listSize = labListSize;

    if (pos == labList.max_size() - 1) { // If pos is the last element in labsList
        delete labList[pos];
        labList[pos] = nullptr;
    }
    else if (listSize == 1) { // If pos is the only element in the list
        delete labList[pos];
        labList[pos] = nullptr;
    }
    else {
        delete labList[pos];
        for (int i{ pos }; i < listSize - 1; i++) {
            labList[i] = labList[i + 1];
        }

        labList[listSize - 1] = nullptr;
    }

    labListSize--;
}

/*
This function takes the member and lab parameter and adds them to each others' respective lists.
Preconditions:  None
Postconditions: member has been added to lab's memberList and lab has been added to member's labsList.
*/
void attachMemberToLab(Member* member, Lab* lab) {
    member->addLab(lab);
    lab->addMember(member);
}

/*
This function takes the member and lab parameter and removes them to each others' respective lists. Verification that
they are in each others' lists is performed before this function is called.
Preconditions:  member is in lab's memberList and lab is in member's labsList.
Postconditions: member has been removed lab's memberList and lab has been removed from member's labsList.
*/
void detachMemberFromLab(Member* member, Lab* lab) {
    member->removeLab(lab);
    lab->removeMember(member);
}

/*
This function takes the member parameter and removes it from all of the Labs in its labList.
Preconditions:  None
Postconditions: Every Lab in member's labsList do not have member in their memberLists.
*/
void detachMember(Member* member) {
    for (int i{ 0 }; i < member->getLabsListSize(); i++) {
        member->getLabsList()[i]->removeMember(member);
    }
}

/*
This function sets observer to be lab's Observer and lab to be observer's assignedLab.
Preconditions:  None
Postconditions: observer is lab's Observer and lab is observer's assignedLab.
*/
void attachObserverToLab(Observer* observer, Lab* lab) {
    observer->setAssignedLab(lab);
    lab->setObserver(observer);
}

/*
This function writes data from the elements of memberList to the MEMBER_FILE. '~' are added to help with reading the
file at program start. Content in MEMBER_FILE is overwritten with this data.
Preconditions:  None
Postconditions: MEMBER_FILE has been updated with the data from memberList
*/
void writeToMemberFile(array<Member*, MEMBER_ARR_SIZE>& memberList) {
    ofstream memberFile(MEMBER_FILE, ios::trunc);

    for (int i{ 0 }; i < memberListSize; i++) {
        memberFile << memberList[i]->getID() << "~" << memberList[i]->getName() << "~" << memberList[i]->getEmail() <<
            "~" << memberList[i]->getAddress() << "~" << memberList[i]->getPhoneNum() << "~" << 
            memberList[i]->getLabHours() << "~";

        // Add a newline for each entry except the last.
        if (i < memberListSize - 1) {
            memberFile << endl;
         }
    }

    memberFile.close();
}

/*
This function writes data from the elements of observerList to the OBSERVER_FILE. '~' are added to help with reading 
the file at program start. Content in OBSERVER_FILE is overwritten with this data.
Preconditions:  None
Postconditions: OBSERVER_FILE has been updated with the data from observerList
*/
void writeToObserverFile(array<Observer*, LAB_ARR_SIZE>& observerList) {
    ofstream observerFile(OBSERVER_FILE, ios::trunc);

    for (int i{ 0 }; i < observerListSize; i++) {
        observerFile << observerList[i]->getID() << "~" << observerList[i]->getName() << "~" << 
            observerList[i]->getEmail() << "~" << observerList[i]->getAddress() << "~" << 
            observerList[i]->getPhoneNum() << "~" << observerList[i]->getLabHours() << "~";

        // Add a newline for each entry except the last.
        if (i < observerListSize - 1) {
            observerFile << endl;
        }
    }

    observerFile.close();
}

/*
This function writes data from the elements of memberList to the LAB_FILE. '~' are added to help with reading the
file at program start. Content in LAB_FILE is overwritten with this data.
Preconditions:  None
Postconditions: LAB_FILE has been updated with the data from labList
*/
void writeToLabFile(array<Lab*, LAB_ARR_SIZE>& labList) {
    ofstream labFile(LAB_FILE, ios::trunc);

    for (int i{ 0 }; i < labListSize; i++) {
        labFile << labList[i]->getID() << "~" << labList[i]->getType() << "~" << labList[i]->getTotalHours() << "~";

        // Add a newline for each entry except the last.
        if (i < labListSize - 1) {
            labFile << endl;
        }
    }

    labFile.close();
}

/*
This function writes data from the elements of labList to the LIST_LINK_FILE. '~' are added to help with reading the
file at program start. Content in LIST_LINK_FILE is overwritten with this data. The content of this file provides
associations between Labs, Members, and Observers using their respective IDs.
Preconditions:  None
Postconditions: LIST_LINK_FILE has been updated with the data from labList
*/
void writeToListLinkFile(array<Lab*, LAB_ARR_SIZE>& labList) {

    ofstream listLinkFile(LIST_LINK_FILE, ios::trunc);

    for (int i{ 0 }; i < labListSize; i++) {
        listLinkFile << labList[i]->getID() << "~";

        if (labList[i]->getObserver() == nullptr) {
            listLinkFile << "0~";
        }
        else {
            listLinkFile << labList[i]->getObserver()->getID() << "~";
        }

        for (int j{ 0 }; j < labList[i]->getMemberListSize(); j++) {
            listLinkFile << labList[i]->getMemberList()[j]->getID() << "~";
        }

        // Add a newline for each entry except the last.
        if (i < labListSize - 1) {
            listLinkFile << endl;
        }
    }

    listLinkFile.close();
}

/*
This function deallocates all of the memory allocated for the elements in memberList, observerList, and labList.
Preconditions:  All of the elements in memberList, observerList, and labList were created with keyword new.
Postconditions: Every element in memberList, observerList, and labList have had their memory deallocated.
*/
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