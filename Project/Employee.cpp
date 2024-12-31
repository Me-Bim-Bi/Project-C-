//
// Created by Chu Ha Thanh on 2024-12-25.
//

#include "Employee.h"
#include "FuntionToEditInformation.h"
#include <string>
#include <iomanip>
#include <sstream>

Employee::Employee(int id, string name, double baseSalary, double salesCommission):id(id), baseSalary(baseSalary), name(name),salesCommission(salesCommission) {
}

Employee::~Employee() {
}

int Employee::getId() const {
	return this->id;
}

string Employee::getName() const {
	return this->name;
}

double Employee::getBaseSalary() const {
	return this->baseSalary;
}

double Employee::getSalesCommission() const {
	return this->salesCommission;
}

void Employee::setID(int id) {
	this->id = id;
}

void Employee::setSalesCommission(double salesCommission) {
	this->salesCommission = salesCommission;;
}

double Employee::totalIncome() const {
	return this->baseSalary + this->salesCommission;
}

void Employee::editID() {
	editPrice("\nID: ", id, "ID");
}

void Employee::editName() {
	editPrice("\nName: ", name, "Name");
}

void Employee::editBaseSalary() {
	editPrice("\nBase salary: ", baseSalary, "Base salary");
}

void Employee::editSalesCommission() {
	editPrice("\nSales commission: ", salesCommission, "Sales Commission");
}

void Employee::editInfoButNotID() {
	editName();
	editBaseSalary();
	editSalesCommission();
}

string Employee::showInfo() const {
	ostringstream stringInfo;
	stringInfo << fixed << setprecision(0);
	stringInfo << "ID: " << id
	<< ", name: " << name
	<< ", base salary: " << baseSalary
	<< ", sales commission: " << salesCommission
	<< ", total income: " << totalIncome();
	return stringInfo.str();
}

