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
#include <typeinfo>

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
	if(const int index = findIndexProduct(idProduct); index != -1) {
		//Check product type
		if(typeid(*products[index]) == typeid(*product)) {
			if(askYesNo("The product ID already exists in the system. "
			  "Would you like to import additional quantities of this product?")) {
				int WantToImport;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				editPrice("\nQuantity imported: ", WantToImport, "Quantity imported");
				int quantityAfterImport = products[index]->getQuantityImported() + WantToImport;
				products[index]->setQuantityImported(quantityAfterImport);
			  }
			else {
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "The product with id: " << idProduct << " has not been updated." << endl;
			}
		}
		else {
			cerr << "You have selected the wrong menu. " << endl
		   << "The product with id: " << idProduct << " has the following information: " << endl
			<< products[index]->showInfo() << endl
			<< "Please select the correct menu if you want to import the product!" << endl;
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
			cerr << "The product with id: " << idProduct << " exists in system "
												   "but the other information do not match. "
			"So we could not add them to the stock." << endl;
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
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			products.erase(products.begin() + index);
			cout << "The product has been deleted." << endl;
		}
		else{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			editProductId(id);
			if (askYesNo("Do you want change the another information of this product? ")) {
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Please insert the new value: " << endl;
				products[index]->editInfoButNotID();
				cout << "The product information has been edited." << endl;
			}
			else {
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "The another information of this product has not been edited." << endl;
			}
		}
		else{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "The product information has not been edited." << endl;
		}
	}
	else {
		cout << "Product with ID: " << id << " was not found!";
	}
}

void ProductHandler::sellProduct(const EmployeeHandler& emp) const {
	int checkProductID = -1, checkEmployeeID = -1, quantitySale = -1, index = -1;
	//check if the product id exists
	while(true) {
		cout << "\nProduct ID: ";
		checkProductID = checkInputDataInt();
		index = findIndexProduct(checkProductID);
		if(index == -1) {
			cout << "The product id: " << checkProductID << " does not exist. Please try again!" << endl;
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
			cout << "The employee id: " << checkEmployeeID << " does not exist. Please try again!" << endl;
		}
		else {
			break;
		}
	}
	//check if the goods in stock are enough to sell
	while(true) {
		cout << "\nQuantity sold: ";
		quantitySale = checkInputDataInt();
		int quantity = products[index]->getQuantityBeginningInventory()+products[index]->getQuantityImported() - products[index]->getQuantitySold();
		int totalQuantitySold = products[index]->getQuantitySold()+quantitySale;
		if(quantitySale <= quantity) {
			products[index]->setQuantitySold(totalQuantitySold);
			const auto employeeCommission = products[index]->getSellingPrice() * static_cast<double>(quantitySale) * 0.02;
			emp.addCommission(checkEmployeeID,employeeCommission);
			cout << "The item with id: " << checkProductID << " sold " << quantitySale << " products." << endl
			<< "The commission calculated for the employee with id: " << checkEmployeeID << " is "
			<< employeeCommission << endl;
			break;
		}
		cout << "We have only " << quantity << " products with id " << checkProductID << " in store. Please try again!" << endl;
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

void ProductHandler::sortProducts() {
	try {
		// Check for duplicate IDs before sorting
		for (size_t i = 0; i < products.size(); ++i) {
			for (size_t j = i + 1; j < products.size(); ++j) {
				if (products[i]->getID() == products[j]->getID()) {
					throw runtime_error("Duplicate product ID found: " + to_string(products[i]->getID()));
				}
			}
		}
		// Sorting the products by type (Clothing before Cosmetic) and by ID in descending order
		sort(products.begin(), products.end(), [](Product* p1, Product* p2) {
			// Check if the product type is valid (either Clothing or Cosmetic)
				// this product format and id duplication check is mainly to anticipate and handle
					//possible errors.
			if (typeid(*p1) != typeid(Clothing) && typeid(*p1) != typeid(Cosmetic)) {
				throw runtime_error("Invalid product type: " + string(typeid(*p1).name()));
				// using string to convert typeid(*(p1).name from const. char* to string
			}
			if (typeid(*p2) != typeid(Clothing) && typeid(*p2) != typeid(Cosmetic)) {
				throw runtime_error("Invalid product type: " + string(typeid(*p2).name()));
			}

			// Arrange clothing before cosmetic
			if (typeid(*p1) == typeid(Clothing) && typeid(*p2) != typeid(Clothing)) {
				return true;
			}
			if (typeid(*p2) == typeid(Clothing) && typeid(*p1) != typeid(Clothing)) {
				return false;
			}
			return p1->getID() > p2->getID();  // Sort by ID in descending order
		});

	} catch (const exception& e) {
		cerr << "Error during sorting: " << e.what() << endl;
	}
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
		cerr << "Could not open the file: " << fileName << " for reading. Please check the file name!" << endl;
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
				int id = validateAndConvertToInt(productInformation[1],
					"ID must be an integer");
				float purchasePrice = validateAndConvertToFloat(productInformation[3],
					"Purchase price must be a float");
				float sellingPrice = validateAndConvertToFloat(productInformation[4],
					"Selling price must be a float");
				int quantityBeginningInventory = validateAndConvertToInt(productInformation[5],
					"Beginning inventory quantity must be an integer");
				int quantitySold = validateAndConvertToInt(productInformation[6],
					"Sold quantity must be an integer");
				int quantityImported = validateAndConvertToInt(productInformation[7],
					"Imported quantity must be an integer");

				unique_ptr<Product> product; //create a smart pointer to make everything easier

				if(productType == "Clothing") {   //check if product type is Clothing to add product
					if(productInformation.size() != 10) {
						cerr << "Error on line: " << lineNumber << ". Invalid data. Must be 10 fields. Skipping..." << endl;
						continue;
					}
					const string& size = productInformation[8];
					const string& colour = productInformation[9];
					product = make_unique <Clothing> (id, name, purchasePrice, sellingPrice, quantityBeginningInventory,
						quantitySold, quantityImported, size, colour);
				}
				else if(productType == "Cosmetic") {
					//check if product type is Cosmetic to add product
					if(productInformation.size() != 9) {
						cerr << "Error on line: " << lineNumber << ". Invalid data. Must be 9 fields. Skipping..." << endl;
						continue;
					}
					const string& typeCosmetic = productInformation[8];
					product = make_unique <Cosmetic> (id, name, purchasePrice, sellingPrice, quantityBeginningInventory,
					quantitySold, quantityImported, typeCosmetic);
				}
				else {
					cerr << "Error on line: " << lineNumber << ". Unknown product type. Skipping..." << endl;
					continue;
				}
				importProductFromFile(product.get()); //add product - raw pointer
			}
			catch (exception& e){
				cerr << "Error in line: " << lineNumber << " in file " << fileName << ". " << e.what() << " .Skipping..." << endl;
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
