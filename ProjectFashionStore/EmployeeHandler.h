//
// Created by Chu Ha Thanh on 2024-12-25.
//

#ifndef EMPLOYEEHANDLER_H
#define EMPLOYEEHANDLER_H
#include "Employee.h"


class EmployeeHandler {
private:
	//The number of employees does not fluctuate too much
	//so it is more suitable to use a dynamic pointer.
	Employee* *employees;
	int nrOfCurrent;
	int capacity;
	void expand();
	void freeMemory();
	int findID(int id) const;
public:
	EmployeeHandler(int capacity = 5);
	~EmployeeHandler();

	void addEmployee(int id = 0, string name = "?", float salary = 0.0f, float salesCommission = 0.0f);
	void findEmployee(int id) const;
	void showInfo() const;

};



#endif //EMPLOYEEHANDLER_H
