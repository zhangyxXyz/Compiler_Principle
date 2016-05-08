#include "stdafx.h"
#include "First_Follow.h"


CFirst_Follow::CFirst_Follow()
{
}


CFirst_Follow::~CFirst_Follow()
{
}


void CFirst_Follow::Init()
{
	//FIRST集合
	m_First[0] = { "{" };
	m_First[1] = { "int" };
	m_First[2] = { "if","while","for","read","write","{",";","ID","NUM","(" };
	m_First[3] = { "int" };
	m_First[4] = { "if","while","for","read","write","{",";","ID","NUM","(" };
	m_First[5] = { "if" };
	m_First[6] = { "else" };
	m_First[7] = { "while" };
	m_First[8] = { "for" };
	m_First[9] = { "read" };
	m_First[10] = { "write" };
	m_First[11] = { "{" };
	m_First[12] = { ";","(","ID","NUM" };
	m_First[13] = { "ID","NUM","(" };
	m_First[14] = { "ID","NUM","(" };
	m_First[15] = { "ID","NUM","(" };
	m_First[16] = { ">","<",">=","<=","==","!=" };
	m_First[17] = { "ID","NUM","(" };
	m_First[18] = { "+","-" };
	m_First[19] = { "ID","NUM","(" };
	m_First[20] = { "*","/" };

	//FOLLOW集合
	m_Follow[1] = { "if","while","for","read","write","{","}",";","ID","NUM","(" };
	m_Follow[2] = { "}" };
	m_Follow[3] = { "int","if","while","for","read","write","{","}",";","ID","NUM","(" };
	m_Follow[4] = { "if","else","while","for","read","write","{","}",";","ID","NUM","(" };
	m_Follow[5] = { "if","else","while","for","read","write","{","}",";","ID","NUM","(" };
	m_Follow[6] = { "if","else","while","for","read","write","{","}",";","ID","NUM","(" };
	m_Follow[7] = { "if","else","while","for","read","write","{","}",";","ID","NUM","(" };
	m_Follow[8] = { "if","else","while","for","read","write","{","}",";","ID","NUM","(" };
	m_Follow[9] = { "if","else","while","for","read","write","{","}",";","ID","NUM","(" };
	m_Follow[10] = { "if","else","while","for","read","write","{","}",";","ID","NUM","(" };
	m_Follow[11] = { "if","else","while","for","read","write","{","}",";","ID","NUM","(" };
	m_Follow[12] = { "if","else","while","for","read","write","{","}",";","ID","NUM","(" };
	m_Follow[13] = { ";",")" };
	m_Follow[14] = { ";" ,")" };
	m_Follow[15] = { ">","<",">=","<=","==","!=" ,";" ,")" };
	m_Follow[16] = { ";" };
	m_Follow[17] = { "+","-",";",")",">","<",">=","<=","==","!=" };
	m_Follow[18] = { ";",")",">","<",">=","<=","==","!=" };
	m_Follow[19] = { "+","-","*","/",";",")",">","<",">=","<=","==","!=" };
	m_Follow[20] = { "+","-",";",")",">","<",">=","<=","==","!=" };
}


bool CFirst_Follow::Search_First(const int&ID, const string& ptr)
{
	if (find(m_First[ID].begin(), m_First[ID].end(), ptr) != m_First[ID].end())
		return true;
	return false;
}


bool CFirst_Follow::Search_Follow(const int&ID, const string& ptr)
{
	if (find(m_Follow[ID].begin(), m_Follow[ID].end(), ptr) != m_Follow[ID].end())
		return true;
	return false;
}


void CFirst_Follow::vec_clear()
{
	for (int i = 0;i < 22;i++)
	{
		m_First[i].clear();
		m_Follow[i].clear();
	}
}
