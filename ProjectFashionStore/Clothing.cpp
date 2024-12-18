//
// Created by Chu Ha Thanh on 2024-12-14.
//

#include "Clothing.h"
#include"Product.h"
#include <iostream>

using namespace std;

Clothing::Clothing(int id, const string &name, float price, const string &brand, int quantity, const string &size,
	const string &colour) : Product(id,name,price,brand,quantity), size(size), colour(colour){
}

Clothing::Clothing(): Product(), size("?"), colour("?") {
}

string Clothing::getSize() const {
	return this->size;
}

string Clothing::getColour() const {
	return this->colour;
}

void Clothing::setSize(const string &size) {
	this->size = size;
}

void Clothing::setColour(const string &colour) {
	this->colour = colour;
}

void Clothing::editInfo() {
	cout << "Enter new information to update the product: " << endl;
	Product::editInfo();
	cout << "\nSize: ";
	getline(cin, size);
	cout << "\nColour: ";
	getline(cin, colour);
}

string Clothing::showInfo() const {
	return "Clothing: " + Product::showInfo() + ", size: " + size + ", colour " + colour;
}

Product * Clothing::clone() const {
	return new Clothing(*this);
}
