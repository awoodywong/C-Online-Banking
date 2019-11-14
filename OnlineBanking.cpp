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

void menu(string);
void credits();
void readFile(string);
void writeFile_openAC(string);
bool checkPhone(int);
bool checkName(string);
bool checkPassword(string);
string acName_input();
int phNum_input();
string acPw_input();
int genAccNum(int);
double balance_input();
void inputReq();
double deposit();
double withdraw();
bool ynexit();

/*--------------------------------------class--------------------------------------*/

class Account {
private:
	string name, password;
	int acNum, tel;
	double balance;
	size_t hash_val;

public:
	/*Account(string acName, size_t hash_pw , int acc_no, int acTel, double bal) {
		name = acName;
		acNum = acc_no;
		tel = acTel;
		balance = bal;
	}*/

	string getName() {
		return name;
	}

	void setName(string acName) {
		name = acName;
	}

	int getAcNum() {
		return acNum;
	}

	void setAcNum(int acc_no) {
		acNum = acc_no;
	}

	int getTel() {
		return tel;
	}

	void setTel(int acTel) {
		tel = acTel;
	}

	double getBalance() {
		return balance;
	}

	void setBalance(double bal) {
		balance = bal;
	}

	void bankMenu() {
		string bankMenuOption;
		do {
			system("cls");
			cout << "Hello, " << name << endl;
			cout << "Account NO: " << acNum << endl;
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

			if (bankMenuOption == "1") {
				system("cls");
				cout << setw(30) << left << "Account Holder Name:" << name << endl;
				cout << setw(30) << left << "Account Number:" << acNum << endl;
				cout << setw(30) << left << "Account Balance:" << fixed << balance << " HKD" << endl;
				system("pause");
			}
			else if (bankMenuOption == "2") {
				double deposit_amount;
				system("cls");
				deposit_amount = deposit();
				balance += deposit_amount;
				cout << endl;
				cout << "-----SUCCESS-----" << endl;
				system("pause");
			}
			else if (bankMenuOption == "3") {
				double withdraw_amount;
				system("cls");
				withdraw_amount = withdraw();
				balance -= withdraw_amount;
				cout << endl;
				cout << "-----SUCCESS-----" << endl;
				system("ppause");
			}
			else if (bankMenuOption == "4") {

			}
			else if (bankMenuOption == "5") {

			}
			else if (bankMenuOption == "6") {

			}
			else if (bankMenuOption == "7") {
				if (ynexit()) {
					system("cls");
					cout << "Thanks For Using Online Banking." << endl;
					break;
				}
				else {

				}
			}
			else {
				cout << "\a";
			}
		} while (bankMenuOption != "7");
	}

};

/*--------------------------------------main--------------------------------------*/

int main() {
	string file_name;
	cout << "Welcome Message designed by Group ___" << endl;
	cout << "Please input the file name of the data file: ";
	cin >> file_name;
	//readFile(file_name);
	//system("pause");
	menu(file_name);

	return 0;
}

/*--------------------------------------function--------------------------------------*/

//credits
void credits() {
	system("cls");
	cout << left << setw(20) << "Name" << setw(15) << "ID" << setw(10) << "Class" << setw(20) << "Tutorial Group" << endl;
	cout << "-----------------------------------------------------------" << endl;
	cout << left << setw(20) << "Wong Kong Lun" << setw(15) << "18039547A" << setw(10) << "class" << setw(20) << "tut class" << endl;
	cout << left << setw(20) << "name" << setw(15) << "student ID" << setw(10) << "class" << setw(20) << "tut class" << endl;
	cout << left << setw(20) << "name" << setw(15) << "student ID" << setw(10) << "class" << setw(20) << "tut class" << endl;
	cout << left << setw(20) << "name" << setw(15) << "student ID" << setw(10) << "class" << setw(20) << "tut class" << endl;
	cout << left << setw(20) << "name" << setw(15) << "student ID" << setw(10) << "class" << setw(20) << "tut class" << endl;
}

