/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include "console.h"
#include "tokenscanner.h"
#include "filelib.h"
using namespace std;

/* function prototypes */
bool isVowel(char c);
int getSyllableCount(string word);
double calculateFKGrade(int wordCount, int sentenceCount, int syllableCount);

int main() {
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.addWordCharacters("-'\"");

	ifstream infile; // input file
	promptUserForFile(infile, "File Name: "); // prompts user until valid filename is given
	scanner.setInput(infile);

	int wordCount = 0;
	int sentenceCount = 0;
	int syllableCount = 0;

	while (scanner.hasMoreTokens()) {
		string word = scanner.nextToken();
		if (word == "'" || word == ",") continue; // filter this characters on early stage
		if (scanner.getTokenType(word) == STRING || scanner.getTokenType(word) == WORD) { // I saw implementation of getTokenTypes and both types of strings were acceptable
			wordCount++;
			syllableCount += getSyllableCount(word);
		}
		if (word == "." || word == "?" || word == "!") sentenceCount++; // this characters indicate end of a sentence
	}

	cout << "words " << wordCount << endl;
	cout << "syllables " << syllableCount << endl;
	cout << "sentences " << sentenceCount << endl;
	cout << calculateFKGrade(wordCount, sentenceCount, syllableCount) << endl;

	infile.close();
	return 0;
}

bool isVowel(char c) {
	string vowels = "AaEeIiOoUuYy";
	return vowels.find(c) != -1;
}

int getSyllableCount(string word) {
	int count = 0;
	if (isVowel(word[0])) count++;
	for (int i = 1; i < word.length(); i++) {
		if (!isVowel(word[i-1]) && isVowel(word[i])) { // checks pair by pair
			count++;
		}
	}
	if (word[word.length() - 1] == 'e') count--;
	if (count == 0) count++;

	return count;
}

double calculateFKGrade(int wordCount, int sentenceCount, int syllableCount) {
	double c0 = -15.59;
	double c1 = 0.39;
	double c2 = 11.8;

	return (c0 + c1*((double)wordCount/sentenceCount) + c2*((double)syllableCount/wordCount));
}
