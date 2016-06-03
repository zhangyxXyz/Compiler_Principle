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
	const CReceivingData *m_ReceivingData;			//���Ե��ôʷ������Ľ������
	int m_nowIndex;									//���Ƶ��ʵķ���λ��
	bool m_isHaveWrong;								//�Ƿ�������˴���
	bool isWrong;		
	CMiddleCodeFactory m_MiddleCodeFactory;			//�м����ӹ���
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
};

