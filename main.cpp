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
Marie       12/02/2024  Created main
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
    //member.addLab(lab); //add lab to members lab list
}

int main() {
  
    Administrator admin(1, "Bill", "BillyBob123", "BabyBilly@gmail.com"); //create an admin

    cout << "Administrator Login: " << endl;
    string name, password;
    cout << "Enter Username: " ;
    cin >> name;
    cout << "Enter Password: ";
    cin >> password;
    if (!admin.login(name, password)){
        cout << "Login failed, try again " << endl;
        return 1;
    }

    Member member1(11, "Phil Hartman", "Phartman@gmail.com", "123 Cropdust Ln", 3421243, 0.0);  //initialize members with accounts
    Member member2(12, "Julia Kindly", "jewlzizkoolz@aol.com", "143 OakTree Ave", 3450989, 10.0);
    Member member3(13, "Micheal Jordan", "theRealGooooaaat@gmail.com", "345 Rand Ave", 3094953, 12.2);
    Member member4(14, "Mary Prescott", "Mprescott@gmail.com", "325 S Sunset Ln", 5989765, 20.5);
    Member member5(15, "Robert Jackson", "MrJackson11@yahoo.com", "435 S Cherrywood Ln", 3453245, 7);
    Member member6(16, "Boyd Crowder", "crawDaddy@yahoo.com", "643 Grizzly Lane", 4503495, 19);
   
    Observer observer1(17, "Julia Kindly", "jewlzizkoolz@aol.com", "143 OakTree Ave", 3450989, 0);
    Observer observer2(18,  "Robert Jackson", "MrJackson11@yahoo.com", "435 S Cherrywood Ln", 3453245, 5.0); 
    Observer observer3(19, "Boyd Crowder", "crawDaddy@yahoo.com", "643 Grizzly Lane", 4503495, 2.5);
   
    Lab lab1(1, "Faceting", 50, Observer()); //initialize labs
    Lab lab2(2, "Lapidary", 75.2, Observer());
    Lab lab3(3, "Blacksmithing", 19.5, Observer());

    addMembertoLab(member1, lab1);
    addMembertoLab(member2, lab1);
    addMembertoLab(member2, lab2);
    addMembertoLab(member3, lab1);
    addMembertoLab(member5, lab3);
    addMembertoLab(member5, lab2);
    addMembertoLab(member6, lab2);
    addMembertoLab(member4, lab3);

    cout << "Observer Report: "<< endl;
    observer1.pullReport();
    cout << "Lab Reports: " << endl;
    lab1.pullReport();
    lab2.pullReport();
    lab3.pullReport();
    cout << "Member 2 Report: " << endl; 
    member2.pullReport();

    return 0;
}