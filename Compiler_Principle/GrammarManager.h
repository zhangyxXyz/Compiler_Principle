#pragma once
#include "ReceivingData.h"
#include "MiddleCodeFactory.h"
#define WORDDATA m_ReceivingData->m_ProcessedData[m_nowIndex]
#define PREWORDDATA m_ReceivingData->m_ProcessedData[m_nowIndex-1]

class CGrammarManager
{
public:
	CGrammarManager();
	~CGrammarManager();
private:
	const CReceivingData *m_ReceivingData;			//用以调用词法分析的结果数据
	int m_nowIndex;									//控制单词的访问位置
	bool m_isHaveWrong;								//是否分析出了错误
	bool isWrong;		
	CMiddleCodeFactory m_MiddleCodeFactory;			//中间代码加工厂
//语义分析递归下降
public:
	void Init(const CReceivingData *ptr);
	bool Process();
	int GetNextSymbol() { return ++m_nowIndex; }	//放回当前操作地址的下一位
	void Program();
	void Declaration_List();
	void Declaration_Stat();
	void Statement_List();
	void Statement();
	void If_Stat();
	void While_Stat();
	void For_Stat();
	void Write_Stat();
	void Read_Stat();
	void Compound_Stat();
	void Expression_Stat();
	void Expression();
	void Bool_Expr();
	void Oper_Additive_Expr();
	void Additive_Expr();
	void Oper_Term();
	void Term();
	void Oper_Factor();
	void Factor();
};

