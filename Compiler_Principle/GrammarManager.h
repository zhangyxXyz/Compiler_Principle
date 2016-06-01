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
	int m_LableNum;									//当前处理的标签位置
//语义分析递归下降
public:
	void Init(const CReceivingData *ptr);
	void Process();
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
	void Pop() { m_middleCode.push_back(string("        POP")); }
	int Look(string word) { return m_PropertyTable.GetAddByNmme(word); }
	void Sto(int address) { m_middleCode.push_back(string("        STO ") + address); }
	void Gt() { m_middleCode.push_back(string("        GT")); }
	void Les() { m_middleCode.push_back(string("        LES")); }
	void Ge() { m_middleCode.push_back(string("        GE")); }
	void Le() { m_middleCode.push_back(string("        LE")); }
	void Eq() { m_middleCode.push_back(string("        EQ")); }
	void Noteq() { m_middleCode.push_back(string("        NOTEQ")); }
	void Add() { m_middleCode.push_back(string("        ADD")); }
	void Sub() { m_middleCode.push_back(string("        SUB")); }
	void Mult() { m_middleCode.push_back(string("        MULT")); }
	void Div() { m_middleCode.push_back(string("        DIV")); }
	void Load(int address) { m_middleCode.push_back(string("        LOAD ") + address); }
	void Loadi(int num) { m_middleCode.push_back(string("        LOADI ") + num); }
	void Brf(string label) { m_middleCode.push_back(string("        BRF ") + label); }
	void Br(string label) { m_middleCode.push_back(string("        BR ") + label); }
	void Setlabel(string label) { m_middleCode.push_back(label + ":"); }
	void In() { m_middleCode.push_back(string("        IN")); }
	void Out() { m_middleCode.push_back(string("        OUT")); }

	string newLabel() { return string("LABEL") + m_LableNum++; }
public:
	void OutMiddleCode();		//输出中间代码
};

