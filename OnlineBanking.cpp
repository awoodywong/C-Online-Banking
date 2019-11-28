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
#include <ctime>

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
void login(string, int, string);
bool searchPhone(string, int);
bool searchNum(string, int);
void updateFile(string, string, int, int, size_t, double);
double retTrans_num(string, int, int);
double retTrans_tel(string, int, int);
void fixedDeposit(double, double, int);
int update_tel();
string update_pw();

/*--------------------------------------class--------------------------------------*/

class Time {
private:
	int startTime;

public:
	void start() {
		startTime = time(0);
	}

	int stop() {
		int elapsed = time(0) - startTime;
		return elapsed;
	}
};


//the class of account
class Account {
private:
	//the variables of the account
	string name, password;
	int acNum;
	int tel;
	double balance;
	size_t hash_val;

	//the variables of the transfer account
	int trans_num;
	int trans_tel;
	string trans_name;
	size_t trans_hash;
	double trans_balance;

public:

	//line 62-140 is the get and set function of the Account class variables

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

	size_t getHashPW() {
		return hash_val;
	}

	void setHashPW(size_t hpw) {
		hash_val = hpw;
	}

	double getBalance() {
		return balance;
	}

	void setBalance(double bal) {
		balance = bal;
	}

	string getTransName() {
		return trans_name;
	}

	void setTransName(string acName) {
		trans_name = acName;
	}

	int getTransNum() {
		return trans_num;
	}

	void setTransNum(int acNum) {
		trans_num = acNum;
	}

	int getTransTel() {
		return trans_tel;
	}

	void setTransTel(int tel) {
		trans_tel = tel;
	}

	size_t getTransHash() {
		return trans_hash;
	}

	void setTransHash(size_t pw) {
		trans_hash = pw;
	}

	double getTransBalance() {
		return trans_balance;
	}

	void setTransBalance(double bal) {
		trans_balance = bal;
	}

	double transfer(string file_name);

	void bankMenu(string file_name);
};
//the transfer function
double Account::transfer(string file_name) {
	Time t;
	t.start();
	system("cls");

	double amount = 0; //the variable of the transfer amount

	//the transfer function surface
	cout << "***************TRANSFER***************" << endl;
	cout << setw(30) << left << "Your Account Holder Name: " << name << endl;
	cout << setw(30) << left << "Your Account Number: " << acNum << endl;
	cout << endl;
	cout << setw(30) << left << "Account Holder Name: " << trans_name << endl;
	cout << setw(30) << left << "Account Number: " << trans_num << endl;
	cout << setw(30) << left << "Enter Transfer Amount: ";

	//while loop for check input data
	while (!(cin >> amount) || (amount < 0)) {
		cout << endl;
		cout << "-The Input Is Not A Number / Negative Amount-" << endl;
		system("pause");
		system("cls");
		cout << "***************TRANSFER***************" << endl;
		cout << setw(30) << left << "Your Account Holder Name: " << name << endl;
		cout << setw(30) << left << "Your Account Number: " << acNum << endl;
		cout << endl;
		cout << setw(30) << left << "Account Holder Name: " << trans_name << endl;
		cout << setw(30) << left << "Account Number: " << trans_num << endl;
		cout << setw(30) << left << "Enter Transfer Amount: ";
		cin.clear(); //Reset the input error status to no error
		cin.ignore(256, '\n'); //Discard the content in the input sequence
	}
	if (t.stop() > 15) {
		cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
		system("pause");
		return 0;
	}
	else {
		t.start();
		if ((amount > balance)) {
			cout << "-The Amount Is Over Your Balance-" << endl;
			system("pause");
			return 0;
		}
	}

	balance = (balance - amount); //calculate the balance
	setBalance(balance); //set the balance

	trans_balance = (trans_balance + amount); //calculate the recipient account balance

	updateFile(file_name, trans_name, trans_num, trans_tel, trans_hash, trans_balance); //update the recipient account record in .dat

	cout << "-SUCCESS-" << endl; //meaningful message display
	system("pause");

	return amount; //return amount data to retTrans_num or retTrans_tel
}

