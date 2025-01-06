//
// Created by Chu Ha Thanh on 2024-12-25.
//

#include "EmployeeHandler.h"
#include "ProductHandler.h"
#include "FuntionToEditInformation.h"
#include "Menu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

void EmployeeHandler::expand() {
	this->capacity += 5;
	auto** temp = new Employee* [this->capacity]{nullptr};
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
	employees = nullptr;
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

EmployeeHandler& EmployeeHandler::operator=(const EmployeeHandler &other) {
	if(this != &other) {
		freeMemory();
		this->nrOfCurrent = other.nrOfCurrent;
		this->capacity = other.capacity;
		employees = new Employee * [other.capacity]{nullptr};
		for (int i = 0; i < nrOfCurrent; i++) {
			employees[i] = new Employee (*other.employees[i]);
		}
	}
	return *this;
}

int EmployeeHandler::getNrOfCurrent() const {
	return this->nrOfCurrent;
}

void EmployeeHandler::addEmployee() {
	int id = -1;
	editPrice("\nID: ", id, "ID");
	if(findIdIndex(id) == -1) {
		if(nrOfCurrent == capacity) {
			expand();
		}
		double salesCommission = 0.0f;
		double baseSalary = 0.0;
		string name = "?";
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
	if (int index = findIdIndex(id); index != -1) {
		if (askYesNo("Do you want to edit the id of this employee? ")) {
			int newID = 0;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			editPrice("\nNew ID: ", newID, "New ID");
			if (findIdIndex(newID) != -1) {
				cerr << "Error! The new ID you entered already exists. The id changed failed." << endl;
			}
			else {
				employees[index]->setID(newID);
				cout << "The employee's id has been edited." << endl;
			}
		}
		else{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "The employee's id has not been edited." << endl;
		}
	}
	else {
		cerr << "The ID: " << id << " was not found!" << endl;
	}
}

void EmployeeHandler::editEmployee(int id) const {
	if (int index = findIdIndex(id); index != -1) {
		cout << "The employee with the id number " << id << " have got following information: " << endl
		<< employees[index]->showInfo() << endl;
		if (askYesNo("Is it the employee that you want to edit? ")) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			editIdEmployee(id);
			if (askYesNo("Do you want change the another information of this employee? ")) {
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				employees[index]->editInfoButNotID();
				cout << "The employee's information has been edited." << endl;
			}
			else {
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "The another information of this employee has not been edited." << endl;
			}
		}
		else{
			cout << "The employee's information has not been edited." << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	else {
		cerr << "The ID: " << id << " was not found!";
	}
}

void EmployeeHandler::removeEmployee(int id) {
	if (int index = findIdIndex(id); index != -1) {
		cout << "The employee with the id " << id << " have got the following information: " << endl
		<< employees[index]->showInfo() << endl;
		if (askYesNo("Do you want to remove this employee? ")) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			delete employees[index];
			nrOfCurrent--;
			employees[index] = employees[nrOfCurrent];
			employees[nrOfCurrent] = nullptr;
			cout << "The product has been deleted." << endl;
		}
		else {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "The information of employee with id: " << id << " has not been removed" << endl;
		}
	}
	else{
		cerr << "The id " << id << " was not found!" << endl;
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
	if(int index = findIdIndex(id); index != -1) {
		double currentCommission = employees[index]->getSalesCommission();
		double newCommission = currentCommission + salesCommission;
		employees[index]->setSalesCommission(newCommission);
	}
	else {
		cerr << "Error: The ID " << id << " was not found." << endl;
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

bool EmployeeHandler::compareEmployees(Employee *emp1, Employee *emp2) {
	//Convert all names to lowercase for comparison
	string nameEmp1 = emp1->getName();
	string nameEmp2 = emp2->getName();
	transform(nameEmp1.begin(), nameEmp1.end(), nameEmp1.begin(), ::tolower);
	transform(nameEmp2.begin(), nameEmp2.end(), nameEmp2.begin(), ::tolower);

	//Use string stream to split name into words
	istringstream nameStream1(nameEmp1);
	istringstream nameStream2(nameEmp2);

	string word1, word2;
	//Compare every word in name
	while (nameStream1 >> word1 && nameStream2 >> word2) {
		if (word1 != word2) {
			return word1 < word2;  //compare if the words are different.w
		}
	}

	//if all words are same then sort by ID in descending order
	return (emp1->getId()) > (emp2->getId());
}


void EmployeeHandler::sortEmployees() const {
	sort(employees, employees + nrOfCurrent, compareEmployees);
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
				int id = validateAndConvertToInt(employeeInformation[0],
					"ID must be an integer");
				const string& name = employeeInformation[1];
				double baseSalary = validateAndConvertToDouble(employeeInformation[2],
					"Base salary must be a number");
				double salesCommission = validateAndConvertToDouble(employeeInformation[3],
					"Sales commission must be a number");

				addEmployeeFromFile(id, name, baseSalary, salesCommission);
			}
			catch (exception& e){
				cerr << "Error in line: " << lineNumber << " in file " << fileName << ". " << e.what() << " .Skipping..." << endl;
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
		  "\nYou can not add an employee twice to the system. " << endl;
	}
}

void EmployeeHandler::saveEmployeesToFile(const string &fileName) const {
	ofstream out(fileName);
	if(out.is_open()) {
		for(int i = 0; i < this->nrOfCurrent; i++){
			int id = employees[i]->getId();
			string name = employees[i]->getName();
			double baseSalary = employees[i]->getBaseSalary();
			double salesCommission = employees[i]->getSalesCommission();

			out << id << ',' << name << ',' << baseSalary << ',' << salesCommission << '\n';
		}
		if(out.fail()) {
			cerr << "Error! Something happened when we tried to save the file." << endl;
		}
		else {
			cout << "All employees information saved to file: " << fileName << endl;
		}
		out.close();
	}
	else {
		cerr << "Could not open the file to writing." << endl;
	}
}
