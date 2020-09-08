#pragma once
class DBMS : public Singleton<DBMS>
{
public:
	DBMS();
	~DBMS();

	bool LoadCSV(const string path);
	void ShowTable(const string name);
	void Clear();
	void ShowTables();
	void Help() const;
	vector<string> GetFilesInDirectory(const string _path, const string _filter);
private:
	string Curpath;
	vector<vector<vector<string>>> vCurDataBase;
	vector<string> vTableName;
};

