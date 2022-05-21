// project term yek.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <string>
using namespace std;

// constants
const int g = 4;
const int VALUE_TO_WIN = 2048;

// entery point
void playGame();
void credit();
void menu();
int main() {
	menu();
	cout << "\nPress any key to close the game ...\n";
	_getch();
}
string Message;
void menu() {
	char input_menu;
	system("cls");
	cout << " *** 2048 Menu *** \n";
	cout << Message;
	Message = "";
	cout << " [1] start game \n";
	cout << " [2] credits \n";
	cout << " [3] Exit \n";
	cout << "pleas enter menu number\n";
	input_menu = _getch();
	switch (input_menu) {
	case'1':
	{	playGame();
	break;
	}
	case'2':
	{	system("CLS");
	credit();
	break;
	}
	case'3':
	{
		break;
	}
	default:
	{
		Message = " cammand was not valid \n";
		menu();
	}
	}
}
void credit() {
	cout << "  masum sheykhan  \n";
	cout << " student number : 990122680038 \n";
	cout << "Press any key to show menu again \n";
	_getch();
	menu();
}
// global variables : shared state
bool gameOver, stuck, win;
int score;
char input_char;
string logMessage;
int n[g][g];
int ranki, rankj;

// game manager section
void setGlobals();
void gameLoop();
void render();
void playGame() {
	setGlobals();
	render();
	while (!gameOver) {
		gameLoop();
	}
	if (win)
	{
		cout << " You won! \n";
		cout << "Press any key to show menu again \n";
	}
	else if (stuck)
	{
		cout << " You lost the game! \n";
		cout << "Press any key to show menu again \n";
	}
	else
	{
		cout << " See you later. \n";
		cout << "Press any key to show menu again \n";
	}
	_getch();
	menu();
}


void updateScore();
void setGlobals() {
	for (int i = 0; i < g; i++)
	{
		for (int j = 0; j < g; j++)
		{
			n[i][j] = 0;
			n[g % 2][g / 2] = 2;
		}
	}
	gameOver = false;
	stuck = false;
	win = false;
	updateScore();
	logMessage = "";
}


void input();
void update();
void render();
void gameLoop() {
	input();
	update();
	render();
}

// input section
void input() {
	cout << "[Move: L R U D |Exit: E]\n";
	input_char = _getch();
	switch (input_char) {
	case 'l':
		input_char = 'L';
		break;
	case 'r':
		input_char = 'R';
		break;
	case 'u':
		input_char = 'U';
		break;
	case 'd':
		input_char = 'D';
		break;
	case 'e':
		input_char = 'E';
		break;
	}
}

// update (game logic) section
bool move(char);
void updateScore();
void gameOverCheck();
void addTile(char);
void update() {
	bool moved;
	switch (input_char) {
	case 'E':
		gameOver = true;
		break;
	case 'L':
	{	moved = move(input_char);
	if (moved)
		addTile(input_char);
	break; }
	case 'R':
	{	moved = move(input_char);
	if (moved)
		addTile(input_char);
	break; }
	case 'U':
	{	moved = move(input_char);
	if (moved)
		addTile(input_char);
	break; }
	case 'D':
	{	moved = move(input_char);
	if (moved)
		addTile(input_char);
	break; }
	default:
		logMessage = "* COMMAND WAS NOT VALID. ";
	}
	updateScore();
	gameOverCheck();
}

bool moveLeft();
bool moveRight();
bool moveup();
bool movedown();
bool move(char direction) {
	//cout << direction << " move\n";
	bool moved = false;
	switch (direction) {
	case 'L':
		moved = moveLeft();
		break;
	case 'R':
		moved = moveRight();
		break;
	case 'U':
		moved = moveup();
		break;
	case 'D':
		moved = movedown();
		break;
	}
	return moved;
}

