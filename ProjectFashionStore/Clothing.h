//
// Created by Chu Ha Thanh on 2024-12-14.
//

#ifndef CLOTHING_H
#define CLOTHING_H
#include "Product.h"


class Clothing : public Product{
private:
	string size;
	string colour;
public:
	Clothing(int id, const string& name, float purchasePrice, float sellingPrice, const string& brand,
		int quantity, int quantitySold, int quantityPurchased, const string& size = "?", const string& colour = "?");

	string getSize() const;
	string getColour() const;

	void setSize(const string& size);
	void setColour(const string& colour);

	void editInfoButNotID() override;
	bool operator ==(const Product& other) const override;
	string showInfo() const override;

	Product* clone() const override;


};



#endif //CLOTHING_H
