//
// Created by Chu Ha Thanh on 2024-12-14.
//

#include "Product.h"
#include <iostream>

using namespace std;

Product::Product(int id, const string& name, float price, const string& brand, int quantity):
id(id), name(name), price(price), brand(brand), quantity(quantity){
}

Product::~Product() {
}

int Product::getID() const {
	return this->id;
}

string Product::getName() const {
	return this->name;
}

float Product::getPrice() const {
	return this->price;
}

string Product::getBrand() const {
	return this->brand;
}

int Product::getQuantity() const {
	return this->quantity;
}

void Product::setID(int id) {
	this->id = id;
}

void Product::setName(const string &name) {
	this->name = name;
}

void Product::setPrice(float price) {
	this->price = price;
}

void Product::setBrand(const string &brand) {
	this->brand = brand;
}

void Product::setQuantity(int quantity) {
	this->quantity = quantity;
}

void Product::editInfo(){
	cout << "Enter new information to update the product: " << endl;
	cout << "ID: ";
	cin >> id;
	cin.ignore();
	cout << "\nName: ";
	getline(cin, name);
	cout << "\nPrice: ";
	cin >> price;
	cin.ignore();
	cout << "\nBrand: ";
	getline(cin, brand);
	cout << "\nQuantity: ";
	cin >> quantity;
	cin.ignore();
}

string Product::showInfo() const {
	return "Name: " + name + ", id: " + to_string(id) + ", brand: "
	+ brand + ", price: " + to_string(price) + ", quantity: " + to_string(quantity);
}

float Product::totalPrice() const {
	return this->price * static_cast<float>(this->quantity);
}

Product * Product::clone() const {
}
