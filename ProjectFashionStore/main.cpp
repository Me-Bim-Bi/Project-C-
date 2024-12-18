//
// Created by Chu Ha Thanh on 2024-12-15.
//
#include <iostream>
#include <string>

#include "Product.h"
#include "Clothing.h"
#include "Cosmetic.h"
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
		if(!cin.fail() && answer < 15 && answer > 0) {
			if(answer == 14) {
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
	abd.addProduct(new Clothing (123, "Klänning", 123.5f, "Lindex", 3, "M", "Rosa"));
	abd.addProduct(new Clothing (123, "Tröja", 123.5f, "Zara", 3, "M", "Rosa"));
	abd.addProduct(new Clothing (456, "Vaska", 123.5f, "HM", 3, "M", "Rosa"));
	abd.addProduct(new Cosmetic (789, "solkräm", 123.5f, "ACo", 3, "solkräm"));
	abd.showProduct();
	cout << endl;
	cout << endl;

	abd.editProduct(3);
	abd.showProduct();

	//man skulle fråga om användaren vill tillägga Clothing eller Cosmetic. Sedan skapar man det i Managment.
	//Managment behöver vara en source file eller en klass?
	//det kommer att läsa filen först när program statar och tillägga alla product till objekt ProductHandler.
	//problem är att hur kan man veta om att det är Clothing eller Cosmetic => den första raden är hur många i filen
	//det är hur många element i vector products. sedan skriver man efter syntax: Clothing - eller Cosmetic.

  return 0;
}