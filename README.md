OLD PUEBLO LAPIDARY CLUB RECORD SYSTEM MANUAL

PROGRAM DESCRIPTION 
This program is record management system for the Old Pueblo Lapidary Club. It helps track Club Members,
Labs, and Lab Observers, including Lab rosters, Members' lists of the labs they're attending, and Observers' assigned
Labs. Administrator credentials are required to access the program and make changes to records. Operations have been
separated into different menus, generally grouped by operations for Members, for Labs, and for pulling Reports.

IMPORTANT
-------------------------------------------------------------------------------------------------------------------------------------
- Record changes are only saved if the program is closed normally from the Main Menu. If the program closes prematurely, record
changes will not be saved.
- Control variables and macros for the program can be found in defines.h
- Source code for the program can be found at https://github.com/ianp-cs/CIS-281-Skynet
- A video demo of the program can be found at https://youtu.be/jYwWLPxdZEE

HOW-TO
-------------------------------------------------------------------------------------------------------------------------------------
LOGIN
To log into the program, an Administrator's username and password must be entered. Both the username and password are case sensitive.
-------------------------------------------------------------------------------------------------------------------------------------
ADDING A MEMBER
To add a Member to the record system, log into the program and select option 1 at the Main Menu. On the following screen, select
option 2 at the Member Data Menu. You will be prompted to enter data for the new Member, including their ID (ID's must be unique), 
name, email address, physical address, phone number and available lab hours. All data fields, besides the ID, can be left blank, but 
this is strongly discouraged.
-------------------------------------------------------------------------------------------------------------------------------------
EDITING A MEMBER
Note: This action should not be used to add or remove lab hours from a Member's account, except in cases where data was corrupted or 
otherwise lost.

To edit a Member in the record system, log into the program and select option 1 at the Main Menu. On the following screen, select
option 3 at the Member Data Menu. You will be prompted to enter a Member ID, which must match the ID of an existing Member in the 
records. If the Member exists, you will be prompted to enter new data for each of the Member's data fields. If a data field does not
need to be edited, simply press enter with no other input to skip to the next data field.
-------------------------------------------------------------------------------------------------------------------------------------
REMOVING A MEMBER
Note: This action cannot be done. If a Member is erroneously removed from the system, their data will have to be manually entered into 
the system again.

To remove a Member from the record system, log into the program and select option 1 at the Main Menu. On the following screen, select
option 4 at the Member Data Menu. You will be prompted to enter a Member ID, which must match the ID of an existing Member in the 
records. If the Member exists, their data will be deleted from the records. 
-------------------------------------------------------------------------------------------------------------------------------------
PROMOTING A MEMBER TO OBSERVER OR DEMOTING AN OBSERVER TO MEMBER
To promote or demote a Member in the record system, log into the program and select option 1 at the Main Menu. On the following screen, 
select option 5 at the Member Data Menu. You will be prompted to enter a Member ID, which must match the ID of an existing Member in 
the records. If the Member is not an Observer, they will be promoted to Observer, but they will not have an assigned Lab. If the 
Member is already an Observer, they are demoted from Observer, and their assigned Lab will no longer have an assigned Observer.
-------------------------------------------------------------------------------------------------------------------------------------
ADDING LAB HOURS TO A MEMBER'S ACCOUNT
To add lab hours to a Member's account, log into the program and select option 1 at the Main Menu. On the following screen, select 
option 6 at the Member Data Menu. You will be prompted to enter a Member ID, which must match the ID of an existing Member in the 
records. You will then be prompted to enter the number of lab hours to be added to the Member's account balance. Lab hour entries 
should always be positive values. The Member's lab hour balance will be adjusted.
-------------------------------------------------------------------------------------------------------------------------------------
SPENDING LAB HOURS FROM A MEMBER'S ACCOUNT
Note: It is possible to spend enough lab hours to push a Member's account into a negative balance.

To spend lab hours from a Member's account, log into the program and select option 1 at the Main Menu. On the following screen, select 
option 7 at the Member Data Menu. You will be prompted to enter a Member ID, which must match the ID of an existing Member in the 
records. You will then be prompted to enter the Lab ID of the Lab that the lab hours are being spent at. Finally, you will be prompted
to enter the number of lab hours being spent. Both the Member's lab hour balance and the total hours for the Lab will be adjusted.
-------------------------------------------------------------------------------------------------------------------------------------
REFUNDING LAB HOURS TO A MEMBER's ACCOUNT
Note: It is possible to refund enough lab hours to push a Lab's total hours into the negatives.

To spend lab hours from a Member's account, log into the program and select option 1 at the Main Menu. On the following screen, select 
option 8 at the Member Data Menu. You will be prompted to enter a Member ID, which must match the ID of an existing Member in the 
records. You will then be prompted to enter the Lab ID of the Lab that the lab hours are being refunded from. Finally, you will be 
prompted to enter the number of refunded lab hours. Both the Member's lab hour balance and the total hours for the Lab will be 
adjusted.
-------------------------------------------------------------------------------------------------------------------------------------
ADDING A LAB
To add a Lab to the record system, log into the program and select option 2 at the Main Menu. On the following screen, selected option 
2 at the Lab Data Menu. You will be prompted to enter data for the new Lab, including their ID (ID's must be unique) and the type of 
Lab (ex. silversmithing). The Lab type data field can be left blank, but this is strongly discouraged.
-------------------------------------------------------------------------------------------------------------------------------------
EDITING A LAB
Note: This action should not be used to add or remove hours from the Lab's total hours, except in cases where data was corrupted or
otherwise lost. Labs' total hours is automatically updated based on the spending/refunding of Members' lab hours.

To edit a Lab in the record system, log into the program and select option 2 at the Main Menu. On the following screen, selected option 
3 at the Lab Data Menu. You will be prompted to enter a Lab ID, which must match the ID of an existing Lab in the records. If the Lab 
exists, you will be prompted to enter new data for each of the Lab's data fields. If a data field does not need to be edited, simply
press enter with no other input to skip to the next data field.
-------------------------------------------------------------------------------------------------------------------------------------
REMOVING A LAB
Note: This action cannot be done. If a Lab is erroneously removed from the system, its data will have to be manually entered into 
the system again.

To remove a Lab from the record system, log into the program and select option 2 at the Main Menu. On the following screen, selected 
option 4 at the Lab Data Menu. You will be prompted to enter a Lab ID, which must match the ID of an existing Lab in the records. If
the Lab exists, its data will be deleted from the records.
-------------------------------------------------------------------------------------------------------------------------------------
ASSIGNING AN OBSERVER TO A LAB
To assign an Observer to a Lab, log into the program and select option 2 at the Main Menu. On the following screen, selected option 5 
at the Lab Data Menu. You will be prompted to enter a Member ID, which must match the ID of an existing Observer in the records. If 
the Observer exists, you will then be prompted to enter a Lab ID. If the Lab ID exists, then the Observer will be assigned to the Lab.
-------------------------------------------------------------------------------------------------------------------------------------
REMOVING AN OBSERVER FROM A LAB
To remove an Observer from a Lab, log into the program and select option 2 at the Main Menu. On the following screen, selected option 
6 at the Lab Data Menu. You will be prompted to enter a Member ID, which must match the ID of an existing Observer in the records. If
the Observer exists, their assigned lab will be set to none, and the Lab they were previously assigned to will no longer have an
assigned Observer.
-------------------------------------------------------------------------------------------------------------------------------------
ADDING A MEMBER TO A LAB
To add a Member to a Lab, log into the program and select option 2 at the Main Menu. On the following screen, selected option 7 at 
the Lab Data Menu. You will be prompted to enter a Member ID, which must match the ID of an existing Member or Observer in the 
records. If the Member exists, you will then be prompted to enter a Lab ID, which must match the ID of an existing Lab. If the Lab
exists, the Member will be added to the Lab's roster and the Lab will be added to the Member's Labs list.
-------------------------------------------------------------------------------------------------------------------------------------
REMOVING A MEMBER FROM A LAB
To remove a Member from a Lab, log into the program and select option 2 at the Main Menu. On the following screen, selected option 7 
at the Lab Data Menu. You will be prompted to enter a Member ID, which must match the ID of an existing Member or Observer in the 
records. If the Member exists, you will then be prompted to enter a Lab ID, which must match the ID of a Lab in the Member's Labs 
list. If they match, the Member will be removed from the Lab's roster and the Lab will be removed from the Member's Labs list.
-------------------------------------------------------------------------------------------------------------------------------------
PULLING A MEMBER'S REPORT
To pull a specific Member's report, log into the program and select option 3 at the Main Menu. On the following screen, select option 
1 at the Pull Reports Menu. You will be prompted to enter a Member ID, which must match the ID of an existing Member of Observer in
the records. If the Member exists, their report will show up in the console.
-------------------------------------------------------------------------------------------------------------------------------------
PULLING A LAB'S REPORT
To pull a specific Lab's report, log into the program and select option 3 at the Main Menu. On the following screen, select option 2 
at the Pull Reports Menu. You will be prompted to enter a Lab ID, which must match the ID of an existing Lab in the records. If the
Lab exists, its report will show up in the console.
-------------------------------------------------------------------------------------------------------------------------------------
PULLING ALL MEMBER REPORTS
To pull the reports of all Members in the records, log into the program and select option 3 at the Main Menu. On the following screen,
select option 3 at the Pull Reports Menu. All Member reports will appear in the console.
-------------------------------------------------------------------------------------------------------------------------------------
PULLING ALL LAB REPORTS
To pull the reports of all Labs in the records, log into the program and select option 3 at the Main Menu. On the following screen,
select option 4 at the Pull Reports Menu. All Lab reports will appear in the console.

