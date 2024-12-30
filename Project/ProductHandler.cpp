//
// Created by Chu Ha Thanh on 2024-12-16.
//

#include "ProductHandler.h"
#include "Clothing.h"
#include "Cosmetic.h"
#include "EmployeeHandler.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> // to use "transform" to change string input in function "askYesNO" to capital letters
#include <cctype> // to "toupper" to change string input in function "askYesNO" to capital letters

using namespace std;

//rule: only 1 id product number can exist in system => always need to check
//if the id already exists.

int ProductHandler::findIndexProduct(int id) const {
	int index = -1;
	for (int i = 0; i < products.size(); i++) {
		if(products[i]->getID() == id) {
			index = i;
			}
	}
	return index;
}

ProductHandler::ProductHandler()= default;

//free up memory
ProductHandler::~ProductHandler() {
	for (auto product : products) {
		delete product;
	}
}

ProductHandler::ProductHandler(const ProductHandler &other) {
	for (auto product : other.products) {
		products.push_back(product->clone());
	}
}

ProductHandler& ProductHandler::operator=(const ProductHandler &other) {
	if(this != & other) {
		for (auto product : products) {
			delete product;
		}
		products.clear();
		for (const auto& product : other.products) {
			products.push_back(product->clone());
		}
	}
	return *this;
}

void ProductHandler::importProduct(Product* product) {
	int idProduct = product->getID();
	int index = findIndexProduct(idProduct);
	//check if the product exists in system => only add the quantityPurchase
	if(index != -1) {
		if(*this->products[index] == *product) {
			int quantityAfterImport = products[index]->getQuantityImported() + product->getQuantityImported();
			products[index]->setQuantityImported(quantityAfterImport);
		}
		else
		{
			cout << "The product's id exist in system but the other information do not match. "
		   "Please check again!" << endl
			<< "Here is the information of product in the system now: " << endl
			<< products[index]->showInfo();
		}
	}
	else {
		products.push_back(product->clone());
	}
}

void ProductHandler::findAndShowProduct(const int id) const {
	int index = findIndexProduct(id);
	if (index != -1)
	{
		cout << "The product with the id " << id << " have got the following information: " << endl
		<< products[index]->showInfo() << endl;
	}
	else{
		cout << "Product with ID: " << id << " was not found!";
	}
}

void ProductHandler::removeProduct(const int id) {
	int index = findIndexProduct(id);
	if (index != -1) {
		cout << "The product with the id " << id << " have got the following information: " << endl
		<< products[index]->showInfo() << endl;
		if (askYesNo("Do you want to remove this product? ")) {
			products.erase(products.begin() + index);
			cout << "The product has been deleted." << endl;
		}
		else{
			cout << "Product with ID: " << id << " was not deleted!" << endl;
		}
	}
	else {
		cout << "Product with ID: " << id << " was not found." << endl;
	}
}

void ProductHandler::editProductId(int id) const {
	int index = findIndexProduct(id);
	if (index != -1) {
		if (askYesNo("Do you want to edit the id of this product? ")) {
			int newID;
			while (true) {
				string input;
				cout << "\nNew ID: ";
				cin >> input;
				bool isNumeric = true;
				for (char cha : input) {
					if (!isdigit(cha)) {
						isNumeric = false;
						break;
					}
				}
				if(!isNumeric) {
					cout << "Invalid input. ID must be a number. Please try again.\n" << endl;
				}
				else {
					try {
						long long temp = stoll (input);

						// check if input is within the range of int
						if (temp < numeric_limits<int>::min() || temp > numeric_limits<int>::max()) {
							throw out_of_range("Number out of range for int type.");
						}

						else {
							newID = static_cast<int>(temp);
						}

						if (newID < 0) {
							cout << "Invalid input. ID must be a positive number. Please try again.\n";
						} else {
							break;
						}
					} catch (invalid_argument&) {
						cout << "Invalid input. ID must be a valid number. Please try again.\n";
					} catch (out_of_range&) {
						cout << "You must have entered the wrong information. "
					"The number you entered is too large or too small for become an ID number. Please try again.\n";
					}
				}
				cin.clear(); //delete the wrong status
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the wrong input data
			}
			cin.ignore();
			if (findIndexProduct(newID) != -1) {
				cout << "Error! The new ID you entered already exists. The id changed failed." << endl;
			}
			else {
				products[index]->setID(newID);
				cout << "The product id has been edited." << endl;
			}
		}
		else{
			cout << "The product id has not been edited." << endl;
		}
	}
	else {
		cout << "Product with ID: " << id << " was not found!";
	}
}

