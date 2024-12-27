//
// Created by Chu Ha Thanh on 2024-12-16.
//

#ifndef PRODUCTHANDLER_CPP
#define PRODUCTHANDLER_CPP
#include "Product.h"
#include "EmployeeHandler.h"
#include <vector>

class ProductHandler {
private:
	vector<Product*> products;
	int findIndexProduct(int id) const;
public:
	ProductHandler();
	~ProductHandler();
	ProductHandler(const ProductHandler& other);
	ProductHandler operator=(const ProductHandler& other);

	void importProduct(Product* product);
	void findAndShowProduct(int id) const;
	void removeProduct(int id);
	void editProductId(int id);
	void editProduct(int id);

	void sellProduct(int idProduct, int quantitySale, int idEmployee);
	float totalCostOfProducts() const;
	float totalRevenue() const;

	void showProduct () const;

	static bool askYesNo(const string& question);


	//void updateSourceFile(string fileName);

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