void Account::bankMenu(string file_name) {
	//the variable of option
	string bankMenuOption;

	Time t;

	//do-while loop of the menu
	do {
		t.start();
		//menu surface
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

		//use if statement to use different function in bank menu

		//check balance function
		if (bankMenuOption == "1") {
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
				updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
				return;
			}
			else {
				t.start();
			}
			system("cls");
			t.start();
			//dasplay the class variables
			cout << setw(30) << left << "Account Holder Name:" << name << endl;
			cout << "------------------------------------------------------------------------------" << endl;
			cout << setw(30) << left << "Account Number:" << acNum << endl;
			cout << "------------------------------------------------------------------------------" << endl;
			cout << setw(30) << left << "Account Balance:" << setprecision(2) << fixed << balance << " HKD" << endl;
			system("pause");
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
				updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
				return;
			}
			else {
				t.start();
			}
		}

		//deposit function
		else if (bankMenuOption == "2") {
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
				updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
				return;
			}
			else {
				t.start();
			}
			t.start();
			double deposit_amount;
			system("cls");
			deposit_amount = deposit(); //call the daposit function
			balance += deposit_amount; //modify the value of class variable
			if (t.stop() > 15) {
				updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
				return;
			}
			else {
				t.start();
			}
			setBalance(balance);
			cout << endl;
			cout << "-----SUCCESS-----" << endl; //meaningful message display
			system("pause");
		}

		//withdraw function
		else if (bankMenuOption == "3") {
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
				updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
				return;
			}
			else {
				t.start();
			}
			t.start();
			double withdraw_amount;
			system("cls");
			withdraw_amount = withdraw(balance); //call the withdarw
			balance -= withdraw_amount; //modify the value of class variable
			setBalance(balance);
			if (t.stop() > 15) {
				updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
				return;
			}
			else {
				t.start();
			}
			cout << endl;
			cout << "-----SUCCESS-----" << endl; //meaningful message display
			system("pause");
		}

		//transfer function
		else if (bankMenuOption == "4") {
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
				updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
				return;
			}
			else {
				t.start();
			}
			t.start();
			system("cls");

			double amount;
			char choice;
			int num;
			int phNum;

			//transfer surface
			cout << "***************TRANSFER***************" << endl;
			cout << "Chose Either One Recipient Information" << endl;
			cout << "(1) Account Number" << endl;
			cout << "(2) Mobile Phone Number" << endl;
			cout << "--------------------------------------" << endl;
			cout << "(3) Exit" << endl;
			cout << endl;

			//do-while loop for input choices
			do {
				cout << "Choice: ";
				cin >> choice; //input the choice

				//using account number to transfer
				if (choice == '1') {
					if (t.stop() > 15) {
						cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                        system("pause");
						updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
						return;
					}
					else {
						t.start();
						system("cls");
						cout << "***************TRANSFER***************" << endl;
						cout << "Recipient Account Number: ";
						cin >> num; //input the recipient account number
						if (t.stop() > 15) {
							cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                            system("pause");
							updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
							return;
						}
						else {
							t.start();
							if (num == acNum) {
								cout << "***Can Not Transfer To Yourself***" << endl;
								system("pause");
								break;
							}
							amount = retTrans_num(file_name, num, acNum); //call the search account function (account number), this function also call the transtion main funcion
							if (t.stop() > 15) {
								system("pause");
								updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
								return;
							}
							else {
								t.start();
								balance -= amount; //modify the value of calss variable

								break; //return to bank menu
							}
						}
					}
				}


				//using mobile phone to transfer
				else if (choice == '2') {
					if (t.stop() > 15) {
						cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                        system("pause");
						updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
						return;
					}
					else {
						t.start();
						system("cls");
						cout << "***************TRANSFER***************" << endl;
						cout << "Mobile Phone Number: ";
						cin >> phNum; //input the recipient mobile phone number
						if (t.stop() > 15) {
							cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                            system("pause");
							updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
							return;
						}
						else {
							t.start();
							if (phNum == tel) {
								cout << "***Can Not Transfer To Yourself***" << endl;
								system("pause");
								break;
							}
							amount = retTrans_tel(file_name, phNum, acNum); //call the search account function (mobile phone number), this function also call the transtion main funcion
							if (t.stop() > 15) {
								system("pause");
								updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
								return;
							}
							else {
								t.start();
								balance -= amount; //modify the value of class variable

								break; //return to bank menu
							}
						}
					}
				}


				//exit the transfer function
				else if (choice == '3') {
					if (t.stop() > 15) {
						cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                        system("pause");
						updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
						return;
					}
					else {
						t.start();
						break;
					}

				}

				//input other choice
				else {
					if (t.stop() > 15) {
						cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                        system("pause");
						updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
						return;
					}
					else {
						t.start();
						cout << "\a";
					}
				}
			} while (choice != 3);
		}

		//fixed deposit enquiry function
		else if (bankMenuOption == "5") {
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
				updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
				return;
			}
			else {
				t.start();
			}
			t.start();
			double p, r; //p for principal, r for the interest rate per year
			int z; //z for the period
			system("cls");
			cout << "***************FIXED DEPOSIT ENQUIRY***************" << endl;
			cout << setw(50) << left << "Enter The Principal: ";

			//input checking for the principal
			while (!(cin >> p) || (p < 0) || (p > balance)) {
				cout << endl;
				cout << "-The Input Is Not A Number / Negative Amount / Over Your Balance-" << endl;
				system("pause");
				system("cls");
				cout << "***************FIXED DEPOSIT ENQUIRY***************" << endl;
				cout << setw(50) << left << "Enter The Principal: ";
				cin.clear(); //Reset the input error status to no error
				cin.ignore(256, '\n'); //Discard the content in the input sequence
			}
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
				updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
				return;
			}
			else {
				t.start();
			}
			//input checking for the rate
			cout << setw(50) << left << "Enter The Interest Rate Per Year (In \%): ";
			while (!(cin >> r) || (r < 0)) {
				cout << endl;
				cout << "-The Input Is Not A Number / Negative Amount" << endl;
				system("pause");
				cout << endl;
				cout << setw(50) << left << "Enter The Interest Rate Per Year (In \%): ";
				cin.clear(); //Reset the input error status to no error
				cin.ignore(256, '\n'); //Discard the content in the input sequence
			}
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
				updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
				return;
			}
			else {
				t.start();
			}
			//input checking for the period
			cout << setw(50) << left << "Enter The Period (In Months): ";
			while (!(cin >> z) || (z < 0)) {
				cout << endl;
				cout << "-The Input Is Not A Number / Negative Amount" << endl;
				system("pause");
				cout << endl;
				cout << setw(50) << left << "Enter The Period (In Months): ";
				cin.clear(); //Reset the input error status to no error
				cin.ignore(256, '\n'); //Discard the content in the input sequence
			}
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
				updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
				return;
			}
			else {
				t.start();
				fixedDeposit(p, r, z); //call the fixed deposit function
				if (t.stop() > 15) {
					cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                    system("pause");
					updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
					return;
				}
				else {
					t.start();
				}
			}
		}

		//update account information function
		else if (bankMenuOption == "6") {
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
				updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
				return;
			}
			else {
				t.start();
			}
			t.start();
			system("cls");
			hash<string> str_hash; //hash value function
			char n;
			int new_tel;
			string in_pw;
			string new_pw;
			size_t in_pw_h;
			size_t new_hash;

			//update account information function surface
			cout << "***************UPDATE ACCOUNT INFORMATION***************" << endl;
			cout << "Updat Which Information?" << endl;
			cout << "(1) Mobile Phone Number" << endl;
			cout << "(2) Password" << endl;
			cout << "(3) Exit" << endl;
			cout << "Chose The Option: ";

			//do-while for input choices
			do {
				cin >> n; //input the user choice
				if (t.stop() > 15) {
					cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                    system("pause");
					updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
					return;
				}
				else {
					t.start();
					//update mobile phone number
					if (n == '1') {
						system("cls");
						cout << "***************UPDATE MOBILE PHONE NUMBER***************" << endl;
						new_tel = update_tel(); //input and checking new tel, and return the new tel into new_tel variable
						if (t.stop() > 30) {
							updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
							return;
						}
						else {
							t.start();
						}
						cout << "Enter Your Account Password: ";
						cin >> in_pw; //confirm the account password
						if (t.stop() > 15) {
							cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                            system("pause");
							updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
							return;
						}
						else {
							t.start();
						}
						in_pw_h = str_hash(in_pw); //hash the confirm password for compare

						//compare the account password (class variable) and the comfirm password in hash value
						if (in_pw_h == hash_val) {
							tel = new_tel;
							updateFile(file_name, name, acNum, new_tel, hash_val, balance); //update the account record in .dat
							cout << "-UPDATE SUCCESS-" << endl; //meaningful message display
							system("pause");
							break; //return to bank menu

						}

						//if the comfirm was wrong
						else {
							cout << "-PASSWORD WRONG-" << endl; //meaningful message display
							system("pause");
							break; //return to bank menu

						}

					}

					//updatt account password
					else if (n == '2') {
						system("cls");
						cout << "***************UPDATE PASSWORDN***************" << endl;
						cout << "Enter Current Password: ";
						cin >> in_pw; //input the account current password
						if (t.stop() > 15) {
							cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                            system("pause");
							updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
							return;
						}
						else {
							t.start();
						}
						in_pw_h = str_hash(in_pw); //hash the input of current password for compare

						//compare the input password and the account password (class variable)
						if (in_pw_h == hash_val) {
							new_pw = update_pw(); //input and checking new password, and return the new password into new_pw variable
							if (t.stop() > 30) {
								updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
								return;
							}
							else {
								t.start();
							}
							new_hash = str_hash(new_pw); //hash the new password
							hash_val = new_hash; //modify the class variable (old hashed password to new hashed password)
							updateFile(file_name, name, acNum, tel, new_hash, balance); //update the account record in .dat
							cout << "-UPDATE SUCCESS-" << endl; //meaningful message display
							system("pause");
							break; //return to bank menu
						}

						//if the password was wrong
						else {
							cout << "-PASSWORD WRONG-" << endl; //meaningful message display
							system("pause");
							break; //return to bank menu
						}
					}
					//exit to bank menu
					else if (n == '3') {
						break;
					}

					//input other choice
					else {
						if (t.stop() > 15) {
							cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                            system("pause");
							updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
							return;
						}
						else {
							t.start();
							cout << "\a";
						}

					}
				}
			} while (n != '3');
		}

		//logout function
		else if (bankMenuOption == "7") {
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
				updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
				return;
			}
			else {
				t.start();
			}
			cout << "Are You Sure To Logout?" << endl;
			bool x = ynexit(); //call the yes no exit function

			if (x) {
				updateFile(file_name, name, acNum, tel, hash_val, balance); //updat the account record when exit
				cout << "Thanks For Using Online Banking System." << endl;
				break; //return to main menu
			}

			//if exit input the"NO"
			else {
				bankMenuOption = "8";
				cout << "\a";
			}

		}

		//bank menu option input other choice (i.e. out of 1-7)
		else {
			cout << "\a";
		}
	} while (bankMenuOption != "7");
}

