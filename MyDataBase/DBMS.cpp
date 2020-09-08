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
	//파싱 참고 사이트들 ^^
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
	Log("					< 도움말 >					", TYPE::E_NORMAL, LIGHT_YELLOW);
	Log(" LOAD (FOLDER PATH) - FOLDER PATH(상대경로)에 있는 모든 .csv파일을 읽어들여 옵니다.", TYPE::E_NORMAL, LIGHT_YELLOW);
	Log(" USE (TABLE NAME) - TABLE NAME으로 된 .csv파일을 읽어온 뒤 선택합니다. (절대경로 or 상대경로)", TYPE::E_NORMAL, LIGHT_YELLOW);
	Log(" SHOW TABLES - 선택된 테이블의 COLUME을 보여줍니다.", TYPE::E_NORMAL, LIGHT_YELLOW);
	Log(" DESC (TABLENAME) | DESCRIBE (TABLENAME) - 입력한 TABLENAME에 어떤 row가 있는지 보여줍니다.", TYPE::E_NORMAL, LIGHT_YELLOW);
	Log(" SELECT (TABLE ROW) FROM (TABLE NAME)- ", TYPE::E_NORMAL, LIGHT_YELLOW);
	Log(" EXIT - 프로그램을 종료합니다.", TYPE::E_NORMAL, LIGHT_YELLOW);
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
	//참고 사이트 : https://rex0725.tistory.com/2

	string searching = "./" + _path + _filter;	//검색할 폴더의 경로, ./는 앞에 상대 경로를 없앤것 함수가 절대경로만 인식함
	vector<string> return_;	//리턴할 벡터 정의

	_finddata_t fd;		//읽어온 파일의 데이터가 있는 변수 _finddata_t는 구조체
	//여기에 쓰인 함수들은 3기가가 넘으면 사용을 할 수 앖음(무거운 파일) 그럴려면 _findfirsti64() / _findnexti64() 를 사용해야한다.

	int handle = _findfirst(searching.c_str(), &fd);  //현재 폴더 내 모든 파일을 찾는다.(핸들값)

	if (handle == -1)    return return_;	//검색 조건에 맞는 파일을 발견했으면 0을 리턴, 아니면 -1을 리턴(핸들값)

	int result = 0;
	do
	{
		return_.push_back("./" + _path + fd.name);		//return_에 읽은 파일의 이름을 넣어줌
		result = _findnext(handle, &fd);	//검색 조건에 맞는 파일을 발견했으면 0을 리턴, 아니면 -1을 리턴(핸들값)
	} while (result != -1);

	_findclose(handle);		//검색 핸들을 닫는 함수

	return return_;
}
