// // // // // // // // // // // // // //
//
//      NAME: Michael Crowley
//      Login: cs102@029    
//      CUNY Email: mcrowle000@citymail.ccny.cuny.edu
//
// // // // // // // // // // // // // //

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

ofstream out_file("out.8", ios::out);

class BANCO_EASIER{

   public:      // public interfaces for this class
	BANCO_EASIER(string, string);// constructor
	void ACTIVATE(string); // a method;

   private:
	// NEW FUNCTIONS:
	int DEPOSIT(string, int, int); // private func to deposit money
	int WITHDRAW(string, int, int); // private func to withdraw money
	// EXISTING FUNCTION FROM PROJECT 7:
	void DRAW_WELCOME(); // private func to draw welcome
	void DRAW_MENU(); // private func to draw menu
	int FIND_CUSTOMER(int, int); // private func to find balance
	int GET_BALANCE(string, int); // private func to find balance
	int CHANGE_PIN(int, int); // private func to change PIN

	string NAME; // var to store name of the section
	string BRANCH_NAME; // var to store name of the section
	int NOOF_CUSTOMERS; // var to store the number of customers
	int ACCOUNT_NO[50]; // int array for account numbers (50 max)
	int PIN[50]; // int array for PINs (50 max)
	int CHECKING_BALANCE[50];// int array for checking account balance
	int SAVINGS_BALANCE[50]; // int array for savings account balance
	float AVERAGE_BALANCE[50]; // Average daily balance for each customer
	string FIRST_NAMES[50]; // string array for first names
	string LAST_NAMES[50]; // string array for last names
};

BANCO_EASIER::BANCO_EASIER(string  str_1, string str_2)
{
	int i;

	NAME = str_1;

	char file_name[80];
	strcpy(file_name, str_2.c_str());
	ifstream in_file(file_name,ios::in);

	in_file >> NOOF_CUSTOMERS;
	
	for(i=0 ; i < NOOF_CUSTOMERS ; i++)
	{
		in_file >> FIRST_NAMES[i] >> LAST_NAMES[i] >> ACCOUNT_NO[i] >> 
		PIN[i] >> CHECKING_BALANCE[i] >> SAVINGS_BALANCE[i];
	}

	    cout << "AN OBJECT CALLED " << NAME << " IS CREATED." << endl;
	out_file << "AN OBJECT CALLED " << NAME << " IS CREATED." << endl;
	    cout << "THERE ARE " << NOOF_CUSTOMERS << " CUSTOMERS IN " << NAME << endl;
	out_file << "THERE ARE " << NOOF_CUSTOMERS << " CUSTOMERS IN " << NAME << endl;
}