/*--------------------------------------main--------------------------------------*/

int main() {
	string file_name; //the file name variable
	cout << "Welcome Message designed by Wong Kong Lun" << endl; //welcome message
	cout << "Please input the file name of the data file: "; //prompt user input the file name i.e. account.dat
	cin >> file_name;

	menu(file_name); //call the main menu function

	return 0;
}

/*--------------------------------------function--------------------------------------*/

//credits of this project
void credits() {
	system("cls");
	cout << left << setw(20) << "Name" << setw(15) << "ID" << setw(10) << "Class" << setw(20) << "Tutorial Group" << endl;
	cout << "-----------------------------------------------------------" << endl;
	cout << left << setw(20) << "Wong Kong Lun" << setw(15) << "18039547A" << setw(10) << "101" << setw(20) << "101C" << endl;
	cout << left << setw(20) << "Lam Chun  Choi" << setw(15) << "18078757A" << setw(10) << "101" << setw(20) << "101C" << endl;
	cout << left << setw(20) << "Cheng Man Kit" << setw(15) << "18053542A" << setw(10) << "101" << setw(20) << "101C" << endl;
	cout << left << setw(20) << "Lam Wingpan" << setw(15) << "18046526A" << setw(10) << "101" << setw(20) << "101B" << endl;
	cout << left << setw(20) << "Hui Wing Yau" << setw(15) << "18011599A" << setw(10) << "101" << setw(20) << "101D" << endl;
	cout << left << setw(20) << "Tsui Ka Lok" << setw(15) << "18054090A" << setw(10) << "101" << setw(20) << "101C" << endl;
}

