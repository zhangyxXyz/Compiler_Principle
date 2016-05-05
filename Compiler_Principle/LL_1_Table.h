#pragma once
#include "NounMapSet.h"
#include "FileDatabyTxt.h"
//���ʽ��Ϣ
class CExpr
{
public:
	CExpr() {}
	~CExpr() {}
	string left;
	vector<string> right;
};

class CLL_1_Table
{
public:
	CLL_1_Table();
	~CLL_1_Table();
	CNounMapSet	m_NoumMapSet;
	CExpr m_Expr[25][27];			//���ʽ�ڽӾ���
private:
	CFileDatabyTxt m_file;
public:
	void Init();
	void ADD_Tablelayer(const string& name, const string& symbol, const vector<string> &vec);
	void OutTable();
};