void
BANCO_EASIER::ACTIVATE(string  str_3)
{
	int USER_ACCT_NO, USER_PIN;
	int USER_ENTRY_INT = 0;
	int USER_NEW_PIN_FIRST;
	int USER_NEW_PIN_SECOND;
	int USER_BALANCE;
	int RET_VALUE;
	string USER_ENTRY_STRING;
	int cust_pos;

	BRANCH_NAME = str_3;

  DRAW_WELCOME();
	    cout << " ENTER ACCOUNT NUMBER" << endl;
	out_file << " ENTER ACCOUNT NUMBER" << endl;
	cin >> USER_ACCT_NO;
			cout << " ENTER PIN" << endl;
	out_file << " ENTER PIN" << endl;
	cin >> USER_PIN;

	cust_pos = FIND_CUSTOMER(USER_ACCT_NO, USER_PIN);

	if (cust_pos == -1)
  {
	    cout << "NO SUCH CUSTOMER. GOOD BYE." << endl;
	out_file << "NO SUCH CUSTOMER. GOOD BYE." << endl;
	}
	else
	{
		    cout << "HELLO " << LAST_NAMES[cust_pos] << ", " << FIRST_NAMES[cust_pos] << endl;
		out_file << "HELLO " << LAST_NAMES[cust_pos] << ", " << FIRST_NAMES[cust_pos] << endl;

		DRAW_MENU();

	while(USER_ENTRY_INT != 8)
		{
			USER_ENTRY_INT = 0;
			USER_ENTRY_STRING = "";
			cin >> USER_ENTRY_INT;
			if (USER_ENTRY_INT == 1)
			{
				    cout << "WHAT TYPE OF ACCOUNT? (CHECKING OR SAVINGS)" << endl;
				out_file << "WHAT TYPE OF ACCOUNT? (CHECKING OR SAVINGS)" << endl;
				cin >> USER_ENTRY_STRING;
				USER_BALANCE = GET_BALANCE(USER_ENTRY_STRING, cust_pos);
				if(USER_ENTRY_STRING == "CHECKING")
				{
					    cout << "YOUR CHECKING BALANCE IS " << USER_BALANCE << " USD." << endl;
					out_file << "YOUR CHECKING BALANCE IS " << USER_BALANCE << " USD." << endl;
				}
				else if(USER_ENTRY_STRING == "SAVINGS")
				{
					    cout << "YOUR SAVINGS BALANCE IS " << USER_BALANCE << " USD." << endl;
					out_file << "YOUR SAVINGS BALANCE IS " << USER_BALANCE << " USD." << endl;
				}
				else
				{
					    cout << "INVALID USER ENTRY." << endl;
					out_file << "INVALID USER ENTRY." << endl;
					break;
				}
			}
			else if (USER_ENTRY_INT == 2)
			{
				    cout << "ENTER NEW PIN: " << endl;
				out_file << "ENTER NEW PIN: " << endl;
				cin >> USER_NEW_PIN_FIRST;
				    cout << "RE-ENTER NEW PIN: " << endl;
				out_file << "RE-ENTER NEW PIN: " << endl;
				cin >> USER_NEW_PIN_SECOND;
				if (CHANGE_PIN(USER_NEW_PIN_FIRST,USER_NEW_PIN_SECOND) == 1)
				{
					PIN[cust_pos] = USER_NEW_PIN_FIRST;
					    cout << "YOUR PIN HAS BEEN CHANGED." << endl;
					out_file << "YOUR PIN HAS BEEN CHANGED." << endl;
				}
				else if(CHANGE_PIN(USER_NEW_PIN_FIRST,USER_NEW_PIN_SECOND) == 0)
				{
					cout << "YOUR PIN HAS NOT BEEN CHANGED. TWO ENTRIES DO NOT MATCH." << endl;
					out_file << "YOUR PIN HAS NOT BEEN CHANGED. TWO ENTRIES DO NOT MATCH." << endl;
				}
				else {}
			}
			else if (USER_ENTRY_INT == 3)
			{
				    cout << "WHAT TYPE OF ACCOUNT? (CHECKING OR SAVINGS)" << endl;
				out_file << "WHAT TYPE OF ACCOUNT? (CHECKING OR SAVINGS)" << endl;
				cin >> USER_ENTRY_STRING;
				if(USER_ENTRY_STRING == "CHECKING")
				{
					cout << "HOW MUCH TO DEPOSIT?" << endl;
					out_file << "HOW MUCH TO DEPOSIT?" << endl;
					cin >> USER_ENTRY_INT;
					USER_BALANCE = DEPOSIT(USER_ENTRY_STRING, cust_pos, USER_ENTRY_INT);
					cout << "YOUR CHECKING BALANCE IS " << USER_BALANCE << " USD." << endl;
					out_file << "YOUR CHECKING BALANCE IS " << USER_BALANCE << " USD." << endl;
				}
				else if (USER_ENTRY_STRING == "SAVINGS")
				{
					cout << "HOW MUCH TO DEPOSIT?" << endl;
					out_file << "HOW MUCH TO DEPOSIT?" << endl;
					cin >> USER_ENTRY_INT;
					USER_BALANCE = DEPOSIT(USER_ENTRY_STRING, cust_pos, USER_ENTRY_INT);
					cout << "YOUR SAVINGS BALANCE IS " << USER_BALANCE << " USD." << endl;
					out_file << "YOUR SAVINGS BALANCE IS " << USER_BALANCE << " USD." << endl;
				}
				else
				{
					cout << "INVALID USER ENTRY." << endl;
					out_file << "INVALID USER ENTRY." << endl;
					break;
				}

			}
			else if (USER_ENTRY_INT == 4)
			{
				    cout << "WHAT TYPE OF ACCOUNT? (CHECKING OR SAVINGS)" << endl;
				out_file << "WHAT TYPE OF ACCOUNT? (CHECKING OR SAVINGS)" << endl;
				cin >> USER_ENTRY_STRING;
				if(USER_ENTRY_STRING == "CHECKING")
				{
					cout << "HOW MUCH TO WITHDRAW (MULTIPLES OF 10 PLEASE)?" << endl;
					out_file << "HOW MUCH TO WITHDRAW (MULTIPLES OF 10 PLEASE)?" << endl;
					cin >> USER_ENTRY_INT;
					if(USER_ENTRY_INT %10 != 0)
					{
						cout << "INVALID USER ENTRY." << endl;
						out_file << "INVALID USER ENTRY." << endl;
						break;
					}
					else if(CHECKING_BALANCE[cust_pos] - (USER_ENTRY_INT + 2) < 0)
					{
						cout << "INSUFFICIENT FUNDS." << endl;
						out_file << "INSUFFICIENT FUNDS." << endl;
					}
					else
					{
						WITHDRAW(USER_ENTRY_STRING, cust_pos, USER_ENTRY_INT);
						cout << "ENJOY YOUR MONEY." << endl;
						out_file << "ENJOY YOUR MONEY." << endl;
					}
				}
				else if(USER_ENTRY_STRING == "SAVINGS")
				{
					cout << "HOW MUCH TO WITHDRAW (MULTIPLES OF 10 PLEASE)?" << endl;
					out_file << "HOW MUCH TO WITHDRAW (MULTIPLES OF 10 PLEASE)?" << endl;
					cin >> USER_ENTRY_INT;
					if(USER_ENTRY_INT %10 != 0)
					{
						cout << "INVALID USER ENTRY." << endl;
						out_file << "INVALID USER ENTRY." << endl;
						break;
					}
					else if(SAVINGS_BALANCE[cust_pos] - (USER_ENTRY_INT + 2) < 0)
					{
						cout << "INSUFFICIENT FUNDS." << endl;
						out_file << "INSUFFICIENT FUNDS." << endl;
					}
				  else
					{
						WITHDRAW(USER_ENTRY_STRING, cust_pos, USER_ENTRY_INT);
						cout << "ENJOY YOUR MONEY." << endl;
						out_file << "ENJOY YOUR MONEY." << endl;
					}
				}
				else
				{
					    cout << "INVALID USER ENTRY." << endl;
					out_file << "INVALID USER ENTRY." << endl;
					break;
				}
			}
			else if (USER_ENTRY_INT == 7)
			{
				DRAW_MENU();
			}
			else if (USER_ENTRY_INT == 8)
			{
				    cout << "GOOD BYE " << LAST_NAMES[cust_pos] << ", " << FIRST_NAMES[cust_pos] << ". HAVE A NICE DAY." << endl;
				out_file << "GOOD BYE " << LAST_NAMES[cust_pos] << ", " << FIRST_NAMES[cust_pos] << ". HAVE A NICE DAY." << endl;
				break;
			}
			else
			{
				    cout << " INVALID USER ENTRY." << endl;
				out_file << " INVALID USER ENTRY." << endl;
				break;
			}
		}// end while
	}
} // end ACTIVATE 

