#include "stdafx.h"
#include "LL_1_Table.h"


CLL_1_Table::CLL_1_Table()
{
}


CLL_1_Table::~CLL_1_Table()
{
}


void CLL_1_Table::Init()
{
	vector<string> vec;
	m_NoumMapSet.Init();

	vec = { "declaration_list","statement_list" };
	ADD_Tablelayer("program", "{", vec);
}


void CLL_1_Table::ADD_Tablelayer(const string& name, const string& symbol, vector<string> &vec)
{
	int x = m_NoumMapSet.GetSynbolIDByName(name);
	int y = m_NoumMapSet.GetIntSymbolIDByName(symbol);
	m_Expr[x][y].left = name;
	m_Expr[x][y].right = vec;
	vec.clear();
}
