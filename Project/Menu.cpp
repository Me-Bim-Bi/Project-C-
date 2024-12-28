//
// Created by Chu Ha Thanh on 2024-12-17.
//

#include "Menu.h"
#include <iostream>

using namespace std;

Menu::Menu() {
	cout << "*************************************************************************" << endl
	<< "<<<<<<<<<<<<<<<<<<<<< Welcome To The Fashion Store! >>>>>>>>>>>>>>>>>>>>>" << endl
	<< "*************************************************************************" << endl
	<< "|									MENU								|" << endl
	<< "------------------------------------------------------------------------" << endl
	<< "|1. Import a clothing				||11. Find an employee				|" << endl
	<< "|2. Import a cosmetic				||12. Remove an employee			|" << endl
	<< "|3. Find a product					||13. Edit an employee's ID			|" << endl
	<< "|4. Remove a product				||14. Edit an employee's information|" << endl
	<< "|5. Edit a product's id				||15. Pay salary and commission		|" << endl
	<< "|6. Edit a product's information	||16. Show all employees			|" << endl
	<< "|7. Sell a product					||17. Save employees' list to file	|" << endl
	<< "|8. Show all products				||18. Show financial statement		|" << endl
	<< "|9. Save products' list to file		||19. Save the statement in file	|" << endl
	<< "|10. Add an employee				||20. Exit							|" << endl
	<< "------------------------------------------------------------------------" << endl
	<< "|				***	Please select from the menu above: ***		  		| " << endl
	<< "------------------------------------------------------------------------" << endl;
}
