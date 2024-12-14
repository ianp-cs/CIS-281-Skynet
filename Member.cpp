#include "Member.h"
#include "observer.h"
#include "Lab.h"

Member::Member() : Account() {
	this->labHours = 0.0;
}

Member::Member(const int& accountID, const string& name, const string& email, const string& address, 
	const string& phoneNum, const double& labHours) : Account(accountID, name, email, address, phoneNum) {

	this->labHours = labHours;
}

Member::Member(const Member& member) {
	this->setID(member.getID());
	this->setName(member.getName());
	this->setEmail(member.getEmail());
	this->setAddress(member.getAddress());
	this->setPhoneNum(member.getPhoneNum());
	this->labHours = member.getLabHours();

	for (int i{ 0 }; i < member.listSize; i++) {
		this->addLab(member.labsList[i]);
	}
}

Lab** Member::getLabsList() {
	return this->labsList;
}

int Member::getLabsListSize() const {
	return this->listSize;
}

double Member::getLabHours() const {
	return this->labHours;
}

void Member::setLabHours(const double& labHours) {
	this->labHours = labHours;
}

void Member::addLab(Lab* lab) {
	if (this->listSize == MAX_LABS) {
		cout << "Failed to add lab. This Member's Labs list is full." << endl << endl;
		return;
	}

	for (int i{ 0 }; i < this->listSize; i++) {
		if (lab == this->labsList[i]) {
			cout << "Failed to add Lab. Lab is already in Member's Labs list." << endl << endl;
			return;
		}
	}

	this->labsList[listSize] = lab;
	this->listSize++;
}

void Member::removeLab(Lab* lab) {
	if (this->listSize == 0) {
		cout << "Failed to remove Lab. This Member's Labs list is empty." << endl << endl;
		return;
	}

	for (int i{ 0 }; i < this->listSize; i++) {
		if (lab == this->labsList[i]) {
			this->shiftListElements(i);
			this->listSize--;
			return;
		}
	}

	cout << "Failed to remove Lab. Lab is not in Member's Labs list." << endl << endl;
}

bool Member::hasLab(Lab* lab) {
	for (int i{ 0 }; i < listSize; i++) {
		if (this->getLabsList()[i] == lab) {
			return true;
		}
	}

	return false;
}

void Member::spendLabHours(const double& hours) {
	this->labHours -= hours;
}

void Member::refundLabHours(const double& hours) {
	this->labHours += hours;
}

void Member::print() const {
	cout << left << setw(13) << this->getID() << setw(10) << "Member" << setw(22) << this->getName() << setw(30) << 
		this->getEmail() << setw(31) << this->getAddress() << this->getPhoneNum() << endl;
}

void Member::pullReport() const {
	cout << "********************************************" << endl;
	cout << this->getName() << endl;
	cout << "----------------------" << endl;
	cout << "ID: " << this->getID() << endl;
	cout << "Email: " << this->getEmail() << endl;
	cout << "Address: " << this->getAddress() << endl;
	cout << "Phone: " << this->getPhoneNum() << endl;
	cout << "Available Lab Hours: " << this->getLabHours() << endl << endl;

	cout << "Labs List" << endl;
	cout << "----------------------" << endl;
	if (this->listSize > 0) {
		cout << "Lab ID     Lab Type          Observer" << endl;
		cout << "--------------------------------------------" << endl;
		for (int i{ 0 }; i < this->listSize; i++) {
			Lab* lab = this->labsList[i];
			if (lab->getObserver() != nullptr) {
				cout << left << setw(11) << to_string(lab->getID()) << setw(18) << lab->getType() <<
					lab->getObserver()->getName() << endl;
			}
			else {
				cout << left << setw(11) << to_string(lab->getID()) << setw(18) << lab->getType() <<
					"None Assigned" << endl;
			}
		}
	}
	else {
		cout << "This Member is not attending any Labs." << endl;
	}
	cout << "********************************************" << endl << endl;
}

bool Member::operator==(const Member& otherMember) const {
	return this->getID() == otherMember.getID();
}

Member& Member::operator=(const Member& otherMember) {
	this->setID(otherMember.getID());
	this->setName(otherMember.getName());
	this->setEmail(otherMember.getEmail());
	this->setAddress(otherMember.getAddress());
	this->setPhoneNum(otherMember.getPhoneNum());
	this->labHours = otherMember.getLabHours();

	for (int i{ 0 }; i < otherMember.listSize; i++) {
		this->addLab(otherMember.labsList[i]);
	}

	return *this;
}

void Member::shiftListElements(const int& pos) {
	if (pos == MAX_LABS - 1) { // If pos is the last element in labsList
		this->labsList[pos] = nullptr;
	}
	else if (this->listSize == 1) { // If pos is the only element in the list
		this->labsList[pos] = nullptr;
	}
	else {
		for (int i{ pos }; i < this->listSize - 1; i++) {
			this->labsList[i] = this->labsList[i + 1];
		}

		this->labsList[this->listSize - 1] = nullptr;
	}
}