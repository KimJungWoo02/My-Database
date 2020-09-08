#include "MyDataBase.h"

void Log(string str, TYPE type, CONSOLECOLOR color)
{ 
	switch (type)
	{
	case TYPE::E_INFO:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		cout << "[INFO] ";
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

CommandInfo InputCommands()
{
	cout << " >> ";
	CommandInfo commands;
	string command;
	getline(cin, command);

	//예외처리 ^^
	if (command == "" || command == " ")
		return commands;

	//공백 구분하여 commands 벡터에 저장
	int str_cnt = 0;
	char* str_buff = new char[1000];
	strcpy(str_buff, command.c_str());

	char* tok = strtok(str_buff, " ");		//문자열 슬라이싱
	while (tok != nullptr) {
		commands.Originalcommands.push_back(string(tok));
		strupr(tok);	//<<--- 이 함수는 문자열을 대문자로 바꿔주는 함수 cstring 내장 함수
		commands.commands.push_back(string(tok));
		tok = strtok(nullptr, " ");	// nullptr을 주게되면 내부 버퍼에 저장되어있는 포인터에서 다음 " "를 찾고 그 뒤에 문자열의 주소를 반환하게 된다.
	}
	delete[] str_buff;
	return commands;
}

//TODO msg벡터 길이 벗어나는 예외처리 할 것
bool CommandCalc(CommandInfo msg)
{
	if (msg.commands.size() == 0)
		return true;

	if ((msg.commands[0]) == "EXIT")
		return false;
	else if (msg.commands[0] == "HELP" || msg.commands[0] == "?")
		DBMS::Ins()->Help();
	else if (msg.commands[0] == "USE")
		DBMS::Ins()->SetuseTable(msg.commands[1]);
	else if (msg.commands[0] == "SHOW")
	{
		if (msg.commands[1] == "TABLES")
			DBMS::Ins()->ShowTables();
	}
	else if (msg.commands[0] == "SELECT")
	{
		if (msg.commands[2] == "FROM")
			DBMS::Ins()->Select(msg.Originalcommands[1], msg.Originalcommands[3]);
	}
	else if (msg.commands[0] == "LOAD")
	{
		if (DBMS::Ins()->LoadCSV(msg.Originalcommands[1]))
			Log("File Succese Load!", TYPE::E_SUCCESE);
		else
			Log("File Not found..(File path : " + msg.Originalcommands[1] + " )", TYPE::E_ERROR);
	}
	else if (msg.commands[1] == "DESCRIBE" || msg.commands[1] == "DESC")
	{
		DBMS::Ins()->ShowTableRow(msg.commands[1]);
	}
	else
	{
		string s;
		for (auto it : msg.Originalcommands)
			s += it + " ";
		Log(s + "은(는) 잘못 된 명령어입니다. 명령어를 볼려면 'help' 또는 '?'를 입력하세요.", TYPE::E_ERROR);
	}
	return true;
}

int main()
{
	//system("mode con: cols=120 lines=30 | title My DataBase");
	Log("Hello! My Database", TYPE::E_NORMAL, CONSOLECOLOR::JADE);
	while (CommandCalc(InputCommands()))
	{

	}

	Log("My DataBase Done...", TYPE::E_NORMAL, CONSOLECOLOR::LIGHT_RED);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	exit(0);
	return 1;
}