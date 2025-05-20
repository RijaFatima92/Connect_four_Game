#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<Windows.h>
#include<fstream>
#include<iomanip>
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
using namespace std;

string name1, name2;
int choice = 0, count1 = 0, count2 = 0;

void display(char game1[6][7], string& name1, string& name2, bool& turn1, int& count1, int& count2);
void inputTurn(char game1[6][7], bool turn1, int& count1, int& count2, string& name1, string& name2, int& i);
void continuousDisplay(char game1[6][7]);
bool horizontalConnect(char game1[6][7]);
bool verticalConnect(char game1[6][7]);
bool mainDiagonal(char game1[6][7]);
bool invertDiagonal(char game1[6][7]);
void fun_into_fun(char game[6][7], bool& isWin, bool& turn1, int& count1, int& count2, string& name1, string& name2);
void menu();

int main()
{
	menu();
	return 0;
}
void save_history(string name, int count)
{
	fstream History;
	History.open("GameHistory.txt", ios::out | ios::app);
	if (History.is_open())
	{
		History << CYAN << "\n Players: \n\t" << GREEN << name1 << RED << " Turns: " << YELLOW << count1 << "\n\t" << GREEN << name2 << RED << " Turns: " << YELLOW << count2 << endl;
		if (name == "Game draw")
		{
			cout << MAGENTA << "\nGame Draw" << RESET << endl;
		}
		else
		{
			History << MAGENTA << "\n Winner: \n\t" << BLUE << name << RESET;
			History << MAGENTA << "\n\tTurns\t" << BLUE << count << RESET << endl;;
		}

		for (int i = 1; i <= 20; i++)History << CYAN << "*" << RESET;

		History << "\n\n\n\n";
		History.close();
	}
	else cout << RED << "Error opening file" << RESET;
}

void history()
{
	system("cls");
	int choice = 0;
	fstream History;
	History.open("GameHistory.txt", ios::in | ios::app);
	if (History.is_open())
	{
		History << "\n";
		History.seekg(0, ios::beg);
		cout << History.rdbuf();
		History.close();
	}
	else cout << RED << "Error Opening This File." << RESET;

	string a;
	do {
		cout << CYAN << "\n\nPress 1 to go to menu\n" << RESET;
		cin >> a;
	} while (a != "1");

	if (a == "1") menu();
}

void menu()
{
	system("cls");
	cout << MAGENTA;
	cout << "************************************************************************************************************************\n";
	cout << "*                                                                                                                      *\n";
	cout << "*              /////   ||||  |\\   |||  |\\   |||  ||||||   /////  |||||||     ||||||  ||||   ||   ||  |||||/            *\n";
	cout << "*             ||      ||  || |\\\\  |||  |\\\\  |||  ||      ||        ||        ||     ||  ||  ||   ||  ||  //            *\n";
	cout << "*             ||      ||  || |\\\\  |||  |\\\\  |||  ||||||  ||        ||        ||||   ||  ||  ||   ||  || //             *\n";
	cout << "*             ||      ||  || ||\\\\ |||  ||\\\\ |||  ||      ||        ||        ||     ||  ||  ||   ||  ||/\\\\             *\n";
	cout << "*              /////   ||||  || \\\\|||  || \\\\|||  ||||||   /////    ||        ||      ||||    |||||   ||  \\\\            *\n";
	cout << "*                                                                                                                      *\n";
	cout << "************************************************************************************************************************\n";
	cout << RESET;
	cout << GREEN << "SELECT ONE OF THE FOLLOWING:" << RESET << endl;
	//srand(time(0));
	bool isWin = false, turn1 = false;
	char game[6][7] = { 0 };
	int  choice1 = 0;
	count1 = 0, count2 = 0;
	string choice;
	do {

		do {

			cout << CYAN;
			cout << "1. Play game\n2. Game Credits\n";
			cout << "3. Instructions";
			cout << "\n4. Check Record";
			cout << "\n0. Exit Game\n";// Taking correct choice input

			cin >> choice;
			cout << RESET;

				if (choice < "0" || choice > "4") {
					cout << RED << "Invalid choice! Please select a number between 0 and 4.\n" << RESET;
				}

		} while (choice < "0" || choice>"4");
		choice1 = stoi(choice);
		switch (choice1)
		{
		case 1:
			fun_into_fun(game, isWin, turn1, count1, count2, name1, name2);
			break;
		case 2:
			system("cls");
			cout << GREEN << "\n\nThe game credits go to Rao Waleed & Rija Fatima\n" << RESET << endl;
			break;
		case 3:
			system("cls");
			cout << YELLOW << "\n\nHere are the instructions & rules for Connect 4!" << endl;
			cout << "The Connect 4 game is a classic strategy game where two players compete to dominate the grid!" << endl;

			cout << "\n1: The game is played on a 6x7 board." << endl;
			cout << "2: It is a two-player game." << endl;
			cout << "3: Each player takes turns dropping pieces of their chosen color into the grid." << endl;
			cout << "4: The goal is to connect four pieces in a row, which can be:" << endl;
			cout << "   - Horizontally" << endl;
			cout << "   - Vertically" << endl;
			cout << "   - Diagonally (forward or backward)" << endl;
			cout << "5: The first player to connect four pieces in a row wins the game!" << endl;

			cout << "Now, let the game begin!\n\n" << RESET;
			break;
		case 4:
			if (isWin == false)
			{
				history();
			}
			else
			{
				if (turn1 == true)
				{
					cout << endl;
					cout << MAGENTA << "Winner's name is " << GREEN << name1 << MAGENTA << " and number of turns are " << GREEN << count1 << RESET << endl;
				}
				else
				{
					cout << endl;
					cout << MAGENTA << "Winner's name is " << BLUE << name2 << MAGENTA << " and number of turns are " << BLUE << count2 << RESET << endl;
				}
			}
			break;

		}

	} while (choice1 != 0);
	cout << CYAN << "\nExiting......" << RESET << endl;

	system("pause");
}


