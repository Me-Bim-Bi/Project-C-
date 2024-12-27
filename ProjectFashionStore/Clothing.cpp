//
// Created by Chu Ha Thanh on 2024-12-14.
//

#include "Clothing.h"
#include"Product.h"
#include <iostream>

using namespace std;

Clothing::Clothing(int id, const string& name, float purchasePrice, float sellingPrice, const string& brand,
		int quantity, int quantitySold, int quantityPurchased, const string& size, const string& colour) : Product(id,name,purchasePrice,sellingPrice,
			brand,quantity,quantitySold,quantityPurchased), size(size), colour(colour){
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

void Clothing::editInfoButNotID() {
	cout << "Enter new information to update the product: ";
	Product::editInfoButNotID();
	cout << "\nSize: ";
	getline(cin, size);
	cout << "\nColour: ";
	getline(cin, colour);
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

//när vi skriver på filen får vi skriva med "CLothing" eller "Cosmetic" i början
// sedan kommer de andra infomation. Vilken blir seperatade för de?
Product * Clothing::clone() const {
	return new Clothing(*this);
}
