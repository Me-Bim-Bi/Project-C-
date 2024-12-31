#ifndef FUNTIONTOEDITINFORMATION_H
#define FUNTIONTOEDITINFORMATION_H

#include <iostream>
#include <string>
#include <limits> //check the limit of data type
#include <stdexcept> //error handling

using namespace std;

//this function template is used for functions that need to check data entered from the keyboard,
//ensuring that the data entered is in the required format.
template <typename T>
void editPrice(const string& textToInput, T& value, const string& valueType) {
	while (true) {
		string input;
		cout << textToInput;
		cin >> input;

		try {
	        size_t onlyNumber;
	        T temp;

	        if constexpr (is_same<T, string>::value) {
	            // Assign direct if it is string
	            temp = input;
	        }
	        else if constexpr (is_same_v<T, int>) {
	            //convert to longlong to check size
	            long long tempLong = stoll(input, &onlyNumber);
	            if (onlyNumber != input.size()) {
	                throw invalid_argument("Contains invalid characters");
	            }
	            if (tempLong < numeric_limits<int>::min() || tempLong > numeric_limits<int>::max()) {
	                throw out_of_range("Number out of range for int");
	            }
	            //convert to int if the data type is ok. Continue check if the value is less than 0
	            temp = static_cast<int>(tempLong);
	            if (temp < 0) {
	                cerr << valueType << " must be a positive number. Please try again.\n" << endl;
	                continue;
	            }
	        }
	        else if constexpr (is_same_v<T, double>) {
	            // convert to double if the data type is double
	            temp = stod(input, &onlyNumber);
	            if (onlyNumber != input.size()) {
	                throw invalid_argument("Contains invalid characters");
	            }
	            if (temp < 0) {
	                cerr << valueType << " must be a positive number. Please try again.\n" << endl;
	                continue;
	            }
	        }
	        else if constexpr (is_same_v<T, float>) {
	            // convert to float if the data type is float
	            temp = stof(input, &onlyNumber);
	            if (onlyNumber != input.size()) {
	                throw invalid_argument("Contains invalid characters");
	            }
	            if (temp < 0) {
	                cerr << valueType << " must be a positive number. Please try again.\n" << endl;
	                continue;
	            }
	        }
	        // Assign value after checking
	        value = temp;
	        break;
		}
		catch (const invalid_argument&) {
			cerr << "Invalid input. " << valueType << " must be valid. Please try again.\n" << endl;
		}
		catch (const out_of_range&) {
			cerr << "You must have entered the wrong information. "
			"It's too large amount. Please try agarin!" << endl;
		}
		cin.clear();  // Clear the error state
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
	}
	cin.ignore();
};

#endif

