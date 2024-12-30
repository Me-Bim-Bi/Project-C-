//
// Created by Chu Ha Thanh on 2024-12-14.
//

#include "Clothing.h"
#include"Product.h"
#include <iostream>

using namespace std;

Clothing::Clothing(int id, const string& name, float purchasePrice, float sellingPrice, int quantityBeginningInventory,
	int quantitySold, int quantityImported, const string& size, const string& colour) : Product(id,name,purchasePrice,
		sellingPrice,quantityBeginningInventory,quantitySold,quantityImported), size(size), colour(colour){
}

Clothing::~Clothing() = default;

string Clothing::getSize() const {
	return this->size;
}

string Clothing::getColour() const {
	return this->colour;
}

void Clothing::editSize() {
	cout << "\nSize: ";
	getline(cin, size);
}

void Clothing::editColour() {
	cout << "\nColour: ";
	getline(cin, colour);
}

void Clothing::editInfoButNotID() {
	Product::editInfoButNotID();
	editSize();
	editColour();
}

bool Clothing::operator==(const Product &other) const {
	const Clothing* otherClothing = dynamic_cast<const Clothing*>(&other);
	return otherClothing && Product::operator==(*otherClothing) &&
		size == otherClothing->size &&
			colour == otherClothing->colour;
}

string Clothing::showInfo() const {
	return "Clothing: " + Product::showInfo() + ", size: " + size + ", colour " + colour;
}

Product * Clothing::clone() const {
	return new Clothing(*this);
}
