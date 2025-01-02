//
// Created by Chu Ha Thanh on 2024-12-18.
//

#ifndef MANAGEMENT_H
#define MANAGEMENT_H
#include "ProductHandler.h"
#include "EmployeeHandler.h"


class Management {
private:
	double profit;
	double revenue;
	double cost;

public:
	Management(const ProductHandler& pro, const EmployeeHandler& emp);
	~Management();

	void showInfo() const;
	void saveToFile(const string& fileName) const;
};

#endif //MANAGEMENT_H
