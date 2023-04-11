#include<iostream>
#include"console.h"
#include<conio.h>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
#define MAUNEN 176
#define MAUCHU 112
enum TRANGTHAI { UP, DOWN, LEFT, RIGHT, ENTER, SPACE };
const int BOARD_SIZE = 4;
const int TEMP_SIZE = 8;
char board[BOARD_SIZE][BOARD_SIZE];
TRANGTHAI key(int z)
{
	if (z == 224)
	{
		char c;
		c = _getch();
		if (c == 72)
		{
			return UP;
		}
		if (c == 80)
		{
			return DOWN;
		}
		if (c == 77)
		{
			return RIGHT;
		}
		if (c == 75)
		{
			return LEFT;
		}
	}
	else if (z == 13)
		return ENTER;
	else if (z == 32)
	{
		return SPACE;
	}
}

void initBoard(char board[][BOARD_SIZE])
{
	srand(time(NULL));

	vector<char> character(TEMP_SIZE);
	for (int i = 0; i < TEMP_SIZE; i++)
	{
		character[i] = 'A' + rand() % 26;
	}
	random_shuffle(character.begin(), character.end());
	int Temp = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			board[i][j] = character[Temp];
			Temp++;
			if (Temp >= TEMP_SIZE)
			{
				Temp = 0;
			}
		}
	}
}
int Test(char board[][BOARD_SIZE])
{
	initBoard(board);
	int tt = 0, tt1 = 0;
	int mau[4][4];
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			mau[i][j] = MAUCHU;
		}
	mau[0][0] = MAUNEN;
	while (1)
	{
		clrscr();
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			cout << "\n";

			for (int j = 0; j < BOARD_SIZE; j++)
			{
				TextColor(mau[i][j]);
				cout << "  " << board[i][j] << "  ";
			}
			cout << endl;
		}
		int z = _getch();
		TRANGTHAI trangthai = key(z);
		switch (trangthai)
		{
		case UP:
		{
			if (tt == 0)
			{
				tt = BOARD_SIZE - 1;
			}
			else
				tt -= 1;
			break;

		}
		case DOWN:
		{
			if (tt == BOARD_SIZE - 1)
			{
				tt = 0;
			}
			else
				tt += 1;
			break;

		}
		case LEFT:
		{
			if (tt1 == 0)
			{
				tt1 = BOARD_SIZE - 1;
			}
			else
				tt1 -= 1;
			break;
		}
		case RIGHT:
		{
			if (tt1 == BOARD_SIZE - 1)
			{
				tt1 = 0;
			}
			else
				tt1 += 1;
			break;
		}
		case SPACE:
		{
			gotoXY(0, 1);
			for (int i = 0; i < BOARD_SIZE; i++)
			{
				cout << "\n";

				for (int j = 0; j < BOARD_SIZE; j++)
				{
					TextColor(mau[i][j]);
					cout << "  " << board[i][j] << "  ";
				}
				cout << endl;
			}
			break;
		}
		case ENTER: return tt;
		}
		for (int i = 0; i < BOARD_SIZE; i++)
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				mau[i][j] = MAUCHU;
			}
		mau[tt][tt1] = MAUNEN;

	}
}