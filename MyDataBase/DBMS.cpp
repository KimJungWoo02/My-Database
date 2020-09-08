#include "MyDataBase.h"
DBMS::DBMS()
{
	Curpath = "[NONE]";
	UseTable = "[NONE]";
}

DBMS::~DBMS()
{
}

bool DBMS::LoadCSV(const string path)
{
	//�Ľ� ���� ����Ʈ�� ^^
	//https://m.blog.naver.com/PostView.nhn?blogId=kks227&logNo=220245263973&proxyReferer=https:%2F%2Fwww.google.com%2F
	//https://steemit.com/kr-dev/@codingman/c-17-csv--1560125046366
	//https://www.it-swarm.dev/ko/c%2B%2B/c-%EC%97%90%EC%84%9C-csv-%ED%8C%8C%EC%9D%BC%EC%9D%84-%EC%9D%BD%EA%B3%A0-%EA%B5%AC%EB%AC%B8-%EB%B6%84%EC%84%9D%ED%95%98%EB%A0%A4%EB%A9%B4-%EC%96%B4%EB%96%BB%EA%B2%8C%ED%95%B4%EC%95%BC%ED%95%A9%EB%8B%88%EA%B9%8C/967277856/

	vector<string> allPath = GetFilesInDirectory(path, "*.csv");
	vector<string> tableName;


	for (auto n : allPath)
	{
		string name = n;
		name.erase(n.length() - string(".csv").length(), n.length());
		name.erase(0, path.length() + string("./").length());
		Log("Table Path : " + n + ", " + "Table Name : " + name, TYPE::E_INFO);
		tableName.push_back(name);
	}

	Curpath = path;
	Clear();
	char* str_buf = new char[200];

	for (unsigned int i = 0; i < allPath.size(); i++)
	{
		fstream fs;
		fs.open(allPath[i], ios::in);
		vector<vector<string>> table;
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
				getline(ss, cell, ',');
				rowTable.push_back(cell);
			}
			table.push_back(rowTable);
		}
		mCurDataBase.insert(make_pair(tableName[i], table));
		fs.close();
	}
	delete[] str_buf;
	return true;
}

void DBMS::ShowTable(const string name, const string rowname)
{	
	stringstream ss;
	string cell;
	vector<string> rownameList;

	Log("Show Tables...", TYPE::E_INFO);

	if (rowname != "*")
	{
		ss.str(rowname);
		while (true)
		{
			if (ss.eof())
				break;
			getline(ss, cell, ',');
			rownameList.push_back(cell);
		}
	}

	if (mCurDataBase.find(name) != mCurDataBase.end())
	{
		for (int i = 0; i < mCurDataBase[name].size(); i++)
		{
			for (int j = 0; j < mCurDataBase[name][i].size(); j++)
			{
				if (rowname == "*")
				{
					cout.flags(ios::left);
					cout.fill(' ');
					cout.width(15);
					cout << mCurDataBase[name][i][j];
				}
				else
				{
					for (int row = 0; row < rownameList.size(); row++)
					{
						if (mCurDataBase[name][0][j] == rownameList[row])
						{
							cout.flags(ios::left);
							cout.fill(' ');
							cout.width(15);
							cout << mCurDataBase[name][i][j];
						}
					}
				}
			}
			cout << "\n";
		}
	}
	else
	{
		Log(name + " : There is no table matching the name.", TYPE::E_ERROR);
	}
}

void DBMS::ShowTableRow(const string Tablename)
{
	for (int i = 0; i < mCurDataBase[Tablename][0].size(); i++)
	{
		Log(mCurDataBase[Tablename][0][i], TYPE::E_INFO);
	}
}

void DBMS::Clear()
{
	if (!mCurDataBase.empty())
		mCurDataBase.clear();
}

void DBMS::ShowTables() const
{
	if (!mCurDataBase.empty())
	{
		Log(Curpath + "'s Tables...");
		for (auto it : mCurDataBase)
			Log(it.first);
	}
	else
	{
		Log(Curpath + " : Currently, this DB is empty.");
	}
}

void DBMS::Help() const
{
	Log("					< ���� >					", TYPE::E_NORMAL, LIGHT_YELLOW);
	Log(" LOAD (FOLDER PATH) - FOLDER PATH(�����)�� �ִ� ��� .csv������ �о�鿩 �ɴϴ�.", TYPE::E_NORMAL, LIGHT_YELLOW);
	Log(" USE (TABLE NAME) - TABLE NAME���� �� .csv������ �о�� �� �����մϴ�. (������ or �����)", TYPE::E_NORMAL, LIGHT_YELLOW);
	Log(" SHOW TABLES - ���õ� ���̺��� COLUME�� �����ݴϴ�.", TYPE::E_NORMAL, LIGHT_YELLOW);
	Log(" DESC (TABLENAME) | DESCRIBE (TABLENAME) - �Է��� TABLENAME�� � row�� �ִ��� �����ݴϴ�.", TYPE::E_NORMAL, LIGHT_YELLOW);
	Log(" SELECT (TABLE ROW) FROM (TABLE NAME)- ", TYPE::E_NORMAL, LIGHT_YELLOW);
	Log(" EXIT - ���α׷��� �����մϴ�.", TYPE::E_NORMAL, LIGHT_YELLOW);
}

void DBMS::SetuseTable(string tablename)
{
	UseTable = tablename;
}

void DBMS::Select(string rowRange, string table)
{
	ShowTable(table, rowRange);
}

vector<string> DBMS::GetFilesInDirectory(const string _path, const string _filter)
{
	//���� ����Ʈ : https://rex0725.tistory.com/2

	string searching = "./" + _path + _filter;	//�˻��� ������ ���, ./�� �տ� ��� ��θ� ���ذ� �Լ��� �����θ� �ν���
	vector<string> return_;	//������ ���� ����

	_finddata_t fd;		//�о�� ������ �����Ͱ� �ִ� ���� _finddata_t�� ����ü
	//���⿡ ���� �Լ����� 3�Ⱑ�� ������ ����� �� �� ����(���ſ� ����) �׷����� _findfirsti64() / _findnexti64() �� ����ؾ��Ѵ�.

	int handle = _findfirst(searching.c_str(), &fd);  //���� ���� �� ��� ������ ã�´�.(�ڵ鰪)

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
