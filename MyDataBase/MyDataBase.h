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

using namespace std;

extern void Log(string str, TYPE type = TYPE::E_NORMAL, CONSOLECOLOR color = CONSOLECOLOR::WHITE);


#include "DBMS.h"