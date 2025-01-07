//
// Created by Chu Ha Thanh on 2024-12-25.
//

#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include<string>

using namespace std;

class Employee {
private:
	int id;
	string name;
	double baseSalary;
	double salesCommission;

public:
	Employee(int id = 0, const string& name = "?", double baseSalary = 0.0f, double salesCommission = 0.0f);
	~Employee();

	int getId() const;
	string getName() const;
	double getBaseSalary() const;
	double getSalesCommission() const;

	void setID(int id);
	void setSalesCommission(double salesCommission);

	double totalIncome() const;

	void editID();
	void editName();
	void editBaseSalary();
	void editSalesCommission();
	void editInfoButNotID();
	string showInfo() const;
};

#endif //EMPLOYEE_H