//menu
void menu(string file_name) {
	Account ac;
	string menuOption;
	do {
		system("cls");
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
			system("cls");
			inputReq();
			writeFile_openAC(file_name);
		}
		else if (menuOption == "2") {

		}
		else if (menuOption == "3") {
			system("cls");
			readFile(file_name);
			system("pause");
		}
		else if (menuOption == "4") {
			system("cls");
			credits();
			system("pause");
		}
		else if (menuOption == "5") {
			char n;
			cout << "Are You Sure To Exit?" << endl;
			cout << "Press \"Y/y\" For YES, \"N/n\" For NO: ";
			cin >> n;
			if (n == 'Y' || n == 'y') {
				system("cls");
				cout << "Thanks For Using Online Banking." << endl;
				break;
			}
			else if (n == 'N' || n == 'n') {

			}
			else {
				cout << "\a";
			}
		}
		else {
			cout << "\a";
		}
	} while (menuOption != "5");
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

void writeFile_openAC(string file_name) {

	Account ac;

	// set up the hash function
	hash<string> str_hash;
	// open the file
	int acc_no, tel;
	string name, pw;
	double balance;
	size_t hash_val;
	ofstream outFile;

	// file is written and put in same folder as source code
	outFile.open(file_name, ios::app);

	// data fields to write into file
	tel = phNum_input();
	name = acName_input();
	pw = acPw_input();
	acc_no = genAccNum(tel);
	hash_val = str_hash(pw);
	balance = balance_input();

	// ensure floating point is written in 2 d.p.
	outFile.setf(ios::fixed, ios::floatfield);
	outFile.precision(2);

	// write contents into file (will overwrite orignal file)
	outFile << acc_no << "\t" << name << "\t" << tel << "\t" << hash_val << "\t" << balance << "\n";

	// close the file
	outFile.close();

	ac.setName(name);
	ac.setAcNum(acc_no);
	ac.setTel(tel);
	ac.setBalance(balance);

	system("cls");

	cout << "---A New Bank Account Created---" << endl;
	cout << endl;
	cout << "The Following Is Your Account Information" << endl;
	cout << endl;
	cout << setw(30) << left << "Account Holder Name:" << name << endl;
	cout << setw(30) << left << "Account Number:" << acc_no << endl;
	cout << setw(30) << left << "Mobile Phone Number:" << tel << endl;
	cout << setw(30) << left << "Account Balance:" << fixed << balance << " HKD" << endl;
	cout << endl;
	cout << "*****PLEASE WRITE DOWN YOUR ACCOUNT NUMBER BY YOURSELF*****" << endl;
	cout << endl;
	system("pause");
	ac.bankMenu();
}

/*void bankMenu(string accountName, int accountNumber) {
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
}*/


