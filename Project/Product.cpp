//
// Created by Chu Ha Thanh on 2024-12-14.
//

#include "Product.h"
#include "ProductHandler.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

Product::Product(int id, const string& name, float purchasePrice, float sellingPrice,
	int quantityBeginningInventory, int quantitySold, int quantityImported): id(id), name(name), purchasePrice(purchasePrice),
sellingPrice(sellingPrice), quantityBeginningInventory(quantityBeginningInventory), quantitySold(quantitySold),
quantityImported(quantityImported){
}

Product::~Product() {
}

int Product::getID() const {
	return this->id;
}

string Product::getName() const {
	return this->name;
}

float Product::getPurchasePrice() const {
	return this->purchasePrice;
}

float Product::getSellingPrice() const {
	return this->sellingPrice;
}

int Product::getQuantityBeginningInventory() const {
	return this->quantityBeginningInventory;
}

int Product::getQuantitySold() const {
	return this->quantitySold;
}

int Product::getQuantityImported() const {
	return this->quantityImported;
}

void Product::setID(int id) {
	this->id = id;
}

void Product::setQuantitySold(int quantitySold) {
	this->quantitySold = quantitySold;
}

void Product::setQuantityImported(int quantityImported) {
	this->quantityImported = quantityImported;
}

void Product::editId() {
	while (true) {
		string input;
		cout << "\nID: ";
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
				// check if input is within the range of int
				if (long long temp = stoll (input); temp < numeric_limits<int>::min() || temp > numeric_limits<int>::max()) {
					throw out_of_range("Number out of range for int type.");
				}
				else {
					id = static_cast<int>(temp);
				}

				if (id <= 0) {
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
}

void Product::editName() {
	cout << "\nName: ";
	getline(cin, name);
}

void Product::editPurchasePrice() {
	while (true) {
		string input;
		cout << "\nPurchase price: ";
		cin >> input;

		try {
			size_t onlyNumber;
			float temp = stof(input, &onlyNumber);

			if(onlyNumber != input.size()) {
				throw invalid_argument("Contains invalid characters");
			}
			if (temp < 0) {
				cout << "Input is less than 0. Purchase price must be a positive number. Please try again.\n" << endl;
			}
			else {
				purchasePrice = temp;
				break;
			}
		}
		catch (invalid_argument&) {
			cout << "Invalid input. Purchase price must be a positive number. Please try again.\n" << endl;
		}
		catch (out_of_range&) {
			cout << "You must have entered the wrong information"
			<< ". We do not have anything that expensive." << endl;
		}
		cin.clear(); //delete the wrong status
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the wrong input data
	}
	cin.ignore();
}

void Product::editSellingPrice() {
	while (true) {
		string input;
		cout << "\nSelling price: ";
		cin >> input;

		try {
			size_t onlyNumber;
			float temp = stof(input, &onlyNumber);

			if(onlyNumber != input.size()) {
				throw invalid_argument("Contains invalid characters");
			}
			if (temp < 0) {
				cout << "Input is less than 0. Selling price must be a positive number. Please try again.\n" << endl;
			}
			else {
				sellingPrice = temp;
				break;
			}
		}
		catch (invalid_argument&) {
			cout << "Invalid input. Selling price must be a positive number. Please try again.\n" << endl;
		}
		catch (out_of_range&) {
			cout << "You must have entered the wrong information"
			<< ". We do not sale anything that expensive." << endl;
		}
		cin.clear(); //delete the wrong status
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the wrong input data
	}
	cin.ignore();
}

void Product::editQuantityBeginningInventory(){
	while (true) {
		string input;
		cout << "\nBeginning inventory quantity: ";
		cin >> input;
		bool isNumeric = true;
		for (char cha : input) {
			if (!isdigit(cha)) {
				isNumeric = false;
				break;
			}
		}
		if(!isNumeric) {
			cout << "Invalid input. Beginning inventory quantity must be a number. Please try again.\n" << endl;
		}
		else {
			try {
				long long temp = stoll (input);

				// check if input is within the range of int
				if (temp < numeric_limits<int>::min() || temp > numeric_limits<int>::max()) {
					throw out_of_range("Number out of range for int type.");
				}
				else {
					quantityBeginningInventory = static_cast<int>(temp);
				}

				if (quantityBeginningInventory < 0) {
					cout << "Invalid input. Beginning inventory quantity must be a positive number. Please try again.\n";
				} else {
					break;
				}
			} catch (invalid_argument&) {
				cout << "Invalid input. Beginning inventory quantity must be a valid number. Please try again.\n";
			} catch (out_of_range&) {
				cout << "You must have entered the wrong information. "
			"We do not have so many products in our stock. Please try again.\n";
			}
		}
		cin.clear(); //delete the wrong status
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the wrong input data
	}
	cin.ignore();
}

void Product::editQuantitySold() {
	while (true) {
		string input;
		cout << "\nSold quantity: ";
		cin >> input;
		bool isNumeric = true;
		for (char cha : input) {
			if (!isdigit(cha)) {
				isNumeric = false;
				break;
			}
		}
		if(!isNumeric) {
			cout << "Invalid input. Sold quantity must be a number. Please try again.\n" << endl;
		}
		else {
			try {
				long long temp = stoll (input);

				// check if input is within the range of int
				if (temp < numeric_limits<int>::min() || temp > numeric_limits<int>::max()) {
					throw out_of_range("Number out of range for int type.");
				}
				else {
					quantitySold = static_cast<int>(temp);
				}

				if (quantitySold < 0) {
					cout << "Invalid input. Sold quantity must be a positive number. Please try again.\n";
				} else {
					break;
				}
			} catch (invalid_argument&) {
				cout << "Invalid input. Sold quantity must be a valid number. Please try again.\n";
			} catch (out_of_range&) {
				cout << "You must have entered the wrong information."
			" Unfortunately we can't sell that many products.. Please try again.\n";
			}
		}
		cin.clear(); //delete the wrong status
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the wrong input data
	}
	cin.ignore();
}


void Product::editQuantityImported() {
	while (true) {
		string input;
		cout << "\nImported quantity: ";
		cin >> input;
		bool isNumeric = true;

		for (char cha : input) {
			if (!isdigit(cha)) {
				isNumeric = false;
				break;
			}
		}
		if(!isNumeric) {
			cout << "Invalid input. Imported quantity must be a number. Please try again.\n" << endl;
		}
		else {
			try {
				long long temp = stoll (input);

				// check if input is within the range of int
				if (temp < numeric_limits<int>::min() || temp > numeric_limits<int>::max()) {
					throw out_of_range("Number out of range for int type.");
				}
				else {
					quantityImported = static_cast<int>(temp);
				}

				if (quantityImported < 0) {
					cout << "Invalid input. Imported quantity must be a positive number. Please try again.\n";
				} else {
					break;
				}
			} catch (invalid_argument&) {
				cout << "Invalid input. Imported quantity must be a valid number. Please try again.\n";
			} catch (out_of_range&) {
				cout << "You must have entered the wrong information."
			" Our warehouse cannot import that much goods.. Please try again.\n";
			}
		}
		cin.clear(); //delete the wrong status
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the wrong input data
	}
	cin.ignore();
}

void Product::editInfoButNotID(){
	editName();
	editPurchasePrice();
	editSellingPrice();
	editQuantityBeginningInventory();
	editQuantityImported();
	while(true) {
		editQuantitySold();
		int quantityInStock = endOfDayInventory();
		if(quantityInStock >= 0) {
			break;
		}
		else {
			cout << "The quantity of goods sold is incorrect. "
		   "There is not enough stock to sell that much. "
			"Please try again!" << endl;
			continue;
		}
	}
}

bool Product::operator==(const Product &other) const {
	return id == other.id &&
		name == other.name &&
			purchasePrice == other.purchasePrice &&
				sellingPrice == other.sellingPrice &&
					quantityBeginningInventory == other.quantityBeginningInventory &&
						quantitySold == other.quantitySold;
}

double Product::totalCostOfGoods() const{
	return purchasePrice*(static_cast<float>(quantityBeginningInventory) + static_cast<float>(quantityImported));
}

double Product::totalRevenue() const {
	return sellingPrice*static_cast<float>(quantitySold);
}

int Product::endOfDayInventory() const {
	int quantityEndOfDay = quantityBeginningInventory + quantityImported - quantitySold;
	return quantityEndOfDay;
}

string Product::showInfo() const {
	ostringstream stringInfo;
	stringInfo << fixed << setprecision(2);
	stringInfo << "ID: " << id
	<< ", name: " << name
	<< ", purchase price: " << purchasePrice
	<< ", selling price: " << sellingPrice
	<< ", beginning inventory: " << quantityBeginningInventory
	<< ", number of goods imported: " << quantityImported
	<< ", number of goods sold: " << quantitySold
	<< ", number of goods in stock: " << endOfDayInventory();
	return stringInfo.str();
}

Product * Product::clone() const {
}
