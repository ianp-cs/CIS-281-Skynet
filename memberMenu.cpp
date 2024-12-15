#include "memberMenu.h"

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

        if (cin) {
            switch (userInput) {
            case 1:
                printMembersList(memberList, observerList);
                break;
            case 2:
                addMember(memberList, observerList);
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
        else {
            clearBuffer(stdin);
            validInput = false;
            cout << "Invalid input. Please try again." << endl << endl;
        }
    }
}

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

void addMember(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList) {
    string userInput;
    bool validInput{ false };
    int memberID;
    string name;
    string email;
    string address;
    string phoneNum;
    double labHours;

    clearBuffer(stdin);

    cout << "Adding new Club Member..." << endl << endl;

    while (validInput == false) {
        cout << "Enter the Member's ID or enter \"0\" to return: ";
        getline(cin, userInput);
        cout << endl;

        try {
            if (stoi(userInput) == 0) {
                cout << endl;
                return;
            }
            memberID = stoi(userInput);

            if (checkIDAvailability(memberList, observerList, memberID)) {
                validInput = true;
            }
            else {
                cout << "Member ID " << memberID << " is already assigned. Please try a different ID." << endl << endl;
            }
        }
        catch (const exception& e) {
            cout << "Invalid input. Member ID must be a number. Please try again." << endl << endl;
        }
    }

    validInput = false;

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

    while (validInput == false) {
        cout << "Enter the Member's phone number (digits only, include area code): ";
        getline(cin, userInput);
        cout << endl;

        try {
            phoneNum = userInput;
            stod(userInput);    // Test that the input is a number, no special characters or spaces

            if (userInput.length() == 10) {
                validInput = true;
            }
            else {
                cout << "Invalid input. Phone number must be 10 digits, include the area code. Please try again" << 
                    endl << endl;
            }
        }
        catch (const exception& e) {
            cout << "Invalid input. Phone number must be a number with no special characters or spaces. Please try "
                "again." << endl << endl;
        }
    }

    validInput = true;

    while (validInput == false) {
        cout << "Enter the Member's available lab hours: ";
        getline(cin, userInput);
        cout << endl;

        try {
            labHours = stod(userInput);
            validInput = true;
        }
        catch (const exception& e) {
            cout << "Invalid input. Member's lab hours must be a number. Please try again." << endl << endl;
        }
    }

    memberList[memberListSize] = new Member(memberID, name, email, address, phoneNum, labHours);
    memberListSize++;
}

void editMember(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList) {
    int memberID;
    Member* target{ nullptr };
    string userInput;
    bool validInput{ false };

    clearBuffer(stdin);

    while (validInput == false) {
        cout << "Enter the Member's ID to edit or enter \"0\" to return: ";
        getline(cin, userInput);
        cout << endl;

        try {
            if (stoi(userInput) == 0) {
                cout << endl;
                return;
            }
            memberID = stoi(userInput);
            validInput = true;
        }
        catch (const exception& e) {
            cout << "Invalid input. Member ID must be a number. Please try again." << endl << endl;
        }
    }

    validInput = false;

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
        cout << "For the following prompts, enter a new value if the data needs to be changed, otherwise hit ENTER to " 
            "skip." << endl << endl;

        while (validInput == false) {
            cout << "Enter the Member's ID: ";
            getline(cin, userInput);
            cout << endl;
            if (userInput != "") {
                try {
                    if (checkIDAvailability(memberList, observerList, stoi(userInput))) {
                        target->setID(stoi(userInput));
                        validInput = true;
                    }
                    else {
                        cout << "Member ID " << stoi(userInput) << " is already assigned. Please try a different ID." 
                            << endl << endl;
                    }
                }
                catch (const exception& e) {
                    cout << "Invalid input. Member ID must be a number. Please try again." << endl << endl;
                }
            }
            else {
                validInput = true;
            }
        }

        validInput = false;

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

        while (validInput == false) {
            cout << "Enter the Member's phone number (digits only, include area code): ";
            getline(cin, userInput);
            cout << endl;

            if (userInput != "") {
                try {
                    stod(userInput);    // Test that the input is a number, no special characters or spaces

                    if (userInput.length() == 10) {
                        target->setPhoneNum(userInput);
                        validInput = true;
                    }
                    else {
                        cout << "Invalid input. Phone number must be 10 digits, include the area code. Please try again" <<
                            endl << endl;
                    }
                }
                catch (const exception& e) {
                    cout << "Invalid input. Phone number must be a number with no special characters or spaces. Please try "
                        "again." << endl << endl;
                }
            }
            else {
                validInput = true;
            }
        }

        validInput = false;

        while (validInput == false) {
            if (userInput != "") {
                cout << "Enter the Member's available lab hours: ";
                getline(cin, userInput);
                cout << endl;

                try {
                    target->setLabHours(stod(userInput));
                    validInput = true;
                }
                catch (const exception& e) {
                    cout << "Invalid input. Member's lab hours must be a number. Please try again." << endl << endl;
                }
            }
            else {
                validInput = true;
            }
        }
    }
    else {
        cout << "There is no Member with ID \"" << memberID << "\". Returning to previous menu..." << endl << endl;
    }
}

