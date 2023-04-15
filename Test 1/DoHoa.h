#include"console.h"
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<time.h>
#include<conio.h>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <mmsystem.h>
#include<string>
using namespace std;
#define MAUNEN 176
#define MAUCHU 112
enum TRANGTHAI { UP, DOWN, LEFT, RIGHT, ENTER, SPACE };
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
