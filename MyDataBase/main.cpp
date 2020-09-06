#include "MyDataBase.h"

void Log(string str) { cout << str.c_str() << endl; }
vector<string> InputCommands()
{
	//파싱 참고 사이트들 ^^
	//https://m.blog.naver.com/PostView.nhn?blogId=kks227&logNo=220245263973&proxyReferer=https:%2F%2Fwww.google.com%2F
	//https://steemit.com/kr-dev/@codingman/c-17-csv--1560125046366
	//https://www.it-swarm.dev/ko/c%2B%2B/c-%EC%97%90%EC%84%9C-csv-%ED%8C%8C%EC%9D%BC%EC%9D%84-%EC%9D%BD%EA%B3%A0-%EA%B5%AC%EB%AC%B8-%EB%B6%84%EC%84%9D%ED%95%98%EB%A0%A4%EB%A9%B4-%EC%96%B4%EB%96%BB%EA%B2%8C%ED%95%B4%EC%95%BC%ED%95%A9%EB%8B%88%EA%B9%8C/967277856/
	
	cout << ">> ";

	vector<string> commands;
	string command;
	getline(cin, command);


	//예외처리 ^^
	if (command == "" || command == " ")
		return commands;


	//공백 구분하여 commands 벡터에 저장
	int str_cnt = 0;
	char* str_buff = new char[1000];
	strcpy(str_buff, command.c_str());

	char* tok = strtok(str_buff, " ");
	strupr(tok);  // <<--- 이 함수는 문자열을 대문자로 바꿔주는 함수 cstring 내장 함수
	while (tok != nullptr) {
		commands.push_back(string(tok));
		tok = strtok(nullptr, " ");
	}
	delete[] str_buff;
	return commands;
}

void CommandCalc(vector<string> msg)
{
	if (msg.size() <= 0)
		return;

	if ((msg[0]) == "EXIT")
		exit(0);
	else if (msg[0] == "USE")
	{
		//TODO 벡터 길이 벗어나는 예외처리 할 것
		if (DBMS::Ins()->LoadCSV(msg[1]))
			Log("File Succese Load!");
		else
			Log("File No Load..(File Dir : " + msg[1] + " )");
	}
}

int main()
{
	Log("Hello! My Database");

	while (1)
	{
		CommandCalc(InputCommands());
	}

	Log("My DataBase Done...");
	return 1;
}