void removeMember(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList) {
    string userInput;
    int memberID;
    bool validInput{ false };

    clearBuffer(stdin);

    while (validInput == false) {
        cout << "Enter the ID of the Member to remove them or enter \"0\" to return: ";
        getline(cin, userInput);
        cout << endl;

        try {
            if (stoi(userInput) == 0) {
                cout << endl;
                return;
            }
            memberID = stoi(userInput);
            validInput = true;
        }
        catch (const exception& e) {
            cout << "Invalid input. Member ID must be a number. Please try again." << endl << endl;
        }
    }

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
    string userInput;
    int memberID;
    bool validInput{ false };

    cout << "Entering the ID of a Member will promote them to Observer, if they are not already one. Otherwise, if " <<
        "the ID is of an Observer, they will be demoted to Member. Enter \"0\" to return to the previous menu." << endl << endl;

    clearBuffer(stdin);

    while (validInput == false) {
        cout << "Enter a Member's ID to promote/demote them: ";
        getline(cin, userInput);
        cout << endl;

        try {
            if (stoi(userInput) == 0) {
                cout << endl;
                return;
            }
            memberID = stoi(userInput);
            validInput = true;
        }
        catch (const exception& e) {
            cout << "Invalid input. Member ID must be a number. Please try again." << endl << endl;
        }
    }

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

                if (observerList[i]->getAssignedLab() != nullptr) {
                    observerList[i]->getAssignedLab()->setObserver(nullptr);
                }
                shiftObserverListElements(observerList, i);

                cout << "Member " << memberID << " successfully demoted to Member." << endl << endl;
                return;
            }
        }

        cout << "There is no Member with ID \"" << memberID << "\". Returning to previous menu..." << endl << endl;
    }
}

void addMemberLabHours(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList) {
    string userInput;
    int memberID;
    bool validInput{ false };
    Member* target{ nullptr };
    double labHours;

    clearBuffer(stdin);

    while (validInput == false) {
        cout << "Enter a Member's ID to add Lab hours or enter \"0\" to return: ";
        getline(cin, userInput);
        cout << endl;

        try {
            if (stoi(userInput) == 0) {
                cout << endl;
                return;
            }
            memberID = stoi(userInput);
            validInput = true;
        }
        catch (const exception& e) {
            cout << "Invalid input. Member ID must be a number. Please try again." << endl << endl;
        }
    }

    validInput = false;

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
        while (validInput == false) {
            cout << "Enter the number of hours to add to Member " << memberID << " total Lab hours: ";
            getline(cin, userInput);
            cout << endl;

            try {
                labHours = stod(userInput);

                if (labHours >= 0) {
                    validInput = true;
                }
                else {
                    cout << "Invalid input. Lab hours must be a positive value. Please try again." << endl << endl;
                }
            }
            catch (const exception& e) {
                cout << "Invalid input. Member's lab hours must be a number. Please try again." << endl << endl;
            }
        }

        target->refundLabHours(labHours);
        cout << fixed << setprecision(2);
        cout << "Successfully added " << labHours << " hours to Member " << memberID << "'s balance." << endl << endl;
    }

    cout << "There is no Member with ID \"" << memberID << "\". Returning to previous menu..." << endl << endl;
}

