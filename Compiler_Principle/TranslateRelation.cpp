#include "stdafx.h"
#include "TranslateRelation.h"


CTranslateRelation::CTranslateRelation()
{
}


CTranslateRelation::~CTranslateRelation()
{
	//ƒ⁄¥Ê Õ∑≈£¨÷∏’Î÷√ø’
	for (int i = 0;i < m_stamanager->GetSize();i++)
		delete[] m_tranlist[i];
	delete[] m_tranlist;
	m_stamanager = nullptr;
	m_chaTable = nullptr;
}


void CTranslateRelation::TranslateRelationInit(CCharacterTable& chaTable, CStateManger& stamanager)
{
	m_stamanager = &stamanager;
	m_chaTable = &chaTable;
	if (m_stamanager == nullptr || m_chaTable == nullptr) return;
	m_tranlist = new CSTATE*[m_stamanager->GetSize()];
	for (int i = 0;i < m_stamanager->GetSize();i++)
	{
		m_tranlist[i] = new CSTATE[m_chaTable->GetTableSize() + 1];
		for (int j = 0;j < m_chaTable->GetTableSize() + 1;j++)m_tranlist[i][j] = CSTATE("WRONG", false);
	}
	for (int i = 'a';i <= 'z';i++)
	{
		TranslateRelationBulit("START", "IDENTIFIER", char(i));
		TranslateRelationBulit("IDENTIFIER", "IDENTIFIER", char(i));

	}
	for (int i = 'A';i <= 'Z';i++)
	{
		TranslateRelationBulit("START", "IDENTIFIER", char(i));
		TranslateRelationBulit("IDENTIFIER", "IDENTIFIER", char(i));
	}

	for (int i = '1'; i <= '9'; i++)
	{
		TranslateRelationBulit("START", "NUM_NORMAL", char(i));
	}

	TranslateRelationBulit("START", "NUM_ZERO", '0');

	for (int i = '0'; i <= '9'; i++)
	{
		TranslateRelationBulit("NUM_NORMAL", "NUM_NORMAL", char(i));
		TranslateRelationBulit("IDENTIFIER", "IDENTIFIER", char(i));
	}
	TranslateRelationBulit("START", "DELIMITER", '(');
	TranslateRelationBulit("START", "DELIMITER", ')');
	TranslateRelationBulit("START", "DELIMITER", '{');
	TranslateRelationBulit("START", "DELIMITER", '}');
	TranslateRelationBulit("START", "DELIMITER", ';');
	TranslateRelationBulit("START", "OPERATOR", '+');
	TranslateRelationBulit("START", "OPERATOR", '-');
	TranslateRelationBulit("START", "OPERATOR", '*');

	TranslateRelationBulit("START", "UNDEFINE_MARK", '!');
	TranslateRelationBulit("START", "OPERATOR_TWO_BUFF", '>');
	TranslateRelationBulit("START", "OPERATOR_TWO_BUFF", '<');
	TranslateRelationBulit("START", "OPERATOR_TWO_BUFF", '=');

	TranslateRelationBulit("OPERATOR_TWO_BUFF", "OPERATOR", '=');
	TranslateRelationBulit("UNDEFINE_MARK", "OPERATOR", '=');

	TranslateRelationBulit("START", "OPERATOR_DIV_NOTE_BUFF", '/');
	TranslateRelationBulit("OPERATOR_DIV_NOTE_BUFF", "NOTE_START", '*');

	TranslateRelationBulit("NOTE_START", "NOTE_END_BUFF", '*');

	TranslateRelationBulit("NOTE_END_BUFF", "NOTE_END", '/');
	TranslateRelationBulit("START", "SPACE", ' ');
	TranslateRelationBulit("SPACE", "SPACE", ' ');
	TranslateRelationBulit("START", "SPACE", '\n');
	TranslateRelationBulit("SPACE", "SPACE", '\n');

}

void CTranslateRelation::TranslateRelationBulit(const string& l, const string& r, const char& conduct)
{
	m_tranlist[m_stamanager->GetNumByName(l)][m_chaTable->GetNumByChar(conduct)] = m_stamanager->GetStateByName(r);
}


CSTATE CTranslateRelation::GetNextState(const CSTATE& now_State, const char& ptr)
{
	return m_tranlist[m_stamanager->GetNumByState(now_State)][m_chaTable->GetNumByChar(ptr)];
}
