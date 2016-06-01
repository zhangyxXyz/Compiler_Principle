#pragma once
#include "ReceivingData.h"
#include "SymbolTable.h"
#include "DataProcess.h"
#define WORDDATA m_ReceivingData->m_ProcessedData[m_nowIndex]
#define PREWORDDATA m_ReceivingData->m_ProcessedData[m_nowIndex-1]

class CGrammarManager
{
public:
	CGrammarManager();
	~CGrammarManager();
	//程序数据
	vector<string> m_middleCode;					//中间代码
private:
	const CReceivingData *m_ReceivingData;			//用以调用词法分析的结果数据
	CSymbolTable m_PropertyTable;					//属性表
	int m_nowIndex;									//控制单词的访问位置
	bool m_isHaveWrong;								//是否分析出了错误
	bool isWrong;						
	int m_LableNum;									//当前处理的标签位置
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

//语义&中间代码,属性翻译
public:
	void Pop();
	int Look(string m_name);
	void Sto(int address);
	void Gt();
	void Les();
	void Ge();
	void Le();
	void Eq();
	void Noteq();
	void Add();
	void Sub();
	void Mult();
	void Div();
	void Load(int address);
	void Loadi(int num);
	void Brf(string label);
	void Br(string label);
	void Setlabel(string label);
	void In();
	void Out();
	string newLabel();
public:
	void OutMiddleCode();		//输出中间代码
};

