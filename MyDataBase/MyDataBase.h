#pragma once
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <Windows.h>
#include <vector>
#include <List>
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

extern void Log(string str);

#include "Command.h"

#include "DBMS.h"