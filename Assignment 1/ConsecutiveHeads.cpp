/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "random.h"
using namespace std;

void simulate() {
	int headCount = 0;
	int tries = 0;

	while (headCount != 3) {
		if (randomChance(0.5)) {
			headCount++;
			cout << "heads" << endl;
		} else {
			headCount = 0;
			cout << "tails" << endl;
		}
		tries++;
	}

	cout << "It took " << tries << " flips to get 3 consecutive heads." << endl;
}

int main() {
	simulate();
	return 0;
}