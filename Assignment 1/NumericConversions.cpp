/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {
	cout << intToString(137) << endl;
	cout << intToString(-137) << endl;
	cout << intToString(0) << endl;
	cout << stringToInt("137") << endl;
	cout << stringToInt("-137") << endl;
	cout << stringToInt("0") << endl;
    return 0;
} 

string intToString(int n) {
	int m = abs(n);
	if (m == 0) return "0";
	string result;
	if ((m - m%10)/10 != 0) {
		result = intToString((m - m%10)/10) + string() + char(m%10 + '0');
	} else {
		result = string() + char(m%10 + '0');
	}
	result = n < 0 ? "-" + result : result;
	return result;
}

int stringToInt(string str) {
	if (str == "-") return 0;
	if (str.size() == 1) return str[0] - '0';
	int currentDigit = str[str.size()-1] - '0';
	if (str[0] == '-') currentDigit *= -1;
	return currentDigit + stringToInt(str.substr(0, str.size()-1))*10;
}
