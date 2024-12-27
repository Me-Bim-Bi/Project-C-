//
// Created by Chu Ha Thanh on 2024-12-16.
//

#include "ProductHandler.h"
#include "Clothing.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "Employee.h"

using namespace std;

//only 1 id product number exist in system


bool ProductHandler::askYesNo(const string &question) {
    string input;
    while (true) {
        cout << question << " (yes/no): ";
        cin >> input;
        if (input == "yes" || input == "YES" || input == "Yes") {
            return true;
        } else if (input == "no" || input == "NO" || input == "No") {
            return false;
        } else {
            cout << "Invalid input! Please enter 'yes' or 'no'." << endl;
        }
    }
}

int ProductHandler::findIndexProduct(int id) const {
	int index = -1;
	for (int i = 0; i < products.size(); i++) {
		if(products[i]->getID() == id) {
			index = i;
			}
	}
	return index;
}

ProductHandler::ProductHandler() {
}

ProductHandler::~ProductHandler() {
	for (auto product : products) {
		delete product;
	}
}

void ProductHandler::importProduct(Product* product) {
	int idProduct = product->getID();
	int index = findIndexProduct(idProduct);
	//check if the product exists in system => only add the quantityPurchase
	if(index != -1) {
		if(*this->products[index] == *product) {
			int quantityAfterImport = products[index]->getQuantityPurchased() + product->getQuantityPurchased();
			products[index]->setQuantityPurchased(quantityAfterImport);
		}
		else
		{
			cout << "The product's id exist in system but the other information do not match. "
		   "Please check again!" << endl
			<< "Here is the information of product in the system now: " << endl
			<< products[index]->showInfo();
		}
	}
	else {
		//check if the product does not exist in system => add the new product
		products.push_back(product);
	}
}

void ProductHandler::findAndShowProduct(const int id) const {
	int index = findIndexProduct(id);
	if (index != -1)
	{
		cout << "The product with the id " << id << " have got the following information: " << endl
		<< products[index]->showInfo() << endl;
	}
	else{
		cout << "Product with ID: " << id << " was not found!";
	}
}

void ProductHandler::removeProduct(const int id) {
	int index = findIndexProduct(id);
	if (index != -1) {
		cout << "The product with the id " << id << " have got the following information: " << endl
		<< products[index]->showInfo() << endl;
		if (askYesNo("Do you want to remove this product? ")) {
			products.erase(products.begin() + index);
			cout << "The product has been deleted." << endl;
		}
		else{
			cout << "Product with ID: " << id << " was not found!";
		}
	}
}

void ProductHandler::editProductId(int id) {
	int index = findIndexProduct(id);
	if (index != -1) {
		if (askYesNo("Do you want to edit the id of this product? ")) {
			cout << "New ID: ";
			int newID = 0;
			cin >> newID;
			if (findIndexProduct(newID) != -1) {
				cout << "Error! The new ID you entered already exists. The id changed failed." << endl;
			}
			else {
				products[index]->setID(newID);
				cout << "The product id has been edited." << endl;
			}
		}
		else{
			cout << "The product id has not been edited." << endl;
		}
	}
	else {
		cout << "Product with ID: " << id << " was not found!";
	}
}

void ProductHandler::editProductButNotID(const int id) {
	int index = findIndexProduct(id);
	if (index != -1) {
		cout << "The product with the id number " << id << " have got following information: " << endl
		<< products[index]->showInfo() << endl;
		if (askYesNo("Is it the product that you want to edit? ")) {
			editProductId(id);
			if (askYesNo("Do you want change the another information of this product? ")) {
				products[index]->editInfoButNotID();
				cout << "The product information has been edited." << endl;
			}
			else {
				cout << "The another information of this product has not been edited." << endl;
			}
		}
		else{
			cout << "The product information has not been edited." << endl;
		}
	}
	else {
		cout << "Product with ID: " << id << " was not found!";
	}
}

void ProductHandler::sellProduct(int idProduct, int quantitySale, int idEmployee) {
	int index = findIndexProduct(idProduct);
	if(index != -1) {
		int quantityAfterSale = products[index]->getQuantity()+products[index]->getQuantityPurchased()
	- products[index]->getQuantitySold()-quantitySale;
		if(quantityAfterSale >= 0) {
			products[index]->setQuantitySold(quantityAfterSale);
		}
		else {
			cout << "The product with id " << idProduct << " is out of stock." << endl;
		}
	}
	else {
		cout << "Sorry! We don't have any product with id " << idProduct << " in store." << endl;
	}
}

float ProductHandler::totalCostOfProducts() const {
	float total = 0.0f;
	for (auto product : products) {
		total += product->totalCostOfGoods();
	}
	return total;
}

float ProductHandler::totalRevenue() const {
	float total = 0.0f;
	for (auto product : products) {
		total += product->totalRevenue();
	}
	return total;
}

void ProductHandler::showProduct() const {
	int index = 1;
	cout << "\nProduct in store now:\n";
	for (auto product : products) {
		cout << index << ". " << product->showInfo() << endl;
		index++;
	}
	cout << "Total price of all products is: " << totalCostOfProducts() << endl;
	cout << "Total revenue is: " << totalRevenue() << endl;
}



/*
void ProductHandler::updateSourceFile(string fileName) {
	try{
		ifstream in;
		in.open(fileName);
		if(in.is_open()) {

		}
	}
}
*/
