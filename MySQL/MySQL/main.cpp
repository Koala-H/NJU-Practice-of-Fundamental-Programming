#include"ParseStatement.h"
#include"User.h"
#include"Table.h"
#include<iostream>
#include<string>
using namespace std;

User user[8];
vector<Table> tables;  //���б���

void init()
{
	UserInfo info[4];
	info[0].userName = "user1";
	info[1].userName = "user2";
	info[2].userName = "user3";
	info[3].userName = "user4";

	info[0].password = "user111";
	info[1].password = "user222";
	info[2].password = "user333";
	info[3].password = "user444";

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			info[i].permission[j] = 0;

	user[0] = info[0];
	user[1] = info[1];
	user[2] = info[2];
	user[3] = info[3];
}

int main()
{
	init();
	string s, s1;
	/*cout << "~$ ";
	cin >> s1;
	if (s1 != "mySQL")
		return 0;*/

	/*int n = User::login();
	if (n == -1)
		cout << "Login unsuccessfully" << endl;
	else {
		cout << "Login successfully" << endl;
		cout << "(mysql)==>";
		user[n].run(n);
	}*/

	user[0].run(0);
	cout << tables[0].tableName << endl;
	for (int i = 0; i < 3; ++i)
		cout << tables[0].attribute[i] << " ";
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 3; ++j)
			cout << tables[0].datas[i].data[j] << " ";
	cout << endl;

	/*while (1)
	{
		User::run();
	}*/
}