void spendMemberLabHours(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList) {
    int memberID, labID;
    bool validInput{ false };
    Member* memberTarget{ nullptr };
    Lab* labTarget{ nullptr };
    string userInput;
    double labHours;

    clearBuffer(stdin);

    while (validInput == false) {
        cout << "Enter a Member's ID to spend Lab hours or enter \"0\" to return: ";
        getline(cin, userInput);
        cout << endl;

        try {
            if (stoi(userInput) == 0) {
                cout << endl;
                return;
            }
            memberID = stoi(userInput);
            validInput = true;
        }
        catch (const exception& e) {
            cout << "Invalid input. Member ID must be a number. Please try again." << endl << endl;
        }
    }

    validInput = false;

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

    while (validInput == false) {
        cout << "Enter the ID of the Lab where the Lab hours are spent: ";
        getline(cin, userInput);
        cout << endl;

        try {
            if (stoi(userInput) == 0) {
                cout << endl;
                return;
            }
            labID = stoi(userInput);
            validInput = true;
        }
        catch (const exception& e) {
            cout << "Invalid input. Lab ID must be a number. Please try again." << endl << endl;
        }
    }

    validInput = false;

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

    while (validInput == false) {
        cout << "Member " << memberID << "'s current balance: " << memberTarget->getLabHours() << " hours." << endl;
        cout << "Lab " << labID << "'s current total: " << labTarget->getTotalHours() << " hours." << endl << endl;
        cout << "Enter the number of hours to be spent by Member " << memberID << " for Lab " << labID << ": ";
        getline(cin, userInput);
        cout << endl;

        try {
            labHours = stod(userInput);

            if (labHours >= 0) {
                validInput = true;
            }
            else {
                cout << "Invalid input. Lab hours must be a positive value. Please try again." << endl << endl;
            }
        }
        catch (const exception& e) {
            cout << "Invalid input. Member's lab hours must be a number. Please try again." << endl << endl;
        }
    }

    memberTarget->spendLabHours(labHours);
    labTarget->addHours(labHours);
    cout << "Successfully spent " << labHours << " of Member " << memberID << "'s Lab hours for Lab " << labID << "."
        << endl << endl;
    cout << "Member " << memberID << "'s balance is now " << memberTarget->getLabHours() << " hours." << endl;
    cout << "Lab " << labID << "'s total hours is now " << labTarget->getTotalHours() << " hours." << endl << endl;
}

void refundMemberLabHours(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList) {
    int memberID, labID;
    bool validInput{ false };
    Member* memberTarget{ nullptr };
    Lab* labTarget{ nullptr };
    string userInput;
    double labHours;

    clearBuffer(stdin);

    while (validInput == false) {
        cout << "Enter a Member's ID to refund Lab hours or enter \"0\" to return: ";
        getline(cin, userInput);
        cout << endl;

        try {
            if (stoi(userInput) == 0) {
                cout << endl;
                return;
            }
            memberID = stoi(userInput);
            validInput = true;
        }
        catch (const exception& e) {
            cout << "Invalid input. Member ID must be a number. Please try again." << endl << endl;
        }
    }

    validInput = false;

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

    while (validInput == false) {
        cout << "Enter the ID of the Lab where the Lab hours are refunded from: ";
        getline(cin, userInput);
        cout << endl;

        try {
            if (stoi(userInput) == 0) {
                cout << endl;
                return;
            }
            labID = stoi(userInput);
            validInput = true;
        }
        catch (const exception& e) {
            cout << "Invalid input. Lab ID must be a number. Please try again." << endl << endl;
        }
    }

    validInput = false;

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

    while (validInput == false) {
        cout << "Member " << memberID << "'s current balance: " << memberTarget->getLabHours() << " hours." << endl;
        cout << "Lab " << labID << "'s current total: " << labTarget->getTotalHours() << " hours." << endl << endl;
        cout << "Enter the number of hours to be refunded to Member " << memberID << " from Lab " << labID << ": ";
        getline(cin, userInput);
        cout << endl;

        try {
            labHours = stod(userInput);

            if (labHours >= 0) {
                validInput = true;
            }
            else {
                cout << "Invalid input. Lab hours must be a positive value. Please try again." << endl << endl;
            }
        }
        catch (const exception& e) {
            cout << "Invalid input. Member's lab hours must be a number. Please try again." << endl << endl;
        }
    }

    memberTarget->refundLabHours(labHours);
    labTarget->refundHours(labHours);
    cout << "Successfully refunded " << labHours << " hours to Member " << memberID << "'s balance from Lab " <<
        labID << "." << endl << endl;
    cout << "Member " << memberID << "'s balance is now " << memberTarget->getLabHours() << " hours." << endl;
    cout << "Lab " << labID << "'s total hours is now " << labTarget->getTotalHours() << " hours." << endl << endl;
}