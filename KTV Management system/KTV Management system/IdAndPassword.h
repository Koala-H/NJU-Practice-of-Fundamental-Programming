#pragma once
#include"Draw.h"
#include<string>
using namespace std;
class IdAndPassword
{
	string accountNum;
	string passwordNum;
	int times;  //剩余输入密码次数，三次验证失败自动锁定

public:
	IdAndPassword();  //提供初始账号和密码
	bool judge();   //判断账号密码是否正确
	void changePassword();  //修改密码
	void printChange();  //显示修改密码界面
	void cinPassword(string &s);  //输入密码，显示*
	bool checkFormat(const string &s);  //检查密码格式是否正确

};