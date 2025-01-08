//
// Created by Chu Ha Thanh on 2024-12-17.
//
#include "Menu.h"
#include "FuntionToEditInformation.h"
#include "Management.h"
#include "Clothing.h"
#include "Cosmetic.h"
#include "EmployeeHandler.h"
#include "ProductHandler.h"
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
	editPrice("\nPlease enter a number: ", id, "It");
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
		cerr << "Invalid input! Please enter 'yes' or 'no'." << endl;
	}
}

int checkMenuChoice() {
	int answer = 0;
	while (true) {
		//when user choose wrong menu
		try {
			editPrice("Menu choice: ",  answer,"Menu choice");
			// check if menu choice is in range 1-19
			if (answer < 1 || answer > 19) {
				throw invalid_argument("The input data is out of range! ");
			}
			break;

		} catch (const invalid_argument& e) {
			cerr << "Error: " << e.what() << " Please select from 1 to 19!" << endl<< endl;
		}
	}
	return answer;
}

void getMenuChoice(int answer, ProductHandler& productHandlerVector, EmployeeHandler& employeeHandlerPointers) {
	if (answer == 1){
		auto* clothing = new Clothing;
		clothing->editId();
		productHandlerVector.importProduct(clothing);
		delete clothing;
	}
	else if (answer == 2) {
		auto* cosmetic = new Cosmetic;
		cosmetic->editId();
		productHandlerVector.importProduct(cosmetic);
		delete cosmetic;
	}
	else if (answer == 3) {
		cout << "Insert the product id you want to find: ";
		int checkId = checkInputDataInt();
		productHandlerVector.findAndShowProduct(checkId);
	}
	else if (answer == 4) {
		cout << "Insert the product id you want to remove: ";
		int checkId = checkInputDataInt();
		productHandlerVector.removeProduct(checkId);
	}
	else if (answer == 5) {
		cout << "Insert the product id you want to edit: ";
		int checkId = checkInputDataInt();
		productHandlerVector.editProductId(checkId);
	}
	else if (answer == 6) {
		cout << "Insert the product id you want to edit: ";
		int checkId = checkInputDataInt();
		productHandlerVector.editProduct(checkId);
	}
	else if (answer == 7) {
		cout << "Insert following information to sale a product: ";
		productHandlerVector.sellProduct(employeeHandlerPointers);
	}
	else if (answer == 8) {
		//sort products before show info
		productHandlerVector.sortProducts();
		productHandlerVector.showInfo();
	}
	else if (answer == 9) {
		//sort products before save to file
		productHandlerVector.sortProducts();
		productHandlerVector.saveProductsToFile("All products");
	}
	else if (answer == 10) {
		employeeHandlerPointers.addEmployee();
	}
	else if (answer == 11) {
		cout << "Insert the id of the employee that you want to find: ";
		int checkId = checkInputDataInt();
		employeeHandlerPointers.findEmployeeAndShowInfo(checkId);
	}
	else if (answer == 12) {
		cout << "Insert the id of the employee that you want to remove information: ";
		int checkId = checkInputDataInt();
		employeeHandlerPointers.removeEmployee(checkId);
	}
	else if (answer == 13) {
		cout << "Insert the id of the employee that you want to to edit id information: ";
		int checkId = checkInputDataInt();
		employeeHandlerPointers.editIdEmployee(checkId);
	}
	else if (answer == 14) {
		cout << "Insert the id of the employee that you want to to edit information ";
		int checkId = checkInputDataInt();
		employeeHandlerPointers.editEmployee(checkId);
	}
	else if (answer == 15) {
		//sort employees before show info
		employeeHandlerPointers.sortEmployees();
		employeeHandlerPointers.showInfo();
	}
	else if (answer == 16) {
		//sort employees before save to file
		employeeHandlerPointers.sortEmployees();
		employeeHandlerPointers.saveEmployeesToFile("All employees");
	}
	else if (answer == 17) {
		//count the finance statement before show info
		Management management(productHandlerVector,employeeHandlerPointers);
		management.showInfo();;
	}
	else {
		//count the finance statement before save to file
		Management management(productHandlerVector,employeeHandlerPointers);
		management.saveToFile("Statement");
	}
}

int validateAndConvertToInt(const string &str, const string &errorMessage) {
	if (str.find_first_not_of("0123456789") != string::npos) {
		throw invalid_argument(errorMessage);
	}
	return stoi(str);
}

float validateAndConvertToFloat(const string &str, const string &errorMessage) {
	try {
		return stof(str);
	} catch (const exception&) {
		throw invalid_argument(errorMessage);
	}
}

double validateAndConvertToDouble(const string &str, const string &errorMessage) {
	try {
		return stod(str);
	} catch (const exception&) {
		throw invalid_argument(errorMessage);
	}
}