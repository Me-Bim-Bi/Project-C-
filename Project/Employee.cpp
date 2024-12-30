//
// Created by Chu Ha Thanh on 2024-12-25.
//

#include "Employee.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

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
	while (true) {
		string input;
		cout << "\nID: ";
		cin >> input;
		bool isNumeric = true;

		for (char cha : input) {
			if (!isdigit(cha)) {
				isNumeric = false;
				break;
			}
		}
		if(!isNumeric) {
			cout << "Invalid input. ID must be a number. Please try again.\n" << endl;
		}
		else {
			try {
				long long temp = stoll (input);
				// check if input is within the range of int
				if (temp < numeric_limits<int>::min() || temp > numeric_limits<int>::max()) {
					throw out_of_range("Number out of range for int type.");
				}
				else {
					id = static_cast<int>(temp);
				}

				if (id < 0) {
					cout << "Invalid input. ID must be a positive number. Please try again.\n";
				} else {
					break;
				}
			} catch (invalid_argument&) {
				cout << "Invalid input. ID must be a valid number. Please try again.\n";
			} catch (out_of_range&) {
				cout << "You must have entered the wrong information. "
			"The number you entered is too large or too small for become an ID number. Please try again.\n";
			}
		}
		cin.clear(); //delete the wrong status
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the wrong input data
	}
	cin.ignore();
}

void Employee::editName() {
	cout << "\nName: ";
	getline(cin, name);
}

void Employee::editBaseSalary() {
	while (true) {
		string input;
		cout << "\nBase salary: ";
		cin >> input;

		try {
			size_t onlyNumber;
			double temp = stod(input, &onlyNumber);

			if(onlyNumber != input.size()) {
				throw invalid_argument("Contains invalid characters");
			}
			if (temp < 0) {
				cout << "Input is less than 0. Base salary must be a positive number. Please try again.\n" << endl;
			}
			else {
				baseSalary = temp;
				break;
			}
		}
		catch (invalid_argument&) {
			cout << "Invalid input. Base salary must be a positive number. Please try again.\n" << endl;
		}
		catch (out_of_range&) {
			cout << "You must have entered the wrong information"
			<< ". No one has that much salary." << endl;
		}
		cin.clear(); //delete the wrong status
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the wrong input data
	}
	cin.ignore();
}

void Employee::editSalesCommission() {
	while (true) {
		string input;
		cout << "\nSales commission: ";
		cin >> input;

		try {
			size_t onlyNumber;
			double temp = stod(input, &onlyNumber);

			if(onlyNumber != input.size()) {
				throw invalid_argument("Contains invalid characters");
			}
			if (temp < 0) {
				cout << "Input is less than 0. Sales commission must be a positive number. Please try again.\n" << endl;
			}
			else {
				salesCommission = temp;
				break;
			}
		}
		catch (invalid_argument&) {
			cout << "Invalid input. Sales commission must be a positive number. Please try again.\n" << endl;
		}
		catch (out_of_range&) {
			cout << "You must have entered the wrong information"
			<< ". No one has that much sales commission." << endl;
		}
		cin.clear(); //delete the wrong status
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the wrong input data
	}
	cin.ignore();
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