bool moveLeft() {
	bool moved = false;
	for (int i = 0; i < g; i++)
		for (int j = 0; j < g - 1; j++) {
			int next = j + 1;
			for (; next < g - 1; next++)
				if (n[i][next] > 0)
					break;

			if (n[i][j] == 0) {
				if (n[i][next] > 0) {
					n[i][j] = n[i][next];
					n[i][next] = 0;
					moved = true;
					j--;
				}
			}
			else {
				if (n[i][j] == n[i][next]) {
					n[i][j] = n[i][j] + n[i][next];
					n[i][next] = 0;
					moved = true;
				}
			}
		}
	return moved;
}
bool moveRight() {
	bool moved = false;
	for (int i = 0; i < g; i++) {
		for (int j = g - 1; j > 0; j--) {
			int next = j - 1;
			for (; next > 0; next--)
				if (n[i][next] != 0)
					break;
			if (n[i][j] == 0) {
				if (n[i][next] > 0) {
					n[i][j] = n[i][next];
					n[i][next] = 0;
					moved = true;
					j++;
				}
			}
			else if (n[i][j] == n[i][next]) {
				n[i][j] = n[i][j] + n[i][next];
				n[i][next] = 0;
				moved = true;
			}
		}
	}
	return moved;
}
bool moveup() {
	bool moved = false;
	for (int j = 0; j < g; j++)
		for (int i = 0; i < g - 1; i++) {
			int next = i + 1;
			for (; next < g - 1; next++)
				if (n[next][j] > 0)
					break;

			if (n[i][j] == 0) {
				if (n[next][j] > 0) {
					n[i][j] = n[next][j];
					n[next][j] = 0;
					moved = true;
					i--;
				}
			}
			else {
				if (n[i][j] == n[next][j]) {
					n[i][j] = n[i][j] + n[next][j];
					n[next][j] = 0;
					moved = true;
				}
			}
		}
	return moved;
}
bool movedown() {
	bool moved = false;
	for (int j = 0; j < g; j++) {
		for (int i = g - 1; i > 0; i--) {
			int next = i - 1;
			for (; next > 0; next--)
				if (n[next][j] > 0)
					break;
			if (n[i][j] == 0) {
				if (n[next][j] != 0) {
					n[i][j] = n[next][j];
					n[next][j] = 0;
					moved = true;
					i++;
				}
			}
			else if (n[i][j] == n[next][j]) {
				n[i][j] = n[i][j] + n[next][j];
				n[next][j] = 0;
				moved = true;
			}


		}
	}
	return moved;
}

void addTile(char direction) {
	do
	{
		ranki = rand() % 4;
		rankj = rand() % 4;
	} while (n[ranki][rankj] != 0);
	n[ranki][rankj] = 2;

}
void updateScore() {
	score = 0;
	for (int i = 0; i < g; i++)
		for (int j = 0; j < g; j++)
			score = score + n[i][j];
}

void stuckCheck();
void winCheck();
void gameOverCheck() {
	winCheck();
	stuckCheck();

	if (stuck || win) {
		gameOver = true;
	}
}

void stuckCheck() {
	stuck = true;
	for (int i = 0; i < g; i++)
		for (int j = 0; j < g; j++)
			if (n[i][j] == 0) {
				stuck = false;
				break;
			}
	for (int i = 0; i < g; i++)
		for (int j = 0; j < g - 1; j++)
			if (n[i][j] == n[i][j + 1]) {
				stuck = false;
				break;
			}
	for (int i = 0; i < g - 1; i++)
		for (int j = 0; j < g; j++)
			if (n[i][j] == n[i + 1][j]) {
				stuck = false;
				break;
			}
}

void winCheck() {
	win = false;
	for (int i = 0; i < g; i++)
		for (int j = 0; j < g; j++)
			if (n[i][j] == VALUE_TO_WIN) {
				win = true;
				break;
			}
}

// render section
void topPannel();
void printBoard();
void bottomPannel();
void render() {
	system("CLS");
	topPannel();
	printBoard();
	bottomPannel();
}

void topPannel() {
	cout << "[        2048 GAME      ]\n";
	if (logMessage != "") {
		cout << logMessage;
		logMessage = "";
	}
	cout << '\n';
}

void printCell(int);

void printBoard() {
	for (int i = 0; i < g; i++)
	{
		for (int j = 0; j < g; j++) {
			printCell(n[i][j]);
		}
		cout << "\n";
	}
	cout << '\n';
}

void printCell(int value) {
	if (value == 0)
		cout << "[    ]";
	else if (value < 10) {
		cout << "[ " << value << "  ]";
	}
	else if (value < 100) {
		cout << "[ " << value << " ]";
	}
	else if (value < 1000) {
		cout << "[ " << value << "]";
	}
	else {
		cout << "[" << value << "]";
	}
}

void bottomPannel() {
	cout << "Score: " << score << '\n';
}
//finished!
