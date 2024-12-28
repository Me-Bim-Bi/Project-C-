//
// Created by Chu Ha Thanh on 2024-12-25.
//

#include "EmployeeHandler.h"
#include<iostream>
#include "ProductHandler.h"

using namespace std;

void EmployeeHandler::expand() {
	this->capacity += 5;
	Employee** temp = new Employee* [this->capacity]{nullptr};
	for(int i = 0; i < this->nrOfCurrent; i++) {
		temp[i] = this->employees[i];
	}
	delete[] this->employees;
	this->employees = temp;
}

void EmployeeHandler::freeMemory() {
	for (int i = 0; i < nrOfCurrent; i++) {
		delete employees[i];
	}
	delete[] employees;
}

int EmployeeHandler::findIdIndex(int id) const {
	int index = -1;
	for (int i = 0; i < nrOfCurrent; i++) {
		if(employees[i]->getId() == id) {
			index = i;
		}
	}
	return index;
}

EmployeeHandler::EmployeeHandler(int capacity) : capacity(capacity), nrOfCurrent(0),
                                                employees(new Employee*[capacity]{nullptr}) {
}

EmployeeHandler::~EmployeeHandler() {
	freeMemory();
}

EmployeeHandler::EmployeeHandler(const EmployeeHandler &other) : nrOfCurrent(other.nrOfCurrent),
capacity(other.capacity), employees(new Employee*[other.capacity]{nullptr}) {
	for (int i = 0; i < nrOfCurrent; i++) {
		employees[i] = new Employee(*other.employees[i]);
	}
}

void EmployeeHandler::operator=(const EmployeeHandler &other) {
	if(this != &other) {
		freeMemory();
		this->nrOfCurrent = other.nrOfCurrent;
		this->capacity = other.capacity;
		employees = new Employee * [other.capacity]{nullptr};
		for (int i = 0; i < nrOfCurrent; i++) {
			employees[i] = new Employee (*other.employees[i]);
		}
	}
}


void EmployeeHandler::addEmployee(int id, string name, float salary, float salesCommission) {
	if(nrOfCurrent == capacity) {
		expand();
	}
	if(findIdIndex(id) == -1) {
		employees[this->nrOfCurrent++] = new Employee(id, name, salary, salesCommission);
	}
	else {
		cout << "The id " << id << " has been already exist in the system. "
		  "\nYou can not add it. Please check it again!" << endl;
	}
}

void EmployeeHandler::editIdEmployee (int id) {
	int index = findIdIndex(id);
	if (index != -1) {
		if (ProductHandler::askYesNo("Do you want to edit the id of this employee? ")) {
			cout << "New ID: ";
			int newID = 0;
			cin >> newID;
			if (findIdIndex(newID) != -1) {
				cout << "Error! The new ID you entered already exists. The id changed failed." << endl;
			}
			else {
				employees[index]->setID(newID);
				cout << "The employee's id has been edited." << endl;
			}
		}
		else{
			cout << "The employee's id has not been edited." << endl;
		}
	}
	else {
		cout << "The ID: " << id << " was not found!";
	}
}

void EmployeeHandler::editEmployee(int id) {
	int index = findIdIndex(id);
	if (index != -1) {
		cout << "The employee with the id number " << id << " have got following information: " << endl
		<< employees[index]->showInfo() << endl;
		if (ProductHandler::askYesNo("Is it the employee that you want to edit? ")) {
			editIdEmployee(id);
			if (ProductHandler::askYesNo("Do you want change the another information of this employee? ")) {
				employees[index]->editInfoButNotID();
				cout << "The employee's information has been edited." << endl;
			}
			else {
				cout << "The another information of this employee has not been edited." << endl;
			}
		}
		else{
			cout << "The employee's information has not been edited." << endl;
		}
	}
	else {
		cout << "The ID: " << id << " was not found!";
	}
}

void EmployeeHandler::removeEmployee(int id) {
	int index = findIdIndex(id);
	if (index != -1) {
		cout << "The employee with the id " << id << " have got the following information: " << endl
		<< employees[index]->showInfo() << endl;
		if (ProductHandler::askYesNo("Do you want to remove this employee? ")) {
			delete employees[index];
			nrOfCurrent--;
			employees[index] = employees[nrOfCurrent];
			employees[nrOfCurrent] = nullptr;
			cout << "The product has been deleted." << endl;
		}
		else{
			cout << "Product with ID: " << id << " was not found!";
		}
	}
}

void EmployeeHandler::findEmployeeAndShowInfo(int id) const {
	bool didFind = false;
	for (int i = 0; i < nrOfCurrent; i++) {
		if(employees[i]->getId() == id) {
			cout << "The employee with the id " << id << " have got the following information: " << endl
					<< employees[i]->showInfo() << endl;
			didFind = true;
		}
	}
	if(!didFind) {
		cerr << "The employee with the id: " << id << " does not exist in our system." << endl;
	}
}

void EmployeeHandler::addCommission(int id, float salesCommission) {
	int index = findIdIndex(id);
	if(index != -1) {
		employees[index]->setSalesCommission(salesCommission);
	}
	else {
		cerr << "Error: The ID " << id << " was not found." << endl;
	}
}

int EmployeeHandler::callFindIdIndex(int id) const {
	return findIdIndex(id);
}

void EmployeeHandler::showInfo() const {
	for (int i = 0; i < nrOfCurrent; i++) {
		cout << employees[i]->showInfo() << endl;
	}
}

void EmployeeHandler::loadProductsFromFie(const string &fileName) {

}

void EmployeeHandler::saveProductToFile(const string &fileName) {

}
