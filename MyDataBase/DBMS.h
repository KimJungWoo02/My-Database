#pragma once
class DBMS : public Singleton<DBMS>
{
public:
	DBMS();
	~DBMS();

	bool LoadCSV(const string path);
	void ShowTable(const string name, const string rowname);
	void ShowTableRow(const string Tablename);
	void Clear();
	void ShowTables() const;
	void Help() const;
	void SetuseTable(string tablename);
	void Select(string rowRange, string table);
	vector<string> GetFilesInDirectory(const string _path, const string _filter);

private:
	string Curpath;
	string UseTable;
	map<string, vector<vector<string>>> mCurDataBase;
	map<string, vector<vector<string>>> mSelectDataBase;
};