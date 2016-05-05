#pragma once
#include "LL_1_Table.h"
class CSyntaxAnalysis
{
public:
	CSyntaxAnalysis();
	~CSyntaxAnalysis();
private:
	CLL_1_Table m_LL1_Table;
public:
	void Init();
};

