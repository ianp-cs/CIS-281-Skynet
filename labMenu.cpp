#include "labMenu.h"

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
    cout << "Lab ID    Type                Observer" << endl;
    cout << "----------------------------------------------------" << endl;

    for (int i{ 0 }; i < labListSize; i++) {
        labList[i]->print();
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

    cout << "Enter the Lab's type: ";
    getline(cin, userInput);
    cout << endl;
    type = userInput;

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
            "menu..." << endl << endl;
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