#include"User.h"
#include<algorithm>

vector<int> num;    //用于排序的属性位置

bool saveInFile = false;

bool cmp1(Data &a, Data &b)  //用于升序排序
{
	for (unsigned int i = 0; i < num.size(); ++i)
		if (a.data[i] == b.data[i])
			continue;
		else if (a.data[i] < b.data[i])
			return true;
		else return false;
	return false;
}
bool cmp2(Data &a,Data &b)  //用于降序排序
{
	for (unsigned int i = 0; i < num.size(); ++i)
		if (a.data[i] == b.data[i])
			continue;
		else if (a.data[i]>b.data[i])
			return true;
		else return false;
	return false;
}

int parse(vector<string> &tmp)
{
	if (tmp[1] == "DISTINCT")
		return 3;   //展示不重复项
	if (tmp[1] == "*"&&tmp.size() == 4)
		return 2;   //展示整个table
	if (tmp[tmp.size() - 2] == "=")
		return 5;   //展示满足条件列
	if (tmp[tmp.size() - 2] == "TO")
		return 6;   //将展示结果写入文件
	if (tmp.back() == "ASC"|| tmp.back() == "DESC")
		return 4;   //对结果排序
	if (tmp[tmp.size() - 2] == "FROM")
		return 1;   //选择若干列展示
	return 0;
}

bool isExist(vector<string> &a, string b)
{
	for (auto it = a.begin(); it != a.end(); ++it)
		if (*it == b)
			return true;
	return false;
}

void select1(vector<string> &tmp, Table &tmpTable)
{
	int n = tmp.size();
	string tmpp = tmp[n - 1];

	if (!User::judge(tmpp, "SELECT"))
	{
		cout << "(mysql)==> Permission denied!" << endl;
		return;
	}

	auto it = tables.begin();
	for (; it != tables.end(); ++it)
		if (it->tableName == tmpp)    //找到相应表格
			break;
	vector<string> attb;
	for (int i = 0; i < n - 3; i++)
		attb.push_back(tmp[i + 1]);
	
	tmpTable.tableName = it->tableName;
	tmpTable.attribute = it->attribute;
	tmpTable.datas = it->datas;

	if (!saveInFile)
	{
		for (unsigned int i = 0; i < attb.size(); ++i)
			cout << attb[i] << '\t';
		cout << endl;

		for (unsigned int i = 0; i < it->datas.size(); ++i)
		{
			int k = 0;
			for (unsigned int j = 0; j < it->attribute.size(); ++j)
				if (it->attribute[j] == attb[k])
				{
					cout << it->datas[i].data[j - 1] << '\t';
					k++;
					if (k == attb.size())break;
				}
			cout << endl;
		}
	}
}

void select2(vector<string> &tmp, Table &tmpTable)
{
	string tmpp = tmp[3];

	if (!User::judge(tmpp, "SELECT"))
	{
		cout << "(mysql)==> Permission denied!" << endl;
		return;
	}

	auto it = tables.begin();
	for (; it != tables.end(); ++it)
		if (it->tableName == tmpp)    //找到相应表格
			break;

	tmpTable.tableName = it->tableName;
	tmpTable.attribute = it->attribute;
	tmpTable.datas = it->datas;

	if (!saveInFile)
	{
		for (unsigned int i = 0; i < it->attribute.size(); ++i)
			cout << it->attribute[i] << '\t';
		cout << endl;

		for (unsigned int i = 0; i < it->datas.size(); ++i)
		{
			cout << it->datas[i].id << '\t';
			for (unsigned int j = 0; j < it->datas[i].data.size(); ++j)
				cout << it->datas[i].data[j] << '\t';
			cout << endl;
		}
	}
}

void select3(vector<string> &tmp, Table &tmpTable)
{
	int n = tmp.size();
	string tmpp = tmp[n - 1];

	if (!User::judge(tmpp, "SELECT"))
	{
		cout << "(mysql)==> Permission denied!" << endl;
		return;
	}

	auto it = tables.begin();
	for (; it != tables.end(); ++it)
		if (it->tableName == tmpp)    //找到相应表格
			break;

	tmpTable.tableName = it->tableName;
	tmpTable.attribute = it->attribute;

	string attb= tmp[2];

	unsigned int i = 1;
	for (; i < it->attribute.size(); ++i)
		if (it->attribute[i] == attb)break;
	if (!saveInFile)
		cout << attb << endl;

	vector<string> hasExist;
	tmpTable.datas.push_back(it->datas[0]);
	hasExist.push_back(it->datas[0].data[i - 1]);
	if (!saveInFile)
		cout << it->datas[0].data[i - 1] << endl;
	for (unsigned int j = 1; j < it->datas.size(); ++j)
		if (!isExist(hasExist, it->datas[j].data[i - 1]))
		{
			tmpTable.datas.push_back(it->datas[j]);
			if (!saveInFile)
				cout << it->datas[j].data[i - 1] << endl;
		}
}

