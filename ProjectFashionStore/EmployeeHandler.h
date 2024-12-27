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
	int findIdIndex(int id) const;
public:
	EmployeeHandler(int capacity = 5);
	~EmployeeHandler();
	EmployeeHandler(const EmployeeHandler& other);
	void operator=(const EmployeeHandler& other);

	void addEmployee(int id = 0, string name = "?", float salary = 0.0f, float salesCommission = 0.0f);
	void editIdEmployee(int id);
	void editEmployee(int id);
	void removeEmployee(int id);
	void findEmployeeAndShowInfo(int id) const;
	void addCommission(int id, float salesCommission);

	void showInfo() const;

};



#endif //EMPLOYEEHANDLER_H
