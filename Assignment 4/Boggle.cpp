/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <windows.h>
#include "strlib.h"
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"

#include "math.h"
#include "vector.h"
#include "set.h"
#include "hashmap.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

const Lexicon lexicon("EnglishWords.dat");

/* Function prototypes */

void welcome();
void giveInstructions();
void promptUserForInstructions();
int promptUserForBoggleType();
Grid<char> promptUserForConfiguration(double charAmount, HashMap<char, Vector< Vector<int> >>& capturedLocations);
string retrieveConfigurationCharacters(double charAmount);
void checkDecision(string& choice);
void fillBoardRandomly(double charAmount, Grid<char>& board, HashMap<char, Vector< Vector<int> >>& capturedLocations);
void playerSide(HashMap<char, Vector< Vector<int> >>& capturedLocations, Set<string>& usedWords, Grid<char>& board);
bool canAssembleOnBoard(string word, HashMap<char, Vector< Vector<int> >>& capturedLocations, Vector<int> currentSpot, Vector<Vector<int> >& cubes, Grid<char>& board);
void computerSide(double charAmount, Grid<char>& board, Set<string>& usedWords);
void computerAssembler(string word, Grid<char>& board, Grid<bool> flagged, int row, int col, Set<string>& usedWords);
void gameplay();

/* Main program */

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    welcome();

	gameplay();

    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}
void promptUserForInstructions() {
	cout << endl;
	string instructions = getLine("Do you want instructions? (y/n): ");
	checkDecision(instructions);
	if (instructions == "y" || instructions == "Y") {
		giveInstructions();
	}
}

int promptUserForBoggleType() { // asks user for boggle type and returns amount of characters accordingly
	cout << endl << "You can choose standard Boggle (4x4 grid)," << endl;
	cout << "or Big Boggle (5x5)." << endl;
	string biggle = getLine("Would you like Big Boggle? (y/n): ");
	checkDecision(biggle);

	if (biggle == "y" || biggle == "Y") {
		drawBoard(5, 5);
		return 25;
	} else {
		drawBoard(4, 4);
		return 16;
	}
}
// asks user for configuration and fills the grid accordingly, if answer is yes, will give a choice to player
// if answer is no, will fill up the grid randomly with given algorithm. also, I record every char occurence
// in the map where key is char and value is corresponding locations, this helps me to find out if player can 
// really construct given word on the grid

Grid<char> promptUserForConfiguration(double charAmount, HashMap<char, Vector< Vector<int> >>& capturedLocations) {
	cout << endl;
	cout << "I'll give you a chance to set up the board to your specification, ";
	cout << "Which makes it easier to confirm your boggle program is working. \n";
	string config = getLine("Do you want to force the board configuration? (y/n): ");
	checkDecision(config);

	Grid<char> board((int) sqrt(charAmount), (int) sqrt(charAmount));

	if (config == "y" || config == "Y") {
		string userConfig = retrieveConfigurationCharacters(charAmount);

		for (int i = 0; i < (int) sqrt(charAmount); i++) {
			for (int j = 0; j < (int) sqrt(charAmount); j++) {
				char value = userConfig[(int) sqrt(charAmount)*i + j];
				value = toupper(value);
				labelCube(i, j, toupper(value));
				board[i][j] = value;
				
				Vector<int> entry;
				entry += i, j;
				if (capturedLocations.containsKey(value)) {
					capturedLocations[value] += entry;
				} else {
					Vector< Vector<int> > entries;
					entries += entry;
					capturedLocations.put(value, entries);
				}
			}
		}

	} else {
		fillBoardRandomly(charAmount, board, capturedLocations);
	}

	return board;
}

void checkDecision(string& choice) { // urges user to answer only yes (y) or no (n)
	while (choice != "y" && choice != "n" && choice != "N" && choice != "Y") {
		choice = getLine("Please enter yes or no (y/n): ");
	}
}

string retrieveConfigurationCharacters(double charAmount) {
	cout << "Enter a " << charAmount << "-character string t indentify which letters you want on the cubes.";
	cout << "The first " << (int) sqrt(charAmount) << " letters are the cubes on the top row from left to right, ";
	cout << "the next " << (int) sqrt(charAmount) << " letters are the second row, and so on." << endl;
	return getLine("Enter the string: ");
}

void fillBoardRandomly(double charAmount, Grid<char>& board, HashMap<char, Vector< Vector<int> > >& capturedLocations) { // fills the grid randomly with given algorithm
	Vector<string> combos;
	for (int  i = 0; i < charAmount; i++) {
		combos += BIG_BOGGLE_CUBES[i];
	}

	for (int i = 0; i < charAmount; i ++) {
		int x = randomInteger(i, combos.size() - 1);
		string temp = combos[i];
		combos.set(i, combos[x]);
		combos.set(x, temp);
	}

	for (int i = 0; i < (int) sqrt(charAmount); i++) {
		for (int j = 0; j < (int) sqrt(charAmount); j++) {
			char value = combos[(int) sqrt(charAmount)*i+j][randomInteger(0, (int) sqrt(charAmount))];
			value = toupper(value);
			labelCube(i, j, value);
			board[i][j] = value;

			Vector<int> entry;
			entry += i, j;
			if (capturedLocations.containsKey(value)) {
				capturedLocations[value] += entry;
			} else {
				Vector< Vector<int> > entries;
				entries += entry;
				capturedLocations.put(value, entries);
			}
		}
	}
}

