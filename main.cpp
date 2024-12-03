/*
Program: Old Pueblo Lapidary Club Records Management
Created By: Ian Penrose, Marie Perez, Lyes Attalah
Date Created: 11/29/2024
Description: 

CHANGE HISTORY
---------------------------------------------
Programmer	Date		Description of Change
---------------------------------------------
Ian			11/29/2024	Created Administrator, Account, Member, Observer, and Lab classes
*/

#include <iostream>
#include <string>
#include <list>
#include "Account.h"
#include "Administrator.h"
#include "Lab.h"
#include "Observer.h"
#include "Member.h"


using namespace std;

void addMembertoLab(Member& member, Lab& lab) {
    lab.addMember(member); //add member to lab member list
    member.addLab(lab); //add lab to members lab list
}


int main() {
  
    Administrator admin(1, "Bill", "BillyBob123", "BabyBilly@gmail.com"); //create an admin

    Member member1(011, "Phil Hartman", "Phartman@gmail.com", "123 Cropdust Ln", 3421243);  //initialize members with accounts
    Member member2(012, "Julia Kindly", "jewlzizkoolz@aol.com", "143 OakTree Ave", 3450989)
    Member member3(013, "Micheal Jordan", "theRealGooooaaat@gmail.com", "345 Rand Ave", 3094953);
    Member member4(14, "Mary Prescott", "Mprescott@gmail.com", "325 S Sunset Ln", 5989765);
    Member member5(15, "Robert Jackson", "MrJackson11@yahoo.com", "435 S Cherrywood Ln", 3453245);
    Member member6(16, "Boyd Crowder", "crawDaddy@yahoo.com", "643 Grizzly Lane", 4503495);
   
    Observer observer1(12, "Julia Kindly", "jewlzizkoolz@aol.com", "143 OakTree Ave", 5203450989, 0);

    Lab lab1(001, "Faceting", 0, 0); //initialize labs
    Lab lab2(002, "Lapidary", 0, 0);
    Lab lab3(003, "Blacksmithing", 0, 0);

    addMembertoLab(member1, lab1);
    addMembertoLab(member2, lab1);
    addMemberToLab(member2, lab2);
    observer1.setAssignedLab(lab1)

    cout << "Observer Report: "<< endl;
    observer1.pullReport();
    cout << "Lab Report: " << endl;
    lab1.pullReport();
    cout << "Member 2 Report: " << endl;
    member2.pullReport();




}