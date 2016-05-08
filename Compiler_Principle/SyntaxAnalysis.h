#pragma once
#include "LL_1_Table.h"
#include "ReceivingData.h"
class CSyntaxAnalysis
{
public:
	CSyntaxAnalysis();
	~CSyntaxAnalysis();
private:
	CLL_1_Table m_LL1_Table;
	const CReceivingData *m_ReceivingData;
	stack<string> m_SymbolStack;
	bool m_isFail;									//”Ô∑®∑÷Œˆ «∑Ò ß∞‹
public:
	void Init(const CReceivingData *ptr);
	void Process();
};
