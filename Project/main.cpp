//
// Created by Chu Ha Thanh on 2024-12-15.
//
#include <cmath>
#include <iostream>
#include <string>

#include "Product.h"
#include "Clothing.h"
#include "Cosmetic.h"
#include "Employee.h"
#include "EmployeeHandler.h"
#include "ProductHandler.h"
#include "Menu.h"

/*
* Here is some basic rules:
* 1 product has only 1 id. The user can only add a product if all information match,
* only quantity purchase is different, or the product’s id has not existed att all.
* 1 employee has only 1 id. The user can only add an employee if the employee’s id
* has not existed att all in the system.
* The user can find, edit or remove a product or en employee with the id number.
* The user can only edit id number if the new id number does not exist in the system.
* Every time when the user want to edit a product’s information or remove a product,
* the product’s information will be shown first. The user can choose if they want to change/remove it.
*/

using namespace std;

int main() {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	EmployeeHandler employerHanderpointers;
	ProductHandler productHanderVector;
	productHanderVector.loadProductsFromFie("All products");
	productHanderVector.showProduct();

	bool isWorking = true;
	int answer;

	//print the menu
	while(isWorking) {
		Menu();
		//catch and show the error if the input data is not valid
		try {
			cin >> answer;
			if (cin.fail() || answer > 20 || answer < 1) {
				throw invalid_argument("The input data is not valid!");
			}
		}
		catch (const invalid_argument& e) {
			cout << "Error: " << e.what() << "Please try again! " << endl;
			cin.clear();
			cin.ignore();
		}
		if(!cin.fail() && answer < 21 && answer > 0) {
			if(answer == 20) {
				isWorking = false;
			}
			else if (answer == 1){
				auto* clothing = new Clothing;
				clothing->editId();
				clothing->editInfoButNotID();
				productHanderVector.importProduct(clothing);
				delete clothing;
				productHanderVector.showProduct();
			}
			else if (answer == 2) {
				auto* cosmetic = new Cosmetic;
				cosmetic->editId();
				cosmetic->editInfoButNotID();
				productHanderVector.importProduct(cosmetic);
				productHanderVector.showProduct();
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
				productHanderVector.showProduct();
			}
			else if (answer == 5) {
				
			}
		}
	}
	return 0;
}

	//man skulle fråga om användaren vill tillägga Clothing eller Cosmetic. Sedan skapar man det i Managment.
	//Managment behöver vara en source file eller en klass?
	//det kommer att läsa filen först när program statar och tillägga alla product till objekt ProductHandler.
	//problem är att hur kan man veta om att det är Clothing eller Cosmetic => den första raden är hur många i filen
	//det är hur många element i vector products. sedan skriver man efter syntax: Clothing - eller Cosmetic.
