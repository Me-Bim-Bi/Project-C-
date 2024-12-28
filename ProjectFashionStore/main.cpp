//
// Created by Chu Ha Thanh on 2024-12-15.
//
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
	/*
	bool isWorking = true;
	int answer;
	//print the menu
	while(isWorking) {
		Menu();
		//catch and show the error if the input data is not valid
		try {
			cin >> answer;
			if (cin.fail() || answer > 14 || answer < 1) {
				throw invalid_argument("The input data is not valid!");
			}
		}
		catch (const invalid_argument& e) {
			cout << "Error: " << e.what() << "Please try again! ";
			cin.clear();
			cin.ignore();
		}
		if(!cin.fail() && answer < 18 && answer > 0) {
			if(answer == 17) {
				isWorking = false;
			}
			else if (answer == 1){
				ProductHandler productHandler;
				productHandler.addProduct(new Clothing(12, "Vay", 120, "lindex", 3, "M", "vitt"));
			}
			else if (answer == 4) {

				//isContinue = askYesNo("Do you want to do something else? ");

			}
		}
	}*/
	ProductHandler abd;
	abd.loadProductsFromFie("All products");
	abd.showProduct();
	cout << endl << endl << endl;
	abd.importProduct(new Clothing(123,"Klänning",120,150,"Lindex",16,0,5,"M","Rosa"));
	abd.importProduct(new Clothing(345,"Tröja",120,180,"Lindex",16,0,2,"M","Rosa"));
	abd.importProduct(new Cosmetic(3457,"Ring",120,180,"Lindex",17,0,1,"ring"));
	abd.showProduct();
	cout << endl << endl << endl;
	abd.saveProductToFile("All products");


	//man skulle fråga om användaren vill tillägga Clothing eller Cosmetic. Sedan skapar man det i Managment.
	//Managment behöver vara en source file eller en klass?
	//det kommer att läsa filen först när program statar och tillägga alla product till objekt ProductHandler.
	//problem är att hur kan man veta om att det är Clothing eller Cosmetic => den första raden är hur många i filen
	//det är hur många element i vector products. sedan skriver man efter syntax: Clothing - eller Cosmetic.

  return 0;
}