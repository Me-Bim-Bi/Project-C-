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
	explicit EmployeeHandler(int capacity = 5);
	~EmployeeHandler();
	EmployeeHandler(const EmployeeHandler& other);
	void operator=(const EmployeeHandler& other);

	void addEmployee();
	void editIdEmployee(int id) const;
	void editEmployee(int id);
	void removeEmployee(int id);
	void findEmployeeAndShowInfo(int id) const;
	void addCommission(int id, double salesCommission) const;

	int callFindIdIndex(int id) const;

	double totalSalary() const;
	void showInfo() const;

	void loadEmployeesFromFie(const string& fileName);
	void addEmployeeFromFile(int id, const string& name, double baseSalary, double salesCommission);
	void saveEmployeesToFile(const string& fileName);


};



#endif //EMPLOYEEHANDLER_H
