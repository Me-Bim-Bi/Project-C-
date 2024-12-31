//
// Created by Chu Ha Thanh on 2024-12-14.
//

#include "Product.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include"FuntionToEditInformation.h"

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

void Product::setQuantitySold(int quantitySold) {
	this->quantitySold = quantitySold;
}

void Product::setQuantityImported(int quantityImported) {
	this->quantityImported = quantityImported;
}

bool Product::operator==(const Product &other) const {
	return id == other.id &&
		name == other.name &&
			purchasePrice == other.purchasePrice &&
				sellingPrice == other.sellingPrice &&
					quantityBeginningInventory == other.quantityBeginningInventory &&
						quantitySold == other.quantitySold;
}


void Product::editId() {
	editPrice("\nID: ", id, "ID");
}

void Product::editName() {
	editPrice("\nName: ", name, "Name");
}

void Product::editPurchasePrice() {
	editPrice("\nPurchase price: ", purchasePrice, "Purchase price");
}

void Product::editSellingPrice() {
	editPrice("\nSelling price: ", sellingPrice, "Selling price");
}

void Product::editQuantityBeginningInventory(){
	editPrice("\nBeginning inventory quantity: ", quantityBeginningInventory, "Beginning inventory quantity");
}

void Product::editQuantitySold() {
	editPrice("\nSold quantity: ", quantitySold, "Sold quantity");
}


void Product::editQuantityImported() {
	editPrice("\nImported quantity: ", quantityImported, "Imported quantity");
}

void Product::editInfoButNotID(){
	editName();
	editPurchasePrice();
	editSellingPrice();
	editQuantityBeginningInventory();
	editQuantityImported();
	while(true) {
		editQuantitySold();
		int quantityInStock = endOfDayInventory();
		if(quantityInStock >= 0) {
			break;
		}
		cerr << "The quantity of goods sold is incorrect. "
		"There is not enough stock to sell that much. "
		"Please try again!" << endl;
	}
}

double Product::totalCostOfGoods() const{
	return purchasePrice*(static_cast<float>(quantityBeginningInventory) + static_cast<float>(quantityImported));
}

double Product::totalRevenue() const {
	return sellingPrice*static_cast<float>(quantitySold);
}

int Product::endOfDayInventory() const {
	int quantityEndOfDay = quantityBeginningInventory + quantityImported - quantitySold;
	return quantityEndOfDay;
}

string Product::showInfo() const {
	ostringstream stringInfo;
	stringInfo << fixed << setprecision(2);
	stringInfo << "ID: " << id
	<< ", name: " << name
	<< ", purchase price: " << purchasePrice
	<< ", selling price: " << sellingPrice
	<< ", beginning inventory: " << quantityBeginningInventory
	<< ", number of goods imported: " << quantityImported
	<< ", number of goods sold: " << quantitySold
	<< ", number of goods in stock: " << endOfDayInventory();
	return stringInfo.str();
}

Product * Product::clone() const {
}
