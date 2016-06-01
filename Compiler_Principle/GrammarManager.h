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
	//��������
	vector<string> m_middleCode;					//�м����
private:
	const CReceivingData *m_ReceivingData;			//���Ե��ôʷ������Ľ������
	CSymbolTable m_PropertyTable;					//���Ա�
	int m_nowIndex;									//���Ƶ��ʵķ���λ��
	bool m_isHaveWrong;								//�Ƿ�������˴���
	int m_LableNum;									//��ǰ����ı�ǩλ��
//��������ݹ��½�
public:
	void Init(const CReceivingData *ptr);
	void Process();
	int GetNextSymbol() { return ++m_nowIndex; }	//�Żص�ǰ������ַ����һλ
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

//����&�м����,���Է���
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
	void OutMiddleCode();		//����м����
};

