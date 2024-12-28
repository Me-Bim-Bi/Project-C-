//
// Created by Chu Ha Thanh on 2024-12-14.
//

#ifndef PRODUCT_H
#define PRODUCT_H
#include<string>

using namespace std;


class Product {
private:
	int id;
	string name;
	float purchasePrice;
	float sellingPrice;
	int quantityBeginningInventory;
	int quantitySold;
	int quantityImported;
public:
	Product(int id = -1, const string& name = "?", float purchasePrice = 0.0f, float sellingPrice = 0.0f,
	int quantityBeginningInventory = 0, int quantitySold = 0, int quantityImported = 0);
	virtual ~Product();

	int getID() const;
	string getName() const;
	float getPurchasePrice() const;
	float getSellingPrice() const;
	int getQuantityBeginningInventory() const;
	int getQuantitySold() const;
	int getQuantityImported() const;

	void setID(int id);
	void setName(const string& name);
	void setPurchasePrice(float price);
	void setSellingPrice(float sellingPrice);
	void setQuantityBeginningInventory(int quantityBeginningInventory);
	void setQuantitySold(int quantitySold);
	void setQuantityImported(int quantityImported);

	void editId();
	void editName();
	void editPurchasePrice();
	void editSellingPrice();
	void editQuantityBeginningInventory();
	void editQuantitySold();
	void editQuantityImported();
	virtual void editInfoButNotID() = 0;

	virtual bool operator ==(const Product& other) const = 0;

	float totalCostOfGoods() const;
	float totalRevenue() const;
	int endOfDayInventory() const;

	virtual string showInfo() const = 0;
	virtual Product* clone() const = 0;
};

#endif //PRODUCT_H
