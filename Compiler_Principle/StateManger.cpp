#include "stdafx.h"
#include "StateManger.h"



CStateManger::CStateManger()
{
}


CStateManger::~CStateManger()
{
}

CSTATE::CSTATE(const string& name, const bool& judge)
{
	m_name = name;
	m_isEnd = judge;
}
bool CSTATE::operator==(const CSTATE &state)const
{
	return state.m_name == m_name;
}
bool CSTATE::operator!=(const CSTATE &state)const
{
	return state.m_name != m_name;
}


void CStateManger::StateInit()
{
	int cnt = -1;
	m_state.push_back(CSTATE("WRONG", false));
	m_stateList.insert(pair<string, int>("WRONG", ++cnt));

	m_state.push_back(CSTATE("IDENTIFIER", true));
	m_stateList.insert(pair<string, int>("IDENTIFIER", ++cnt));

	m_state.push_back(CSTATE("RESERVED_WORD", true));
	m_stateList.insert(pair<string, int>("RESERVED_WORD", ++cnt));

	m_state.push_back(CSTATE("NUM_NORMAL", true));
	m_stateList.insert(pair<string, int>("NUM_NORMAL", ++cnt));

	m_state.push_back(CSTATE("NUM_ZERO", true));
	m_stateList.insert(pair<string, int>("NUM_ZERO", ++cnt));

	m_state.push_back(CSTATE("DELIMITER", true));
	m_stateList.insert(pair<string, int>("DELIMITER", ++cnt));

	m_state.push_back(CSTATE("OPERATOR", true));
	m_stateList.insert(pair<string, int>("OPERATOR", ++cnt));

	m_state.push_back(CSTATE("UNDEFINE_MARK", false));
	m_stateList.insert(pair<string, int>("UNDEFINE_MARK", ++cnt));

	m_state.push_back(CSTATE("OPERATOR_TWO_BUFF", true));
	m_stateList.insert(pair<string, int>("OPERATOR_TWO_BUFF", ++cnt));

	m_state.push_back(CSTATE("OPERATOR_DIV_NOTE_BUFF", true));
	m_stateList.insert(pair<string, int>("OPERATOR_DIV_NOTE_BUFF", ++cnt));

	m_state.push_back(CSTATE("NOTE_START", false));//×¢ÊÍ·ûÇ°°ë¶ÎÍê³É£¨·ÇÖÕ½á×´Ì¬£©
	m_stateList.insert(pair<string, int>("NOTE_START", ++cnt));

	m_state.push_back(CSTATE("NOTE_END_BUFF", false));
	m_stateList.insert(pair<string, int>("NOTE_END_BUFF", ++cnt));

	m_state.push_back(CSTATE("NOTE_END", true));
	m_stateList.insert(pair<string, int>("NOTE_END", ++cnt));

	m_state.push_back(CSTATE("SPACE", true));
	m_stateList.insert(pair<string, int>("SPACE", ++cnt));

	m_state.push_back(CSTATE("START", false));
	m_stateList.insert(pair<string, int>("START", ++cnt));
}


int CStateManger::GetSize()
{
	return m_stateList.size();
}

int CStateManger::GetNumByState(const CSTATE& ptr)
{
	return m_stateList[ptr.m_name];
}

CSTATE CStateManger::GetStateByNum(const int& ptr)
{
	return m_state[ptr];
}


CSTATE CStateManger::GetStateByName(const string& ptr)
{
	return m_state[m_stateList[ptr]];
}


int CStateManger::GetNumByName(const string& ptr)
{
	return m_stateList[ptr];
}