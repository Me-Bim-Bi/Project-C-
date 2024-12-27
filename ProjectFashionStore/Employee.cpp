//
// Created by Chu Ha Thanh on 2024-12-25.
//

#include "Employee.h"

Employee::Employee(int id, string name, float salary, float salesCommission):id(id), name(name), salary(salary), salesCommission(0) {
}

Employee::~Employee() {
}

int Employee::getId() const {
	return this->id;
}

string Employee::getName() const {
	return this->name;
}

float Employee::getSalary() const {
	return this->salary;
}

void Employee::setID(int id) {
	this->id = id;
}

void Employee::setName(const string &name) {
	this->name = name;
}

void Employee::setSalary(float salary) {
	this->salary = salary;
}

void Employee::totalSalesCommission(float commission) {
	this->salesCommission += commission;
}


string Employee::description() const {
	return "ID: " + to_string(id) + ", name: " + name + ", base salary: " + to_string(salary)
	+ ", sales commission: " + to_string(salesCommission) + ", total income: "
	+ to_string(salary + salesCommission) ;
}
