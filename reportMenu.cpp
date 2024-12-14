#include "reportMenu.h"

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

void pullAllLabsReport(array<Lab*, LAB_ARR_SIZE>& labList) {
    cout << "Lab Reports:" << endl;

    for (int i{ 0 }; i < labListSize; i++) {
        labList[i]->pullReport();
    }
}