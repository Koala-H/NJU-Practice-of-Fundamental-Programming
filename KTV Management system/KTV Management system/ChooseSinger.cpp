#include"InfoHandle.h"

void InfoHandle::judgeSinger(vector<Song> &findSong, const string &s)
{
	findSong.clear();
	for (auto song2 : songs)
		if (song2.singerName == s)
			findSong.push_back(song2);
}

int InfoHandle::judgeID(vector<Song> &findSong, int num)
{
	for (unsigned int i = 0; i < findSong.size(); ++i)
		if (findSong[i].id == num)return i;
	return -1;
}

void InfoHandle::chooseSinger()
{
	system("cls");
	string name;
	vector<Song> findSong;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Draw::drawRect(26, 7, 45, 12);
	Draw::gotoxy(40, 8);
	cout << "***歌手点歌***";
	Draw::gotoxy(28, 10);
	cout << "输入要查找的歌手(end结束)：";
	while (1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
		Draw::gotoxy(55, 10);
		cout << "          ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		Draw::gotoxy(55, 10);
		cin >> name;
		if (name == "end")return;
		judgeSinger(findSong, name);
		if (findSong.size() == 0)  //歌手不存在
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			Draw::gotoxy(32, 15);
			cout << "该歌手不存在！请重新查找...";
			Sleep(750);
			Draw::gotoxy(32, 15);
			cout << "                           ";
		}
		else {    //歌手存在
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
			Draw::gotoxy(28, 11);
			cout << "相关歌曲如下：";
			unsigned int i = 0;
			for (; i < findSong.size();++i)
			{
				Draw::gotoxy(30, 12 + i);
				cout << findSong[i].id;
				Draw::gotoxy(35, 12 + i);
				cout << findSong[i].songName;
				Draw::gotoxy(55, 12 + i);
				cout << findSong[i].singerName;
			}
			while (1) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
				Draw::gotoxy(28, 12 + i);
				cout << "请选择你要添加的歌曲ID(输入0结束)：   \b\b\b";
				int num;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
				cin >> num;
				if (num == 0)break;
				else {
					int locate = judgeID(findSong, num);
					if (locate != -1)
					{
						if (mySong.empty())  //歌单中尚无歌曲
						{
							findSong[locate].status = 0;
							nowTheSong = findSong[locate].singerName + "-" + findSong[locate].songName;
							th1 = thread(&InfoHandle::playMusic, this);
							th2 = thread(&InfoHandle::printLyrics, this);
							th1.detach();
							th2.detach();
						}
						mySong.push_back(findSong[locate]);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
						Draw::gotoxy(36, 14 + i);
						cout << "添加成功！！！";
					}
					else {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
						Draw::gotoxy(36, 14 + i);
						cout << "歌曲不存在！请重新选择...";
					}
					Sleep(750);
					Draw::gotoxy(36, 14 + i);
					cout << "                          ";
				}
			}
			for (i = 0; i <= findSong.size() + 1; ++i)
			{
				Draw::gotoxy(28, 11 + i);
				cout << "                                      ";
			}
		}
	}
}