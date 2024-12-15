/*
Program: Old Pueblo Lapidary Club Records Management
Created By: Ian Penrose, Marie Perez, Lyes Attalah
Date Created: 11/29/2024
Last Updated: 12/14/2024
Description: 
*/

#include <iostream>
#include <array>
#include <fstream>
#include <sstream>
#include "Administrator.h"
#include "Lab.h"
#include "Observer.h"
#include "Member.h"
#include "defines.h"
#include "processingFunctions.h"
#include "memberMenu.h"
#include "labMenu.h"
#include "reportMenu.h"
using namespace std;

// Startup + Closing
void initializeLists(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList, 
    array<Lab*, LAB_ARR_SIZE>& labList);
void deallocateLists(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList,
    array<Lab*, LAB_ARR_SIZE>& labList);

// File Handling
void userLogin();
void readMemberFile(array<Member*, MEMBER_ARR_SIZE>& memberList, ifstream& memberFile);
void readObserverFile(array<Observer*, LAB_ARR_SIZE>& observerList, ifstream& observerFile);
void readLabFile(array<Lab*, LAB_ARR_SIZE>& labList, ifstream& labFile);
void readListLinkFile(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList,
    array<Lab*, LAB_ARR_SIZE>& labList, ifstream& listLinkFile);
void writeToMemberFile(array<Member*, MEMBER_ARR_SIZE>& memberList);
void writeToObserverFile(array<Observer*, LAB_ARR_SIZE>& observerList);
void writeToLabFile(array<Lab*, LAB_ARR_SIZE>& labList);
void writeToListLinkFile(array<Lab*, LAB_ARR_SIZE>& labList);

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

        if (cin) {
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
                cout << "Invalid input. Please try again." << endl << endl;
            }
        }
        else {
            clearBuffer(stdin);
            validInput = false;
            cout << "Invalid input. Please try again." << endl << endl;
        }
    }
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
        cout << "Failed to find or open Member file. Closing program..." << endl;
        exit(1);
    }
    if (!observerFile.is_open()) {
        cout << "Failed to find or open Observer file. Closing program..." << endl;
        exit(1);
    }
    if (!labFile.is_open()) {
        cout << "Failed to find or open Lab file. Closing program..." << endl;
        exit(1);
    }
    if (!listLinkFile.is_open()) {
        cout << "Failed to find or open list link file. Closing program..." << endl;
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
        adminList[i] = nullptr;
    }
    adminFile.close();
}

/*
This function reads the Member file and extracts its data to initialize new Members that are then added to memberList.
Preconditions:  memberFile was opened successfully.
Postconditions: memberList has been initialized.
*/
void readMemberFile(array<Member*, MEMBER_ARR_SIZE>& memberList, ifstream& memberFile) {
    string line;

    try {
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
    catch (const exception& e) {
        cout << "There was an error reading data from " << MEMBER_FILE << ". Please verify the integrity of the file. "
            "Closing program..." << endl << endl;
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
    
    try {
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
    catch (const exception& e) {
        cout << "There was an error reading data from " << OBSERVER_FILE << ". Please verify the integrity of the "
            "file. Closing program..." << endl << endl;
    }
}

/*
This function reads the Lab file and extracts its data to initialize new Labs that are then added to labList.
Preconditions:  labFile was opened successfully.
Postconditions: labList has been initialized.
*/
void readLabFile(array<Lab*, LAB_ARR_SIZE>& labList, ifstream& labFile) {
    string line, id, type, hours;
    
    try {
        while (getline(labFile, line) && labListSize < LAB_ARR_SIZE) {
            istringstream iss(line);

            getline(iss, id, '~');
            getline(iss, type, '~');
            getline(iss, hours, '~');

            labList[labListSize] = new Lab(stoi(id), type, stod(hours), nullptr);
            labListSize++;
        }
    }
    catch (const exception& e) {
        cout << "There was an error reading data from " << LAB_FILE << ". Please verify the integrity of the file. "
            "Closing program..." << endl << endl;
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

    try {
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
    catch (const exception& e) {
        cout << "There was an error reading data from " << LIST_LINK_FILE << ". Please verify the integrity of the "
            "file. Closing program..." << endl << endl;
    }
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