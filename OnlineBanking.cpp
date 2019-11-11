#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <functional>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <cstring>

using namespace std;

void menu();
void credits();
void readFile(string);
void writeFile(string);
void openAccount();
bool checkPhone(string);
bool checkName(string);
bool checkPassword(string);
int genAccNum(int);
int hashPW(string);

/*--------------------------------------class--------------------------------------*/

class Account {
private:
	string acHolderName, acPassword, phNumber;
	int acNumber;
	double acBalance;

public:
	void openAccount();
	void transfer();
	void depoist();
	void withdraw();


};

/*--------------------------------------main--------------------------------------*/

int main() {
	string file_name;
	cout << "Welcome Message designed by Group ___" << endl;
	cout << "Please input the file name of the data file: ";
	cin >> file_name;

	//readFile(file_name);
	//writeFile(file_name);

	menu();

	return 0;
}

/*--------------------------------------function--------------------------------------*/

//credits
void credits() {
	cout << left << setw(20) << "name" << setw(15) << "id" << setw(10) << "class" << setw(20) << "tutorial group" << endl;
	cout << "-----------------------------------------------------------" << endl;
	cout << left << setw(20) << "Wong Kong Lun" << setw(15) << "18039547A" << setw(10) << "class" << setw(20) << "tut class" << endl;
	cout << left << setw(20) << "name" << setw(15) << "student ID" << setw(10) << "class" << setw(20) << "tut class" << endl;
	cout << left << setw(20) << "name" << setw(15) << "student ID" << setw(10) << "class" << setw(20) << "tut class" << endl;
	cout << left << setw(20) << "name" << setw(15) << "student ID" << setw(10) << "class" << setw(20) << "tut class" << endl;
	cout << left << setw(20) << "name" << setw(15) << "student ID" << setw(10) << "class" << setw(20) << "tut class" << endl;
}

//menu
void menu() {
	string menuOption;

	cout << "*** Main Menu ***" << endl;
	cout << "[1] Open Account" << endl;
	cout << "[2] Login" << endl;
	cout << "[3] List All Account" << endl;
	cout << "[4] Credits" << endl;
	cout << "[5] Exist" << endl;
	cout << "*****************" << endl;
	cout << "Option (1 - 5): ";
	cin >> menuOption;

	if (menuOption == "1") {
		openAccount();
	}
	else if (menuOption == "2") {

	}
	else if (menuOption == "3") {

	}
	else if (menuOption == "4") {
		credits();
	}
	else if (menuOption == "5") {

	}
	else {
		cout << "No This Option" << endl;
	}
}

void readFile(string file_name) {
	char line[100];

	// open the file
	ifstream inFile;

	// file should be put in same folder as the source code file
	inFile.open(file_name);

	// repeat until end of file is reached
	while (!inFile.eof()) {
		// get each line from file and print
		inFile.getline(line, 100, '\n');
		cout << line << endl;
	}

	// close the file
	inFile.close();
}

void writeFile(string file_name) {
	// set up the hash function
	hash<string> str_hash;

	// open the file
	ofstream outFile;

	// file is written and put in same folder as source code
	outFile.open(file_name);

	// data fields to write into file
	int acc_no = 567987654;
	string name = "Wong Siu Ming";
	int tel = 60123456;
	size_t hash_val = str_hash("123456");    // hash value has type "size_t"
	double balance = 1300000.12;

	// ensure floating point is written in 2 d.p.
	outFile.setf(ios::fixed, ios::floatfield);
	outFile.precision(2);

	// write contents into file (will overwrite orignal file)
	outFile << acc_no << "\t" << name << "\t" << tel << "\t" << hash_val << "\t" << balance << "\n";

	// close the file
	outFile.close();
}

void bankMenu(string accountName, int accountNumber) {
	string bankMenuOption;
	do {
		system("cls");
		cout << "Hello, " << accountName << endl;
		cout << "Account NO: " << accountNumber << endl;
		cout << "***** Bank Menu *****" << endl;
		cout << "[1] Check Balance" << endl;
		cout << "[2] Deposit" << endl;
		cout << "[3] Withdraw" << endl;
		cout << "[4] Transfer" << endl;
		cout << "[5] Fixed Deposit Enquiry" << endl;
		cout << "[6] Update Account Info" << endl;
		cout << "[7] Logout" << endl;
		cout << "*********************" << endl;
		cout << "Option (1 - 7): ";
		cin >> bankMenuOption;
		system("cls");

		if (bankMenuOption == "1") {

		}
		else if (bankMenuOption == "2") {

		}
		else if (bankMenuOption == "3") {

		}
		else if (bankMenuOption == "4") {

		}
		else if (bankMenuOption == "5") {

		}
		else if (bankMenuOption == "6") {

		}
		else if (bankMenuOption == "7") {

		}
		else {

		}
	} while (bankMenuOption != "8");
}


