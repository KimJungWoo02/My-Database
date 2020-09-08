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
	//path 경로에 읽이 모드로 파일을 읽어 옴

	//파싱 참고 사이트들 ^^
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
	Log("					< 도움말 >					", TYPE::E_NORMAL, LIGHT_YELLOW);
	Log(" LOAD (FOLDER PATH) - FOLDER PATH(상대경로)에 있는 모든 .csv파일을 읽어들여 옵니다.", TYPE::E_NORMAL, LIGHT_YELLOW);
	Log(" USE (TABLE NAME) - TABLE NAME으로 된 .csv파일을 읽어온 뒤 선택합니다. (절대경로 or 상대경로)", TYPE::E_NORMAL, LIGHT_YELLOW);
	Log(" SHOW TABLES - 선택된 테이블의 COLUME을 보여줍니다.", TYPE::E_NORMAL, LIGHT_YELLOW);
}

vector<string> DBMS::GetFilesInDirectory(const string _path, const string _filter)
{
	//참고 사이트 : https://rex0725.tistory.com/2

	string searching = "./" + _path + _filter;	//검색할 폴더의 경로, ./는 앞에 상대 경로를 없앤것 함수가 절대경로만 인식함
	vector<string> return_;	//리턴할 벡터 정의

	_finddata_t fd;		//읽어온 파일의 데이터가 있는 변수 _finddata_t는 구조체
	//여기에 쓰인 함수들은 3기가가 넘으면 사용을 할 수 앖음(무거운 파일) 그럴려면 _findfirsti64() / _findnexti64() 를 사용해야한다.

	long handle = _findfirst(searching.c_str(), &fd);  //현재 폴더 내 모든 파일을 찾는다.(핸들값)

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
