#pragma once
#include "SymbolTable.h"
#include "DataProcess.h"
#include "FileDatabyTxt.h"
class CMiddleCodeFactory
{
public:
	CMiddleCodeFactory();
	~CMiddleCodeFactory();
public:
	CSymbolTable m_PropertyTable;					//属性表
private:
	//程序数据
	vector<string> m_middleCode;					//中间代码
	int m_LableNum;									//当前处理的标签编号
public:
	void Pop();
	int Look(string m_name);
	void Sto(int address);
	void Gt();
	void Les();
	void Ge();
	void Le();
	void Eq();
	void Noteq();
	void Add();
	void Sub();
	void Mult();
	void Div();
	void Load(int address);
	void Loadi(int num);
	void Brf(string label);
	void Br(string label);
	void Setlabel(string label);
	void In();
	void Out();
	string newLabel();
public:
	void OutMiddleCode();		//输出中间代码
};