void display(char game1[6][7], string& name1, string& name2, bool& turn1, int& count1, int& count2)
{
	system("cls");
	count1 = 0; count2 = 0;
	do {
		cout << YELLOW << "Enter the last name of Player 1" << endl;
		cin >> name1;
	} while (name1[0] < 'a' && name1[0] < 'A' || name1[0] > 'z' && name1[0] > 'Z');
	do {
		cout << RESET << RED << "Enter the last name of Player 2" << endl;
		cin >> name2;
	} while (name2[0] < 'a' && name2[0] < 'A' || name2[0] > 'z' && name2[0] >'Z');
	cout << RESET;
	string toss;
	int random = 0;
	do {
		cout << CYAN << name1 << "! please select 0 or 1 for toss" << endl;
		cin >> toss;
		cout << RESET;
	} while (toss < "0" || toss>"1");
	random = rand() % 2;
	if (stoi(toss) == random)
		turn1 = true;
	else
		turn1 = false;
	cout << RED;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
			game1[i][j] = '_';
	}
	cout << " 1 2 3 4 5 6 7" << endl;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			cout << "|" << game1[i][j];
			if (j == 6)
				cout << "|";
		}
		cout << endl;

	}
	cout << RESET;


}

void end()
{
	string i;
	do {
		cout << CYAN << "\nPress 1 to continue to menu\n";
		cin >> i;
		cout << RESET;
	} while (i != "1");
	if (i == "1")menu();
}



void inputTurn(char game1[6][7], bool turn1, int& count1, int& count2, string& name1, string& name2, int& i)
{
	int col = 0;
	string col1;
	bool isTrue = false;

	do {
		isTrue = false;
		if (turn1)
		{
			cout << GREEN << name1 << RESET << YELLOW << "'s turn (Your attack is 'O') :" << RESET << endl;
		}
		else
			cout << BLUE << name2 << RESET << YELLOW << "'s turn (Your attack is 'X') :" << endl;

		do {
			cout << CYAN << "Enter column number between 1 & 7:" << endl;
			cin >> col1;
		} while (col1 < "1" || col1> "7");
		col = stoi(col1);

		cout << RESET;
		// Checking either selecting column is filled or not
		if (col > 0 && col < 8)
		{
			for (int i = 5; i >= 0; i--)
			{
				if (game1[i][col - 1] == '_')
				{
					if (turn1 == true)
					{
						game1[i][col - 1] = 'O';			// For player 1
						count1++;
						i++;
					}
					else
					{
						game1[i][col - 1] = 'X';			// For player 2
						count2++;
						i++;
					}
					isTrue = true;
					break;
				}
			}
			if (isTrue == false)
				cout << RED << "Already filled this column! Try other one\n" << RESET << endl;
		}
	} while (col < 1 || col > 7 || isTrue == false);
}


