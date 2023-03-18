/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "map.h"
#include "vector.h"
#include "random.h"
using namespace std;

/* function prototypes */
int getOrder();
Map<string, Vector<string>> getAnalyzedText(ifstream& infile, int order, string& seed);
string getNextChar(Map<string, Vector<string>>& patterns, string str);
string generateMarkov(Map<string, Vector<string>>& patterns, string seed);
string generateCharacters (Map<string, Vector<string>> & patterns, string seed, int amount);

const int charAmount = 2000;

int main() {
	ifstream infile;
	promptUserForFile(infile, "Enter the source text: ");

	int order = getOrder();
	cout << "Processing file..." << endl;

	string seed;
	Map<string, Vector<string>> initialPatterns = getAnalyzedText(infile, order, seed);

	cout << generateMarkov(initialPatterns, seed) << endl;

	infile.close();
    return 0;
}

int getOrder () {
	int order = getInteger("Enter the Markov order [1-10]: ");
	if (order < 1 || order > 10) {
		cout << "That value is out of range" << endl;
		getOrder();
	}
	return order;
}

Map<string, Vector<string>> getAnalyzedText(ifstream& infile, int order, string& seed) {
	Map<string, Vector<string>> samples; // maps strings on their possible next characters

	string combo;
	char ch;
	int frequest = 0;

	for (int i = 0; i < order; i++) {
		combo += infile.get();
	}
	while (infile.get(ch)) {
		if (!samples.containsKey(combo)) {
			Vector<string> empty;
			samples.put(combo, empty);
		}
		samples[combo].add(string() + ch);

		if (samples[combo].size()>frequest) {
			frequest = samples[combo].size();
			seed = combo;
		}
		combo = combo.substr(1) + ch;
	}

	if (samples.containsKey(combo)) { // last combo, in the end of file
		samples[combo].add("");
	} else {
		Vector<string> empty;
		empty.add("");
		samples.put(combo, empty);
	}
	return samples;
}

string getNextChar(Map<string, Vector<string>>& patterns, string str) { // returns random next char, obtained from vector
	int randomIndex = randomInteger(0, patterns[str].size()-1);
	return patterns[str][randomIndex];
}

string generateMarkov(Map<string, Vector<string>>& patterns, string seed) { // returns first seed + further generated characters
	return seed + generateCharacters(patterns, seed, charAmount - seed.length());
}

string generateCharacters (Map<string, Vector<string>>& patterns, string seed, int amount) { // generates $(amount) characters based on given seed
	if (amount == 0 || !patterns.containsKey(seed)) return "";
	string nextChar = getNextChar(patterns, seed);
	if (nextChar == "") return ""; // if the combo occurs only once, in the end of the file
	return nextChar + generateCharacters(patterns, seed.substr(1) + nextChar, amount - 1);
}