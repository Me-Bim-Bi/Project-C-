//
// Created by Chu Ha Thanh on 2024-12-17.
//

#ifndef MENU_H
#define MENU_H
#include "ProductHandler.h"
#include "EmployeeHandler.h"
#include <string>


using namespace std;

void Menu();
int checkInputDataInt();
bool askYesNo(const string &question);
int checkMenuChoice();
void getMenuChoice(int answer, ProductHandler& productHandlerVector, EmployeeHandler& employeeHandlerPointers);
int validateAndConvertToInt(const string& str, const string& errorMessage);
float validateAndConvertToFloat(const string& str, const string& errorMessage);
double validateAndConvertToDouble(const string& str, const string& errorMessage);


#endif //MENU_H
