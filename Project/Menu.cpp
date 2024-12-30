//
// Created by Chu Ha Thanh on 2024-12-17.
//

#include "Menu.h"
#include <iostream>

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
	while (true) {
		string input;
		cin >> input;
		bool isNumeric = true;

		for (char cha : input) {
			if (!isdigit(cha)) {
				isNumeric = false;
				break;
			}
		}
		if(!isNumeric) {
			cout << "Invalid input. It must be a number. Please try again.\n" << endl;
		}
		else {
			try {
				long long temp = stoll (input);

				// check if input is within the range of int
				if (temp < numeric_limits<int>::min() || temp > numeric_limits<int>::max()) {
					throw out_of_range("Number out of range for int type.");
				}

				else {
					id = static_cast<int>(temp);
				}

				if (id < 0) {
					cout << "Invalid input. It must be a positive number. Please try again.\n";
				} else {
					break;
				}
			} catch (invalid_argument&) {
				cout << "Invalid input. It must be a valid number. Please try again.\n";
			} catch (out_of_range&) {
				cout << "You must have entered the wrong information. "
			"The number you entered is too large or too small. Please try again.\n";
			}
		}
		cin.clear(); //delete the wrong status
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the wrong input data
	}
	cin.ignore();
	return id;
}



