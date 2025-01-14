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
	//Check if two objects have the same value, considering specific details
	//use for function importProductFromFile
	const auto* otherCosmetic = dynamic_cast<const Cosmetic*>(&other);
	return otherCosmetic && Product::operator==(*otherCosmetic) &&
		type == otherCosmetic->type;
}

string Cosmetic::showInfo() const {
	return "Cosmetic: " + Product::showInfo() + ", type: " + type;
}

Product * Cosmetic::clone() const {
	return new Cosmetic(*this);
}
