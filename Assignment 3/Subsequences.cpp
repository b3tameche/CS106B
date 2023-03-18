/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);

int main() {
	string text = "least";
	string subsequence = "steal";
	cout << isSubsequence(text, subsequence) << endl;
    return 0;
}

bool isSubsequence(string text, string subsequence) {
	if (subsequence == "") return true;
	if (text.find(subsequence[0]) != string::npos) {
		return isSubsequence(text.substr(text.find(subsequence[0])+1), subsequence.substr(1));
	} return false;
}