void ProductHandler::editProduct(const int id) const {
	int index = findIndexProduct(id);
	if (index != -1) {
		cout << "The product with the id number " << id << " have got following information: " << endl
		<< products[index]->showInfo() << endl;
		if (askYesNo("Is it the product that you want to edit? ")) {
			editProductId(id);
			if (askYesNo("Do you want change the another information of this product? ")) {
				cout << "Please insert the new value: " << endl;
				products[index]->editInfoButNotID();
				cout << "The product information has been edited." << endl;
			}
			else {
				cout << "The another information of this product has not been edited." << endl;
			}
		}
		else{
			cout << "The product information has not been edited." << endl;
		}
	}
	else {
		cout << "Product with ID: " << id << " was not found!";
	}
}

void ProductHandler::sellProduct(int idProduct, int quantitySale, int idEmployee, EmployeeHandler& emp) const {
	int index = findIndexProduct(idProduct);
	if(index != -1 && emp.callFindIdIndex(idEmployee) != -1) {
		int quantity = products[index]->getQuantityBeginningInventory()+products[index]->getQuantityImported();
		int totalQuantitySold = products[index]->getQuantitySold()+quantitySale;
		if(totalQuantitySold <= quantity) {
			products[index]->setQuantitySold(totalQuantitySold);
			auto employeeCommission = products[index]->getSellingPrice() * static_cast<double>(quantitySale) * 0.02;
			emp.addCommission(idEmployee,employeeCommission);
			}
		else {
			cout << "The product " << idProduct<< " is out of stock." << endl;
			}
	}
	else {
		cout << "Sorry! We don't have any product with id " << idProduct << " in store"
		<< " or the employee with id " << idEmployee << "does not exist." << endl;
	}
}

double ProductHandler::totalCostOfProducts() const {
	double total = 0.0f;
	for (auto product : products) {
		total += product->totalCostOfGoods();
	}
	return total;
}

double ProductHandler::totalRevenue() const {
	double total = 0.0f;
	for (auto product : products) {
		total += product->totalRevenue();
	}
	return total;
}

void ProductHandler::showInfo() const {
	int index = 1;
	cout << "\nProduct in store now:\n";
	for (auto product : products) {
		cout << index << ". " << product->showInfo() << endl;
		index++;
	}
	cout << "Total price of all products is: " << totalCostOfProducts() << endl
	<< "Total revenue is: " << totalRevenue() << endl;
}


bool ProductHandler::askYesNo(const string &question) {
	string input;
	while (true) {
		cout << question << " (yes/no): ";
		cin >> input;
		transform(input.begin(), input.end(), input.begin(), ::toupper);
		if (input == "YES") {
			return true;
		} else if (input == "NO") {
			return false;
		} else {
			cout << "Invalid input! Please enter 'yes' or 'no'." << endl;
		}
	}
}

