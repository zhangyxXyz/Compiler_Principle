#pragma once
#include "stdafx.h"

//数据处理,操作符重载
static string IntToString(int num)
{
	stringstream ss;
	ss << num;
	return  ss.str();
}
static int StringToInt(string str)
{
	stringstream ss;
	int num;
	ss << str;
	ss >> num;
	return  num;
}
static string operator+(string str, int num)
{
	return str + IntToString(num);
}
static string operator+(int num, string str)
{
	return str + IntToString(num);
}