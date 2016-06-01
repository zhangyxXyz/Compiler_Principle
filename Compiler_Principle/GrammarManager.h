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
	bool isWrong;						
	int m_LableNum;									//��ǰ����ı�ǩλ��
//��������ݹ��½�
public:
	void Init(const CReceivingData *ptr);
	bool Process();
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
	void OutMiddleCode();		//����м����
};

