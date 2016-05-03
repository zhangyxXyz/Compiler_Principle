#pragma once

//各个状态的具体参数,每一个状态都是以个CSTATE的类对象
class CSTATE
{
public:
	string m_name;			//状态名称
	bool m_isEnd;			//是否为终态
	CSTATE() = default;
	CSTATE(const string& name, const bool& judge);
	~CSTATE() {}
public:
	bool operator==(const CSTATE &state)const;
	bool operator!=(const CSTATE &state)const;
};


class CStateManger
{
public:
	CStateManger();
	~CStateManger();
	void StateInit();														//各状态初始化
private:
	map<string, int> m_stateList;											//状态映射表映射为数字
	pair<map<string, int>::iterator, map<string, int>::iterator> m_Search;	//状态对应查找索引
	vector<CSTATE> m_state;													//存放所有状态

public:
	CSTATE GetStateByNum(const int& ptr);										//通过编号索引状态
	int GetNumByState(const CSTATE& ptr);										//通过状态索引编号
	int GetSize();																//返回状态集大小，用于建立关系表
	CSTATE GetStateByName(const string& ptr);									//通过名字索引状态
	int GetNumByName(const string& ptr);										//通过名字索引编号
};


//<summary>各个状态对照及含义<summary>
///		IDENTIFIER,						标识符状态
///     RESERVED_WORD,					保留字状态
///		NUM_NORMAL,						非零数字状态
///		NUM_ZERO,						数字0状态
///		DELIMITER,						分界符状态
///		OPERATOR,						运算符状态
///		UNDEFINE_MARK,					单个！错误状态
///		OPERATOR_TWO_BUFF,				由两个字符构成的运算符的中间状态
///		OPERATOR_DIV_NOTE_BUFF,			除法符号与注释符号临界判断状态
///		NOTE_START,						注释起始状态
///		NOTE_END_BUFF,					注释终点临界状态
///		NOTE_END,						注释终结状态
///		SPACE,							空格或者换行状态
///		WRONG							错误状态
///		START							初始状态