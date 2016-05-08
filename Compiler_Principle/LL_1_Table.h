#pragma once
#include "NounMapSet.h"
#include "FileDatabyTxt.h"
#include "First_Follow.h"
//表达式信息
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
	CFirst_Follow m_First_Follow;
	CExpr m_Expr[25][27];			//表达式邻接矩阵
private:
	CFileDatabyTxt m_file;
public:
	void Init();
	void ADD_Tablelayer(const string& name, const string& symbol, const vector<string> &vec);
	void OutTable();
};
