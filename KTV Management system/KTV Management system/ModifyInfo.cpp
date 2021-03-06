#include"InfoHandle.h"

void modifySongName(int num)
{
	Draw::gotoxy(28, 17);
	cout << "输入新的歌名:";
	cin >> songs[num - 1].songName;
}
void modifySingerName(int num)
{
	Draw::gotoxy(28, 17);
	cout << "输入新的歌手名:";
	cin >> songs[num - 1].singerName;
}
void modifySongAbbreviation(int num)
{
	Draw::gotoxy(28, 17);
	cout << "输入新的歌名缩写:";
	cin >> songs[num - 1].songAbbreviation;
}

void InfoHandle::modifyInfo()
{
	system("cls");
	int num;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Draw::drawRect(26, 7, 45, 12);
	Draw::gotoxy(40, 7);
	cout << "***修改歌曲信息***";
	Draw::gotoxy(28, 10);
	cout << "请输入要修改的歌曲ID(输入0退出):";
	while (1)
	{
		Draw::gotoxy(61, 10);
		cout << "        ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		Draw::gotoxy(61, 10);
		cin >> num;
		if (num == 0)return;
		if (num<0 || num>(int)songs.size())
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			Draw::gotoxy(34, 15);
			cout << "歌曲不存在！请重新输入";
			Sleep(750);
			Draw::gotoxy(34, 15);
			cout << "                        ";
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
			Draw::gotoxy(28, 12);
			cout << "歌曲信息如下:";
			Draw::gotoxy(34, 13);
			cout << "1.歌名:" << songs[num - 1].songName;
			Draw::gotoxy(34, 14);
			cout << "2.歌手:" << songs[num - 1].singerName;
			Draw::gotoxy(34, 15);
			cout << "3.歌名缩写:" << songs[num - 1].songAbbreviation;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
			Draw::gotoxy(28, 16);
			cout << "想修改哪一项:";
			int n;
			while (1) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
				Draw::gotoxy(42, 16);
				cout << "       ";
				Draw::gotoxy(42, 16);
				cin >> n;
				if(n<1||n>3)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
					Draw::gotoxy(30, 17);
					cout << "没有该选项！请重新选择";
					Sleep(750);
					Draw::gotoxy(30, 17);
					cout << "                        ";
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
					if (n == 1)modifySongName(num);
					if (n == 2)modifySingerName(num);
					if (n == 3)modifySongAbbreviation(num);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
					Draw::gotoxy(34, 18);
					cout << "修改成功！！！";
					Sleep(750);
					for (int i = 0; i < 7; ++i)
					{
						Draw::gotoxy(28, 12 + i);
						cout << "                                ";
					}
					break;
				}
			}
		}
	}
}