//
// Created by Chu Ha Thanh on 2024-12-15.
//

#ifndef COSMETIC_H
#define COSMETIC_H
#include "Product.h"


class Cosmetic : public Product {
private:
	string type;
public:
	Cosmetic(int id = -1, const string& name = "?", float purchasePrice = 0.0f, float sellingPrice = 0.0f, int quantityBeginningInventory = 0,
		int quantitySold = 0, int quantityImported = 0, const string& type = "?");
	~Cosmetic();

	string getType() const;
	void setType(const string& type);

	bool operator ==(const Product& other) const override;

	void editType();
	void editInfoButNotID() override;

	string showInfo() const override;
	Product* clone() const override;
};


#endif //COSMETIC_H
