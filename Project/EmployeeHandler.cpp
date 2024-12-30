//
// Created by Chu Ha Thanh on 2024-12-25.
//

#include "EmployeeHandler.h"
#include "ProductHandler.h"

#include <iostream>
#include <fstream>
#include <sstream>

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

void EmployeeHandler::addEmployee() {
	int id = -1;
	string name;
	double baseSalary = 0.0, salesCommission = 0.0f;
	while (true) {
		cout << "\nID: ";
		cin >> id;
		if (cin.fail() || id < 0) { //check if the input data less than 0 or not a number
			cin.clear(); //delete the wrong status
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the wrong input data
			cout << "Invalid input. ID must be a positive number. Please try again.\n";
		} else {
			break;
		}
	}
	cin.ignore();
	if(findIdIndex(id) == -1) {
		if(nrOfCurrent == capacity) {
			expand();
		}
		employees[this->nrOfCurrent] = new Employee(id, name, baseSalary, salesCommission);
		employees[this->nrOfCurrent]->editInfoButNotID();
		nrOfCurrent++;
	}
	else {
		cout << "The employee has id number: " << id << " has been already exist in the system. "
		  "\nYou can not add an employee twice to the system. Please check it again!" << endl;
	}
}

void EmployeeHandler::editIdEmployee (int id) const {
	int index = findIdIndex(id);
	if (index != -1) {
		if (ProductHandler::askYesNo("Do you want to edit the id of this employee? ")) {
			int newID = 0;
			cin >> newID;
			if (findIdIndex(newID) != -1) {
				cout << "Error! The new ID you entered already exists. The id changed failed." << endl;
			}
			else {
				employees[index]->editID();
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

void EmployeeHandler::addCommission(int id, double salesCommission) const {
	int index = findIdIndex(id);
	if(index != -1) {
		double currentCommission = employees[index]->getSalesCommission();
		double newCommission = currentCommission + salesCommission;
		employees[index]->setSalesCommission(newCommission);
	}
	else {
		cerr << "Error: The ID " << id << " was not found." << endl;
		return;
	}
}

int EmployeeHandler::callFindIdIndex(int id) const {
	return findIdIndex(id);
}

double EmployeeHandler::totalSalary() const {
	double total = 0;
	for(int i = 0; i<nrOfCurrent; i++) {
		total += employees[i]->totalIncome();
	}
	return total;
}

void EmployeeHandler::showInfo() const {
	int count = 1;
	for (int i = 0; i < nrOfCurrent; i++) {
		cout << count++ << ". " << employees[i]->showInfo() << endl;
	}
}

void EmployeeHandler::loadEmployeesFromFie(const string &fileName) {
	ifstream in(fileName);
	if(in.is_open()) {
		string line;
		int lineNumber = 0;
		while (getline(in, line)) {
			++lineNumber;
			istringstream input(line);
			vector <string> employeeInformation;
			string anEmployee;

			while(getline(input,anEmployee,',')) {
				employeeInformation.push_back(anEmployee);
			}

			if(employeeInformation.size() != 4) {
				cerr << "Error on line: " << lineNumber << ". Invalid data. Must be 4 fields. Skipping..." << endl;
				continue;
			}
			try {
				int id = stoi(employeeInformation[0]);
				string name = employeeInformation[1];
				double baseSalary = stof(employeeInformation[2]);
				double salesCommission = stof(employeeInformation[3]);

				addEmployeeFromFile(id, name, baseSalary, salesCommission);

			}
			catch(exception& e){
				cerr << "Error in line: " << lineNumber << ". Invalid data. Skipping..." << endl;
			}
		}
		in.close();
	}
	else {
		cerr << "Could not open the file " << fileName << " for reading. Please check the file name!" << endl;
		return;
	}
}

void EmployeeHandler::addEmployeeFromFile(int id, const string &name, double baseSalary, double salesCommission) {
	if(findIdIndex(id) == -1) {
		if(nrOfCurrent == capacity) {
			expand();
		}
		employees[this->nrOfCurrent++] = new Employee(id, name, baseSalary, salesCommission);
	}
	else {
		cerr << "The employee has id number: " << id << " has been already exist in the system. "
		  "\nYou can not add an employee twice to the system. Skipping.." << endl;
	}
}

void EmployeeHandler::saveEmployeesToFile(const string &fileName) {
	ofstream out(fileName);
	if(out.is_open()) {
		for(int i = 0; i < this->nrOfCurrent; i++){
			int id = employees[i]->getId();
			string name = employees[i]->getName();
			double baseSalary = employees[i]->getBaseSalary();
			double salesCommission = employees[i]->getSalesCommission();

			out << id << ',' << name << ',' << baseSalary << ',' << salesCommission << '\n';
			}
		out.close();
		cout << "All employees information saved to file: " << fileName << endl;
	}
	else {
		cerr << "Could not open the file to writing." << endl;
		return;
	}
}

