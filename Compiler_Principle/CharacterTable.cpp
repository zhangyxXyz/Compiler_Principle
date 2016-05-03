#include "stdafx.h"
#include "CharacterTable.h"


CCharacterTable::CCharacterTable()
{
}


CCharacterTable::~CCharacterTable()
{
}


void CCharacterTable::CharacterTableInit()
{
	int cnt = 0;
	for (int i = '0'; i <= '9';i++)
		m_letter.insert(pair<char, int>(char(i), cnt++));
	for (int i = 'a';i <= 'z';i++)
		m_letter.insert(pair<char, int>(char(i), cnt++));
	for (int i = 'A'; i <= 'Z'; i++)
		m_letter.insert(pair<char, int>(char(i), cnt++));
	m_letter.insert(pair<char, int>('(', cnt++));
	m_letter.insert(pair<char, int>(')', cnt++));
	m_letter.insert(pair<char, int>('{', cnt++));
	m_letter.insert(pair<char, int>('}', cnt++));
	m_letter.insert(pair<char, int>('+', cnt++));
	m_letter.insert(pair<char, int>('-', cnt++));
	m_letter.insert(pair<char, int>('*', cnt++));
	m_letter.insert(pair<char, int>('/', cnt++));
	m_letter.insert(pair<char, int>('=', cnt++));
	m_letter.insert(pair<char, int>('!', cnt++));
	m_letter.insert(pair<char, int>('>', cnt++));
	m_letter.insert(pair<char, int>('<', cnt++));
	m_letter.insert(pair<char, int>(';', cnt++));
	m_letter.insert(pair<char, int>(' ', cnt++));
	m_letter.insert(pair<char, int>('\n', cnt++));
}


int CCharacterTable::GetTableSize()
{
	return m_letter.size();
}

bool CCharacterTable::JudgeCharacter(const char& ptr)
{
	m_Search = m_letter.equal_range(ptr);
	if (m_Search.first == m_Search.second)
		return false;
	return true;
}

int CCharacterTable::GetNumByChar(const char& ptr)
{
	if (JudgeCharacter(ptr) == false)
		return m_letter.size();//不是字符表内的数字，返回最大容量，进入未知字符状态转换
	return m_letter[ptr];
}


char CCharacterTable::GetCharByNum(const int& ptr)
{
	return m_letter[ptr];
}
