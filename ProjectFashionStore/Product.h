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
	float price;
	string brand;
	int quantity;
public:
	Product(int id = -1, const string& name = "?", float price = 0.0f, const string& brand = "?", int quantity = 0);
	virtual ~Product();

	int getID() const;
	string getName() const;
	float getPrice() const;
	string getBrand() const;
	int getQuantity() const;

	void setID(int id);
	void setName(const string& name);
	void setPrice(float price);
	void setBrand(const string& brand);
	void setQuantity(int quantity);

	virtual void editInfo() = 0;
	//virtual bool operator ==(const Product& other) const = 0;

	float totalPrice() const;

	virtual string showInfo() const = 0;
	virtual Product* clone() const = 0;
	//void sendToFile(string fileName = "product.txt");
	//void readFromFile(string fileName = "product.txt");
};



#endif //PRODUCT_H
