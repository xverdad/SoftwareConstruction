/* Name:		     Xavier Verdad
/  Auburn UserID:    xcv0001
/  File name:	     Project1.cpp
/  Code Compilation: This source code can be compiled by using a g++ compiler in
/					 a linux machine, or an equivalent to a linux machine.
/
/  Help Used:		 I used the slides provided via Canvas for syntax reference, the C++ book for the course,
/					 and the internet for any additional help.
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <fstream>


using namespace std;

//Reads and writes a text file for high scores
struct HighScores { 
	public:
		double score;
		string name;
		//Score is calculated by multiplying time, money, and intel together.
		// Name associated with the score
}highScore;

//Saves where your stats are
struct CharacterStats {
	public:
		int position;
		int intel;
		int time;
		double money;
} stats;

class Character {
	public: 
		void scoreCalculator();
		void statsGenerator(); //Randomly generates stats with a minimum and maximum threshold (Good)
		//functions and structs
};

class Menu {
	public:
		bool restart;
		string option;
		void selectname();
		void openingScreen(); //generates the opening screen pre-game
		void mainGameMenu(); //Handles the main menu of the game
		void inGameMenu(); //generates the in game menu and options
		void highScoreMenu(); //generates the high score menu
		//functions and structs
};

class Encounter {
	public:
		int randomChance;
		int encounterChoice;
		void rnGeesus();
		//functions and structs
};

class System {
public:
	Character player;
	Menu screen;
	Encounter encounter;
	//functions and structs
};

////////// Function "functionality" ///////////////
void Encounter::rnGeesus() {
	int statDecay;

	randomChance = rand() % 100; //Results from 0 to 99
	
	if (randomChance < 25) {
		cout << "\nYou moved forward. Nothing interesting happened." << endl;
	}
	else if (25 <= randomChance && randomChance < 50) {
		cout << "\nYou encountered a NOTHING!" << endl;
	}
	else if (50 <= randomChance && randomChance <  60) {
		cout << "\nYou encountered a professor. You lose time, but gained ";
		cout << "some intelligence." << endl;
		statDecay = rand() % 3 + 1;
		stats.time = stats.time - statDecay;
		stats.intel = stats.intel + statDecay;
	}
	else if (60 <= randomChance && randomChance <  70) {
		cout << "\nYou encountered another graduate student.";
		cout << " You lost some time." << endl;
		statDecay = rand() % 3 + 1;
		stats.time = stats.time - statDecay;
	}
	else if (70 <= randomChance && randomChance <  80) {
		cout << "\nYou got to grade papers. You lose time, but gained ";
		cout << "some money." << endl;
		statDecay = rand() % 3 + 1;
		stats.time = stats.time - statDecay;
		stats.money = stats.money + statDecay;
	}
	else if (randomChance >= 80) {
		cout << "\nYou have been swamped with grunt work! You lose both ";
		cout << "time and intelligence!" << endl;
		statDecay = rand() % 3 + 1;
		stats.time = stats.time - statDecay;
		stats.intel = stats.intel - statDecay;
	}
}

void Character::statsGenerator() {
	int randomNumber;
	
	do {
		randomNumber = rand() % 100;
		stats.intel = randomNumber;
	} while (randomNumber < 25 || randomNumber > 35);

	do {
		randomNumber = rand() % 100;
		stats.time = randomNumber;
	} while (randomNumber < 35 || randomNumber > 45);

	do {
		randomNumber = rand() % 100;
		stats.money = randomNumber;
	} while (randomNumber < 25 || randomNumber > 35);
}

void Character::scoreCalculator() {
	highScore.score = (stats.intel * stats.money * stats.time);
	if (highScore.score < 0) {
		highScore.score = 0;
	}

	string outputName = "highScores.txt";
	ofstream highScorefile;
	highScorefile.open((char*)outputName.c_str());

	highScorefile << highScore.score << endl;
	highScorefile.close();
}

void Menu::selectname() {
	restart = false;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
	cout << "What's your name? ";
	cin >> highScore.name;
}

void Menu::openingScreen() {
	cout << "\n ========================================================" << endl;
	cout << "\t\t\tWelcome, " << highScore.name << endl;
	cout << " ========================================================\n" << endl;

	cout << "1.) Start a New Game of Shelby Center and Dragons!" << endl;
	cout << "2.) View top 5 High Scores" << endl;
	cout << "3.) Quit" << endl;
	cout << "\n\t Please choose an option: ";
	cin >> option;
}

void Menu::mainGameMenu() {
	bool invAnswer = false;

	if (option == "1") {
		cout << "\nEntering the Game...\n" << endl;
	}
	else if (option == "2") {
		cout << "\nLoading top score..." << endl;
	}
	else if (option == "3") {
		exit(0);
	}
	else {
		invAnswer = true;
		while (invAnswer) {
			cout << "\nInvalid input." << endl;
			cout << "Please choose an option: 1, 2, or 3: ";
			cin >> option;
			if (option == "1") {
				cout << "\nEntering the Game...\n" << endl;
				break;
			}
			else if (option == "2") {
				cout << "\nLoading tp 5 high scores..." << endl;
				break;
			}
			else if (option == "3") {
				exit(0);
			}
		}
	}
}


void Menu::inGameMenu() {
	bool invAnswer = false;
	int statGrowth;

	cout << "\nYou are " << stats.position << " steps from the goal.";
	cout << "Time left: " << stats.time << ".\n" << endl;
	cout << "\t1.) Move forward (takes time, could be risky...)" << endl;
	cout << "\t2.) Read technical papers (boost intelligence, takes time)" << endl;
	cout << "\t3.) Search for loose change (boost money, takes time)" << endl;
	cout << "\t4.) View character stats" << endl;
	cout << "\t5.) Restart the game (your progress will not be saved)" << endl;
	cout << "\n\n    Please choose an action: ";

	do {
		cin >> option;

		//If player wants to move a space forward
		if (option == "1") {
			stats.position--;
			stats.time--;
			if (stats.position <= 0) {
				string output;
				cout << "\nYOU HAVE REACHED YOUR GOAL!" << endl;
				cout << "Press the enter key to go back to the main menu." << endl;
				cout << "Your score will be saved." << endl;
				cin.ignore().get();
				restart = true;
			}
			invAnswer = false;
		}

		//If player wants to read a technical paper
		else if (option == "2") {
			statGrowth = (rand() % 3) + 1;
			stats.intel = stats.intel + statGrowth;
			stats.time = stats.time - statGrowth;
			if (stats.time <= 0) {
				restart = true;
			}
			invAnswer = false;
		}

		//If player wants to search for money
		else if (option == "3") {
			statGrowth = (rand() % 3) + 1;
			stats.money = stats.money + statGrowth;
			stats.time = stats.time - statGrowth;
			if (stats.time <= 0) {
				restart = true;
			}
			invAnswer = false;
		}

		//If player wants to view character's stats
		else if (option == "4") {
			cout << "\nYou have:\n" << endl;
			cout << "Intelligence: " << stats.intel << endl;
			cout << "Time: " << stats.time << endl;
			cout << "Money: " << stats.money << endl;
			invAnswer = false;
		}

		//If player wants to quit
		else if (option == "5") {
			string answer;
			cout << "\nAre you sure? (y or n): ";
			cin >> answer;

			if (answer == "y") {
				restart = true;
				invAnswer = false;
			}
			else if (answer == "n") {
				restart = false;
				cout << "\nReturning to the in-game menu." << endl;
				invAnswer = false;
			}
			else {
				invAnswer = true;
				while (invAnswer) {
					cout << "\nInvalid input." << endl;
					cout << "Enter 'y' or 'n': ";
					cin >> answer;
					if (answer == "y") {
						restart = true;
						invAnswer = false;
					}
					else if (answer == "n") {
						restart = false;
						cout << "\nReturning to the in game menu." << endl;
						invAnswer = false;
					}
				}
			}
		}
		else {
			invAnswer = true;
			cout << "\nInvalid input." << endl;
			cout << "Enter 1, 2, 3, 4, or 5: ";
		}
	} while (invAnswer);
}

void Menu::highScoreMenu() {
	cout << "\nDisplaying top score..." << endl;
	string line;
	ifstream file;
	file.open("highScores.txt");
	if (getline(file, line)) {
		cout << "Top score: " << line.data() << endl;
		file.close();
	}
	cout << "\nPress enter to return to main menu" << endl;
	cin.ignore().get();
	restart = true;
}

int main() {
	srand((unsigned)time(0)); // Initiates psuedo-random number generator with time(0), which is seconds passed since Jan. 1, 1970
	System game;

	do {
		stats.position = 20;
		game.player.statsGenerator();
		game.screen.selectname();
		game.screen.openingScreen(); //The option to see high score needs work
		game.screen.mainGameMenu();

		if (game.screen.option == "1") {
			do {
				game.screen.inGameMenu();
				if (game.screen.option == "1") {
					if (!(stats.position <= 0)) {
					game.encounter.rnGeesus();
				}
				}
				if (stats.intel <= 0 || stats.money <= 0 || stats.position <= 0 || stats.time <= 0) {
					if (stats.time <= 0) {
						cout << "\nYOU LOSE!" << endl;
						cout << "You ran out of time!" << endl;
						cout << "Your score will now be recorded." << endl;
						cout << "Press enter to return to the main menu" << endl;
						cin.ignore().get();
						game.screen.restart = true;
					}
					game.player.scoreCalculator();
				}
			} while (!game.screen.restart);
		} 
		else if (game.screen.option == "2") {
			game.screen.highScoreMenu();
			//THIS IS WHERE THE HIGH SCORES WILL BE
		}
	} while (game.screen.restart);

	return 0;
}