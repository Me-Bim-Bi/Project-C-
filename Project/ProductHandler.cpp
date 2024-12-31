//
// Created by Chu Ha Thanh on 2024-12-16.
//

#include "ProductHandler.h"
#include "Clothing.h"
#include "Cosmetic.h"
#include "EmployeeHandler.h"
#include "Menu.h"
#include "Product.h"
#include "FuntionToEditInformation.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

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

ProductHandler::ProductHandler()= default;

//free up memory
ProductHandler::~ProductHandler() {
	for (auto product : products) {
		delete product;
	}
}

ProductHandler::ProductHandler(const ProductHandler &other) {
	for (auto product : other.products) {
		products.push_back(product->clone());
	}
}

ProductHandler& ProductHandler::operator=(const ProductHandler &other) {
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

void ProductHandler::importProduct(Product *product) {
	const int idProduct = product->getID();
	if(int index = findIndexProduct(idProduct); index != -1) {
		if(askYesNo("The product ID already exists in the system. "
			  "Would you like to import additional quantities of this product?")) {
			int WantToImport;
			editPrice("\nQuantity imported: ", WantToImport, "Quantity imported");
			int quantityAfterImport = products[index]->getQuantityImported() + WantToImport;
			products[index]->setQuantityImported(quantityAfterImport);
			  }
		else {
			cout << "The product with id: " << idProduct << " has not been updated." << endl;
		}
	}
	else {
		product->editInfoButNotID();
		products.push_back(product->clone());
	}
}


void ProductHandler::importProductFromFile(const Product* product) {
	const int idProduct = product->getID();
	//check if the product exists in system => only add the quantityPurchase
	if(int index = findIndexProduct(idProduct); index != -1) {
		if(*this->products[index] == *product) {
			int quantityAfterImport = products[index]->getQuantityImported() + product->getQuantityImported();
			products[index]->setQuantityImported(quantityAfterImport);
		}
		else
		{
			cerr << "The product's id exist in system but the other information do not match. "
		   "So we could not add them to the stock. Skipping..." << endl;
		}
	}
	else {
		products.push_back(product->clone());
	}
}

void ProductHandler::findAndShowProduct(const int id) const {
	if (int index = findIndexProduct(id); index != -1)
	{
		cout << "The product with the id " << id << " have got the following information: " << endl
		<< products[index]->showInfo() << endl;
	}
	else{
		cerr << "Product with ID: " << id << " was not found!";
	}
}

void ProductHandler::removeProduct(const int id) {
	if (int index = findIndexProduct(id); index != -1) {
		cout << "The product with the id " << id << " have got the following information: " << endl
		<< products[index]->showInfo() << endl;
		if (askYesNo("Do you want to remove this product? ")) {
			products.erase(products.begin() + index);
			cout << "The product has been deleted." << endl;
		}
		else{
			cout << "Product with ID: " << id << " was not deleted!" << endl;
		}
	}
	else {
		cerr << "Product with ID: " << id << " was not found." << endl;
	}
}

void ProductHandler::editProductId(int id) const {
	if (int index = findIndexProduct(id); index != -1) {
		if (askYesNo("Do you want to edit the id of this product? ")) {
			int newID;
			editPrice("\nNew ID: ", newID, "New ID");
			if (findIndexProduct(newID) != -1) {
				cerr << "Error! The new ID you entered already exists. The id changed failed." << endl;
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
		cerr << "Product with ID: " << id << " was not found!";
	}
}

void ProductHandler::editProduct(const int id) const {
	if (int index = findIndexProduct(id); index != -1) {
		cout << "The product with the id number " << id << " have got following information: " << endl
		<< products[index]->showInfo() << endl;
		if (askYesNo("Is it the product that you want to edit? ")) {
			editProductId(id);
			if (askYesNo("Do you want change the another information of this product? ")) {
				cout << "Please insert the new value: " << endl;
				cin.ignore();
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

void ProductHandler::sellProduct(EmployeeHandler& emp) const {
	int checkProductID = -1, checkEmployeeID = -1, quantitySale = -1, index = -1;
	//check if the product id exists
	while(true) {
		cout << "\nProduct ID: ";
		checkProductID = checkInputDataInt();
		index = findIndexProduct(checkProductID);
		if(index == -1) {
			cerr << "The product id: " << checkProductID << " does not exist. Please try again!" << endl;
		}
		else {
			break;
		}
	}
	//check if the employee id exists
	while(true) {
		cout << "\nEmployee ID: ";
		checkEmployeeID = checkInputDataInt();
		if(emp.callFindIdIndex(checkEmployeeID) == -1) {
			cerr << "The employee id: " << checkEmployeeID << " does not exist. Please try again!" << endl;
		}
		else {
			break;
		}
	}
	//check if the goods in stock are enough to sell
	while(true) {
		cout << "\nQuantity sold: ";
		quantitySale = checkInputDataInt();
		int quantity = products[index]->getQuantityBeginningInventory()+products[index]->getQuantityImported();
		int totalQuantitySold = products[index]->getQuantitySold()+quantitySale;
		if(totalQuantitySold <= quantity) {
			products[index]->setQuantitySold(totalQuantitySold);
			auto employeeCommission = products[index]->getSellingPrice() * static_cast<double>(quantitySale) * 0.02;
			emp.addCommission(checkEmployeeID,employeeCommission);
			break;
		}
		cerr << "The product " << checkProductID << " is out of stock. Please try again!" << endl;
	}
}

double ProductHandler::totalCostOfProducts() const {
	double total = 0.0f;
	for (auto product : products) {
		total += product->totalCostOfGoods();
	}
	return total;
}

double ProductHandler::totalRevenue() const {
	double total = 0.0f;
	for (auto product : products) {
		total += product->totalRevenue();
	}
	return total;
}

void ProductHandler::showInfo() const {
	int index = 1;
	cout << "\nProduct in store now:\n";
	for (auto product : products) {
		cout << index << ". " << product->showInfo() << endl;
		index++;
	}
}

void ProductHandler::loadProductsFromFie(const string &fileName) {
	ifstream in(fileName);
	if(!in.is_open()) {
		cerr << "Could not open the file: " << fileName << " for reading" << endl;
		return;              //throw the error message and stopp reading
	}
	else {
		string line;
		int lineNumber = 0; //count the line number to show the error message

		while(getline(in, line)) { //read through all lines to the end
			++lineNumber;
			istringstream input(line);
			vector <string> productInformation;    //create a vector to check the input data
			string aProduct;

			while(getline(input,aProduct,',')) {  //add input data to vector to check the data
				productInformation.push_back(aProduct);
			}

			if(productInformation.size() < 9) { //show the error message if the input data has not enough
				cerr << "Error on line: " << lineNumber <<". Unknown product format. Skipping..." << endl;
				continue;
			}
			string productType= productInformation[0], name = productInformation[2];
			try {
				int id = stoi(productInformation[1]);      //check if input data is valid, throw error message if it fails
				float purchasePrice = stof(productInformation[3]);
				float sellingPrice = stof(productInformation[4]);
				int quantityBeginningInventory = stoi(productInformation[5]);
				int quantitySold = stoi(productInformation[6]);
				int quantityImported = stoi(productInformation[7]);

				unique_ptr<Product> product; //create a smart pointer to make everything easier

				if(productType == "Clothing") {   //check if product type is Clothing to add product
					if(productInformation.size() != 10) {
						cerr << "Error on line: " << lineNumber << ". Invalid data. Must be 10 fields. Skipping..." << endl;
						continue;
					}
					else {
						const string& size = productInformation[8];
						const string& colour = productInformation[9];
						product = make_unique <Clothing> (id, name, purchasePrice, sellingPrice, quantityBeginningInventory,
							quantitySold, quantityImported, size, colour);
					}
				}
				else if(productType == "Cosmetic") {
					//check if product type is Cosmetic to add product
					if(productInformation.size() != 9) {
						cerr << "Error on line: " << lineNumber << ". Invalid data. Must be 9 fields. Skipping..." << endl;
						continue;
					}
					else {
						const string& typeCosmetic = productInformation[8];
						product = make_unique <Cosmetic> (id, name, purchasePrice, sellingPrice, quantityBeginningInventory,
						quantitySold, quantityImported, typeCosmetic);
					}
				}
				else {
					cerr << "Error on line: " << lineNumber << ". Unknown product type. Skipping..." << endl;
					continue;
				}
				importProductFromFile(product.get()); //add product - raw pointer
			}
			catch (exception& ){
				cerr << "Error in line: " << lineNumber << ". Invalid data. Skipping..." << endl;
			}
		}
	}
}

void ProductHandler::saveProductsToFile(const string& fileName) const {
	ofstream out(fileName);
	if(out.is_open()) {
		for(const auto& product : products) {
			string typeProduct;
			int id = product->getID();
			string name = product->getName();
			float purchasePrice = product->getPurchasePrice();
			float sellingPrice = product->getSellingPrice();
			int quantityBeginningInventory = product->getQuantityBeginningInventory();
			int quantitySold = product->getQuantitySold();
			int quantityImported = product->getQuantityImported();

			if(auto* clothing = dynamic_cast<Clothing*>(product)) {
				typeProduct = "Clothing";
				string size = clothing->getSize();
				string colour = clothing->getColour();
				out << typeProduct << ',' << id << ',' << name << ',' << purchasePrice << ','
				<< sellingPrice << ',' << quantityBeginningInventory << ','
				<< quantitySold << ',' << quantityImported << ',' << size << ',' << colour << '\n';
			}
			else if (auto* cosmetic = dynamic_cast<Cosmetic*>(product)) {
				typeProduct = "Cosmetic";
				string typeCosmetic = cosmetic->getType();
				out << typeProduct << ',' << id << ',' << name << ',' << purchasePrice << ','
				<< sellingPrice << ',' << quantityBeginningInventory << ','
				<< quantitySold << ',' << quantityImported << ',' << typeCosmetic << '\n';
			}
			else {
				continue;
			}
		}
			//check if for some reason the file cannot be written
		if(out.fail()) {
			cerr << "Error! Something happened when we tried to save the file." << endl;
		}
		else {
			cout << "Products saved to file: " << fileName << endl;
		}
		out.close();
	}
	else {
		cerr << "Could not open the file to writing." << endl;
	}
}
