#pragma once
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <map>
#include <io.h>		//����,�������� ������ �� �� ���̴� �������


#include "enum.h"
#pragma warning(disable : 4996)
using namespace std;

struct CommandInfo
{
	CommandInfo(vector<string> uprcmd, vector<string> originalcmd)
	{
		commands = uprcmd;
		Originalcommands = originalcmd;
	}
	CommandInfo()
	{

	}
	vector<string> commands;
	vector<string> Originalcommands;
};

template<class T>
class Singleton
{
	static T* instance;
public:
	static T* Ins()
	{
		if (instance == nullptr)
			instance = new T();
		return instance;
	}
};
template <class T> T* Singleton<T>::instance = nullptr;


extern void Log(string str, TYPE type = TYPE::E_NORMAL, CONSOLECOLOR color = CONSOLECOLOR::WHITE);


#include "DBMS.h"