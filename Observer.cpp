#include "Observer.h"

Observer::Observer() : Member() {
	//this->setAssignedLab(Lab());
}

Observer::Observer(int accountID, string name, string email, string address, int phoneNum, double labHours) : Member(accountID, name, email, address, phoneNum, labHours) {

	//this->setAssignedLab(assignedLab);
}

//Lab Observer::getAssignedLab() const {
//	return this->assignedLab;
//}

//void Observer::setAssignedLab(Lab lab) {
//	this->assignedLab = assignedLab;
//}

string Observer::toString() const {
	// Add and adjust formatting as necessary
	return to_string(this->getID()) + " Observer " + this->getName() + " " + this->getEmail() + " " + this->getAddress() +
		" " + to_string(this->getPhoneNum());
}

void Observer::pullReport() const {
	cout << "***********************" << endl;
	cout << this->getName() << endl;
	cout << "-----------------------" << endl;
	cout << "ID: " << this->getID() << endl;
	cout << "Email: " << this->getEmail() << endl;
	cout << "Address: " << this->getAddress() << endl;
	cout << "Phone: " << this->getPhoneNum() << endl;
	cout << "Available Lab Hours: " << this->getLabHours() << endl;
	cout << "***********************" << endl << endl;
}