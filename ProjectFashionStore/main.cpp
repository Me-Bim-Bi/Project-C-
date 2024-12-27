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
	EmployeeHandler abd;
	abd.addEmployee(1201,"chu ha thanh", 14750);
	abd.addEmployee(926,"tran quang huy", 32000);
	abd.addEmployee(1006,"tran dieu uyen", 20000);
	abd.addEmployee(1030,"tran phuong linh", 21302);

	abd.showInfo();
	cout << endl;
	cout << endl;
	abd.findEmployee(1006);
	cout << endl;
	cout << endl;

	//man skulle fråga om användaren vill tillägga Clothing eller Cosmetic. Sedan skapar man det i Managment.
	//Managment behöver vara en source file eller en klass?
	//det kommer att läsa filen först när program statar och tillägga alla product till objekt ProductHandler.
	//problem är att hur kan man veta om att det är Clothing eller Cosmetic => den första raden är hur många i filen
	//det är hur många element i vector products. sedan skriver man efter syntax: Clothing - eller Cosmetic.

  return 0;
}