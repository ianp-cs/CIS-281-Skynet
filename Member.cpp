#include "Member.h"

Member::Member() : Account() {
	this->labHours = 0.0;
}

Member::Member(int accountID, string name, string email, string address, int phoneNum, double labHours) :
	Account(accountID, name, email, address, phoneNum) {

	this->labHours = labHours;
}

list<Lab> Member::getLabList() const {
	return this->labList;
}

double Member::getLabHours() const {
	return this->labHours;
}

void Member::addLab(Lab lab) {
	this->labList.push_back(lab);
}

void Member::removeLab(Lab lab) {
	this->labList.remove(lab);
}

void Member::spendLabHours(double hours) {
	this->labHours -= hours;
}

void Member::refundLabHours(double hours) {
	this->labHours += hours;
}

string Member::toString() const {
	// Add and adjust formatting as necessary
	return to_string(this->getID()) + " Member " + this->getName() + " " + this->getEmail() + " " + this->getAddress() + 
		" " + to_string(this->getPhoneNum());
}

void Member::pullReport() const {
	cout << "***********************" << endl;
	cout << this->getName() << endl;
	cout << "-----------------------" << endl;
	cout << "ID: " << this->getID() << endl;
	cout << "Email: " << this->getEmail() << endl;
	cout << "Address: " << this->getAddress() << endl;
	cout << "Phone: " << this->getPhoneNum() << endl;
	cout << "Available Lab Hours: " << this->getLabHours() << endl << endl;

	cout << "Registered Labs" << endl;
	cout << "-----------------------" << endl;
	for (list<Lab>::iterator lab = this->getLabList().begin(); lab != this->getLabList().end(); lab++) {
		cout << lab->toString() << endl;
	}
	cout << "***********************" << endl << endl;
}