void select4(vector<string> &tmp, Table &tmpTable)
{
	int n = tmp.size();
	string tmpp = tmp[3];

	if (!User::judge(tmpp, "SELECT"))
	{
		cout << "(mysql)==> Permission denied!" << endl;
		return;
	}

	auto it = tables.begin();
	for (; it != tables.end(); ++it)
		if (it->tableName == tmpp)    //找到相应表格
			break;

	vector<string> column;
	for (int i = 6; i < n - 1; ++i)
		column.push_back(tmp[i]);

	for (unsigned int m = 0; m < column.size(); ++m)
	{
		for (unsigned int i = 1; i < it->attribute.size(); ++i)
			if (column[m] == it->attribute[i])
			{
				num.push_back(i - 1);
				break;
			}
	}

	if (tmp[n - 1] == "ASC")
		sort(it->datas.begin(), it->datas.end(), cmp1);
	else if (tmp[n - 1] == "DESC")
		sort(it->datas.begin(), it->datas.end(), cmp2);

	tmpTable.tableName = it->tableName;
	tmpTable.attribute = it->attribute;
	tmpTable.datas = it->datas;

	if (!saveInFile)
	{
		for (auto p = it->attribute.begin(); p != it->attribute.end(); ++p)
			cout << *p << '\t';
		cout << endl;
		for (unsigned int i = 0; i < it->datas.size(); ++i)
		{
			cout << it->datas[i].id << '\t';
			for (auto p = it->datas[i].data.begin(); p != it->datas[i].data.end(); ++p)
				cout << *p << '\t';
			cout << endl;
		}
	}
}

void select5(vector<string> &tmp, Table &tmpTable)
{
	int n = tmp.size();
	string tmpp = tmp[n - 5];

	if (!User::judge(tmpp, "SELECT"))
	{
		cout << "(mysql)==> Permission denied!" << endl;
		return;
	}

	auto it = tables.begin();
	for (; it != tables.end(); ++it)
		if (it->tableName == tmpp)    //找到相应表格
			break;

	tmpTable.tableName = it->tableName;
	tmpTable.attribute = it->attribute;

	string column = tmp[n - 3];
	string value = tmp[n - 1];
	unsigned int i = 1;        //column对应第i+1个属性
	for (; i < it->attribute.size(); ++i)
		if (it->attribute[i] == column)break;
	if (i == it->attribute.size()) {  //属性不存在
		cout << "The attribute is not exist!" << endl;
		return;
	}

	if (tmp[1] == "*")
	{
		if (!saveInFile)
		{
			for (unsigned int j = 0; j < it->attribute.size(); ++j)
				cout << it->attribute[j] << '\t';
			cout << endl;
		}
		for (unsigned int j = 0; j < it->datas.size();++j)
			if (it->datas[j].data[i - 1] == value)
			{
				tmpTable.datas.push_back(it->datas[j]);
				if (!saveInFile)
				{
					cout << it->datas[j].id << '\t';
					for (unsigned int k = 0; k < it->datas[j].data.size(); ++k)
						cout << it->datas[j].data[k] << '\t';
					cout << endl;
				}
			}
	}
	else {
		vector<string> attb;
		for (int k = 0; k < n - 7; k++)
			attb.push_back(tmp[k + 1]);
		if (!saveInFile)
		{
			for (unsigned int i = 0; i < attb.size(); ++i)
				cout << attb[i] << '\t';
			cout << endl;
		}

		for (unsigned int j = 0; j < it->datas.size(); ++j)
			if (it->datas[j].data[i - 1] == value)
			{
				tmpTable.datas.push_back(it->datas[j]);
				if (!saveInFile)
					for (unsigned int k = 0; k < it->datas[j].data.size(); ++k)
					{
						int m = 0;
						if (it->attribute[k + 1] == attb[m])
						{
							cout << it->datas[j].data[k] << '\t';
							m++;
							if (m == attb.size()) {
								cout << endl;
								break;
							}
						}
					}
			}
	}
}

void select6(Table &tmpTable)
{
	vector<string> t(ParseStatement::result.begin(), ParseStatement::result.end() - 2);
	saveInFile = true;
	int choice = parse(t);
	switch (choice)
	{
	case 1:select1(t,tmpTable); break;
	case 2:select2(t,tmpTable); break;
	case 3:select3(t,tmpTable); break;
	case 4:select4(t, tmpTable); break;
	case 5:select5(t,tmpTable); break;
	default:
		break;
	}
	if (tmpTable.attribute.size() == 0)
		return;
	string fname = ParseStatement::result.back();
	const char *filename = fname.c_str();
	ofstream fout(filename);
	if (fout) {
		unsigned int j = 0;
		for (; j < tmpTable.attribute.size() - 1; ++j)
			fout << tmpTable.attribute[j] << '\t';
		fout << tmpTable.attribute[j] << endl;
		for (unsigned int k = 0; k < tmpTable.datas.size(); ++k)
		{
			fout << tmpTable.datas[k].id << '\t';
			auto p = tmpTable.datas[k].data.begin();
			for (; p != tmpTable.datas[k].data.end() - 1; ++p)
				fout << *p << '\t';
			fout << *p << endl;
		}
		fout.close();
	}
}

void User::selectFrom()
{
	saveInFile = false;
	Table tmp;
	int choice = parse(ParseStatement::result);
	switch (choice)
	{
	case 1:select1(ParseStatement::result, tmp); break;
	case 2:select2(ParseStatement::result, tmp); break;
	case 3:select3(ParseStatement::result, tmp); break;
	case 4:select4(ParseStatement::result, tmp); break;
	case 5:select5(ParseStatement::result, tmp); break;
	case 6:select6(tmp); break;
	default:
		break;
	}
}