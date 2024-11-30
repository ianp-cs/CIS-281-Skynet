#include "Lab.h"

Lab::Lab() {
	this->setID(0);
	this->setType("NO TYPE");
	this->totalHours = 0;
	this->setObserver(Observer());
}

Lab::Lab(int labID, string type, double totalHours, Observer observer) {
	this->setID(labID);
	this->setType(type);
	this->totalHours = totalHours;
	this->setObserver(observer);
}

int Lab::getID() const {
	return this->labID;
}

void Lab::setID(int id) {
	this->labID = id;
}

string Lab::getType() const {
	return this->type;
}

void Lab::setType(string type) {
	this->type = type;
}

double Lab::getTotalHours() const {
	return this->totalHours;
}

Observer Lab::getObserver() const {
	return this->observer;
}

void Lab::setObserver(Observer observer) {
	this->observer = observer;
}

list<Member> Lab::getMemberList() const {
	return this->memberList;
}

void Lab::addHours(double hours) {
	this->totalHours += hours;
}

void Lab::refundHours(double hours) {
	this->totalHours -= hours;
}

void Lab::resetHours() {
	this->totalHours = 0;
}

void Lab::addMember(Member member) {
	this->memberList.push_back(member);
}

void Lab::removeMember(Member member) {
	this->memberList.remove(member);
}

string Lab::toString() {
	// Add and adjust formatting as necessary
	return to_string(this->getID()) + this->getType();
}

void Lab::pullReport() {
	cout << "***********************" << endl;
	cout << "Lab " << this->getID() << endl;
	cout << "-----------------------" << endl;
	cout << "Type: " << this->getType() << endl;
	cout << "Total Hours: " << this->getTotalHours() << endl << endl;

	cout << "Member List" << endl;
	cout << "-----------------------" << endl;
	for (list<Member>::iterator member = this->getMemberList().begin(); member != this->getMemberList().end(); member++) {
		cout << member->toString() << endl;
	}
	cout << "***********************" << endl << endl;
}