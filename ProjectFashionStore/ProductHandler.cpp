//
// Created by Chu Ha Thanh on 2024-12-16.
//

#include "ProductHandler.h"
#include "Clothing.h"
#include "Employee.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm> // to use "transform" to change string input in function "askYesNO" to capital letters

#include "EmployeeHandler.h"

#include <cctype> // to "toupper" to change string input in function "askYesNO" to capital letters

using namespace std;

//rule: only 1 id product number can exist in system => always need to check
//if the id already exists.

int ProductHandler::findIndexProduct(int id) const {
	int index = -1;
	for (int i = 0; i < products.size(); i++) {
		if(products[i]->getID() == id) {
			index = i;
			}
	}
	return index;
}

ProductHandler::ProductHandler(){
}

//free up memory
ProductHandler::~ProductHandler() {
	for (auto product : products) {
		delete product;
	}
	cout << "destruct ProductHandler" << endl;
}

ProductHandler::ProductHandler(const ProductHandler &other) {
	for (auto product : other.products) {
		products.push_back(product->clone());
	}
}

ProductHandler ProductHandler::operator=(const ProductHandler &other) {
	if(this != & other) {
		for (auto product : products) {
			delete product;
		}
		products.clear();
		for (const auto& product : other.products) {
			products.push_back(product->clone());
		}
	}
	return *this;
}

void ProductHandler::importProduct(Product* product) {
	int idProduct = product->getID();
	int index = findIndexProduct(idProduct);
	//check if the product exists in system => only add the quantityPurchase
	if(index != -1) {
		if(*this->products[index] == *product) {
			int quantityAfterImport = products[index]->getQuantityImported() + product->getQuantityImported();
			products[index]->setQuantityImported(quantityAfterImport);
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
		//check if the product does not exist in system => add the new product via clone
		products.push_back(product->clone());
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

void ProductHandler::editProduct(const int id) {
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

void ProductHandler::sellProduct(int idProduct, int quantitySale, int idEmployee, EmployeeHandler& emp) {
	int index = findIndexProduct(idProduct);
	if(index != -1) {
		int quantityInStock = products[index]->getQuantityBeginningInventory()+products[index]->getQuantityImported();
		int totalQuantitySold = products[index]->getQuantitySold()+quantitySale;
		if(totalQuantitySold <= quantityInStock) {
			products[index]->setQuantitySold(totalQuantitySold);
			if(emp.callFindIdIndex(idEmployee) != -1) {
				float employeeCommission = (products[index]->getSellingPrice() * quantitySale) * 0.02;
				emp.addCommission(idEmployee,employeeCommission);
			}
			else {
				cout << "The employee's ID " << idEmployee << " was not found. The commission has not been credited to anyone." << endl;
			}
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
	cout << "Total price of all products is: " << totalCostOfProducts() << endl
	<< "Total revenue is: " << totalRevenue() << endl;
}


bool ProductHandler::askYesNo(const string &question) {
	string input;
	while (true) {
		cout << question << " (yes/no): ";
		cin >> input;
		transform(input.begin(), input.end(), input.begin(), ::toupper);
		if (input == "YES") {
			return true;
		} else if (input == "NO") {
			return false;
		} else {
			cout << "Invalid input! Please enter 'yes' or 'no'." << endl;
		}
	}
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
