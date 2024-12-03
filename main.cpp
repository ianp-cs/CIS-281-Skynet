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

void addMemberToLab(Member& member, Lab& lab) {
    lab.addMember(member); //add member to lab member list
    member.addLab(lab); //add lab to members lab list
}


int main() {
  
    Administrator admin(1, "Bill", "BillyBob123", "BabyBilly@gmail.com"); //create an admin

    Account acct1(011, "Phil Hartman", "Phartman@gmail.com", "123 Cropdust Ln", 5203421243); //create accounts
    Account acct2(012, "Julia Kindly", "jewlzizkoolz@aol.com", "143 OakTree Ave", 5203450989);
    Account acct3(013, "Micheal Jordan", "theRealGooooaaat@gmail.com", "345 Rand Ave", 5203094953);
    
    Member member1(acct1.getID(), acct1.getName(), acct1.getEmail(), acct1.getAddress(), acct1.getPhoneNum(),  10.0);  //initialize members with accounts
    Member member2(acct2.getID(), acct2.getName(), acct2.getEmail(),  acct2.getAddress(), acct2.getPhoneNum(), 20.0);
    Member member3(acct3.getID(), acct3.getName(), acct3.getEmail(), acct3.getAddress(), acct3.getPhoneNum(), 20.0);

    Observer observer1(acct2, 0, nullptr); //initialize observer

    Lab lab1(001, "Faceting", 0, 0); //initialize labs
    Lab lab2(002, "Lapidary", 0, 0);
    Lab lab3(003, "Blacksmithing", 0, 0);

    addMembertoLab(member1, lab1);
    addMembertoLab(member2, lab1);
    addMemberToLab(member2, lab2);
    observer1.setAssignedLab(lab1)

    observer1.pullReport();
    lab1.pullReport();





}