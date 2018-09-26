/* Name:		     Xavier Verdad
/  Auburn UserID:    xcv0001
/  File name:	     Project2.cpp
/  Code Compilation: This source code can be compiled by using a g++ compiler in
/					 a linux machine, or an equivalent to a linux machine.
/
/  Help Used:		 I used the slides provided via Canvas for syntax reference, the C++ book for the course,
/					 and the internet for any additional help.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <sstream>

using namespace std;

//The menu class handles all menus in the program
class Menu {
	public:
		bool resetToMain;
		string option;
		string username;
		string password;
		void openingMenu();
		void loginMenu();
		void systemAdminMenu();
		void branchStaffMenu();
		void clientAndAccountMenu();
};

//The Admin class handles all the functions employee has along with specialized functions
class Admin {
	public:
		void addBranch();
		void deleteBranch();
		void displayStaff();
};

//Employees: Administrator and Branch Staff
class Employee {
	public:
		int count;
		string DEFAULTADMIN;
		string defaultPass;
		string ROLE1;
		string  ROLE2;
		string roleHolder;
		string STAFF_;

		Admin admin;
		void roleChecker(string role);
		void changePassword(string username);
		void addAccount(); //WORK
		void addClient();//WORK
		void clientEdit(); //Work
		void manageAccount();
};

// Stores all information of a client
struct Client {
	public:
		string clientName;
		string clientAddress;
		string clientSS;
		string clientEmployer;
		string clientIncome;
} client;

//Stores all information of an account
struct Account {
	public:
		string accountNumber;
		string accountType;
		string balance;
} account;

Client clientArray[200];
Account accountArray[200];
int clientNumber = 0;
int accountNumber = 0;

//The system class handles all file reading and is the top tier class
class System {
	public:
		bool validLogin;
		Menu menu;
		Employee employee;
		void readFile_(string name, string password);
		void writeFile_();
		bool searchFile(string username, string filename);
		void recordEverything();
} tellerSystem;

//The idle state of the teller machine prior to loggin-in
void Menu::openingMenu() {
		bool reset = true;
		tellerSystem.menu.resetToMain = false;
		do {
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
			cout << " ===========================================================" << endl;
			cout << " |\t  Welcome to the Auburn Branch of Tiger Bank! \t   |" << endl;
			cout << " ===========================================================" << endl;

			cout << "1.) Login" << endl;
			cout << "2.) Quit" << endl;
			cout << "\tPlease choose an option: ";
			cin >> option;

			bool invAnswer;
			string answer;

			if (option == "1") {
				break;
			}
			else if (option == "2") {
				cout << "\n\tAre you sure?" << endl;
				cout << "\tEnter 'y' for yes or 'n' for no: ";
				cin >> answer;

				do {
					if (answer == "y") {
						exit(0);
					}
					else if (answer == "n") {
						break;
					}
					else {
						invAnswer = true;
						cout << "\n\tInvalid input. \n\tEnter either 'y' or 'n': ";
						cin >> answer;
					}
				} while (invAnswer);
			}
			else {
				bool validOption = true;
				do {
					cout << "\n\tInvalid input. \n\tEnter the following options of 1 or 2: ";
					cin >> option;

					if (option == "1") {
						reset = false;
						break;
					}
					else if (option == "2") {
						validOption = false;
						cout << "\n\tAre you sure?" << endl;
						cout << "\tEnter 'y' for yes or 'n' for no: ";
						cin >> answer;

						do {
							if (answer == "y") {
								exit(0);
							}
							else if (answer == "n") {
								break;
							}
							else {
								invAnswer = true;
								cout << "\n\tInvalid input. \n\tEnter either 'y' or 'n': ";
								cin >> answer;
							}
						} while (invAnswer);
					}
				} while (validOption);
			}
		} while (reset);
}

///The log-in menu that checks if the username with the matching password are correct
void Menu::loginMenu() {
	tellerSystem.validLogin = false;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
	cout << " ===========================================================" << endl;
	cout << " |\t  Login to Access the Teller Terminal System \t   |" << endl;
	cout << " ===========================================================" << endl;
	do {
		cout << "User Name: ";
		cin >> username;
		cout << "Password: ";
		cin >> password;

		tellerSystem.readFile_(username, password);
		if (tellerSystem.validLogin == false) {
			cout << "The user name or password is incorrect. Try again!" << endl;
		}
	} while (!tellerSystem.validLogin);
}

//Shows the menu of a system administrator
void Menu::systemAdminMenu() {
	do {
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
		cout << " ===========================================================" << endl;
		cout << " |      Teller Terminal System - System Administration     |" << endl;
		cout << " ===========================================================" << endl;
		cout << "1.) Client and Account Management" << endl;
		cout << "2.) Add a branch staff member" << endl;
		cout << "3.) Delete a branch staff member" << endl;
		cout << "4.) Display branch staff" << endl;
		cout << "5.) Change password" << endl;
		cout << "6.) Exit" << endl;
		cout << "\tPlease choose an option: ";

		bool invAnswer = false;
		bool invAnswer2 = false;
		string answer;
		do {
			cin >> option;

			if (option == "1") {
				invAnswer = false;
				tellerSystem.menu.clientAndAccountMenu();
			}
			else if (option == "2") {
				invAnswer = false;
				tellerSystem.employee.admin.addBranch();
			}
			else if (option == "3") {
				invAnswer = false;
				tellerSystem.employee.admin.deleteBranch();
			}
			else if (option == "4") {
				invAnswer = false;
				tellerSystem.employee.admin.displayStaff();
			}
			else if (option == "5") {
				invAnswer = false;
				tellerSystem.employee.changePassword(tellerSystem.menu.username);
			}
			else if (option == "6") {
				invAnswer = false;
				cout << "\n\tAre you sure?" << endl;
				cout << "\tEnter 'y' for yes or 'n' for no: ";
				cin >> answer;

				do {
					if (answer == "y") {
						resetToMain = true;
						invAnswer2 = false;
					}
					else if (answer == "n") {
						invAnswer2 = false;
					}
					else {
						invAnswer2 = true;
						cout << "\n\tInvalid input. \n\tEnter either 'y' or 'n': ";
						cin >> answer;
					}
				} while (invAnswer2);
			}
			else {
				cout << "Invalid input. Enter either a 1, 2, 3, 4, 5, or 6: ";
				invAnswer = true;
			}
		} while (invAnswer);
	} while (!resetToMain);
}

//Shows the menu of a branch staff member
void Menu::branchStaffMenu() {
	do {
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
		cout << " ===========================================================" << endl;
		cout << " |\t  Teller Terminal System - Branch Staff \t   |" << endl;
		cout << " ===========================================================" << endl;
		cout << "1.) Client and Account Management" << endl;
		cout << "2.) Change password" << endl;
		cout << "3.) Exit" << endl;
		cout << "\tPlease choose an option: ";

		bool invAnswer = false;
		bool invAnswer2 = false;
		string answer;
		do {
			cin >> option;

			if (option == "1") {
				invAnswer = false;
				tellerSystem.menu.clientAndAccountMenu();
			}
			else if (option == "2") {
				invAnswer = false;
				tellerSystem.employee.changePassword(tellerSystem.menu.username);
			}
			else if (option == "3") {
				invAnswer = false;
				cout << "\n\tAre you sure?" << endl;
				cout << "\tEnter 'y' for yes or 'n' for no: ";
				cin >> answer;

				do {
					if (answer == "y") {
						resetToMain = true;
						invAnswer2 = false;
					}
					else if (answer == "n") {
						invAnswer2 = false;
					}
					else {
						invAnswer2 = true;
						cout << "\n\tInvalid input. \n\tEnter either 'y' or 'n': ";
						cin >> answer;
					}
				} while (invAnswer2);
			}
			else {
				cout << "Invalid input. Enter either a 1, 2, or 3: ";
				invAnswer = true;
			}
		} while (invAnswer);
	} while (!resetToMain);
}

//Shows the menu of the client and account management
void Menu::clientAndAccountMenu() {
	bool resetToSubMenu = false;
	do {
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
		cout << " ===========================================================" << endl;
		cout << " | Teller Terminal System - Client and Account Management  |" << endl;
		cout << " ===========================================================" << endl;
		cout << "1.) Add a client" << endl;
		cout << "2.) Add an account" << endl;
		cout << "3.) Edit Client Information" << endl;
		cout << "4.) Manage an account" << endl;
		cout << "5.) Save Client and Account Information" << endl;
		cout << "6.) Exit" << endl;
		cout << "\tPlease choose an option: ";

		bool invAnswer = false;
		bool invAnswer2 = false;
		string answer;
		do {
			cin >> option;

			if (option == "1") {
				invAnswer = false;
				tellerSystem.employee.addClient();
			}
			else if (option == "2") {
				invAnswer = false;
				tellerSystem.employee.addAccount();
			}
			else if (option == "3") {
				invAnswer = false;
				tellerSystem.employee.clientEdit();

			}
			else if (option == "4") {
				invAnswer = false;
				tellerSystem.employee.manageAccount();
			}
			else if (option == "5") {
				invAnswer = false;
				tellerSystem.recordEverything();
			}
			else if (option == "6") {
				invAnswer = false;
				cout << "\n\tAre you sure?" << endl;
				cout << "\tEnter 'y' for yes or 'n' for no: ";
				cin >> answer;

				do {
					if (answer == "y") {
						resetToSubMenu = true;
						invAnswer2 = false;
					}
					else if (answer == "n") {
						invAnswer2 = false;
					}
					else {
						invAnswer2 = true;
						cout << "\n\tInvalid input. \n\tEnter either 'y' or 'n': ";
						cin >> answer;
					}
				} while (invAnswer2);
			}
			else {
				cout << "Invalid input. Enter either a 1, 2, 3, 4, 5, or 6: ";
				invAnswer = true;
			}
		} while (invAnswer);
	} while (!resetToSubMenu);
}

//Writes the information of employees and clients and saves them into a .txt file (good)
void System::writeFile_() {
	ofstream staffFile((char*)employee.STAFF_.c_str());
	if (staffFile.is_open()) {
		staffFile << employee.DEFAULTADMIN + " ";
		staffFile << employee.defaultPass;
		staffFile << employee.ROLE1 + "\n";
	}
	staffFile.close();
}

//Reads the information of employees and clients from a .txt file for Display function
void Admin::displayStaff() {
	ifstream staffFile((char*)tellerSystem.employee.STAFF_.c_str());
	string nameInFile;
	string passwordInFile;
	string roleHolder;
	int i = 0;

	cout << "\nNumber of users in the system: ";
	cout << tellerSystem.employee.count << endl;

	while (i < tellerSystem.employee.count) {
		staffFile >> nameInFile;
		staffFile >> passwordInFile;
		getline(staffFile, roleHolder);

		cout << i + 1;
		cout << ". User Name: " + nameInFile + "       Role:" + roleHolder << endl;
		i++;
	}
	cout << "Press any key to continue...";
	cin.ignore().get();
}

//Searches for any usernames with a matching password in Staff file (need to modify into 3 other files)
//Functionality is good.
void System::readFile_(string name, string password) {
	ifstream staffFile((char*)employee.STAFF_.c_str());
	string nameInFile;
	string passwordInFile;
	string lineBuffer;
	string roleHolder;

	while (staffFile.good()) {
		staffFile >> nameInFile;
		if (nameInFile == name) {
			staffFile >> passwordInFile;
			if (passwordInFile == password) {
				validLogin = true;
				getline(staffFile, roleHolder);
				tellerSystem.employee.roleChecker(roleHolder);
				break;
			}
		}
		getline(staffFile, lineBuffer);
	}
	staffFile.close();
}

//Checks what role the user is and opens which menu accordingly (good)
void Employee::roleChecker(string role) {
	if (role == " System Administrator") {
		tellerSystem.menu.systemAdminMenu();
	}
	else if (role == " Branch Staff") {
		tellerSystem.menu.branchStaffMenu();
	}
}

//Adds a client into the system
void Employee::addClient() {
	cout << "A new client will be added: ";
	cout << "\nPress Enter to continue..." << endl;
	cin.ignore().get();
	cout << "Client name: ";
	getline(cin, client.clientName);

	cout << "Address: ";
	getline(cin, client.clientAddress);
	
	cout << "Social security number: ";
	getline(cin, client.clientSS);
	
	cout << "Employer: ";
	getline(cin, client.clientEmployer);
	
	cout << "Annual income: ";
	getline(cin, client.clientIncome);
	
	cout << "A new client was added!" << endl;
	cout << "Press any key to continue...";
	cin.ignore().get();

	clientArray[clientNumber] = client;
	clientNumber++;
}

//Adds an account for the client
void Employee::addAccount() {
	string name;
	bool match = false;
	int counter = 0;
	cin.ignore().get();
	cout << "Choose a client: ";
	getline(cin, name);

	for (int i = 0; i < clientNumber; i++) {
		if (clientArray[i].clientName == name) {
			match = true;
			break;
		}
		counter++;
	}

	if (!match) {
		cout << "Error - The client is not in the system!" << endl;
		cout << "Returning back to previous menu." << endl;
		cout << "Press Enter to continue." << endl;
		cin.ignore().get();
	}

	if (match) {
		cout << "A new account will be created for ";
		cout << clientArray[counter].clientName;
		cout << "..." << endl;
		cout << "Account Number: ";
		getline(cin, account.accountNumber);

		cout << "Account Type: ";
		getline(cin, account.accountType);

		cout << "Balance: ";
		getline(cin, account.balance);

		cout << "A new account was created for " + clientArray[counter].clientName;
		cout << "!" << endl;
		cout << "Press Enter to continue...";
		cin.ignore().get();

		accountArray[accountNumber] = account;
		accountNumber++;
	}
}

//Edits the client's information
void Employee::clientEdit() {
	string name;
	bool valid = false;
	bool match = false;
	cin.ignore().get();
	cout << "Choose a client: ";
	getline(cin, name);

	string fileName;
	int counter = 0;
	for (int i = 0; i < clientNumber; i++) {
		if (clientArray[i].clientName == name) {
			fileName = name;
			match = true;
			break;
		}
		counter++;
	}

	if (!match) {
		cout << "Name was not found in the system. Returning back to previous menu." << endl;
		cout << "Press Enter to continue...";
		cin.ignore().get();
	}

	if (match) {
		cout << "Display ";
		cout << clientArray[counter].clientName;
		cout << "'s information: " << endl;
		cout << "Address: " + clientArray[counter].clientAddress << endl;
		cout << "Social security number: " + clientArray[counter].clientSS << endl;
		cout << "Employer: " + clientArray[counter].clientEmployer << endl;
		cout << "Annual income: " + clientArray[counter].clientIncome << endl;
		cout << "Client ";
		cout << clientArray[counter].clientName;
		cout << "'s information will be updated..." << endl;

		string option;
		do {
			cout << "1.) Confirm" << endl;
			cout << "2.) Cancel" << endl;
			cout << "\tPlease choose an option: ";
			cin >> option;
			if (option == "1") {
				valid = true;
				cout << "Press Enter to continue.";
				cin.ignore().get();
				cout << "Address: ";
				getline(cin, clientArray[counter].clientAddress);
				cout << "Social security number: ";
				getline(cin, clientArray[counter].clientSS);
				cout << "Employer: ";
				getline(cin, clientArray[counter].clientEmployer);
				cout << "Annual income: ";
				getline(cin, clientArray[counter].clientIncome);
				cout << "Client " + clientArray[counter].clientName;
				cout << "'s information was updated!" << endl;
				cout << "Press any key to continue...";
				cin.ignore().get();
			}
			else if (option == "2") {
				cout << "Returning back to more options." << endl;
				cout << "Press Enter to continue.";
				valid = true;
				cin.ignore().get();
			}
			else {
				cout << "Error - Invalid input. Enter '1' or '2':" << endl;
				valid = false;
			}
		} while (!valid);

	}
}

//Manages the account
void Employee::manageAccount() {
	stringstream stream;
	string number;
	bool match = false;
	cout << "Which account will be managed? ";
	cin.ignore();
	getline(cin, number);

	int counter = 0;
	for (int i = 0; i < clientNumber; i++) {
		if (accountArray[i].accountNumber == number) {
			match = true;
			break;
		}
		counter++;
	}

	if (!match) {
		cout << "Error - Account number: ";
		cout << number;
		cout << " is not in the system! Returning to previous menu.";
		cout << "\nPress Enter to continue...";
		cin.ignore().get();
	}

	if (match) {
		string option;
		cout << "1.) Manage an account" << endl;
		cout << "2.) Cancel" << endl;
		cout << "\tPlease choose an option: ";
		cin >> option;

		if (option == "1") {
			cout << "Manage account number: ";
			cout << number << endl;

			string option2;
			bool isTrue = false;
			cout << "1.) Deposit" << endl;
			cout << "2.) Withdraw" << endl;
			cout << "3.) Cancel" << endl;
			do {
				cin >> option2;

				if (option2 == "1") {
					int depositAmount;
					isTrue = true;
					cout << "Deposit Amount: ";
					cin >> depositAmount;
					stream << accountArray[counter].balance;
					int newBalance;
					stream >> newBalance;
					stream.clear();
					stream.str("");
					int sum = depositAmount + newBalance;
					string sumString;
					stream << sum;
					stream >> sumString;
					accountArray[counter].balance = sumString;
				}
				else if (option2 == "2") {
					int depositAmount;
					isTrue = true;
					cout << "Withdraw Amount: ";
					cin >> depositAmount;
					stream << accountArray[counter].balance;
					int newBalance;
					stream >> newBalance;
					stream.clear();
					stream.str("");
					int sum = depositAmount - newBalance;
					string sumString;
					stream << sum;
					stream >> sumString;
					accountArray[counter].balance = sumString;
				}
				else if (option2 == "3") {
					isTrue = true;
					cout << "Returning to previous menu." << endl;
					cout << "Press Enter to continue..." << endl;
					cin.ignore().get();
				}
				else {
					cout << "Invalid input. Please enter '1', '2', or '3': \n";
					isTrue = false;
				}
			} while (!isTrue);
		}
		else if (option != "2") {
			cout << "Returning to previous menu." << endl;
			cout << "Press Enter to continue..." << endl;
			cin.ignore().get();
		}
		else {
			cout << "Invalid input." << endl;
			cout << "Returning to previous menu." << endl;
			cout << "Press Enter to continue..." << endl;
			cin.ignore().get();
		}
	}
}

//Adds a new branch staff member, if one doesn't already exists into a .text file (good)
void Admin::addBranch() {
	string username;
	string password;
	string role;
	string confimation;
	bool exist = false;
	bool validRole = false;
	ofstream filename;
	
	do {
		cout << "\nUser Name: ";
		cin >> username;
		if (!tellerSystem.searchFile(username, (char*)tellerSystem.employee.STAFF_.c_str())) {
			exist = true;
			cout << "Password: ";
			cin >> password;
			
			do {
				do {
					cout << "Role (1 - Administrator; 2 - Branch Staff): ";
					cin >> role;

					if (role == "1") {
						validRole = true;
						role = " System Administrator";
					}
					else if (role == "2") {
						validRole = true;
						role = " Branch Staff";
					}
					else {
						cout << "Invalid input. Please select either 1 or 2\n" << endl;
					}
				} while (!validRole);

				cout << "1.) Confirm" << endl;
				cout << "2.) Cancel" << endl;
				cout << "\tPlease choose an option: ";
				cin >> confimation;

				if (confimation == "1") {
					tellerSystem.employee.count++;
					filename.open((char*)tellerSystem.employee.STAFF_.c_str(), ios::app);
					filename << username + " " << password << role + "\n";
					cout << "\nA new" + role + " member is added!" << endl;
					cout << "User Name: " + username + "     Role:" + role;
					cout << "\nPress any key to continue...";
					cin.ignore().get();
				}
				if (confimation == "2") {
					validRole = false;
					cout << "\n";
				}
				else {
					validRole = false;
					cout << "Error. Restarting back to role selection.\n" << endl;
				}
			} while (confimation != "1");
		}
		else {
			cout << "This user name already exist.\n" << endl;
		}
	} while (!exist);
}

//Deletes an account that exists in the staff file (good)
void Admin::deleteBranch() {
	string user;
	string confirmation;
	bool reset = false;

	do {
		cout << "\nDelete a user - User Name: ";
		cin >> user;

		cout << "1.) Confim" << endl;
		cout << "2.) Cancel" << endl;
		cout << "\tPlease choose an option: ";
		cin >> confirmation;

		if (confirmation == "1") {
			if (!tellerSystem.searchFile(user, (char*)tellerSystem.employee.STAFF_.c_str())) {
				reset = false;
				cout << "Warning - User " + user + " is not in the system. No user is deleted!" << endl;
				cout << "Press any key to continue...";
				cin.ignore().get();
			}
			else {
				if (user == "admin") {
					cout << "Warning - user name " + user + " cannot be deleted. Choose another user." << endl;
					reset = true;
				} else if (tellerSystem.menu.username != user) {
					reset = false;
					string line;
					ifstream looker((char*)tellerSystem.employee.STAFF_.c_str());
					ofstream temp("temp.txt");

					while (looker.good()) {
						looker >> line;
						if (line != user) {
							temp << line;
							getline(looker, line);
							temp << line << endl;
						}
						else {
							tellerSystem.employee.count--;
							getline(looker, line);
						}
					}
					temp.close();
					looker.close();

					ifstream looker2("temp.txt");
					ofstream newFile((char*)tellerSystem.employee.STAFF_.c_str());

					int i = 0;
					while (i < tellerSystem.employee.count) {
						getline(looker2, line);
						newFile << line << endl;
						i++;
					}
					looker2.close();
					newFile.close();

					remove("temp.txt");

					cout << "User " + user + " was deleted!" << endl;
					cout << "Press any key to continue...";
					cin.ignore().get();
				}
				else {
					cout << "Warning - You cannot delete yourself. Choose another user." << endl;
					reset = true;
				}
			}
		}
		else if (confirmation == "2") {
			reset = true;
		}
		else {
			reset = true;
			cout << "Error. Invalid input. Restarting back to user deletion selection." << endl;
		}
	} while (reset);
}

//Looks inside a file and see if there is a pre-existing username (good)
bool System::searchFile(string username, string filename) {
	ifstream file((char*)filename.c_str());
	string nameInFile;

	do {
		file >> nameInFile;
		if (nameInFile == username) {
			return true;
			file.close();
			break;
			}
	} while (file.good());

	file.close();
	return false;
}

//Changes the password of the user
void Employee::changePassword(string name) {
	string newPassword;
	string nameInFile;
	string passwordInFile;
	string role;
	bool passwordChange = false;
	ifstream file((char*)tellerSystem.employee.STAFF_.c_str());
	bool valid = false;

	do {
		ifstream file((char*)tellerSystem.employee.STAFF_.c_str());
		cout << "New Password: ";
		cin >> newPassword;

		do {
			file >> nameInFile;
			if (nameInFile == name) {
				file >> passwordInFile;
				if (passwordInFile == newPassword) {
					passwordChange = false;
					break;
				}
				passwordChange = true;
				break;
			}
			getline(file, nameInFile);
		} while (file.good());
		file.close();

		if (passwordChange) {
			valid = true;
			ifstream file((char*)tellerSystem.employee.STAFF_.c_str());
			ofstream temp("temp.txt");
			int i = 0;
			do {
				file >> nameInFile;
				if (nameInFile != name) {
					file >> passwordInFile;
					getline(file, role);
					temp << nameInFile + " ";
					temp << passwordInFile;
					temp << role << endl;
				}
				else if (nameInFile == name) {
					file >> passwordInFile;
					getline(file, role);
					temp << nameInFile + " ";
					temp << newPassword;
					temp << role << endl;
				}
				i++;
			} while (i < tellerSystem.employee.count);


			temp.close();
			file.close();

			ifstream file2("temp.txt");
			ofstream newFile((char*)tellerSystem.employee.STAFF_.c_str());

			i = 0;
			while (i < tellerSystem.employee.count) {
				getline(file2, nameInFile);
				newFile << nameInFile << endl;
				i++;
			}
			file2.close();
			newFile.close();

			remove("temp.txt");

			cout << "Password was changed!" << endl;
			cout << "Press any key to continue...";
			cin.ignore().get();
		}
		else if (!passwordChange) {
			cout << "Error - Your new password must be different from the old one!" << endl;
		}
	} while (!valid);
}

//Records client and account data into a .text file
void System::recordEverything() {
	ofstream file("client-info.txt");

	for (int i = 0; i < clientNumber; i++) {
		file << clientArray[i].clientName << endl;
		file << clientArray[i].clientAddress << endl;
		file << clientArray[i].clientSS << endl;
		file << clientArray[i].clientEmployer << endl;
		file << clientArray[i].clientIncome << endl;
		file << "\n";
	}
	file.close();

	ofstream file2("account-info.txt");
	for (int j = 0; j < accountNumber; j++) {
		file2 << accountArray[j].accountNumber << endl;
		file2 << accountArray[j].accountType << endl;
		file2 << accountArray[j].balance << endl;
		file << "\n";
	}
	file2.close();
	cout << "Client information has been saved in the client-info file; account" << endl;
	cout << "information has been saved int he account-info file!" << endl;
	cout << "Press any key to continue...";
	cin.ignore().get();
}

int main() {
	tellerSystem.menu.resetToMain = false;
	tellerSystem.employee.DEFAULTADMIN = "admin";
	tellerSystem.employee.defaultPass = "0000";
	tellerSystem.employee.count = 1;
	tellerSystem.employee.ROLE1 = " System Administrator";
	tellerSystem.employee.ROLE2 = " Branch Staff";
	tellerSystem.employee.STAFF_ = "staff.txt";

	tellerSystem.writeFile_();

	do {
		tellerSystem.menu.openingMenu();
		tellerSystem.menu.loginMenu();
	} while (tellerSystem.menu.resetToMain);

	return 0;
}