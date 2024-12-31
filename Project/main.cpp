//
// Created by Chu Ha Thanh on 2024-12-15.
//
#include <cmath>
#include <iostream>
#include <string>

#include "Product.h"
#include "Clothing.h"
#include "Cosmetic.h"
#include "EmployeeHandler.h"
#include "ProductHandler.h"
#include "Management.h"
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
	EmployeeHandler employerHanderpointers;
	ProductHandler productHanderVector;
	employerHanderpointers.loadEmployeesFromFie("All Employees");
	productHanderVector.loadProductsFromFie("All Products");

	bool isWorking = true;
	int answer;

	while(isWorking) {
		Menu();
		//catch and show the error if the input data is not valid
		try {
			cin >> answer;
			if (cin.fail() || answer > 19 || answer < 1) {
				throw invalid_argument("The input data is not valid!");
			}
		}
		catch (const invalid_argument& e) {
			cout << "Error: " << e.what() << "Please try again! " << endl;
			cin.clear();
			cin.ignore();
		}
		if(!cin.fail() && answer < 20 && answer > 0) {
			if(answer == 19) {
				isWorking = false;
			}
			else if (answer == 1){
				auto* clothing = new Clothing;
				clothing->editId();
				productHanderVector.importProduct(clothing);
				delete clothing;
				productHanderVector.showInfo();
			}
			else if (answer == 2) {
				auto* cosmetic = new Cosmetic;
				cosmetic->editId();
				cosmetic->editInfoButNotID();
				productHanderVector.importProduct(cosmetic);
				productHanderVector.showInfo();
			}
			else if (answer == 3) {
				cout << "Insert the product id you want to find: ";
				int checkId = checkInputDataInt();
				productHanderVector.findAndShowProduct(checkId);
			}
			else if (answer == 4) {
				cout << "Insert the product id you want to remove: ";
				int checkId = checkInputDataInt();
				productHanderVector.removeProduct(checkId);
				productHanderVector.showInfo();
			}
			else if (answer == 5) {
				cout << "Insert the product id you want to edit: ";
				int checkId = checkInputDataInt();
				productHanderVector.editProductId(checkId);
				productHanderVector.showInfo();
			}
			else if (answer == 6) {
				cout << "Insert the product id you want to edit: ";
				int checkId = checkInputDataInt();
				productHanderVector.editProduct(checkId);
				productHanderVector.showInfo();
			}
			else if (answer == 7) {
				cout << "Insert following information to sale a product: ";
				productHanderVector.sellProduct(employerHanderpointers);
				productHanderVector.showInfo();
			}
			else if (answer == 8) {
				productHanderVector.showInfo();
			}
			else if (answer == 9) {
				productHanderVector.saveProductsToFile("All products");
			}
			else if (answer == 10) {
				employerHanderpointers.addEmployee();
				employerHanderpointers.showInfo();
			}
			else if (answer == 11) {
				cout << "Insert the id of the employee that you want to find: ";
				int checkId = checkInputDataInt();
				employerHanderpointers.findEmployeeAndShowInfo(checkId);
			}
			else if (answer == 12) {
				cout << "Insert the id of the employee that you want to remove information: ";
				int checkId = checkInputDataInt();
				employerHanderpointers.removeEmployee(checkId);
				employerHanderpointers.showInfo();
			}
			else if (answer == 13) {
				cout << "Insert the id of the employee that you want to to edit id information: ";
				int checkId = checkInputDataInt();
				employerHanderpointers.editIdEmployee(checkId);
				employerHanderpointers.showInfo();
			}
			else if (answer == 14) {
				cout << "Insert the id of the employee that you want to to edit information ";
				int checkId = checkInputDataInt();
				employerHanderpointers.editEmployee(checkId);
				employerHanderpointers.showInfo();
			}
			else if (answer == 15) {
				employerHanderpointers.showInfo();
			}
			else if (answer == 16) {
				employerHanderpointers.saveEmployeesToFile("All employees");
			}
			else if (answer == 17) {
				Management management(productHanderVector,employerHanderpointers);
				management.showInfo();;
			}
			else if (answer == 18) {
				Management management(productHanderVector,employerHanderpointers);
				management.saveToFile("Statement");
			}
		}
	}
	return 0;
}
