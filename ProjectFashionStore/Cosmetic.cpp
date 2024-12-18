//
// Created by Chu Ha Thanh on 2024-12-15.
//

#include "Cosmetic.h"
#include "Product.h"
#include <iostream>

using namespace std;

Cosmetic::Cosmetic(int id, const string &name, float price, const string &brand, int quantity,
	const string &type):Product(id, name, price, brand, quantity), type(type){
}

Cosmetic::Cosmetic():Product(), type("?") {
}

string Cosmetic::getType() const {
	return this->type;
}

void Cosmetic::setType(const string& type) {
	this->type = type;
}

void Cosmetic::editInfo() {
	Product::editInfo();
	cout << "\nType: ";
	getline(cin, type);
}

/*bool Cosmetic::operator==(const Cosmetic &other) const {
	return Product::operator==(other)
	&& this->type == other.type;
}
*/
string Cosmetic::showInfo() const {
	return "Cosmetic: " + Product::showInfo() + ", type: " + type;
}

Product * Cosmetic::clone() const {
	return new Cosmetic(*this);
}
