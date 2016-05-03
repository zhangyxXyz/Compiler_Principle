#pragma once
#include "StateManger.h"
#include "CharacterTable.h"

class CTranslateRelation
{
public:
	CTranslateRelation();
	~CTranslateRelation();
private:
	CCharacterTable *m_chaTable;		//字符集
	CStateManger *m_stamanager;			//状态集
	CSTATE **m_tranlist;				//状态转换表，利用二维动态数组建立，包含一个位置字符状态转换
public:
	void TranslateRelationInit(CCharacterTable& m_chaTable, CStateManger& m_stamanager);	//状态转换表的初始化
	void TranslateRelationBulit(const string& l, const string& r, const char& conduct);		//状态转换表的建立
	CSTATE GetNextState(const CSTATE& now_State, const char& ptr);							//在ptr条件下得到下一个状态
};