void continuousDisplay(char game1[6][7])
{
	system("cls");
	cout << MAGENTA << " 1 2 3 4 5 6 7" << RESET << endl;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (game1[i][j] == 'O')
				cout << RED << "|" << GREEN << game1[i][j] << RESET;
			else if (game1[i][j] == 'X')
				cout << RED << "|" << RESET << BLUE << game1[i][j] << RESET;
			else
				cout << RED << "|" << RESET << game1[i][j];
			if (j == 6)
				cout << RED << "|" << RESET;
		}
		cout << endl;
	}
}

bool horizontalConnect(char game1[6][7])				// use this function for returning isWin true/false
{
	bool isWin = false;
	int ocount = 0, xcount = 0;
	for (int i = 5; i >= 0; i--)
	{
		ocount = 0, xcount = 0;
		for (int j = 0; j < 7; j++)
		{
			if (game1[i][j] == 'O')
			{
				ocount++; xcount = 0;
			}
			else if (game1[i][j] == 'X')
			{
				xcount++; ocount = 0;
			}
			else
			{
				ocount = 0; xcount = 0;
			}
			if (ocount == 4 || xcount == 4)
			{
				isWin = true;
				break;
			}
		}
		if (isWin == true)
			break;
	}
	if (isWin == true)
		return true;
	else
		return false;
}


bool verticalConnect(char game1[6][7])				// use this function for returning isWin true/false
{
	bool isWin = false;
	int ocount = 0, xcount = 0;;
	for (int j = 0; j < 7; j++)
	{
		for (int i = 5; i >= 0; i--)
		{
			if (game1[i][j] == 'O')
			{
				ocount++; xcount = 0;
			}
			else if (game1[i][j] == 'X')
			{
				ocount = 0; xcount++;
			}
			else
			{
				ocount = 0; xcount = 0;
			}
			if (ocount == 4 || xcount == 4)
			{
				isWin = true;
				break;
			}
		}
		if (isWin == true)
			break;
	}
	if (isWin == true)
		return true;
	else
		return false;
}


bool mainDiagonal(char game1[6][7])
{
	bool isWin = false;
	int oc1 = 0, oc2 = 0, oc3 = 0, oc4 = 0, oc5 = 0, oc6 = 0;
	int xc1 = 0, xc2 = 0, xc3 = 0, xc4 = 0, xc5 = 0, xc6 = 0;

	for (int i = 5; i >= 0; i--)
	{
		for (int j = 0; j < 7; j++)
		{
			if (i - j == 2)
			{
				if (game1[i][j] == 'O')
					oc1++;
				else
					oc1 = 0;
			}
			else if (i - j == 1)
			{
				if (game1[i][j] == 'O')
					oc2++;
				else
					oc2 = 0;
			}
			else if (i == j)
			{
				if (game1[i][j] == 'O')
					oc3++;
				else
					oc3 = 0;
			}
			else if (j - i == 1)
			{
				if (game1[i][j] == 'O')
					oc4++;
				else
					oc4 = 0;
			}
			else if (j - i == 2)
			{
				if (game1[i][j] == 'O')
					oc5++;
				else
					oc5 = 0;
			}
			else if (j - i == 3)
			{
				if (game1[i][j] == 'O')
					oc6++;
				else
					oc6 = 0;
			}
			else {}
			if (i - j == 2)
			{
				if (game1[i][j] == 'X')
					xc1++;
				else
					xc1 = 0;
			}
			else if (i - j == 1)
			{
				if (game1[i][j] == 'X')
					xc2++;
				else
					xc2 = 0;
			}
			else if (i == j)
			{
				if (game1[i][j] == 'X')
					xc3++;
				else
					xc3 = 0;
			}
			else if (j - i == 1)
			{
				if (game1[i][j] == 'X')
					xc4++;
				else
					xc4 = 0;
			}
			else if (j - i == 2)
			{
				if (game1[i][j] == 'X')
					xc5++;
				else
					xc5 = 0;
			}
			else if (j - i == 3)
			{
				if (game1[i][j] == 'X')
					xc6++;
				else
					xc6 = 0;
			}
			else {}
			if (oc1 == 4 || oc2 == 4 || oc3 == 4 || oc4 == 4 || oc5 == 4 || oc6 == 4 || xc1 == 4 || xc2 == 4 || xc3 == 4 || xc4 == 4 || xc5 == 4 || xc6 == 4)
			{
				isWin = true;
				break;
			}
		}
		if (isWin == true)
			break;
	}
	if (isWin == true)
		return true;
	else
		return false;
}


