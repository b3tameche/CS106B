/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "queue.h"
#include "lexicon.h"
#include "simpio.h"
using namespace std;

/* function prototypes */
string getLadder(string start, string end);
string getLastWordFromLadder(string ladder, string startWord);
void promptUserAndFindLadder();

int main() {
	promptUserAndFindLadder();
    return 0;
}

string getLadder(string start, string end) { // prints ladder if found, prompts if not
	Lexicon wordlist("EnglishWords.dat");
	Lexicon usedWords; // to remember already used words
	usedWords.add(start);
	Queue<string> ladders; // to store possible ladders
	ladders.enqueue(start);

	cout << "Searching..." << endl;
	if (!wordlist.contains(start) || !wordlist.contains(end)) return "No word ladder could be found"; // if no such word exists
	while (!ladders.isEmpty()) {
		string currentLadder = ladders.dequeue();
		if (getLastWordFromLadder(currentLadder, start) == end) { // if ladder is already completed
			return "Found Ladder: " + currentLadder;
		}
		for (int i = 0; i < start.length(); i++) {
			for (int j = 97; j <= 122; j++) { // loop over ascii values of characters
				string lastWord = getLastWordFromLadder(currentLadder, start);
				lastWord[i] = (char) j; // change each index to casted to char to generate possible words
				if (lastWord == end) {
					return "Found Ladder: " + currentLadder + " -> " + end;
				}
				if (wordlist.contains(lastWord) && !usedWords.contains(lastWord)) { // increase ladder size with generated words
					string copy = currentLadder;
					copy += " -> " + lastWord;
					ladders.enqueue(copy);
					usedWords.add(lastWord);
				}
			}
		}
	}

	return "No word ladder could be found.";
}

/* could've also used vector to reduce time complexity down to O(1),
   but prefered this approach for some reason */
string getLastWordFromLadder(string ladder, string startWord) {
	return ladder.substr(ladder.length() - startWord.length());
}

void promptUserAndFindLadder() {
	string start = getLine("Enter the starting word (or nothing to quit): ");
	if (start == "") {
		cout << "Goodbye!" << endl;
		exit(0);
	}
	string end = getLine("Enter the ending word: ");
	cout << getLadder(start, end) << endl;
	cout << endl;
	promptUserAndFindLadder();
}