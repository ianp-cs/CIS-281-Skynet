#include "Observer.h"
#include "Lab.h"

Observer::Observer() : Member() {
	this->setAssignedLab(nullptr);
}

Observer::Observer(const int& accountID, const string& name, const string& email, const string& address, 
	const int& phoneNum, const double& labHours) : Member(accountID, name, email, address, phoneNum, labHours) {

	this->setAssignedLab(nullptr);
}

Observer::Observer(const Observer& observer) {
	this->setID(observer.getID());
	this->setName(observer.getName());
	this->setEmail(observer.getEmail());
	this->setAddress(observer.getAddress());
	this->setPhoneNum(observer.getPhoneNum());
	this->labHours = observer.getLabHours();
	this->setAssignedLab(observer.getAssignedLab());

	for (int i{ 0 }; i < observer.listSize; i++) {
		this->addLab(observer.labsList[i]);
	}
}

Observer::~Observer() {
	for (int i{ 0 }; i < this->listSize; i++) {
		delete this->labsList[i];
	}
}

Lab* Observer::getAssignedLab() const {
	return this->assignedLab;
}

void Observer::setAssignedLab(Lab* lab) {
	this->assignedLab = assignedLab;
}

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

Observer& Observer::operator=(const Observer& otherObserver) {
	this->setID(otherObserver.getID());
	this->setName(otherObserver.getName());
	this->setEmail(otherObserver.getEmail());
	this->setAddress(otherObserver.getAddress());
	this->setPhoneNum(otherObserver.getPhoneNum());
	this->labHours = otherObserver.getLabHours();
	this->assignedLab = otherObserver.getAssignedLab();

	for (int i{ 0 }; i < otherObserver.listSize; i++) {
		this->addLab(otherObserver.labsList[i]);
	}

	return *this;
}