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

	void sellProduct(int idProduct, int quantitySale, int idEmployee, EmployeeHandler& emp);
	float totalCostOfProducts() const;
	float totalRevenue() const;

	void showProduct () const;

	static bool askYesNo(const string& question);

	void loadProductsFromFie(const string& fileName);
	void saveProductToFile(const string& fileName);

};

#endif //PRODUCTHANDLER_CPP
