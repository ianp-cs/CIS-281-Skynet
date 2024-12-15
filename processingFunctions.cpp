#include "processingFunctions.h"

void clearBuffer(FILE* fp) {
    char ch;
    cin.clear();
    while ((ch = getc(fp)) != '\n' && ch != EOF);
}

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

bool checkIDAvailability(array<Member*, MEMBER_ARR_SIZE>& memberList, array<Observer*, LAB_ARR_SIZE>& observerList, 
    const int& memberID) {

    for (int i{ 0 }; i < memberListSize; i++) {
        if (memberList[i]->getID() == memberID) {
            return false;
        }
    }

    for (int i{ 0 }; i < observerListSize; i++) {
        if (observerList[i]->getID() == memberID) {
            return false;
        }
    }

    return true;
}

bool checkIDAvailability(array<Lab*, LAB_ARR_SIZE>& labList, const int& labID) {
    for (int i{ 0 }; i < labListSize; i++) {
        if (labList[i]->getID() == labID) {
            return false;
        }
    }

    return true;
}