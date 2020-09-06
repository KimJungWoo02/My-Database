#include "MyDataBase.h"

DBMS::DBMS()
{
}

DBMS::~DBMS()
{
}

bool DBMS::LoadCSV(string path)
{
	//TODO .csv파일 이외에 들어왔을 떄 경고 문구 처리
	//path 경로에 읽이 모드로 파일을 읽어 옴
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
