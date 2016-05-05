#include "stdafx.h"
#include "SyntaxAnalysis.h"


CSyntaxAnalysis::CSyntaxAnalysis()
{
}


CSyntaxAnalysis::~CSyntaxAnalysis()
{
}


void CSyntaxAnalysis::Init()
{
	m_LL1_Table.Init();
}
