#include "Lab.h"
#include "Member.h"
#include "Observer.h"

Lab::Lab() {
	this->labID = 0;
	this->type = "NO TYPE";
	this->totalHours = 0;
	this->setObserver(nullptr);
}

Lab::Lab(const int& labID, const string& type, const double& totalHours, Observer* observer) {
	this->setID(labID);
	this->setType(type);
	this->totalHours = totalHours;
	this->setObserver(observer);
}

Lab::Lab(const Lab& lab) {
	this->setID(lab.getID());
	this->setType(lab.getType());
	this->totalHours = lab.getTotalHours();
	this->setObserver(lab.getObserver());
	
	for (int i{ 0 }; i < lab.listSize; i++) {
		this->addMember(lab.memberList[i]);
	}
}

int Lab::getID() const {
	return this->labID;
}

void Lab::setID(const int& id) {
	this->labID = id;
}

string Lab::getType() const {
	return this->type;
}

void Lab::setType(const string& type) {
	this->type = type;
}

double Lab::getTotalHours() const {
	return this->totalHours;
}

void Lab::setTotalHours(const double& totalHours) {
	this->totalHours = totalHours;
}

Observer* Lab::getObserver() const {
	return this->observer;
}

void Lab::setObserver(Observer* observer) {
	this->observer = observer;
}

Member* Lab::getMemberList() const {
	return this->memberList[0];
}

void Lab::addHours(const double& hours) {
	this->totalHours += hours;
}

void Lab::refundHours(const double& hours) {
	this->totalHours -= hours;
}

void Lab::resetHours() {
	this->totalHours = 0;
}

void Lab::addMember(Member* member) {
	if (this->listSize == MAX_MEMBERS) {
		cout << "Failed to add Member. This Lab's Members list is full." << endl << endl;
		return;
	}

	for (int i{ 0 }; i < this->listSize; i++) {
		if (member == this->memberList[i]) {
			cout << "Failed to add Member. Member is already in Lab's Members list." << endl << endl;
			return;
		}
	}

	this->memberList[listSize] = member;
	this->listSize++;
}

void Lab::removeMember(Member* member) {
	if (this->listSize == 0) {
		cout << "Failed to remove Member. This Lab's Member list is empty." << endl << endl;
		return;
	}

	for (int i{ 0 }; i < this->listSize; i++) {
		if (member == this->memberList[i]) {
			this->shiftListElements(i);
			this->listSize--;
			return;
		}
	}

	cout << "Failed to remove Member. Member is not in Lab's Members list." << endl << endl;
}

void Lab::print() {
	if (this->getObserver() != nullptr) {
		cout << left << setw(10) << this->getID() << setw(20) << this->getType() << this->getObserver()->getName() << endl;
	}
	else {
		cout << left << setw(10) << this->getID() << setw(20) << this->getType() << " None Assigned" << endl;
	}
}

void Lab::pullReport() {
	cout << "********************************************" << endl;
	cout << "Lab " << this->getID() << endl;
	cout << "----------------------" << endl;
	cout << "Type: " << this->getType() << endl;
	if (this->getObserver() != nullptr) {
		cout << "Observer: " << this->getObserver()->getName() << " (ID: " << this->getObserver()->getID() << ")" << endl;
	}
	else {
		cout << "Observer: None Assigned" << endl;
	}
	cout << "Total Hours: " << this->getTotalHours() << endl << endl;

	cout << "Members List" << endl;
	cout << "----------------------" << endl;
	if (this->listSize > 0) {
		cout << "Member ID     Name                  Email                            Phone #" << endl;
		cout << "-------------------------------------------------------------------------------" << endl;
		for (int i{ 0 }; i < this->listSize; i++) {
			Member* member = this->memberList[i];
			cout << left << setw(14) << to_string(member->getID()) << setw(22) << member->getName() << setw(33) <<
				member->getEmail() << member->getPhoneNum() << endl;
		}
	}
	else {
		cout << "This Lab has no Members." << endl;
	}
	cout << "********************************************" << endl << endl;
}

Lab& Lab::operator=(const Lab& otherLab) {
	this->setID(otherLab.getID());
	this->setType(otherLab.getType());
	this->totalHours = otherLab.getTotalHours();
	this->setObserver(otherLab.getObserver());

	for (int i{ 0 }; i < otherLab.listSize; i++) {
		this->addMember(otherLab.memberList[i]);
	}

	return *this;
}

bool Lab::operator==(const Lab& otherLab) const {
	return this->getID() == otherLab.getID();
}

void Lab::shiftListElements(const int& pos) {
	if (pos == MAX_MEMBERS - 1) { // If pos is the last element in memberList
		this->memberList[pos] = nullptr;
	}
	else if (this->listSize == 1) { // If pos is the only element in the list
		this->memberList[pos] = nullptr;
	}
	else {
		for (int i{ pos }; i < this->listSize - 1; i++) {
			this->memberList[i] = this->memberList[i + 1];
		}

		this->memberList[this->listSize - 1] = nullptr;
	}
}