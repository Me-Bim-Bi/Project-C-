//
// Created by Chu Ha Thanh on 2024-12-25.
//

#include "EmployeeHandler.h"
#include<iostream>

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

int EmployeeHandler::findID(int id) const {
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


void EmployeeHandler::addEmployee(int id, string name, float salary, float salesCommission) {
	if(nrOfCurrent == capacity) {
		expand();
	}
	if(findID(id) == -1) {
		this->employees[nrOfCurrent++] = new Employee(id, name, salary, salesCommission);
	}
	else {
		cout << "The id " << id << " has been already exist in the system. "
		  "\nYou can not add it. Please check it again!" << endl;
	}
}

//create a function names: find index ID. find ID before add so that ID is the uniq
void EmployeeHandler::findEmployee(int id) const {
	bool didFind = false;
	for (int i = 0; i < nrOfCurrent; i++) {
		if(employees[i]->getId() == id) {
			cout << "The employee with the id " << id << " have got the following information: " << endl
					<< employees[i]->description() << endl;
			didFind = true;
		}
	}
	if(!didFind) {
		cout << "The employee with the id: " << id << " does not exist in our system." << endl;
	}
}

void EmployeeHandler::showInfo() const {
	for (int i = 0; i < nrOfCurrent; i++) {
		cout << employees[i]->description() << endl;
	}
}
