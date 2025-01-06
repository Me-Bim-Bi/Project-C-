//
// Created by Chu Ha Thanh on 2024-12-15.
//
#include <iostream>
#include <string>
#include "EmployeeHandler.h"
#include "ProductHandler.h"
#include "Menu.h"

/*
* Here is some basic rules:
* - 1 product has only 1 id. The user can only add a product if the product’s id has not existed att all
* or all information match but only quantity purchase is different.
* - 1 employee has only 1 id. The user can only add an employee if the employee’s id
* has not existed att all in the system.
* - The user can find, edit or remove a product or en employee information with the id number.
* - The user can only edit id number if the new id number does not exist in the system.
* - Every time when the user want to edit a product’s information or remove a product,
* the product’s information will be shown first. The user can choose if they want to change/remove it.
*/

using namespace std;

int main() {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	EmployeeHandler employeeHandlerPointers;
	ProductHandler productHandlerVector;
	employeeHandlerPointers.loadEmployeesFromFie("All Employees");
	productHandlerVector.loadProductsFromFie("All Products");

	bool isWorking = true;

	while(isWorking) {
		Menu();
		int answer = checkMenuChoice();
		if(answer == 19) {
			isWorking = false;
		}
		else {
			getMenuChoice(answer,productHandlerVector,employeeHandlerPointers);
		}
	}
	return 0;
}