//menu
void menu(string file_name) {
	Time t;

	string menuOption;

	//do-while loop for the main menu
	do {
		system("cls");
		cout << "*** Main Menu ***" << endl;
		cout << "[1] Open Account" << endl;
		cout << "[2] Login" << endl;
		cout << "[3] List All Account" << endl;
		cout << "[4] Credits" << endl;
		cout << "[5] Exit" << endl;
		cout << "*****************" << endl;
		cout << "Option (1 - 5): ";
		cin >> menuOption;

		//open account function
		if (menuOption == "1") {
			system("cls");
			inputReq(); //the introduction of the data requirement
			writeFile_openAC(file_name); //call the open account function
		}

		//login function
		else if (menuOption == "2") {
			t.start();
			system("cls");
			int ac_num;
			string ac_pw;

			//login function surface & input checking
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
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
			}
			else {
				t.start();
				cout << setw(30) << left << "Account Password: ";
				cin >> ac_pw; //account password input
				if (t.stop() > 15) {
					cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                    system("pause");
				}
				else {
					t.start();
					login(file_name, ac_num, ac_pw); //call the login function
				}
			}


		}

		//list all account function
		else if (menuOption == "3") {
			system("cls");
			readFile(file_name); //call the list account function
			system("pause");
		}

		//list the credits function
		else if (menuOption == "4") {
			system("cls");
			credits(); //call the list credits function
			system("pause");
		}

		//exit function
		else if (menuOption == "5") {
			cout << "Are You Sure To Exit?" << endl;
			bool x = ynexit(); //call the yes no exit function

			if (x) {
				cout << "Thanks For Using Online Banking System." << endl;
				break; //return to the [int main()]
			}

			//if yes no exit function chose "NO"
			else {
				menuOption = "6";
				cout << "\a";
			}
		}

		//out of main menu option
		else {
			cout << "\a";
		}
	} while (menuOption != "5");
}