void Account::openAccount() {
	string accountName, accountName_confirm;
	string phoneNumber, phoneNumber_confirm;
	string accountPassword, accountPassword_confirm;
	double accountBalance;
	system("cls");
	/*---------------------------------------account holder name------------------------------------------*/

		 //do-while loop  for checking the name requirment
	do {
		//do-while loop for input account holder name and confirm
		do {
			if (accountName_confirm != accountName) {
				cout << endl;
				cout << "Not Match, Please Enter Again" << endl;
				cout << endl;
			}
			cout << "Enter the name: ";
			getline(cin, accountName);

			cout << "Confirm the name: ";
			getline(cin, accountName_confirm);
		} while (accountName_confirm != accountName);

		//call the function checkName for check the name requirment
	} while (!checkName(accountName));

	cout << endl;
	/*-----------------------------------account holder phone number--------------------------------------*/
	do {
		do {
			if (phoneNumber_confirm != phoneNumber) {
				cout << endl;
				cout << "Not Match, Please Enter Again" << endl;
				cout << endl;
			}
			cout << "Enter Your Mobile Phone Number: ";
			getline(cin, phoneNumber);

			cout << "Confirm Your Mobile Phone Number: ";
			getline(cin, phoneNumber_confirm);
		} while (phoneNumber_confirm != phoneNumber);
	} while (!checkPhone(phoneNumber));
	/*------------------------------------account password------------------------------------------------*/
	cout << endl;

	//do-while loop for checking the password requirement
	do {
		//do-while loop for  confirm the password
		do {
			if (accountPassword_confirm != accountPassword) {
				cout << endl;
				cout << "Not Match, Please Enter Again" << endl;
				cout << endl;

			}
			cout << "Enter Your Account Password: ";
			getline(cin, accountPassword);

			cout << "Confirm Your Account Password: ";
			getline(cin, accountPassword_confirm);
		} while (accountPassword_confirm != accountPassword);
	} while (!checkPassword(accountPassword));
	system("cls");
}

//the function of checking the phone number requirement
bool checkPhone(string s){

	//let array cstr to contain the phone number
	char *cstr = new char[s.length() + 1];

	//copy string s to cstr array
	strcpy(cstr, s.c_str());

	int counter = 0;

	//for-loop for checking the phone requirement
	for (int i = 0; i < s.length(); i++) {
		if ((int(cstr[i]) >= 48) && (int(cstr[i]) <= 57) && s.length() == 8) {
		}
		else {
			counter++;
		}
	}

	//the condition of checking
	if (counter > 0) {
		cout << endl;
		cout << "Not Match The Phone Number Requirement." << endl;
		cout << "Please Enter Again." << endl;
		cout << endl;
		return 0;
	}
	else {
		return 1;
	}
}

//the function of checking the name requirement
bool checkName(string s) {

	//let array cstr to contain the account holder name
	char *cstr = new char[s.length() + 1];

	//copy string s to cstr array
	strcpy(cstr, s.c_str());

	int counter = 0;


	for (int i = 0; i < s.length(); i++) {
		if (int(cstr[i]) == 32 || (int(cstr[i]) >= 65 && int(cstr[i]) <= 90) || (int(cstr[i]) >= 97 && int(cstr[i]) <= 122)) {
		}
		else {
			counter++;
		}
	}

	if (counter > 0) {
		cout << endl;
		cout << "Not Match The Name Requirement." << endl;
		cout << "Please Enter Again." << endl;
		cout << endl;
		return 0;
	}
	else {
		return 1;
	}
}

//the function of checking the password requirement
bool checkPassword(string s) {
	char *cstr = new char[s.length() + 1];

	strcpy(cstr, s.c_str());

	int counter_Cap = 0, counter_Num = 0, counter_Sma = 0;
	
	for (int i = 0; i < s.length(); i++) {
		if (((int(cstr[i]) >= 65) && (int(cstr[i]) <= 90))) {
			counter_Cap++;
		}
		if (((int(cstr[i]) >= 97) && (int(cstr[i]) <= 122))) {
			counter_Sma++;
		}
		if (((int(cstr[i]) >= 48) && (int(cstr[i]) <= 57))) {
			counter_Num++;
		}
	}

	if ((counter_Cap == 0) || (counter_Sma == 0) || (counter_Num == 0) || (s.length() < 8)) {
		cout << endl;
		cout << "Not Match The Password Requirement." << endl;
		cout << "Please Enter Again." << endl;
		cout << endl;
		return 0;
	}
	else {
		return 1;
	}
}

int genAccNum(int phNum) {
	
	int acNum;

	srand(phNum);

	acNum = (567000000 + rand() % 999999);

	return acNum;
}

int hashPW(string PW) {
	int hashPw;
	hash<string> str_hash;
	hashPw = str_hash(PW);
	return hashPw;
}

