#include "MyDataBase.h"
DBMS::DBMS()
{
	Curpath = "[NONE]";
}

DBMS::~DBMS()
{
}

bool DBMS::LoadCSV(const string path)
{
	//path ��ο� ���� ���� ������ �о� ��

	//�Ľ� ���� ����Ʈ�� ^^
	//https://m.blog.naver.com/PostView.nhn?blogId=kks227&logNo=220245263973&proxyReferer=https:%2F%2Fwww.google.com%2F
	//https://steemit.com/kr-dev/@codingman/c-17-csv--1560125046366
	//https://www.it-swarm.dev/ko/c%2B%2B/c-%EC%97%90%EC%84%9C-csv-%ED%8C%8C%EC%9D%BC%EC%9D%84-%EC%9D%BD%EA%B3%A0-%EA%B5%AC%EB%AC%B8-%EB%B6%84%EC%84%9D%ED%95%98%EB%A0%A4%EB%A9%B4-%EC%96%B4%EB%96%BB%EA%B2%8C%ED%95%B4%EC%95%BC%ED%95%A9%EB%8B%88%EA%B9%8C/967277856/

	vector<string> s = GetFilesInDirectory(path, "*.csv");

	for (auto n : s)
		Log(n);

	Curpath = path;
	Clear();
	vTableName.clear();
	char* str_buf = new char[200];

	for (unsigned int i = 0; i < s.size(); i++)
	{
		vector<vector<string>> table;
		vTableName.push_back(s[i]);
		fstream fs;
		fs.open(s[i], ios::in);
		while (true)
		{
			if (fs.fail())
				return false;

			fs.getline(str_buf, 150);
			stringstream ss;
			ss.str(str_buf);

			if (fs.eof())
				break;

			string cell;
			vector<string> rowTable;
			while (true)
			{
				if (ss.eof())
					break;
				std::getline(ss, cell, ',');
				rowTable.push_back(cell);
			}
			table.push_back(rowTable);
		}
		vCurDataBase.push_back(table);
		fs.close();
		for (int j = 0; j < table.size(); j++)
			table[j].clear();
		table.clear();
		ShowTable("");
	}

	delete[] str_buf;

	return true;
}

void DBMS::ShowTable(const string name)
{	
	for (unsigned int i = 0; i < vCurDataBase.size(); i++)
	{
		for (unsigned int j = 0; j < vCurDataBase[i].size(); j++)
		{
			for (unsigned int k = 0; k < vCurDataBase[i][j].size(); k++)
			{
				cout << vCurDataBase[i][j][k] << " ";
			}
			cout << "\n";
		}
		Log(vTableName[i], TYPE::E_SUCCESE);
		cout << "\n";
	}
}

void DBMS::Clear()
{
	if (vCurDataBase.empty())
	{
		for (unsigned int i = 0; i < vCurDataBase[0].size(); i++)
			for (unsigned int j = 0; j < vCurDataBase[0][i].size(); j++)
				vCurDataBase[0][i][j].clear();

		vCurDataBase.clear();
	}
}

void DBMS::ShowTables()
{
	for (int i = 0; i < vTableName.size(); i++)
	{
		Log(vTableName[i]);
	}
}

void DBMS::Help() const
{
	Log("					< ���� >					", TYPE::E_NORMAL, LIGHT_YELLOW);
	Log(" LOAD (FOLDER PATH) - FOLDER PATH(�����)�� �ִ� ��� .csv������ �о�鿩 �ɴϴ�.", TYPE::E_NORMAL, LIGHT_YELLOW);
	Log(" USE (TABLE NAME) - TABLE NAME���� �� .csv������ �о�� �� �����մϴ�. (������ or �����)", TYPE::E_NORMAL, LIGHT_YELLOW);
	Log(" SHOW TABLES - ���õ� ���̺��� COLUME�� �����ݴϴ�.", TYPE::E_NORMAL, LIGHT_YELLOW);
}

vector<string> DBMS::GetFilesInDirectory(const string _path, const string _filter)
{
	//���� ����Ʈ : https://rex0725.tistory.com/2

	string searching = "./" + _path + _filter;	//�˻��� ������ ���, ./�� �տ� ��� ��θ� ���ذ� �Լ��� �����θ� �ν���
	vector<string> return_;	//������ ���� ����

	_finddata_t fd;		//�о�� ������ �����Ͱ� �ִ� ���� _finddata_t�� ����ü
	//���⿡ ���� �Լ����� 3�Ⱑ�� ������ ����� �� �� ����(���ſ� ����) �׷����� _findfirsti64() / _findnexti64() �� ����ؾ��Ѵ�.

	long handle = _findfirst(searching.c_str(), &fd);  //���� ���� �� ��� ������ ã�´�.(�ڵ鰪)

	if (handle == -1)    return return_;	//�˻� ���ǿ� �´� ������ �߰������� 0�� ����, �ƴϸ� -1�� ����(�ڵ鰪)

	int result = 0;
	do
	{
		return_.push_back("./" + _path + fd.name);		//return_�� ���� ������ �̸��� �־���
		result = _findnext(handle, &fd);	//�˻� ���ǿ� �´� ������ �߰������� 0�� ����, �ƴϸ� -1�� ����(�ڵ鰪)
	} while (result != -1);

	_findclose(handle);		//�˻� �ڵ��� �ݴ� �Լ�

	return return_;
}