//list all account function
void readFile(string file_name) {
	char record[100];
	char line[2000][100];
	char temp_line[100];
	int counter = 0;
	int smallestIndex, temp;

	// open the file
	ifstream inFile;

	// file should be put in same folder as the source code file
	inFile.open(file_name);

	// repeat until end of file is reached
	while (!inFile.eof()) {

		inFile.getline(record, 100, '\n'); //get the record from .dat file
		strcpy(line[counter], record); //copy the record from [record] to [line] array(2D)
		counter++; //count how many record
	}

	// close the file
	inFile.close();

	//selection sorting process (ascending order)
	for (int j = 0; j < counter; j++) {
		smallestIndex = j;
		for (int pos = j + 1; pos < counter; pos++)
			if (strncmp(line[smallestIndex], line[pos], 8) > 0) //compare the account number by strncmp() function
				smallestIndex = pos;

		strcpy(temp_line, line[smallestIndex]);
		strcpy(line[smallestIndex], line[j]);
		strcpy(line[j], temp_line);
	}

	//display the record in ascending order of account number
	cout << setw(16) << left << "AC NUMBER" << setw(16) << left << "HOLDER NAME" << setw(16) << left << "TEL" << setw(16) << left << "HASHED PW" << setw(10) << left << "BALANCE" << endl;
	cout << "------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < counter; i++) {
		cout << line[i] << endl;
	}

}

//open account function
void writeFile_openAC(string file_name) {
	Time t;
	Account ac; //class variable
	t.start();
	// set up the hash function
	hash<string> str_hash;
	// open the file
	int acc_no, tel;
	string name, pw;
	double balance;
	size_t hash_val;
	ofstream outFile;

	//open file and use ios::app to add the new account record at the end of file
	outFile.open(file_name, ios::app);

	tel = phNum_input(); //call the input phone number to input and check the phone number
	if (t.stop() > 30) {
		return;
	}
	else {
		t.start();
	}
	//search the phone in the file, a new account can be created only if the input mobile phone number is not present in the data file
	if (!searchPhone(file_name, tel)) {
		cout << "***This Mobile Phone Number Has Already Been Registered***" << endl;
		system("pause");
		return;
	}
	name = acName_input(); //call the function for input account holder name and check it
	if (t.stop() > 30) {
		return;
	}
	else {
		t.start();
	}
	pw = acPw_input(); //call the function for input account password and check it
	if (t.stop() > 30) {
		return;
	}
	else {
		t.start();
	}
	acc_no = genAccNum(tel); //generate the account number by random number, the seed value is the phone number so that it will not be repeat
	if (t.stop() > 30) {
		return;
	}
	else {
		t.start();
	}
	hash_val = str_hash(pw); //hash the password
	if (t.stop() > 30) {
		return;
	}
	else {
		t.start();
	}
	balance = balance_input(); //call the function for input balance and check it
	if (t.stop() > 15) {
		return;
	}
	else {
		t.start();
	}

	//prevent have the same account number, because account number is generate by tel
	while (searchNum(file_name, acc_no)) {
		acc_no++;
	}

	// ensure floating point is written in 2 d.p.
	outFile.setf(ios::fixed, ios::floatfield);
	outFile.precision(2);

	// write contents into file (will overwrite orignal file)
	outFile << acc_no << "\t" << name << "\t" << tel << "\t" << hash_val << "\t" << setprecision(2) << fixed << balance << "\n";

	// close the file
	outFile.close();

	//set the class variables
	ac.setName(name);
	ac.setAcNum(acc_no);
	ac.setTel(tel);
	ac.setBalance(balance);

	system("cls");

	//display new account informations
	cout << "---A New Bank Account Created---" << endl;
	cout << endl;
	cout << "The Following Is Your Account Information" << endl;
	cout << endl;
	cout << setw(30) << left << "Account Holder Name:" << name << endl;
	cout << setw(30) << left << "Account Number:" << acc_no << endl;
	cout << setw(30) << left << "Mobile Phone Number:" << tel << endl;
	cout << setw(30) << left << "Account Balance:" << setprecision(2) << fixed << balance << " HKD" << endl;
	cout << endl;
	cout << "*****PLEASE WRITE DOWN YOUR ACCOUNT NUMBER BY YOURSELF*****" << endl;
	cout << endl;
	system("pause");
	login(file_name, acc_no, pw); //login a account and go to bank menu
}

