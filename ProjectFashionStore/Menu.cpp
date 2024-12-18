//
// Created by Chu Ha Thanh on 2024-12-17.
//

#include "Menu.h"
#include <iostream>

using namespace std;

Menu::Menu() {
	cout << "*********************************" << endl
	<< "<<< Welcome to Fashion store! >>>" << endl
	<< "*********************************" << endl
	<< "			MENU			" << endl
	<< "-------------------------" << endl
	<< "|1. Add a product		|" << endl
	<< "|2. Remove a product	|" << endl
	<< "|3. Edit a product		|" << endl
	<< "|4. Show all products	|" << endl
	<< "-------------------------" << endl
	<< "|5. Add an asset		|" << endl
	<< "|6. Remove an asset		|" << endl
	<< "|7. Edit an asset		|" << endl
	<< "|8. Show all assets		|" << endl
	<< "-------------------------" << endl
	<< "|9. Add an employee		|" << endl
	<< "|10. Remove an employee	|" << endl
	<< "|11. Edit an employee	|" << endl
	<< "|12. Show all employees	|" << endl
	<< "-------------------------" << endl
	<< "|13. Show total cost	|" << endl
	<< "|14. Exit	|" << endl
	<< "-------------------------" << endl
	<< "Please select from the following menu: ";

}
