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
	Clothing(int id, const string& name, float price, const string& brand,
		int quantity, const string& size, const string& colour);
	Clothing();
	string getSize() const;
	string getColour() const;

	void setSize(const string& size);
	void setColour(const string& colour);
	void editInfo() override;
	//bool operator ==(const Clothing& other) const override;

	string showInfo() const override;
	Product* clone() const override;


};



#endif //CLOTHING_H
