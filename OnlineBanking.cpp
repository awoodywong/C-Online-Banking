#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <functional>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <sstream>
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
double withdraw(double);
bool ynexit();
void login(string);
bool searchPhone(string, int);

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
				cout << "------------------------------------------------------------------------------" << endl;
				cout << setw(30) << left << "Account Number:" << acNum << endl;
				cout << "------------------------------------------------------------------------------" << endl;
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
				withdraw_amount = withdraw(balance);
				balance -= withdraw_amount;
				cout << endl;
				cout << "-----SUCCESS-----" << endl;
				system("pause");
			}
			else if (bankMenuOption == "4") {

			}
			else if (bankMenuOption == "5") {

			}
			else if (bankMenuOption == "6") {

			}
			else if (bankMenuOption == "7") {

				cout << "Are You Sure To Logout?" << endl;
				bool x = ynexit();

				if (x) {
					cout << "Thanks For Using Online Banking System." << endl;
					break;
				}

				else {
					bankMenuOption = "8";
					cout << "\a";
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
			system("cls");
			login(file_name);
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
			cout << "Are You Sure To Exit?" << endl;
			bool x = ynexit();

			if (x) {
				cout << "Thanks For Using Online Banking System." << endl;
				break;
			}

			else {
				menuOption = "6";
				cout << "\a";
			}
		}
		else {
			cout << "\a";
		}
	} while (menuOption != "5");
}

