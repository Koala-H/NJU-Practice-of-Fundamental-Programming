#pragma once
#include"Draw.h"
#include<string>
using namespace std;
class IdAndPassword
{
	string accountNum;
	string passwordNum;
	int times;  //ʣ���������������������֤ʧ���Զ�����

public:
	IdAndPassword();  //�ṩ��ʼ�˺ź�����
	bool judge();   //�ж��˺������Ƿ���ȷ
	void changePassword();  //�޸�����
	void printChange();  //��ʾ�޸��������
	void cinPassword(string &s);  //�������룬��ʾ*
	bool checkFormat(const string &s);  //��������ʽ�Ƿ���ȷ

};