string acName_input() {
	string accountName, accountName_confirm;
	//do-while loop  for checking the name requirment
	do {
		cin.clear();
		cin.ignore(256, '\n');
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
	cout << "Press The ENTER BUTTON To Continue." << endl;
	return accountName;
}
/*------------------------account holder phone number--------------------------------------*/
int phNum_input() {
	int phoneNumber = 0, phoneNumber_confirm = phoneNumber;
	do {
		cin.clear();
		cin.ignore(256, '\n');
		do {

			if (phoneNumber_confirm != phoneNumber) {
				cout << endl;
				cout << "Not Match, Please Enter Again." << endl;
				cout << endl;
			}

			cout << "Enter Your Phone Number: ";
			while (!(cin >> phoneNumber) || phoneNumber <= 0) {
				cout << endl;
				cout << "Not Match The Phone Number Requirement." << endl;
				cout << "Please Enter Again." << endl;
				cout << endl;
				cout << "Enter Your Phone Number: ";
				cin.clear(); //Reset the input error status to no error
				cin.ignore(256, '\n'); //Discard the content in the input sequence
			}

			cout << "Confirm Your Phone Number: ";
			while (!(cin >> phoneNumber_confirm) || phoneNumber <= 0) {
				cout << endl;
				cout << "Not Match The Phone Number Requirement." << endl;
				cout << "Please Enter Again." << endl;
				cout << endl;
				cout << "Confirm Your Phone Number: ";
				cin.clear(); //Reset the input error status to no error
				cin.ignore(256, '\n');//Discard the content in the input sequence
			}
		}
		//while loop if phone number and the confirm is not the same
		while (phoneNumber_confirm != phoneNumber);

	}
	//do-while loop for checking the digit of the phone number
	while (!checkPhone(phoneNumber));

	cout << endl;

	return phoneNumber;
}

/*-------------------------account password------------------------------------------------*/
string acPw_input() {

	string accountPassword, accountPassword_confirm;
	//do-while loop for checking the password requirement
	do {
		cin.clear();
		cin.ignore(256, '\n');
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
	
	cout << endl;

	return accountPassword;
}

double balance_input() {
	double bal;

	do {
		cout << "Initial Amount to Deposit (At Least $100) : $";
		cin >> bal;
		if (bal < 100) {
			cout << endl;
			cout << "The Initial Amount Must Be At Least $100" << endl;
			cout << "Please Enter Again" << endl;
			cout << endl;
		}
	} 
	while (bal < 100);
	return bal;
}

//the function of checking the phone number requirement
bool checkPhone(int num) {
	int counter = 0;

	while (num > 0) {
		num /= 10;
		counter++;
	}

	if (counter == 8) {
		return 1;
	}
	else {
		cout << endl;
		cout << "Not Match The Phone Number Requirement." << endl;
		cout << "Please Enter Again." << endl;
		cout << endl;
		return 0;
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
		if (int(cstr[i]) == 32 || (int(cstr[i]) >= 65 && int(cstr[i]) <= 90) || (int(cstr[i]) >= 97 && int(cstr[i]) <= 122) || s.length() <= 20) {
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

void inputReq() {
	cout << "***************Information Requirement***************" << endl;
	cout << setw(30) << left << "Mobile Phone Number:" << "Mobile Phone Number Shoould Be An 8-Digit Input." << endl;
	cout << endl;
	cout << setw(30) << left << "Account Holder Name:" << "The Account Holder Name Does Not Containe Any Digits" << endl;
	cout << setw(30) << " " << " Or Other Symbols Except The Alphabets And The Space Charactor. It Should Be At" << endl;
	cout << setw(30) << " " << " Most 20-Charater Long." << endl;
	cout << endl;
	cout << setw(30) << left << "Account Password: " << "Account Password Should Be Of At Least 8-Charater Long, Which" << endl;
	cout << setw(30) << " " << " Includes At Least One Capital Letter, One Small Letter And One Digit." << endl;
	cout << endl;
	cout << setw(30) << left << "Initial Amount:" << "The Initial Amount To Deposit Should Be At Least $100." << endl;
	cout << "*****************************************************" << endl;
}

double deposit() {
	double amount;
	cout << "***************DEPOSIT***************" << endl;
	cout << setw(30) << left << "Deposit Amount:";
	cin >> amount;

	return amount;
}

double withdraw() {
	double amount;
	cout << "***************WITHDRAW***************" << endl;
	cout << setw(30) << left << "Withdraw Amount:";
	cin >> amount;

	return amount;
}

bool ynexit() {
	char n;
	do {
		cout << "Are You Sure To Logout?" << endl;
		cout << "Press \"Y/y\" For YES, \"N/n\" For NO: ";
		cin >> n;
		if (n == 'Y' || n == 'y') {
			return 1;
		}
		else if (n == 'N' || n == 'n') {
			return 0;
		}
		else {
			cout << "\a";
		}
	} while (n != 'Y' || n != 'y' || n != 'N' || n != 'n');
}