void readFile(string file_name) {
	char num[100];
	char tel[100];
	char name[100];
	char pw[100];
	char balance[100];
	int size;
	streampos begin, end;
	// open the file
	ifstream inFile;

	// file should be put in same folder as the source code file
	inFile.open(file_name);
	begin = inFile.tellg();
	inFile.seekg(0, ios::end);
	end = inFile.tellg();
	size = end - begin;

	inFile.seekg(0, ios::beg);

	cout << setw(30) << left << "Account Number" << setw(30) << left << "Account Holder Name" << setw(25) << left << "Mobile Phone Number" << setw(20) << left << "Hashed Password" << setw(20) << left << "Balance" << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
	// repeat until end of file is reached
	while (inFile.tellg() != size) {
		// get each line from file and print
		inFile.seekg(inFile.tellg());
		inFile.getline(num, 100, '\t');

		inFile.seekg(inFile.tellg());
		inFile.getline(name, 100, '\t');

		inFile.seekg(inFile.tellg());
		inFile.getline(tel, 100, '\t');

		inFile.seekg(inFile.tellg());
		inFile.getline(pw, 100, '\t');
		inFile.seekg(inFile.tellg());

		inFile.getline(balance, 100, '\n');
		inFile.seekg(inFile.tellg());

		cout << setw(30) << left << num << setw(30) << left << name << setw(25) << left << tel << setw(20) << left << pw << setw(20)<< left << balance << endl;
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
	if (!searchPhone(file_name, tel)) {
		cout << "***This Mobile Phone Number Has Already Been Registered***" << endl;
		system("pause");
		return;
	}
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
				cout << "-Not Match, Please Enter Again-" << endl;
				cout << endl;
			}
			cout << setw(40) << left << "Enter The Account Holder Name: ";
			getline(cin, accountName);

			cout << setw(40) << left << "Confirm The Account Holder Name: ";
			getline(cin, accountName_confirm);
		} while (accountName_confirm != accountName);

		//call the function checkName for check the name requirment
	} while (!checkName(accountName));

	cout << endl;
	cout << "<<Press The ENTER BUTTON To Continue>>" << endl;
	return accountName;
}
//account holder phone number
int phNum_input() {
	int phoneNumber = 0, phoneNumber_confirm = phoneNumber;
	do {
		cin.clear();
		cin.ignore(256, '\n');
		do {

			if (phoneNumber_confirm != phoneNumber) {
				cout << endl;
				cout << "-Not Match, Please Enter Again-" << endl;
				cout << endl;
			}

			cout << setw(30) << left << "Enter Your Phone Number: ";
			while (!(cin >> phoneNumber) || phoneNumber <= 0) {
				cout << endl;
				cout << "-Not Match The Phone Number Requirement-" << endl;
				cout << "-Please Enter Again-" << endl;
				cout << endl;
				cout << setw(30) << left << "Enter Your Phone Number: ";
				cin.clear(); //Reset the input error status to no error
				cin.ignore(256, '\n'); //Discard the content in the input sequence
			}

			cout << setw(30) << left << "Confirm Your Phone Number: ";
			while (!(cin >> phoneNumber_confirm) || phoneNumber <= 0) {
				cout << endl;
				cout << "-Not Match The Phone Number Requirement-" << endl;
				cout << "-Please Enter Again-" << endl;
				cout << endl;
				cout << setw(30) << left << "Confirm Your Phone Number: ";
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

//account password
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
				cout << "-Not Match, Please Enter Again-" << endl;
				cout << endl;
			}
			cout << setw(30) << left << "Enter Your Account Password: ";
			getline(cin, accountPassword);

			cout << setw(30) << left << "Confirm Your Account Password: ";
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
			cout << "-The Initial Amount Must Be At Least $100-" << endl;
			cout << "-Please Enter Again-" << endl;
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
		cout << "-Not Match The Phone Number Requirement-" << endl;
		cout << "-Please Enter Again-" << endl;
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
		if ((int(cstr[i]) == 32 || (int(cstr[i]) >= 65 && int(cstr[i]) <= 90) || (int(cstr[i]) >= 97 && int(cstr[i]) <= 122) )&&( (s.length() <= 20))) {
		}
		else {
			counter++;
		}
	}

	if (counter > 0) {
		cout << endl;
		cout << "-Not Match The Name Requirement-" << endl;
		cout << "-Please Enter Again-" << endl;
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
		cout << "-Not Match The Password Requirement-" << endl;
		cout << "-Please Enter Again-" << endl;
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
	while (!(cin >> amount) || (amount < 0)) {
		cout << endl;
		cout << "-The Input Is Not A Number / Negative Amount-" << endl;
		system("pause");
		system("cls");
		cout << "***************DEPOSIT***************" << endl;
		cout << setw(30) << left << "Deposit Amount:";
		cin.clear(); //Reset the input error status to no error
		cin.ignore(256, '\n'); //Discard the content in the input sequence
	}

	return amount;
}

double withdraw(double balance) {
	double amount;
	cout << "***************WITHDRAW***************" << endl;
	cout << setw(30) << left << "Withdraw Amount:";
	while (!(cin >> amount) || (amount < 0) || (amount > balance)) {
		cout << endl;
		cout << "-The Input Is Not A Number / Negative Amount / Over Your Balance-" << endl;
		system("pause");
		system("cls"); 
		cout << "***************WITHDRAW***************" << endl;
		cout << setw(30) << left << "Withdraw Amount:";
		cin.clear(); //Reset the input error status to no error
		cin.ignore(256, '\n'); //Discard the content in the input sequence
	}

	return amount;
}

bool ynexit() {
	char n;
	do {
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

void login(string file_name) {

	Account ac;
	hash<string> str_hash;

	string num;
	string tel;
	string name;
	string pw;
	string balance;
	int size;
	int acnum;
	int phNum;
	double bal;
	size_t hpw;
	size_t hash_pw;
	streampos begin, end;
	bool check = false;

	int ac_num;
	string ac_pw;

	cout << "*****Please Enter Ther Following Information*****" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << setw(30) << left << "Account Number: ";
	while (!(cin >> ac_num)) {
		cout << endl;
		cout << "-Not Match The Account Number Requirement-" << endl;
		cout << "-Please Enter Again-" << endl;
		system("pause");
		system("cls");
		cout << "*****Please Enter Ther Following Information*****" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << setw(30) << left << "Account Number: ";
		cin.clear(); //Reset the input error status to no error
		cin.ignore(256, '\n'); //Discard the content in the input sequence
	}
	cout << setw(30) << left << "Account Password: ";
	cin >> ac_pw;

	hash_pw = str_hash(ac_pw);

	// open the file
	ifstream inFile;

	// file should be put in same folder as the source code file
	inFile.open(file_name);
	begin = inFile.tellg();
	inFile.seekg(0, ios::end);
	end = inFile.tellg();
	size = end - begin;

	inFile.seekg(0, ios::beg);

	// repeat until end of file is reached
	while (inFile.tellg() != size) {
		// get each line from file and print
		inFile.seekg(inFile.tellg());
		getline(inFile, num, '\t');

		inFile.seekg(inFile.tellg());
		getline(inFile, name, '\t');

		inFile.seekg(inFile.tellg());
		getline(inFile, tel, '\t');

		inFile.seekg(inFile.tellg());
		getline(inFile, pw, '\t');

		inFile.seekg(inFile.tellg());
		getline(inFile, balance, '\n');

		inFile.seekg(inFile.tellg());

		stringstream s1(num);
		s1 >> acnum;

		stringstream s2(tel);
		s2 >> phNum;

		stringstream s3(pw);
		s3 >> hpw;

		stringstream s4(balance);
		s4 >> bal;
		
		if ((ac_num == acnum) && (hpw == hash_pw)) {
			ac.setAcNum(acnum);
			ac.setName(name);
			ac.setTel(phNum);
			ac.setBalance(bal);
			check = true;
		}
		
	}


	// close the file
	inFile.close();

	if (check) {
		ac.bankMenu();
	}
	else {
		cout << "-----No This Account / Your Account Number Or Password Was Wrong-----" << endl;
		system("pause");
	}

}

bool searchPhone(string file_name, int tel_num) {
	string num;
	string tel;
	string name;
	string pw;
	string balance;
	int size;
	int acnum;
	int phNum;
	double bal;
	size_t hpw;
	streampos begin, end;
	// open the file
	ifstream inFile;

	// file should be put in same folder as the source code file
	inFile.open(file_name);
	begin = inFile.tellg();
	inFile.seekg(0, ios::end);
	end = inFile.tellg();
	size = end - begin;

	inFile.seekg(0, ios::beg);
	// repeat until end of file is reached
	while (inFile.tellg() != size) {
		// get each line from file and print
		inFile.seekg(inFile.tellg());
		getline(inFile, num, '\t');

		inFile.seekg(inFile.tellg());
		getline(inFile, name, '\t');

		inFile.seekg(inFile.tellg());
		getline(inFile, tel, '\t');

		inFile.seekg(inFile.tellg());
		getline(inFile, pw, '\t');
		inFile.seekg(inFile.tellg());

		getline(inFile, balance, '\n');
		inFile.seekg(inFile.tellg());

		stringstream s1(num);
		s1 >> acnum;

		stringstream s2(tel);
		s2 >> phNum;

		stringstream s3(pw);
		s3 >> hpw;

		stringstream s4(balance);
		s4 >> bal;

		if (tel_num == phNum) {
			return 0;
		}
	}

	// close the file
	inFile.close();

	return 1;
}