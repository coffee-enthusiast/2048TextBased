// 2048Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <cwchar>
#include <windows.h>
#include "Cell.h"
using namespace std;

Cell table[4][4];

int cellsFilled;
bool somethingMoved;
bool mixHappened;
int maxScore;

void SpawnRandomCell()
{
	int randomValue;

	if (rand() % 2 == 0)
		randomValue = 2;
	else
		randomValue = 4;

	int randY = rand() % 4;
	int randX = rand() % 4;
	while (table[randY][randX].getValue() != 0)
	{
		randY = rand() % 4;
		randX = rand() % 4;
	}
	table[randY][randX].setValue(randomValue);

	cellsFilled++;
}

void InitializeTable()
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			table[y][x] = Cell();
		}
	}
	maxScore = 0;

	srand(time(0));
	SpawnRandomCell();
	SpawnRandomCell();
}

void PrintTable()
{
	// Clear console

	cout << "\x1B[2J\x1B[H";
	cout << "----" << endl;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			int value = table[y][x].getValue();
			if(value > 0)
			{
				if (value == 2)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
				else if (value == 4)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				else if (value <= 64)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
				else if (value <= 512)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				else if (value == 2048)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
				else if (value <= 9000)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);

			}
			else
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			cout << table[y][x].getValue() << "\t";
		}
		cout << endl;
	}
	cout << "----" << endl;
}

void MoveUp(int y, int x)
{
	if (table[y][x].getValue() != 0)
	{
		// If upper cell is empty
		int upperValue = table[y - 1][x].getValue();
		if (upperValue == 0)
		{
			table[y - 1][x].setValue(table[y][x].getValue());
			table[y][x].setValue(0);
			somethingMoved = true;
			if (y - 2 >= 0)
				MoveUp(y - 1, x);
		}
		else
		{
			if (upperValue == table[y][x].getValue() && !mixHappened)
			{
				table[y - 1][x].setValue(table[y][x].getValue() * 2);
				table[y][x].setValue(0);
				if (table[y][x].getValue() * 2 > maxScore)
					maxScore = table[y][x].getValue() * 2;
				cellsFilled--;
				mixHappened = true;
				somethingMoved = true;
			}
		}
	}
}

void MoveLeft(int y, int x)
{
	if (table[y][x].getValue() != 0)
	{
		// If left cell is empty
		int leftValue = table[y][x-1].getValue();
		if (leftValue == 0)
		{
			table[y][x-1].setValue(table[y][x].getValue());
			table[y][x].setValue(0);
			somethingMoved = true;
			if (x - 2 >= 0)
				MoveLeft(y, x - 1);
		}
		else
		{
			if (leftValue == table[y][x].getValue() && !mixHappened)
			{
				table[y][x - 1].setValue(table[y][x].getValue() * 2);
				table[y][x].setValue(0);
				if (table[y][x].getValue() * 2 > maxScore)
					maxScore = table[y][x].getValue() * 2;
				cellsFilled--;
				mixHappened = true;
				somethingMoved = true;
			}
		}
	}
}
void MoveDown(int y, int x)
{
	if (table[y][x].getValue() != 0)
	{
		// If down cell is empty
		int downValue = table[y + 1][x].getValue();
		if (downValue == 0)
		{
			table[y + 1][x].setValue(table[y][x].getValue());
			table[y][x].setValue(0);
			somethingMoved = true;
			if (y + 2 < 4)
				MoveDown(y + 1, x);
		}
		else
		{
			if (downValue == table[y][x].getValue() && !mixHappened)
			{
				table[y + 1][x].setValue(table[y][x].getValue() * 2);
				table[y][x].setValue(0);
				if (table[y][x].getValue() * 2 > maxScore)
					maxScore = table[y][x].getValue() * 2;
				cellsFilled--;
				mixHappened = true;
				somethingMoved = true;
			}
		}
	}
}
void MoveRight(int y, int x)
{
	cout << "(" << y << "," << x << ")=" << table[y][x].getValue() << endl;
	if (table[y][x].getValue() != 0)
	{
		// If right cell is empty
		int rightValue = table[y][x + 1].getValue();
		if (rightValue == 0)
		{
			table[y][x + 1].setValue(table[y][x].getValue());
			table[y][x].setValue(0);
			somethingMoved = true;
			if (x + 2 < 4)
				MoveRight(y, x + 1);
		}
		else
		{
			if (rightValue == table[y][x].getValue() && !mixHappened)
			{
				table[y][x + 1].setValue(table[y][x].getValue() * 2);
				table[y][x].setValue(0);
				if (table[y][x].getValue() * 2 > maxScore)
					maxScore = table[y][x].getValue() * 2;
				cellsFilled--;
				mixHappened = true;
				somethingMoved = true;
			}
		}
	}
}

bool CheckIfGameEnds()
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			int currValue = table[y][x].getValue();
			if (y - 1 >= 0)
			{
				if (table[y - 1][x].getValue() == currValue)
					return false;
			}
			if (x + 1 < 4)
			{
				if (table[y][x+1].getValue() == currValue)
					return false;
			}
		}
	}
	return true;
}

int main()
{

	InitializeTable();

	static CONSOLE_FONT_INFOEX  fontex;
	fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(hOut, 0, &fontex);
	fontex.FontWeight = 700;
	fontex.dwFontSize.X = 36;
	fontex.dwFontSize.Y = 36;
	SetCurrentConsoleFontEx(hOut, NULL, &fontex);

	int playerInput;
	bool gameEnds = false;


	while (!gameEnds)
	{
		PrintTable();
		somethingMoved = false;
		playerInput = getchar();
		switch (playerInput)
		{
		case 'w':
			for (int x = 0; x < 4; x++)
			{
				mixHappened = false;
				for (int y = 1; y < 4; y++)
				{
					MoveUp(y,x);
				}
			}
			break;
		case 'a':
			for (int y = 0; y < 4; y++)
			{
				mixHappened = false;
				for (int x = 1; x < 4; x++)
				{
					MoveLeft(y, x);
				}
			}
			break;
		case 's':
			for (int x = 0; x < 4; x++)
			{
				mixHappened = false;
				for (int y = 2; y >= 0; y--)
				{
					MoveDown(y, x);
				}
			}
			break;
		case 'd':
			for (int y = 0; y < 4; y++)
			{
				mixHappened = false;
				for (int x = 2; x >= 0; x--)
				{
					MoveRight(y, x);
				}
			}
			break;
		default:
			continue;
		}

		if(somethingMoved)
			SpawnRandomCell();

		if (cellsFilled == 4 * 4)
		{
			gameEnds = CheckIfGameEnds();
		}

		if (maxScore == 2048)
		{
			cout << " You won!!";
			gameEnds = true;
		}
	}
	PrintTable();
	cout << "Game Ended\n";
}

