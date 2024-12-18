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
	Cosmetic(int id, const string& name, float price, const string& brand,
		int quantity, const string& type);
	Cosmetic();
	string getType() const;
	void setType(const string& type);

	//bool operator ==(const Cosmetic& other) const override;
	void editInfo() override;
	string showInfo() const override;
	Product* clone() const override;


};


#endif //COSMETIC_H
