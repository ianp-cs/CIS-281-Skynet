#include "Lab.h"
#include <algorithm>

Lab::Lab() {
	this->labID = 0;
	this->type = "NO TYPE";
	this->totalHours = 0;
	this->observer = Observer();
}

Lab::Lab(const int& labID, const string& type, const double& totalHours, const Observer& observer) {
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
	this->memberList = lab.getMemberList();
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

Observer Lab::getObserver() const {
	return this->observer;
}

void Lab::setObserver(const Observer& observer) {
	this->observer = observer;
}

list<Member> Lab::getMemberList() const {
	return this->memberList;
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

void Lab::addMember(Member& member) {
	this->memberList.push_back(member);
	member.addLab(this);
}

void Lab::removeMember(Member& member) {
	this->memberList.remove(member);
}

string Lab::toString() {
	// Add and adjust formatting as necessary
	return to_string(this->getID()) + " " + this->getType();
}

void Lab::pullReport() {
	cout << "***********************" << endl;
	cout << "Lab " << this->getID() << endl;
	cout << "-----------------------" << endl;
	cout << "Type: " << this->getType() << endl;
	cout << "Total Hours: " << this->getTotalHours() << endl << endl;

	cout << "Member List" << endl;
	cout << "-----------------------" << endl;
	for (auto const& member : this->memberList) {
		cout << member.toString() << endl;
	}
	cout << "***********************" << endl << endl;
}

Lab& Lab::operator=(const Lab& otherLab) {
	this->setID(otherLab.getID());
	this->setType(otherLab.getType());
	this->totalHours = otherLab.getTotalHours();
	this->setObserver(otherLab.getObserver());
	this->memberList = otherLab.getMemberList();

	return *this;
}