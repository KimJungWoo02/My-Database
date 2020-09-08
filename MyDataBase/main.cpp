#include "MyDataBase.h"

void Log(string str, TYPE type, CONSOLECOLOR color)
{ 
	switch (type)
	{
	case TYPE::E_MSG:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		cout << "[MSG] ";
		break;
	case TYPE::E_WARNING:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
		cout << "[WARNING] ";
		break;
	case TYPE::E_ERROR:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
		cout << "[ERROR] ";
		break;
	case TYPE::E_SUCCESE:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
		cout << "[SUCCESE] ";
		break;
	case TYPE::E_NORMAL:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		break;
	}
	cout << str.c_str() << endl; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

vector<string> InputCommands()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	cout << " >> ";
	vector<string> commands;
	string command;
	getline(cin, command);

	//����ó�� ^^
	if (command == "" || command == " ")
		return commands;

	//���� �����Ͽ� commands ���Ϳ� ����
	int str_cnt = 0;
	char* str_buff = new char[1000];
	strcpy(str_buff, command.c_str());

	strupr(str_buff);	//<<--- �� �Լ��� ���ڿ��� �빮�ڷ� �ٲ��ִ� �Լ� cstring ���� �Լ�
	char* tok = strtok(str_buff, " ");
	while (tok != nullptr) {
		commands.push_back(string(tok));
		tok = strtok(nullptr, " ");
	}
	delete[] str_buff;
	return commands;
}

//TODO msg���� ���� ����� ����ó�� �� ��
bool CommandCalc(vector<string> msg)
{
	if (msg.size() == 0)
		return true;

	if ((msg[0]) == "EXIT")
		return false;
	else if (msg[0] == "HELP" || msg[0] == "?")
		DBMS::Ins()->Help();
	else if (msg[0] == "USE")
	{

	}
	else if (msg[0] == "SHOW")
	{
		if (msg[1] == "TABLES")
			DBMS::Ins()->ShowTables();
	}
	else if (msg[0] == "SELECT")
	{

	}
	else if (msg[0] == "LOAD")
	{
		if (DBMS::Ins()->LoadCSV(msg[1]))
			Log("File Succese Load!", TYPE::E_SUCCESE);
		else
			Log("File Not found..(File path : " + msg[1] + " )", TYPE::E_ERROR);
	}
	else
	{
		string s;
		for (auto it : msg)
			s += it + " ";
		Log(s + "��(��) �߸� �� ��ɾ��Դϴ�. ��ɾ ������ 'help' �Ǵ� '?'�� �Է��ϼ���.", TYPE::E_ERROR);
	}
	return true;
}

int main()
{
	Log("Hello! My Database", TYPE::E_NORMAL, CONSOLECOLOR::JADE);

	while (CommandCalc(InputCommands()))
	{

	}

	Log("My DataBase Done...", TYPE::E_NORMAL, CONSOLECOLOR::LIGHT_RED);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	exit(0);
	return 1;
}