bool invertDiagonal(char game1[6][7])
{
	bool isWin = false;
	int oc1 = 0, oc2 = 0, oc3 = 0, oc4 = 0, oc5 = 0, oc6 = 0;
	int xc1 = 0, xc2 = 0, xc3 = 0, xc4 = 0, xc5 = 0, xc6 = 0;
	for (int i = 5; i >= 0; i--)
	{
		for (int j = 0; j < 7; j++)
		{
			if (i + j == 3)
			{
				if (game1[i][j] == 'O')
				{
					oc1++; xc1 = 0;
				}
				else if (game1[i][j] == 'X')
				{
					oc1 = 0; xc1++;
				}
				else
				{
					oc1 = 0; xc1 = 0;
				}
			}
			else if (i + j == 4)
			{
				if (game1[i][j] == 'O')
				{
					oc2++; xc2 = 0;
				}
				else if (game1[i][j] == 'X')
				{
					oc2 = 0; xc2++;
				}
				else
				{
					oc2 = 0; xc2 = 0;
				}
			}
			else if (i + j == 5)
			{
				if (game1[i][j] == 'O')
				{
					oc3++; xc3 = 0;
				}
				else if (game1[i][j] == 'X')
				{
					oc3 = 0; xc3++;
				}
				else
				{
					oc3 = 0; xc3 = 0;
				}
			}
			else if (i + j == 6)
			{
				if (game1[i][j] == 'O')
				{
					oc4++; xc4 = 0;
				}
				else if (game1[i][j] == 'X')
				{
					oc4 = 0; xc4++;
				}
				else
				{
					oc4 = 0; xc4 = 0;
				}
			}
			else if (i + j == 7)
			{
				if (game1[i][j] == 'O')
				{
					oc5++; xc5 = 0;
				}
				else if (game1[i][j] == 'X')
				{
					oc5 = 0; xc5++;
				}
				else
				{
					oc5 = 0; xc5 = 0;
				}
			}
			else if (i + j == 8)
			{
				if (game1[i][j] == 'O')
				{
					oc6++; xc6 = 0;
				}
				else if (game1[i][j] == 'X')
				{
					oc6 = 0; xc6++;
				}
				else
				{
					oc6 = 0; xc6 = 0;
				}
			}
			else {}
			if (oc1 == 4 || oc2 == 4 || oc3 == 4 || oc4 == 4 || oc5 == 4 || oc6 == 4 || xc1 == 4 || xc2 == 4 || xc3 == 4 || xc4 == 4 || xc5 == 4 || xc6 == 4)
			{
				isWin = true;
				break;
			}
		}
		if (isWin == true)
			break;
	}
	if (isWin == true)
		return true;
	else
		return false;
}

void w1()
{
	cout << MAGENTA << "Congratulations! " << GREEN << name1 << MAGENTA << " won" << RESET << endl;
}

void w2()
{
	cout << MAGENTA << "Congratulations! " << BLUE << name2 << MAGENTA << " won" << RESET << endl;
}
void fun_into_fun(char game[6][7], bool& isWin, bool& turn1, int& count1, int& count2, string& name1, string& name2)
{

	display(game, name1, name2, turn1, count1, count2);
	int i = 0;
	while (isWin == false)
	{
		turn1 = !turn1;
		inputTurn(game, turn1, count1, count2, name1, name2, i);
		continuousDisplay(game);
		if (i < 41)
		{
			isWin = horizontalConnect(game);
			if (isWin == false)
			{
				isWin = verticalConnect(game);
				if (isWin == false)
				{
					isWin = mainDiagonal(game);
					if (isWin == false)
					{
						isWin = invertDiagonal(game);
						if (isWin == true && turn1)
						{
							w1();
							save_history(name1, count1);
							end();
						}

						else {}
						if (isWin == true && !turn1)
						{
							w2();
							save_history(name2, count2);
							end();
						}
						else {}

					}
					else
					{
						if (turn1)
						{
							w1();
							save_history(name1, count1);
							end();
						}
						else
						{
							w2();
							save_history(name2, count2);
							end();
						}
					}
				}
				else
				{
					if (turn1)
					{
						w1();
						save_history(name1, count1);
						end();
					}
					else
					{
						w2();
						save_history(name2, count2);
						end();
					}
				}
			}
			else
			{
				if (turn1)
				{
					w1();
					save_history(name1, count1);
					end();
				}
				else
				{
					w2();
					save_history(name2, count2);
					end();
				}
			}
		}
		else
		{
			cout << MAGENTA << "Game draw" << RESET << endl;
			cout << "Game Draw" << endl;
			save_history("Game Draw", 0);
			end();
			break;
		}
	}
}