// BELOW ARE THE DEFINITIONS OF PRIVATE FUNCTIONS THAT CAN ONLY BE CALLED 
// FROM WITHIN METHODS AND NOT FROM MAIN PROGRAMS

// definition of private function DRAW_MENU
// input parameters: none
// this function draws the menu
void
BANCO_EASIER::DRAW_MENU()
{
	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	cout << "$                                $" << endl;
	cout << "$ PRESS 1 TO GET ACCOUNT BALANCE $" << endl;
	cout << "$ PRESS 2 TO CHANGE PIN          $" << endl;
	cout << "$ PRESS 3 TO DEPOSIT MONEY	      $" << endl;
	cout << "$ PRESS 4 TO WITHDRAW MONEY	    $" << endl;
	cout << "$ PRESS 7 TO REDRAW MENU         $" << endl;
	cout << "$ PRESS 8 TO QUIT                $" << endl;
	cout << "$                                $" << endl;
	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;

	out_file << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	out_file << "$                                $" << endl;
	out_file << "$ PRESS 1 TO GET ACCOUNT BALANCE $" << endl;
	out_file << "$ PRESS 2 TO CHANGE PIN          $" << endl;
	out_file << "$ PRESS 3 TO DEPOSIT MONEY       $" << endl;
	out_file << "$ PRESS 4 TO WITHDRAW MONEY      $" << endl;
	out_file << "$ PRESS 7 TO REDRAW MENU         $" << endl;
	out_file << "$ PRESS 8 TO QUIT                $" << endl;
	out_file << "$                                $" << endl;
	out_file << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
}

// definition of private function DEPOSIT
// input parameters:
// string s4 is either CHECKING or SAVINGS; 
// integer x is the customer position
// integer y is the amount to deposit 
// this function adds y to checking or savings balance
// it returns the final balance value;
int
BANCO_EASIER::DEPOSIT(string s4, int x, int y)
{
	if(s4 == "CHECKING")
	{
		CHECKING_BALANCE[x] = CHECKING_BALANCE[x] + y;
		return CHECKING_BALANCE[x];
	}
	else if(s4 == "SAVINGS")
	{
		SAVINGS_BALANCE[x] = SAVINGS_BALANCE[x] + y;
		return SAVINGS_BALANCE[x];
	}
	else {}
}

