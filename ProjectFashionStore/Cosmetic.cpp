//
// Created by Chu Ha Thanh on 2024-12-15.
//

#include "Cosmetic.h"
#include "Product.h"
#include <iostream>

using namespace std;

Cosmetic::Cosmetic(int id, const string& name, float purchasePrice, float sellingPrice, const string& brand,
		int quantity, int quantitySold, int quantityPurchased, const string& type):Product(id, name, purchasePrice,sellingPrice,
			brand, quantity, quantitySold, quantityPurchased), type(type){
}

string Cosmetic::getType() const {
	return this->type;
}

void Cosmetic::setType(const string& type) {
	this->type = type;
}

bool Cosmetic::operator==(const Product &other) const {
	const Cosmetic* otherClothing = dynamic_cast<const Cosmetic*>(&other);
	return otherClothing && Product::operator==(*otherClothing) &&
		type == otherClothing->type;
}

void Cosmetic::editInfoButNotID() {
	cout << "Enter new information to update the product: ";
	Product::editInfoButNotID();
	cout << "\nType: ";
	getline(cin, type);
}

string Cosmetic::showInfo() const {
	return "Cosmetic: " + Product::showInfo() + ", type: " + type;
}

Product * Cosmetic::clone() const {
	return new Cosmetic(*this);
}