//account holder name input
string acName_input() {
	Time t;

	t.start(); //start count the time

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
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
				return "\0";
			}
			else {
				t.start();
			}

			cout << setw(40) << left << "Confirm The Account Holder Name: ";
			getline(cin, accountName_confirm);
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
				return "\0";
			}
			else {
				t.start();
			}
		} while (accountName_confirm != accountName);

		//call the function checkName for check the name requirment
	} while (!checkName(accountName));

	cout << endl;
	cout << "<<Press The ENTER BUTTON To Continue>>" << endl;
	return accountName;
}

//account mobile phone number input
int phNum_input() {
	Time t;
	t.start();
	int phoneNumber = 0, phoneNumber_confirm = phoneNumber;
	do {
		cin.clear();
		cin.ignore(256, '\n');
		do {

			//check the tel input and confirm the tel
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
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
				return 0;
			}
			else {
				t.start();
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
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
				return 0;
			}
			else {
				t.start();
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

//account password input
string acPw_input() {
	Time t;
	t.start();
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
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
				return "\0";
			}
			else {
				t.start();
			}

			cout << setw(30) << left << "Confirm Your Account Password: ";
			getline(cin, accountPassword_confirm);
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
				return "\0";
			}
			else {
				t.start();
			}
		} while (accountPassword_confirm != accountPassword);
	} while (!checkPassword(accountPassword)); //call the check password function

	cout << endl;

	return accountPassword;
}