// definition of private function WITHDRAW
// input parameters:
// string s4 is either CHECKING or SAVINGS; 
// integer x is the customer position
// integer y is the amount to deposit 
// this function subtracts (y+2) from checking or savings balance
// it returns the final balance value;
int
BANCO_EASIER::WITHDRAW(string s4, int x, int y)
{
	if(s4 == "CHECKING")
	{
		CHECKING_BALANCE[x] = CHECKING_BALANCE[x] - y - 2;
	}
	else if(s4 == "SAVINGS")
	{
		SAVINGS_BALANCE[x] = SAVINGS_BALANCE[x] - y - 2;
	}
	else{}
}

// definition of private function GET_BALANCE
// string s4 is either CHECKING or SAVINGS; 
// integer w is the customer position
// this function returns the balance of checking or savings account
int
BANCO_EASIER::GET_BALANCE(string s4, int w)
{
	if(s4 == "CHECKING")
	{
		return CHECKING_BALANCE[w];
	}
	else if(s4== "SAVINGS")
	{
		return SAVINGS_BALANCE[w];
	}
	else{}
}


// definition of private function FIND_CUSTOMER
// input parameters:
// integer y is the account number 
// integer z is the PIN; 
// this function returns the customer position in private array ACCOUNT_NO; 
// or it returns -1 if no such customer;
int
BANCO_EASIER::FIND_CUSTOMER(int y, int z) 
{
	int i;
	int FOUND = 0;
	int FOUND_POS = -1;

	for(i = 0; i < NOOF_CUSTOMERS; i++)
	{
		if(y == ACCOUNT_NO[i] && z == PIN[i])
		{
			FOUND = 1;
			FOUND_POS = i;
		}
		else{}
	}

	return FOUND_POS;
}

// definition of private function CHANGE_PIN
// input parameters:
// integers v and z are the first and second user entries for new pin
// return value:
// this function returns 0 (if v and z are not equal) or 1 (if v == z) 
int
BANCO_EASIER::CHANGE_PIN(int v, int z)
{
	if(v == z)
	{return 1;}

	else
	{return 0;}
}

// definition of private function DRAW_WELCOME
// input parameters: none
// this function draws the welcome menu (centers the names)
void
BANCO_EASIER::DRAW_WELCOME()
{
 	int i, LENGTH_NAME, WHITE_SPACE, FRONT_BLANK, END_BLANK;
	string THIRD_LINE, FOURTH_LINE;

	// put 34 $ signs
	cout << " $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	out_file << " $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	// put 2 $ signs and 32 spaces 
	cout << " $                                $" << endl;
	out_file << " $                                $" << endl;
	
	LENGTH_NAME = NAME.length();
	WHITE_SPACE = 32 - LENGTH_NAME;
	if ((WHITE_SPACE % 2) == 0)
	{
		FRONT_BLANK = WHITE_SPACE / 2;
		END_BLANK = WHITE_SPACE / 2;
	}
	else
	{
		FRONT_BLANK = (WHITE_SPACE / 2) + 1;
		END_BLANK = WHITE_SPACE / 2;
	}
//cout << " LENGTH_NAME IS " << LENGTH_NAME << endl;
//cout << " WHITE SPACE IS " << WHITE_SPACE 
//	<< " FRONT " << FRONT_BLANK << " END " << END_BLANK << endl;
	THIRD_LINE = "$";
	for (i = 0; i < FRONT_BLANK; i++)
	{
		THIRD_LINE = THIRD_LINE + " ";
	}
	THIRD_LINE = THIRD_LINE + NAME;
	for (i = 0; i < END_BLANK; i++)
	{
		THIRD_LINE = THIRD_LINE + " ";
	}
	THIRD_LINE = THIRD_LINE + "$";
	cout << " " << THIRD_LINE << endl;
	out_file << " " << THIRD_LINE << endl;

	LENGTH_NAME = BRANCH_NAME.length();
	WHITE_SPACE = 32 - LENGTH_NAME;
	if ((WHITE_SPACE % 2) == 0)
	{
		FRONT_BLANK = WHITE_SPACE / 2;
		END_BLANK = WHITE_SPACE / 2;
	}
	else
	{
		FRONT_BLANK = (WHITE_SPACE / 2) + 1;
		END_BLANK = WHITE_SPACE / 2;
	}
	FOURTH_LINE = "$";
	for (i = 0; i < FRONT_BLANK; i++)
	{
		FOURTH_LINE = FOURTH_LINE + " ";
	}
	FOURTH_LINE = FOURTH_LINE + BRANCH_NAME;
	for (i = 0; i < END_BLANK; i++)
	{
		FOURTH_LINE = FOURTH_LINE + " ";
	}
	FOURTH_LINE += "$";
	cout << " " << FOURTH_LINE << endl;
	cout << " $                                $" << endl;
	cout << " $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	out_file << " " << FOURTH_LINE << endl;
	out_file << " $                                $" << endl;
	out_file << " $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
}
