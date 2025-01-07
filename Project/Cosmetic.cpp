//
// Created by Chu Ha Thanh on 2024-12-15.
//

#include "Cosmetic.h"
#include "Product.h"
#include"FuntionToEditInformation.h"
#include <iostream>

using namespace std;

Cosmetic::Cosmetic(int id, const string& name, float purchasePrice, float sellingPrice,
		int quantityBeginningInventory, int quantitySold, int quantityImported, const string& type):
Product(id, name, purchasePrice,sellingPrice, quantityBeginningInventory,
	quantitySold, quantityImported), type(type){
}

Cosmetic::~Cosmetic() = default;

string Cosmetic::getType() const {
	return this->type;
}

void Cosmetic::editType() {
	editPrice("\nType: ", type, "Type");
}

void Cosmetic::editInfoButNotID() {
	Product::editInfoButNotID();
	editType();
}

bool Cosmetic::operator==(const Product &other) const {
	const auto* otherClothing = dynamic_cast<const Cosmetic*>(&other);
	return otherClothing && Product::operator==(*otherClothing) &&
		type == otherClothing->type;
}

string Cosmetic::showInfo() const {
	return "Cosmetic: " + Product::showInfo() + ", type: " + type;
}

Product * Cosmetic::clone() const {
	return new Cosmetic(*this);
}
