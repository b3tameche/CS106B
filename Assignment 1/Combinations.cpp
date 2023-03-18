/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
using namespace std;

int calculateC(int n, int k) {
	if (k <= 0 || n == k) {
		return 1;
	}
	return calculateC(n-1, k-1) + calculateC(n-1, k);
}

int main() {
	cout << calculateC(6,2) << endl;
    return 0;
}