// player-side logic, while given word is not "", algorithm checks given words on stated checkpoints and acts accordingly
void playerSide(HashMap<char, Vector< Vector<int> >>& capturedLocations, Set<string>& usedWords, Grid<char>& board) {
	cout << endl << "Ok, take all the time you want and find all the words you can! ";
	cout << "Signal that you're finished by entering an empty line." << endl << endl;

	Vector<int> empty; // used to store next character locations and compare to generated ones
	Vector<Vector<int> > cubes; // for storing cube locations to highlight them
	
	string word = toUpperCase(getLine("Enter a word: "));
	while (word != "") {
		if (word.size() < 4) {
			cout << "I'm sorry, but we have our standards." << endl;
			cout << "That word doesn't meet the minimum word length." << endl;
		} else if (!lexicon.contains(word) || !canAssembleOnBoard(word, capturedLocations, empty, cubes, board)) {
			cout << "You can't make that word!" << endl;
		} else if (usedWords.contains(word)) {
			cout << "You've already guessed that!" << endl;
		} else {
			Set<string> cubesC; // in cubesC there are joined indices [0,0]->00 and so on, if cubesC and cubes size aren't equal, then there exists at least one cube which was repeated, and I don't want to include that
			foreach (Vector<int> cube in cubes) {
				cubesC += integerToString(cube[0]) + integerToString(cube[1]);
			}
			if (cubesC.size() != cubes.size()) {
				cout << "You' can't make that word!" << endl;
				cubes.clear();
			} else {
				usedWords += word;
				recordWordForPlayer(word, HUMAN);
			
				foreach(Vector<int> cube in cubes) { // highlight
					highlightCube(cube[0], cube[1], true);
				}
				Sleep(1000);
				foreach(Vector<int> cube in cubes) { // unhighlight
					highlightCube(cube[0], cube[1], false);
				}

				cubes.clear(); // clear remembered cubes for next word
			}
		}

		word = toUpperCase(getLine("Enter a word: "));
	}
}

// checks if player can really build given word on the grid, also stores valid cubes in the cubes vector to highlight them later
bool canAssembleOnBoard(string word, HashMap<char, Vector< Vector<int> >>& capturedLocations, Vector<int> currentSpot, Vector< Vector<int>>& cubes, Grid<char>& board) {
	if (word == "") {
		return true;
	} else if (!capturedLocations.containsKey(word[0])) {
		return false;
	} else {
		foreach (Vector<int> loc in capturedLocations[word[0]]) {
			if (!currentSpot.isEmpty() && (loc[0] != currentSpot[0] || loc[1] != currentSpot[1])) continue;
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if ((i == j && i == 0) || !board.inBounds(loc[0]+i, loc[1]+j)) continue;
					Vector<int> nextLoc = loc;
					nextLoc[0] += i;
					nextLoc[1] += j;
					if (canAssembleOnBoard(word.substr(1), capturedLocations, nextLoc, cubes, board)) {
						cubes += loc;
						return true;
					}
				}
			}
		}
	}
	return false;
}

// computer-side logic, stores used cells in "flagged" grid, uses recursion to generate all possible words starting from first cell [0,0]
void computerSide(double charAmount, Grid<char>& board, Set<string>& usedWords) {
	Grid<bool> flagged((int) sqrt(charAmount), (int) sqrt(charAmount));

	for (int i = 0; i < (int) sqrt(charAmount); i++) {
		for (int j = 0; j < (int) sqrt(charAmount); j++) {
			computerAssembler(string() + board[i][j], board, flagged, i, j, usedWords);
		}
	}
}

// adds characters step by step while periodically checking if they were already used, they're in the bounds of given grid and
// if they're not pointing to the same location, then records those words for computer if they're valid english words with size more than 4
void computerAssembler(string word, Grid<char>& board, Grid<bool> flagged, int row, int col, Set<string>& usedWords) {
	if (!lexicon.containsPrefix(word) || flagged[row][col]) return;

	flagged[row][col] = true;

	if (word.size() >= 4 && lexicon.contains(word) && !usedWords.contains(word)) {
		usedWords += word;
		recordWordForPlayer(word, COMPUTER);
	}

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (!board.inBounds(row + i, col + j) || (i == 0 && j == 0) || flagged[row + i][col + j]) {
				continue;
			}
			computerAssembler(word + board[row+i][col+j], board, flagged, row + i, col + j, usedWords);
		}
	}
}

// [gameplay logic] recursively renews gameplay if needed
void gameplay() {
	HashMap<char, Vector<Vector<int> > > capturedLocations;
	Set<string> usedWords;
	promptUserForInstructions();

	double charAmount = promptUserForBoggleType();
	Grid<char> board = promptUserForConfiguration(charAmount, capturedLocations);

	playerSide(capturedLocations, usedWords, board);
	computerSide(charAmount, board, usedWords);

	string playAgain = getLine("Would you like to play again? (y/n): ");
	checkDecision(playAgain);
	if (playAgain == "Y" || playAgain == "y") gameplay();
}