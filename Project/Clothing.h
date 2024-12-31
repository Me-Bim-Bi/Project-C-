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
	Clothing(int id = -1, const string& name = "?", float purchasePrice = 0.0f, float sellingPrice = 0.0f, int quantityBeginningInventory = 0,
		int quantitySold = 0, int quantityImported = 0, const string& size = "?", const string& colour = "?");
	~Clothing();

	string getSize() const;
	string getColour() const;

	void editSize();
	void editColour();
	void editInfoButNotID() override;

	string showInfo() const override;

	Product* clone() const override;


};



#endif //CLOTHING_H
