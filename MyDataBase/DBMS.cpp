#include "MyDataBase.h"

DBMS::DBMS()
{
}

DBMS::~DBMS()
{
}

bool DBMS::LoadCSV(string path)
{
	//TODO .csv���� �̿ܿ� ������ �� ��� ���� ó��
	//path ��ο� ���� ���� ������ �о� ��
	fs.open(path, ios::in);
	if (fs.fail())
		return false;
	char* str_buf = new char();
	string cell;
	while (!fs.eof())
	{
		fs.getline(str_buf, 150);
		stringstream ss;
		ss.str(str_buf);

		while (!ss.eof())
		{
			std::getline(ss, cell, ',');
			cout << cell;
		}
		cout << "\n";
	}

	return true;
}
