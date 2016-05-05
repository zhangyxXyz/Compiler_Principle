#include "stdafx.h"
#include "NounMapSet.h"


CNounMapSet::CNounMapSet()
{
}


CNounMapSet::~CNounMapSet()
{
}


void CNounMapSet::Init()
{
	int cnt = -1;
	m_Symbol.clear();
	m_intSymbol.clear();
	m_Symbol.insert(pair<string, int>("program", ++cnt));
	m_Symbol.insert(pair<string, int>("declaration_list", ++cnt));
	m_Symbol.insert(pair<string, int>("statement_list", ++cnt));
	m_Symbol.insert(pair<string, int>("A", ++cnt));
	m_Symbol.insert(pair<string, int>("declaration_stat", ++cnt));
	m_Symbol.insert(pair<string, int>("B", ++cnt));
	m_Symbol.insert(pair<string, int>("statement", ++cnt));
	m_Symbol.insert(pair<string, int>("if_stat", ++cnt));
	m_Symbol.insert(pair<string, int>("while_stat", ++cnt));
	m_Symbol.insert(pair<string, int>("for_stat", ++cnt));
	m_Symbol.insert(pair<string, int>("read_stat", ++cnt));
	m_Symbol.insert(pair<string, int>("write_stat", ++cnt));
	m_Symbol.insert(pair<string, int>("compound_stat", ++cnt));
	m_Symbol.insert(pair<string, int>("expression_stat", ++cnt));
	m_Symbol.insert(pair<string, int>("expr", ++cnt));
	m_Symbol.insert(pair<string, int>("bool_expr", ++cnt));
	m_Symbol.insert(pair<string, int>("additive_expr", ++cnt));
	m_Symbol.insert(pair<string, int>("E", ++cnt));
	m_Symbol.insert(pair<string, int>("term", ++cnt));
	m_Symbol.insert(pair<string, int>("C", ++cnt));
	m_Symbol.insert(pair<string, int>("factor", ++cnt));
	m_Symbol.insert(pair<string, int>("D", ++cnt));
	cnt = -1;
	m_intSymbol.insert(pair<string, int>("int", ++cnt));
	m_intSymbol.insert(pair<string, int>("if", ++cnt));
	m_intSymbol.insert(pair<string, int>("else", ++cnt));
	m_intSymbol.insert(pair<string, int>("while", ++cnt));
	m_intSymbol.insert(pair<string, int>("for", ++cnt));
	m_intSymbol.insert(pair<string, int>("write", ++cnt));
	m_intSymbol.insert(pair<string, int>("read", ++cnt));
	m_intSymbol.insert(pair<string, int>("ID", ++cnt));
	m_intSymbol.insert(pair<string, int>("NUM", ++cnt));
	m_intSymbol.insert(pair<string, int>("(", ++cnt));
	m_intSymbol.insert(pair<string, int>(")", ++cnt));
	m_intSymbol.insert(pair<string, int>("{", ++cnt));
	m_intSymbol.insert(pair<string, int>("}", ++cnt));
	m_intSymbol.insert(pair<string, int>(">", ++cnt));
	m_intSymbol.insert(pair<string, int>("<", ++cnt));
	m_intSymbol.insert(pair<string, int>(">=", ++cnt));
	m_intSymbol.insert(pair<string, int>("<=", ++cnt));
	m_intSymbol.insert(pair<string, int>("==", ++cnt));
	m_intSymbol.insert(pair<string, int>("!=", ++cnt));
	m_intSymbol.insert(pair<string, int>("+", ++cnt));
	m_intSymbol.insert(pair<string, int>("-", ++cnt));
	m_intSymbol.insert(pair<string, int>("*", ++cnt));
	m_intSymbol.insert(pair<string, int>("/", ++cnt));
	m_intSymbol.insert(pair<string, int>(";", ++cnt));
	m_intSymbol.insert(pair<string, int>("#", ++cnt));
}


int CNounMapSet::GetSynbolIDByName(const string& name)
{
	return m_Symbol[name];
	//return 0;
}


string CNounMapSet::GetSymbolNameByID(const int& ID)
{
	//由于对应类型的操作没有重载，考虑到数据较小，使用范围for语句遍历输出
	for (auto iter : m_Symbol)
	{
		if (iter.second == ID)
			return iter.first;
	}
	return string();
}


int CNounMapSet::GetIntSymbolIDByName(const string& name)
{
	return m_intSymbol[name];
	//return 0;
}


string CNounMapSet::GetIntSymbolNameByID(const int& ID)
{
	for (auto iter : m_intSymbol)
	{
		if (iter.second == ID)
			return iter.first;
	}
	return string();
}
