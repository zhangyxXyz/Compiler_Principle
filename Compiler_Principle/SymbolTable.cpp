#include "stdafx.h"
#include "SymbolTable.h"


CSymbolTable::CSymbolTable()
{
	m_NowAddIndex = 0;
}


CSymbolTable::~CSymbolTable()
{
	m_NowAddIndex = 0;
}


bool CSymbolTable::IsFindSymbol(const string& m_name)
{
	if (m_SymbolTable.find(m_name) != m_SymbolTable.end())
		return true;
	return false;
}


bool CSymbolTable::Insert(const string& m_name)
{
	if (!IsFindSymbol(m_name))
	{
		m_SymbolTable.insert(pair<string, Symbol>(m_name, Symbol(m_name, m_NowAddIndex++)));
		return true;
	}
	return false;
}

bool CSymbolTable::SetData(const string &m_name, const int& m_dada)
{
	try
	{
		if (!IsFindSymbol(m_name))
			throw runtime_error("非法访问数据值,标识符 " + m_name + "未定义\n");
		m_SymbolTable[m_name].m_data = m_dada;
		m_SymbolTable[m_name].m_isHaveData = true;
		return true;
	}
	catch (runtime_error err)
	{
		//cout << err.what();
		return false;
	}
}

bool CSymbolTable::IsHaveData(const string& m_name)
{
	try
	{
		if (!IsFindSymbol(m_name))
			throw runtime_error("非法访问数据值,标识符 " + m_name + "未定义\n");
		return m_SymbolTable[m_name].m_isHaveData;
	}
	catch (runtime_error err)
	{
		//cout << err.what();
		return false;
	}
}

int CSymbolTable::GetAddByNmme(const string& m_name)
{
	try
	{
		if (!IsFindSymbol(m_name))
			throw runtime_error("非法访问地址值,标识符 " + m_name + "未定义\n");
		return m_SymbolTable[m_name].m_Add;
	}
	catch (runtime_error err)
	{
		//cout << err.what();
		return -1;
	}
}
