#include"DOHOA.h"
int main()
{
	while (true)
	{
		system("cls");
		cout << "o---------------------------o" << endl;
		cout << "|1.Chay tro choi            |" << endl;
		cout << "|0.Thoat tro choi           |" << endl;
		cout << "o---------------------------o" << endl;
		int lc;
		cout << "Nhap lua chon:"; cin >> lc;
		switch (lc)
		{
		case 1:
		{
			system("color 70");
			Test(board);
			system("pause");
			_getch();
		}
		case 2:
		{
		}
		case 0:
		{
			return 0;
			break;
		}
		}
	}
}