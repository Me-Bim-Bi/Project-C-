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
	virtual~ProductHandler();
	ProductHandler(const ProductHandler& other);
	ProductHandler& operator=(const ProductHandler& other);

	void importProduct(Product* product);
	void importProductFromFile(const Product* product);
	void findAndShowProduct(int id) const;
	void removeProduct(int id);
	void editProductId(int id) const;
	void editProduct(int id) const;

	void sellProduct(const EmployeeHandler& emp) const;
	double totalCostOfProducts() const;
	double totalRevenue() const;

	void sortProducts();
	void showInfo () const;

	void loadProductsFromFie(const string& fileName);
	void saveProductsToFile(const string& fileName) const;

};

#endif //PRODUCTHANDLER_CPP