//account balance input
double balance_input() {
	Time t;
	t.start();
	double bal;

	do {
		cout << "Initial Amount to Deposit (At Least $100) : $";
		cin >> bal;
		if (t.stop() > 15) {
			cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
            system("pause");
			return 0;
		}
		else {
			t.start();
		}
		if (bal < 100) {
			cout << endl;
			cout << "-The Initial Amount Must Be At Least $100-" << endl;
			cout << "-Please Enter Again-" << endl;
			cout << endl;
		}
	} while (bal < 100);
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

	//the name requirement, using ASCII code check and .length() function
	for (int i = 0; i < s.length(); i++) {
		if ((int(cstr[i]) == 32 || (int(cstr[i]) >= 65 && int(cstr[i]) <= 90) || (int(cstr[i]) >= 97 && int(cstr[i]) <= 122)) && ((s.length() <= 20)) && ((s.length() != 0))) {
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

	//checking the password requirement, using ASCII code to check
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

//generate account number
int genAccNum(int phNum) {

	int acNum;

	srand(phNum); //use tel to be a seed value

	acNum = (567000000 + rand() % 999999);

	return acNum; //return the account number to open account function
}

//the requirement of the open account information
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

//deposit function
double deposit() {
	Time t;
	t.start();
	double amount;
	cout << "***************DEPOSIT***************" << endl;
	cout << setw(30) << left << "Deposit Amount:";
	while (!(cin >> amount) || (amount < 0)) { //checking the deposit amount
		cout << endl;
		cout << "-The Input Is Not A Number / Negative Amount-" << endl;
		system("pause");
		system("cls");
		cout << "***************DEPOSIT***************" << endl;
		cout << setw(30) << left << "Deposit Amount:";
		cin.clear(); //Reset the input error status to no error
		cin.ignore(256, '\n'); //Discard the content in the input sequence
	}
	if (t.stop() > 15) {
		cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
        system("pause");
		return 0;
	}
	else {
		t.start();
	}
	return amount;
}

//withdraw function
double withdraw(double balance) {
	Time t;
	t.start();
	double amount;
	cout << "***************WITHDRAW***************" << endl;
	cout << setw(30) << left << "Withdraw Amount:";
	while (!(cin >> amount) || (amount < 0) || (amount > balance)) { //checking the withdraw amount
		cout << endl;
		cout << "-The Input Is Not A Number / Negative Amount / Over Your Balance-" << endl;
		system("pause");
		system("cls");
		cout << "***************WITHDRAW***************" << endl;
		cout << setw(30) << left << "Withdraw Amount:";
		cin.clear(); //Reset the input error status to no error
		cin.ignore(256, '\n'); //Discard the content in the input sequence
	}
	if (t.stop() > 15) {
		cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
        system("pause");
		return 0;
	}
	else {
		t.start();
	}
	return amount;
}

//the yes no exit function
bool ynexit() {
	string n;
	do {
		cout << "Press \"Y/y\" For YES, \"N/n\" For NO: ";
		cin >> n;
		if (n == "Y" || n == "y") {
			return 1;
		}
		else if (n == "N" || n == "n") {
			return 0;
		}
		else {
			cout << "\a";
		}
	} while (n != "Y" || n != "y" || n != "N" || n != "n");
}

//the login function
void login(string file_name, int ac_num, string ac_pw) {

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



	hash_pw = str_hash(ac_pw); //hash the password to be hashed value

	// open the file
	ifstream inFile;

	// file should be put in same folder as the source code file
	inFile.open(file_name);
	begin = inFile.tellg(); //return the file position (beginning)
	inFile.seekg(0, ios::end); //let the file pointer at the end
	end = inFile.tellg(); //return the file position (end)
	size = end - begin; //calculate the size of the .dat file

	inFile.seekg(0, ios::beg); //set the file pointer at the beginning

	// get the file record until the end of the size
	while (inFile.tellg() != size) {

		//get the name, num, tel, pw, balance separately, in string data type
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

		//convert string to different data type
		stringstream s1(num);
		s1 >> acnum;

		stringstream s2(tel);
		s2 >> phNum;

		stringstream s3(pw);
		s3 >> hpw;

		stringstream s4(balance);
		s4 >> bal;

		//compare the login information (account number and hashed password)
		if ((ac_num == acnum) && (hpw == hash_pw)) {

			//if the information correct, set the account data to the class
			ac.setAcNum(acnum);
			ac.setName(name);
			ac.setTel(phNum);
			ac.setBalance(bal);
			ac.setHashPW(hpw);

			check = true; //the check boolean to be true, that mean found the account
		}

	}


	// close the file
	inFile.close();


	if (check) {
		ac.bankMenu(file_name); //go to the bank menu if found the account
	}

	//if no account found
	else {
		cout << "-----No This Account / Your Account Number Or Password Was Wrong-----" << endl;
		system("pause");
	}

}

//searching the phone number during open account
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

	while (inFile.tellg() != size) {

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

		//if found the tel
		if (tel_num == phNum) {

			inFile.close(); // close the file
			return 0;
		}
	}

	// close the file
	inFile.close();

	//if not found
	return 1;
}

//searching the account number
bool searchNum(string file_name, int ACnum) {
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

	while (inFile.tellg() != size) {

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

		//if found the tel
		if (ACnum == acnum) {

			inFile.close(); // close the file
			return 1;
		}
	}

	// close the file
	inFile.close();

	//if not found
	return 0;
}

//update the file record
void updateFile(string file_name, string name, int num, int tel, size_t hpw, double bal) {
	string ACnum;
	string ACtel;
	string ACname;
	string ACpw;
	string ACbalance;
	string numSearch;

	//convert the variables to string data type
	ACname = name;
	ACnum = to_string(num);
	ACtel = to_string(tel);
	ACpw = to_string(hpw);
	ACbalance = to_string(bal);

	int recno = 0;
	bool found;
	int counter = 0;
	string line;
	string lineArr[1000]; //the update record array

	ifstream file;
	file.open(file_name);
	found = false;

	//search the record is it exist
	while (getline(file, line)) {
		numSearch = line.substr(0, 9); //search the record by the account number

		if (ACnum == numSearch) {
			found = true;
			break;
		}
		else {
			found = false;
		}
	}

	file.close();

	//search the record position
	ifstream file2(file_name);
	while (getline(file2, line)) {
		lineArr[counter] = line;
		numSearch = line.substr(0, 9); //search the record by the account number

		if (ACnum == numSearch) {
			recno = counter;
		}

		counter++; //calculate the line number
	}

	file2.close();

	if (found == true) {

		lineArr[recno] = ACnum + "\t" + ACname + "\t" + ACtel + "\t" + ACpw + "\t" + ACbalance; //add the new account data into one array
		ofstream myUpdateFile(file_name); //open file

		//for-loop for write new into .dat file, cover the old record
		for (int i = 0; i < counter; i++) {
			myUpdateFile << lineArr[i] << endl;
		}
	}
}

//transfer money by using account number
double retTrans_num(string file_name, int ac, int ac_num) {
	Account acc;

	string num;
	string tel;
	string name;
	string pw;
	string balance;
	bool check = false;
	int size;
	int acnum;
	int phNum;
	double bal;
	double amount;
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

		//search the account number in the file record
		if (ac == acnum) {
			//set the recipient information in the class
			acc.setTransName(name);
			acc.setTransNum(acnum);
			acc.setTransTel(phNum);
			acc.setTransHash(hpw);
			acc.setTransBalance(bal);
			check = true;

		}

		if (ac_num == acnum) {
			//set the user account information in the class
			acc.setName(name);
			acc.setAcNum(acnum);
			acc.setTel(phNum);
			acc.setHashPW(hpw);
			acc.setBalance(bal);
			check = true;

		}

	}
	// close the file
	inFile.close();

	if (check) {
		amount = acc.transfer(file_name); //call the transfer function
		return amount; //return the amount to the bank menu
	}
	else {
		cout << "-No This Account-" << endl;
		system("pause");
		return 0; //return to bank menu
	}
}

//the transfer function by using tel to search account
//the principle same as the above function
double retTrans_tel(string file_name, int ph, int ac_num) {
	Account acc;

	string num;
	string tel;
	string name;
	string pw;
	string balance;
	bool check = false;
	int size;
	int acnum;
	int phNum;
	double bal;
	double amount;
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

		if (ph == phNum) {
			acc.setTransName(name);
			acc.setTransNum(acnum);
			acc.setTransTel(phNum);
			acc.setTransHash(hpw);
			acc.setTransBalance(bal);
			check = true;

		}

		if (ac_num == acnum) {
			acc.setName(name);
			acc.setAcNum(acnum);
			acc.setTel(phNum);
			acc.setHashPW(hpw);
			acc.setBalance(bal);
			check = true;

		}
	}
	// close the file
	inFile.close();

	if (check) {
		amount = acc.transfer(file_name);
		return amount;
	}
	else {
		cout << "-No This Account-" << endl;
		system("pause");
		return 0;
	}
}

