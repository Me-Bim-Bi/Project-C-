//
// Created by Chu Ha Thanh on 2024-12-17.
//

#include "Menu.h"
#include "FuntionToEditInformation.h"
#include <iostream>
#include <sstream>
#include <algorithm> // to use "transform" to change string input in function "askYesNO" to capital letters
#include <cctype> // to "toupper" to change string input in function "askYesNO" to capital letters

//Including some functions that are shared by main as well as some other classes.
using namespace std;

void Menu() {
	cout << endl
	<< "*************************************************************************" << endl
	<< "<<<<<<<<<<<<<<<<<<<<< Welcome To The Fashion Store! >>>>>>>>>>>>>>>>>>>>>" << endl
	<< "*************************************************************************" << endl
	<< "|									MENU								|" << endl
	<< "------------------------------------------------------------------------" << endl
	<< "|1. Import a clothing				||11. Find an employee				|" << endl
	<< "|2. Import a cosmetic				||12. Remove an employee			|" << endl
	<< "|3. Find a product					||13. Edit an employee's ID			|" << endl
	<< "|4. Remove a product				||14. Edit an employee's information|" << endl
	<< "|5. Edit a product's id				||15. Show all employees			|" << endl
	<< "|6. Edit a product's information	||16. Save employees' list to file	|" << endl
	<< "|7. Sell a product					||17. Show financial statement		|" << endl
	<< "|8. Show all products				||18. Save the statement in file	|" << endl
	<< "|9. Save products' list to file		||19. Exit							|" << endl
	<< "|10. Add an employee													|" << endl
	<< "------------------------------------------------------------------------" << endl
	<< "|				***	Please select from the menu above: ***		  		| " << endl
	<< "------------------------------------------------------------------------" << endl;
}

int checkInputDataInt() {
	int id= -1;
	editPrice("\nPlease enter a valid number: ", id, "It");
	return id;
}

bool askYesNo(const string &question) {
	string input;
	while (true) {
		cout << question << " (yes/no): ";
		cin >> input;
		transform(input.begin(), input.end(), input.begin(), ::toupper);
		if (input == "YES") {
			return true;
		}
		if (input == "NO") {
			return false;
		}
		cout << "Invalid input! Please enter 'yes' or 'no'." << endl;
	}
}


