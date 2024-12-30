//
// Created by Chu Ha Thanh on 2024-12-18.
//

#include "Management.h"
#include "ProductHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void Management::totalRevenue(const ProductHandler &pro) {
	this->revenue = pro.totalRevenue();
}

void Management::totalCost(const ProductHandler &pro, const EmployeeHandler &emp) {
	this->cost = pro.totalCostOfProducts() + emp.totalSalary();
}

void Management::finalProfit() {
	this->profit = this->revenue - this->cost;
}

Management::Management(const ProductHandler &pro, const EmployeeHandler &emp) {
	totalRevenue(pro);
	totalCost(pro, emp);
	finalProfit();
}

Management::~Management() {
}


double Management::getProfit() const {
	return this->profit;
}

double Management::getRevenue() const {
	return this->revenue;
}

double Management::getCost() const {
	return this->cost;
}

void Management::showInfo() const {
	cout << "Total cost: " << cost << endl
	<< "Total revenue: " << revenue << endl
	<< "_____________________ " << endl
	<< "Gross profit: " << profit << endl;
}

void Management::saveToFile(const string& fileName) const {
	ofstream out(fileName);
	if(!out.is_open()) {
		cerr << "Could not open the file to writing." << endl;
		return;
	}
	out << "Total cost: " << cost << endl
			<< "Total revenue: " << revenue << endl
			<< "_____________________ " << endl
			<< "Gross profit: " << profit << endl;
	out.close();
	cout << "Updated financial statements to file: " << fileName << endl;
}

