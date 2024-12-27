//
// Created by Chu Ha Thanh on 2024-12-14.
//

#include "Product.h"
#include <iostream>
#include "ProductHandler.h"

using namespace std;

Product::Product(int id, const string& name, float purchasePrice, float sellingPrice, const string& brand,
	int quantity, int quantitySold, int quantityPurchased): id(id), name(name), purchasePrice(purchasePrice),
sellingPrice(sellingPrice), brand(brand), quantity(quantity), quantitySold(quantitySold),
quantityPurchased(quantityPurchased){
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

string Product::getBrand() const {
	return this->brand;
}

int Product::getQuantity() const {
	return this->quantity;
}

int Product::getQuantitySold() const {
	return this->quantitySold;
}

int Product::getQuantityPurchased() const {
	return this->quantityPurchased;
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


void Product::setBrand(const string &brand) {
	this->brand = brand;
}

void Product::setQuantity(int quantity) {
	this->quantity = quantity;
}

void Product::setQuantitySold(int quantitySold) {
	this->quantitySold = quantitySold;
}

void Product::setQuantityPurchased(int quantityPurchased) {
	this->quantityPurchased = quantityPurchased;
}

void Product::editInfoButNotID(){
	cin.ignore();
	cout << "\nName: ";
	getline(cin, name);
	cout << "\nPurchase price: ";
	cin >> purchasePrice;
	cin.ignore();
	cout << "\nSelling price: ";
	cin >> sellingPrice;
	cin.ignore();
	cout << "\nBrand: ";
	getline(cin, brand);
	cout << "\nQuantity in stock: ";
	cin >> quantity;
	cin.ignore();
	cout << "\nQuantity sold: ";
	cin >> quantitySold;
	cin.ignore();
	cout << "\nQuantity purchased: ";
	cin >> quantityPurchased;
	cin.ignore();
}

bool Product::operator==(const Product &other) const {
	return id == other.id &&
		name == other.name &&
			purchasePrice == other.purchasePrice &&
				sellingPrice == other.sellingPrice &&
					brand == other.brand &&
						quantity == other.quantity &&
							quantitySold == other.quantitySold;
}

float Product::totalCostOfGoods() const {
	return purchasePrice*(quantity + quantityPurchased);
}

float Product::totalRevenue() const {
	return sellingPrice*quantitySold;
}

int Product::endOfDayInventory() const {
	int quantityEndOfDay = quantity + quantityPurchased - quantitySold;
	return quantityEndOfDay;
}

string Product::showInfo() const {
	return name + ", id: " + to_string(id) + ", brand: "
	+ brand + ", purchase price: " + to_string(purchasePrice) + ", selling price: " +
		to_string(sellingPrice) +", \n\tbeginning inventory: " + to_string(quantity)
	+ ", numbers of goods imported: " + to_string(quantityPurchased)
	+ ", number of goods sold: " + to_string(quantitySold);
}

Product * Product::clone() const {
}
