#include"InfoHandle.h"
#include<algorithm>

bool compareSerialNum(const Song &a, const Song &b)
{
	return a.serialNum < b.serialNum;
}

void placeAtTop()   //�����ö�
{
	unsigned int n;
	while (1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		Draw::gotoxy(28, 26);
		cout << "���������ö��ĸ�����ţ�   \b\b\b";
		cin >> n;
		if (n > 0 && n <= mySong.size())
		{
			mySong[n - 1].status = 0;
			mySong[0].status = 1;
			mySong[n - 1].serialNum = 1;
			for (unsigned int i = 0; i < n - 1; i++)
				mySong[i].serialNum++;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			Draw::gotoxy(35, 27);
			cout << "�ö��ɹ�������";
			Sleep(750);
			Draw::gotoxy(35, 27);
			cout << "              ";
			Draw::gotoxy(28, 26);
			cout << "                         ";
			break;
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			Draw::gotoxy(35, 27);
			cout << "���������ڣ�����������";
			Sleep(750);
			Draw::gotoxy(35, 27);
			cout << "                      ";
		}
	}
}

void giveScore()
{
	unsigned int n;
	while (1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		Draw::gotoxy(28, 26);
		cout << "�����������ֵĸ������(����0����)��   \b\b\b";
		cin >> n;
		if (n == 0)
			break;
		if (n > 0 && n <= mySong.size())
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			Draw::gotoxy(34, 27);
			cout << "�������(1-5):    \b\b\b\b";
			cin >> mySong[n - 1].score;
			while (mySong[n - 1].score < 1 || mySong[n - 1].score>5)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
				Draw::gotoxy(35, 28);
				cout << "����������Ҫ��,����������";
				Sleep(750);
				Draw::gotoxy(35, 28);
				cout << "                         ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
				Draw::gotoxy(34, 27);
				cout << "�������(1-5):    \b\b\b\b";
				cin >> mySong[n - 1].score;
			}
			for(auto &s:songs)
				if (s.id == mySong[n - 1].id)
				{
					s.score = mySong[n - 1].score;
					break;
				}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			Draw::gotoxy(35, 28);
			cout << "���ֳɹ�������";
			Sleep(750);
			Draw::gotoxy(35, 28);
			cout << "              ";
			Draw::gotoxy(28, 26);
			cout << "                                       ";
			Draw::gotoxy(34, 27);
			cout << "                      ";
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			Draw::gotoxy(35, 27);
			cout << "���������ڣ�����������";
			Sleep(750);
			Draw::gotoxy(35, 27);
			cout << "                      ";
		}
	}
	Draw::gotoxy(28, 26);    
	cout << "                                         ";
}

void removeSong()
{
	unsigned int n;
	while (1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		Draw::gotoxy(28, 26);
		cout << "���������Ƴ��ĸ�����ţ�   \b\b\b";
		cin >> n;
		if (n > 0 && n <= mySong.size())
		{
			vector<Song>::iterator it = mySong.begin();
			for (; it->serialNum != n; ++it);
			it = mySong.erase(it);
			for (; it != mySong.end(); ++it)
				it->serialNum--;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			Draw::gotoxy(35, 27);
			cout << "�Ƴ��ɹ�������";
			Sleep(750);
			Draw::gotoxy(35, 27);
			cout << "              ";
			Draw::gotoxy(28, 26);
			cout << "                        ";
			break;
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			Draw::gotoxy(35, 27);
			cout << "���������ڣ�����������";
			Sleep(750);
			Draw::gotoxy(35, 27);
			cout << "                      ";
		}
	}
}

void cutTheSong()
{
	vector<Song>::iterator it = mySong.begin();
	it = mySong.erase(it);
	for (; it != mySong.end(); ++it)
		it->serialNum--;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	Draw::gotoxy(40, 27);
	cout << "�и�ɹ�������";
	Sleep(750);
	Draw::gotoxy(40, 27);
	cout << "              ";
}

void InfoHandle::haveSelected()
{
	system("cls");
	if (mySong.size() == 0)
	{
		Draw::gotoxy(35, 10);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		cout << "��δ��裡����";
		Sleep(750);
		return;
	}
	for (unsigned int i = 0; i < mySong.size(); ++i)
		mySong[i].serialNum = i + 1;
	int count = 1;//�ڼ�ҳ
	int m = 0;
	if (mySong.size() % 10 != 0)
		m = 1;
	int sum = mySong.size() / 10 + m;  //����ҳ
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Draw::drawRect(26, 7, 54, 16);
	Draw::drawHorizontal(27, 8, 53, '-');
	Draw::gotoxy(28, 21);
	cout << "�� " << count << " ҳ���� " << sum << " ҳ";
	Draw::gotoxy(28, 22);
	cout << "��һҳ������һҳ����esc������ҳ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	Draw::gotoxy(30, 7);
	cout << "���";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	Draw::gotoxy(43, 7);
	cout << "������";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
	Draw::gotoxy(60, 7);
	cout << "������";
	while (1)
	{
		for (int i = 0; i < 10; ++i)
		{
			Draw::gotoxy(30, 9 + i);
			cout << "   ";
			Draw::gotoxy(43, 9 + i);
			cout << "              ";
			Draw::gotoxy(60, 9 + i);
			cout << "     ";
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
		Draw::gotoxy(31, 21);
		cout << count;
		unsigned int n = (count - 1) * 10;
		sort(mySong.begin(), mySong.end(), compareSerialNum);
		for (unsigned int i = 0; i < 10 && i + n < mySong.size(); ++i)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			Draw::gotoxy(30, 9 + i);
			cout << mySong[i + n].serialNum;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			Draw::gotoxy(43, 9 + i);
			cout << mySong[i + n].songName;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
			Draw::gotoxy(60, 9 + i);
			cout << mySong[i + n].singerName;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
		Draw::gotoxy(60, 9);
		cout << mySong[n].singerName << "---���ڲ���";
		Draw::gotoxy(28, 24);
		cout << "����1:�ö�����  2:�Ƴ�����  3:�и�  4:����";
		int flag = getInput();
		switch (flag)
		{
		case 0:return;
		case 1:if (count > 1)count--; break;
		case 2:if (count > sum)count++; break;
		case 3:placeAtTop(); break;
		case 4:removeSong(); break;
		case 5:cutTheSong(); break;
		case 6:giveScore(); break;
		default:
			break;
		}
	}
}