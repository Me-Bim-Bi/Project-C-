//
// Created by Chu Ha Thanh on 2024-12-16.
//

#ifndef PRODUCTHANDLER_CPP
#define PRODUCTHANDLER_CPP
#include "Product.h"
#include <vector>

class ProductHandler {
private:
	vector<Product*> products;
	bool askYesNo(const string& question);
public:
	ProductHandler();
	~ProductHandler();
	void addProduct(Product* product);
	void findProduct(int id);
	void removeProduct(const int index);
	void editProduct(const int index);
	float totalPrice() const;
	void showProduct () const;

	/*
		int findClothing(int id, const string& name, float price, const string& brand,
			int quantity, const string& size, const string& colour);
		void removeClothing(int index);
		void editClothing(int index);
		void showClothing() const;
		float totalClothingsCost() const;
		*/
};

#endif //PRODUCTHANDLER_CPP