void ProductHandler::loadProductsFromFie(const string &fileName) {
	ifstream in(fileName);
	if(!in.is_open()) {
		cerr << "Could not open the file: " << fileName << " for reading" << endl;
		return;              //throw the error message and stopp reading
	}
	else {
		string line;
		int lineNumber = 0; //count the line number to show the error message

		while(getline(in, line)) { //read through all lines to the end
			++lineNumber;
			istringstream input(line);
			vector <string> productInformation;    //create a vector to check the input data
			string aProduct;

			while(getline(input,aProduct,',')) {  //add input data to vector
				productInformation.push_back(aProduct);
			}

			if(productInformation.size() < 9) {
				cerr << "Error on line: " << lineNumber <<". Unknown product format. Skipping..." << endl;
				continue;
			}
			string productType= productInformation[0], name = productInformation[2];
			try {
				int id = stoi(productInformation[1]);      //check if input data is valid, throw error message if it fails
				float purchasePrice = stof(productInformation[3]);
				float sellingPrice = stof(productInformation[4]);
				int quantityBeginningInventory = stoi(productInformation[5]);
				int quantitySold = stoi(productInformation[6]);
				int quantityImported = stoi(productInformation[7]);

				Product* product = nullptr;
				if(productType == "Clothing") {   //check if product type is Clothing to add product
					if(productInformation.size() != 10) {
						cerr << "Error on line: " << lineNumber << ". Invalid data. Must be 10 fields. Skipping..." << endl;
						continue;
					}
					else {
						const string& size = productInformation[8];
						const string& colour = productInformation[9];
						product = new Clothing(id, name, purchasePrice, sellingPrice, quantityBeginningInventory,
							quantitySold, quantityImported, size, colour);
					}
				}
				else if(productType == "Cosmetic") {
					//check if product type is Cosmetic to add product
					if(productInformation.size() == 9) {
						cerr << "Error on line: " << lineNumber << ". Invalid data. Must be 9 fields. Skipping..." << endl;
						continue;
					}
					else {
						const string& typeCosmetic = productInformation[8];
						product = new Cosmetic(id, name, purchasePrice, sellingPrice, quantityBeginningInventory,
						quantitySold, quantityImported, typeCosmetic);
					}
				}
				else {
					cerr << "Error on line: " << lineNumber << ". Unknown product type. Skipping..." << endl;
					continue;
				}
				if(product != nullptr) {
					importProduct(product); //add product
				}
			}
			catch (exception& e){
				cerr << "Error in line: " << lineNumber << ". Invalid data. Skipping..." << endl;
			}
		}
	}
}

void ProductHandler::saveProductsToFile(const string& fileName) {
	ofstream out(fileName);
	if(out.is_open()) {
		for(const auto& product : products) {

			string typeProduct;
			int id = product->getID();
			string name = product->getName();
			float purchasePrice = product->getPurchasePrice();
			float sellingPrice = product->getSellingPrice();
			int quantityBeginningInventory = product->getQuantityBeginningInventory();
			int quantitySold = product->getQuantitySold();
			int quantityImported = product->getQuantityImported();

			if(dynamic_cast<Clothing*>(product)) {
				typeProduct = "Clothing";
				auto* clothing = dynamic_cast<Clothing*>(product);
				string size = clothing->getSize();
				string colour = clothing->getColour();
				out << typeProduct << ',' << id << ',' << name << ',' << purchasePrice << ','
				<< sellingPrice << ',' << quantityBeginningInventory << ','
				<< quantitySold << ',' << quantityImported << ',' << size << ',' << colour << '\n';
			}
			else if (dynamic_cast<Cosmetic*>(product)) {
				typeProduct = "Cosmetic";
				auto* cosmetic = dynamic_cast<Cosmetic*>(product);
				string typeCosmetic = cosmetic->getType();
				out << typeProduct << ',' << id << ',' << name << ',' << purchasePrice << ','
				<< sellingPrice << ',' << quantityBeginningInventory << ','
				<< quantitySold << ',' << quantityImported << ',' << typeCosmetic << '\n';
			}
			else {
				continue;
			}
		}
		out.close();
		cout << "Products saved to file: " << fileName << endl;
	}
	else {
		cerr << "Could not open the file to writing." << endl;
		return;
	}
}