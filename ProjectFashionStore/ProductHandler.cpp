//
// Created by Chu Ha Thanh on 2024-12-16.
//

#include "ProductHandler.h"
#include "Clothing.h"
#include <vector>
#include <iostream>

using namespace std;

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

ProductHandler::ProductHandler() {
}

ProductHandler::~ProductHandler() {
	for (auto product : products) {
		delete product;
	}
}

void ProductHandler::addProduct(Product* product) {
	products.push_back(product);
}

void ProductHandler::findProduct(int id) {
	bool didFound = false;
	for (size_t i = 0; i < products.size(); i++) {
		if(products[i]->getID() == id) {
			cout << "Index of the product: " << i << endl
			<< "Full information of the product: " << products[i]->showInfo() << endl;
		didFound = true;
		}
	}
	if(!didFound) {
		cout << "Product with ID: " << id << " was not found!";
	}

}

void ProductHandler::removeProduct(const int index) {
	bool isContinue = true;

	if (index >= 0 && index < products.size()) {
		cout << "The product in the index " << index << " have got following information: " << endl
		<< products[index]->showInfo() << endl;

		isContinue = askYesNo("Do you want to remove this product? ");
		if (isContinue) {
			products.erase(products.begin() + index);
			cout << "The product has been deleted." << endl;
		}
		else{
			cout << "The product has not been deleted." << endl;
		}
	}
}

void ProductHandler::editProduct(const int index) {
	if (index >= 0 && index < products.size()) {
		cout << "The product in the index " << index << " have got following information: " << endl
		<< products[index]->showInfo() << endl;
		bool isContinue = true;
		isContinue = askYesNo("Do you want to edit this product? ");
		if (isContinue) {
			products[index]->editInfo();
			cout << "The product has been edited." << endl;
		}
		else{
			cout << "The product has not been edited." << endl;
		}
	}
}

float ProductHandler::totalPrice() const {
	float total = 0.0f;
	for (auto product : products) {
		total += product->totalPrice();
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
	cout << "Total price of all products is: " << totalPrice() << endl;
}
