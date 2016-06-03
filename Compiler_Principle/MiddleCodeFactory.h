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
	CSymbolTable m_PropertyTable;					//���Ա�
private:
	//��������
	vector<string> m_middleCode;					//�м����
	int m_LableNum;									//��ǰ����ı�ǩ���
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
	void OutMiddleCode();		//����м����
};

