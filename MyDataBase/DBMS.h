#pragma once
class DBMS : public Singleton<DBMS>
{
public:
	DBMS();
	~DBMS();
	fstream fs;
	string Curpath;

	bool LoadCSV(string path);
};

