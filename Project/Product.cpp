//
// Created by Chu Ha Thanh on 2024-12-14.
//

#include "Product.h"
#include <iostream>
#include "ProductHandler.h"

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

void Product::setName(const string &name) {
	this->name = name;
}

void Product::setPurchasePrice(float purchasePrice) {
	this->purchasePrice = purchasePrice;
}

void Product::setSellingPrice(float sellingPrice) {
	this->sellingPrice = sellingPrice;
}

void Product::setQuantityBeginningInventory(int quantityBeginningInventory) {
	this->quantityBeginningInventory = quantityBeginningInventory;
}

void Product::setQuantitySold(int quantitySold) {
	this->quantitySold = quantitySold;
}

void Product::setQuantityImported(int quantityImported) {
	this->quantityImported = quantityImported;
}

void Product::editId() {
	while (true) {
		cout << "\nID: ";
		cin >> id;
		if (cin.fail() || id < 0) { //check if the input data less than 0 or not a number
			cin.clear(); //delete the wrong status
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the wrong input data
			cout << "Invalid input. ID must be a positive number. Please try again.\n";
		} else {
			break;
		}
	}
	cin.ignore();
}

void Product::editName() {
	cout << "\nName: ";
	getline(cin, name);
}

void Product::editPurchasePrice() {
	while (true) {
		cout << "\nPurchase price: ";
		cin >> purchasePrice;
		if (cin.fail() || purchasePrice < 0) { //check if the input data less than 0 or not a number
			cin.clear(); //delete the wrong status
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the wrong input data
			cout << "Invalid input. Purchase price must be a positive number. Please try again.\n";
		} else {
			break;
		}
	}
	cin.ignore();
}

void Product::editSellingPrice() {
	while (true) {
		cout << "\nSelling price: ";
		cin >> sellingPrice;
		if (cin.fail() || sellingPrice < 0) { //check if the input data less than 0 or not a number
			cin.clear(); //delete the wrong status
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the wrong input data
			cout << "Invalid input. Selling price must be a positive number. Please try again.\n";
		} else {
			break;
		}
	}
	cin.ignore();
}

void Product::editQuantityBeginningInventory() {
	while (true) {
		cout << "\nBeginning inventory quantity: ";
		cin >> quantityBeginningInventory;
		if (cin.fail() || quantityBeginningInventory < 0) { //check if the input data less than 0 or not a number
			cin.clear(); //delete the wrong status
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the wrong input data
			cout << "Invalid input. The beginning inventory quantity must be a positive number. Please try again.\n";
		} else {
			break;
		}
	}
	cin.ignore();
}

void Product::editQuantitySold() {
	while (true) {
		cout << "\nSold quantity: ";
		cin >> quantitySold;
		if (cin.fail() || quantitySold < 0) { //check if the input data less than 0 or not a number
			cin.clear(); //delete the wrong status
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the wrong input data
			cout << "Invalid input. The sold quantity must be a positive number. Please try again.\n";
		} else {
			break;
		}
	}
	cin.ignore();
}

void Product::editQuantityImported() {
	while (true) {
		cout << "\nImported quantity: ";
		cin >> quantityImported;
		if (cin.fail() || quantityImported < 0) { //check if the input data less than 0 or not a number
			cin.clear(); //delete the wrong status
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the wrong input data
			cout << "Invalid input. The imported quantity must be a positive number. Please try again.\n";
		} else {
			break;
		}
	}
	cin.ignore();
}



void Product::editInfoButNotID(){
	editName();
	editPurchasePrice();
	editSellingPrice();
	editQuantityBeginningInventory();
	editQuantitySold();
	editQuantityImported();
}

bool Product::operator==(const Product &other) const {
	return id == other.id &&
		name == other.name &&
			purchasePrice == other.purchasePrice &&
				sellingPrice == other.sellingPrice &&
					quantityBeginningInventory == other.quantityBeginningInventory &&
						quantitySold == other.quantitySold;
}

float Product::totalCostOfGoods() const {
	return purchasePrice*(quantityBeginningInventory + quantityImported);
}

float Product::totalRevenue() const {
	return sellingPrice*quantitySold;
}

int Product::endOfDayInventory() const {
	int quantityEndOfDay = quantityBeginningInventory + quantityImported - quantitySold;
	return quantityEndOfDay;
}

string Product::showInfo() const {
	return name + ", id: " + to_string(id) + ", purchase price: "
	+ to_string(purchasePrice) + ", selling price: " + to_string(sellingPrice)
	+", \n\t beginning inventory: " + to_string(quantityBeginningInventory)
	+ ", numbers of goods imported: " + to_string(quantityImported)
	+ ", number of goods sold: " + to_string(quantitySold) + ", number of goods in stock: "
	+ to_string(endOfDayInventory());
}

Product * Product::clone() const {
}
