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
	string brand;
	int quantityBeginningInventory;
	int quantitySold;
	int quantityImported;
public:
	Product(int id = -1, const string& name = "?", float purchasePrice = 0.0f, float sellingPrice = 0.0f,
		const string& brand = "?", int quantityBeginningInventory = 0, int quantitySold = 0, int quantityImported = 0);
	virtual ~Product();

	int getID() const;
	string getName() const;
	float getPurchasePrice() const;
	float getSellingPrice() const;
	string getBrand() const;
	int getQuantityBeginningInventory() const;
	int getQuantitySold() const;
	int getQuantityImported() const;

	void setID(int id);
	void setName(const string& name);
	void setPurchasePrice(float price);
	void setSellingPrice(float sellingPrice);
	void setBrand(const string& brand);
	void setQuantityBeginningInventory(int quantityBeginningInventory);
	void setQuantitySold(int quantitySold);
	void setQuantityImported(int quantityImported);

	virtual void editInfoButNotID() = 0;
	virtual bool operator ==(const Product& other) const = 0;

	float totalCostOfGoods() const;
	float totalRevenue() const;
	int endOfDayInventory() const;

	virtual string showInfo() const = 0;
	virtual Product* clone() const = 0;
};



#endif //PRODUCT_H
