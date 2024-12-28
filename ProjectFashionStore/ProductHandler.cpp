//
// Created by Chu Ha Thanh on 2024-12-16.
//

#include "ProductHandler.h"
#include "Clothing.h"
#include "Cosmetic.h"
#include "EmployeeHandler.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> // to use "transform" to change string input in function "askYesNO" to capital letters
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

void ProductHandler::loadProductsFromFie(const string &fileName) {
	ifstream in(fileName);
	if(in.is_open()) {
		string line;
		while (getline(in, line)) {
			istringstream input(line);
			string typeProduct, name, brand, size, typeCosmetic, colour;
			int id, quantityBeginningInventory, quantitySold, quantityImported, quantityInStock;
			float purchasePrice, sellingPrice;

			getline(input, typeProduct, ',');
			input >> id;
			input.ignore();
			getline(input, name, ',');
			input >> purchasePrice;
			input.ignore();
			input >> sellingPrice;
			input.ignore();
			getline(input, brand, ',');
			input >> quantityBeginningInventory;
			input.ignore();
			input >> quantitySold;
			input.ignore();
			input >> quantityImported;
			input.ignore();
			quantityInStock = quantityBeginningInventory + quantityImported - quantitySold;
			quantityBeginningInventory = quantityInStock;
			quantitySold = 0;
			quantityImported = 0;

			Product* product = nullptr;

			if(typeProduct == "Clothing") {
				getline(input, size, ',');
				getline(input, colour, ',');
				product = new Clothing (id, name, purchasePrice, sellingPrice, brand, quantityBeginningInventory, quantitySold,
					quantityImported, size, colour);
			}
			else if (typeProduct == "Cosmetic") {
				getline(input, typeCosmetic, '\n');
				product = new Cosmetic (id, name, purchasePrice, sellingPrice, brand, quantityBeginningInventory, quantitySold,
					quantityImported, typeCosmetic);
			}
			else {
				cerr << "Unknown product type. Skipping." << endl;
			}
			if(product) {
				importProduct(product);
				delete product;
			}
		}
		in.close();
	}
	else {
		cerr << "The file was not found or could not be opened." << endl
		<< "The inventory was not updated." << endl;
		return;
	}
}

void ProductHandler::saveProductToFile(const string& fileName) {
	ofstream out(fileName);
	if(out.is_open()) {
		for(const auto& product : products) {

			string typeProduct;
			int id = product->getID();
			string name = product->getName();
			float purchasePrice = product->getPurchasePrice();
			float sellingPrice = product->getSellingPrice();
			string brand = product->getBrand();
			int quantityBeginningInventory = product->getQuantityBeginningInventory();
			int quantitySold = product->getQuantitySold();
			int quantityImported = product->getQuantityImported();

			if(dynamic_cast<Clothing*>(product)) {
				typeProduct = "Clothing";
				auto* clothing = dynamic_cast<Clothing*>(product);
				string size = clothing->getSize();
				string colour = clothing->getSize();
				out << typeProduct << ',' << id << ',' << name << ',' << purchasePrice << ','
				<< sellingPrice << ',' << brand << ',' << quantityBeginningInventory << ','
				<< quantitySold << ',' << quantityImported << ',' << size << ',' << colour << '\n';
			}
			else if (dynamic_cast<Cosmetic*>(product)) {
				typeProduct = "Cosmetic";
				auto* cosmetic = dynamic_cast<Cosmetic*>(product);
				string typeCosmetic = cosmetic->getType();
				out << typeProduct << ',' << id << ',' << name << ',' << purchasePrice << ','
				<< sellingPrice << ',' << brand << ',' << quantityBeginningInventory << ','
				<< quantitySold << ',' << quantityImported << ',' << typeCosmetic << '\n';
			}
			else {
				continue;
			}
		}
		out.close();
		cout << "Products saved to file: " << fileName << endl;
	}
	else {
		cerr << "The file was not found or could not be opened." << endl;
		return;
	}
}