//fixed deposit enquiry function
void fixedDeposit(double p, double r, int t) {
	Time time;
	time.start();
	double p_old = p;
	double a;
	double i;

	r = r / 100;
	system("cls");
	cout << "***************FIXED DEPOSIT ENQUIRY***************" << endl;
	cout << setw(15) << right << "Month" << setw(15) << right << "Interest" << setw(15) << right << "Amount" << endl;

	//for-loop for calculate each month
	for (int j = 1; j <= t; j++) {

		a = p * pow((1.0 + (r / 12.0)), j); //the formula of the fixed deposit
		i = a - p_old;
		p_old = a;

		cout << setw(15) << right << j;
		cout << setw(15) << right << setprecision(2) << fixed << i;
		cout << setw(15) << right << setprecision(2) << fixed << a << endl;
	}
	if (time.stop() > 15) {
		cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
        system("pause");
		return;
	}
	else {
		time.start();
		system("pause");
	}

}

//update the account information for mobile phone number
int update_tel() {
	Time t;
	t.start();
	int phoneNumber = 0, phoneNumber_confirm = phoneNumber;

	//do-while loop for checking the tel input
	do {
		cin.clear();
		cin.ignore(256, '\n');
		do {

			if (phoneNumber_confirm != phoneNumber) {
				cout << endl;
				cout << "-Not Match, Please Enter Again-" << endl;
				cout << endl;
			}

			cout << setw(30) << left << "NEW Mobile Phone Number: ";
			while (!(cin >> phoneNumber) || phoneNumber <= 0) {
				cout << endl;
				cout << "-Not Match The Phone Number Requirement-" << endl;
				cout << "-Please Enter Again-" << endl;
				cout << endl;
				cout << setw(30) << left << "NEW Mobile Phone Number: ";
				cin.clear(); //Reset the input error status to no error
				cin.ignore(256, '\n'); //Discard the content in the input sequence
			}
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
				return 0;
			}
			else {
				t.start();
			}

			cout << setw(30) << left << "Confirm NEW Mobile Phone Number: ";
			while (!(cin >> phoneNumber_confirm) || phoneNumber <= 0) {
				cout << endl;
				cout << "-Not Match The Phone Number Requirement-" << endl;
				cout << "-Please Enter Again-" << endl;
				cout << endl;
				cout << setw(30) << left << "Confirm NEW Mobile Phone Number: ";
				cin.clear(); //Reset the input error status to no error
				cin.ignore(256, '\n');//Discard the content in the input sequence
			}
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
				return 0;
			}
			else {
				t.start();
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

//update the account information for account password
string update_pw() {
	Time t;
	t.start();
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
			cout << setw(30) << left << "Enter NEW Password: ";
			getline(cin, accountPassword);
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
				return "\0";
			}
			else {
				t.start();
			}

			cout << setw(30) << left << "Confirm NEW Password: ";
			getline(cin, accountPassword_confirm);
			if (t.stop() > 15) {
				cout << "You are logged out as the system is idle for 15 seconds. Please login again." << endl;
                system("pause");
				return "\0";
			}
			else {
				t.start();
			}
		} while (accountPassword_confirm != accountPassword);
	} while (!checkPassword(accountPassword));

	cout << endl;

	return accountPassword;
}

/*Copyright 2019 Wong Kong Lun . All rights reserved*/
