#include "stdafx.h"
#include "MiddleCodeFactory.h"


CMiddleCodeFactory::CMiddleCodeFactory()
{
	m_LableNum = 1;
}


CMiddleCodeFactory::~CMiddleCodeFactory()
{
}

//具体的属性文法及动作

string CMiddleCodeFactory::newLabel()
{
	return string("LABEL") + m_LableNum++;
}
void CMiddleCodeFactory::Pop()
{
	m_middleCode.push_back(string("POP"));
}
int CMiddleCodeFactory::Look(string word)
{
	return m_PropertyTable.GetAddByNmme(word);
}
void CMiddleCodeFactory::Sto(int address)
{
	m_middleCode.push_back(string("STO ") + address);
}
void CMiddleCodeFactory::Gt()
{
	m_middleCode.push_back(string("GT"));
}
void CMiddleCodeFactory::Les()
{
	m_middleCode.push_back(string("LES"));
}
void CMiddleCodeFactory::Ge()
{
	m_middleCode.push_back(string("GE"));
}
void CMiddleCodeFactory::Le()
{
	m_middleCode.push_back(string("LE"));
}
void CMiddleCodeFactory::Eq()
{
	m_middleCode.push_back(string("EQ"));
}
void CMiddleCodeFactory::Noteq()
{
	m_middleCode.push_back(string("NOTEQ"));
}
void CMiddleCodeFactory::Add()
{
	m_middleCode.push_back(string("ADD"));
}
void CMiddleCodeFactory::Sub()
{
	m_middleCode.push_back(string("SUB"));
}
void CMiddleCodeFactory::Mult()
{
	m_middleCode.push_back(string("MULT"));
}
void CMiddleCodeFactory::Div()
{
	m_middleCode.push_back(string("DIV"));
}
void CMiddleCodeFactory::Load(int address)
{
	m_middleCode.push_back(string("LOAD ") + address);
}
void CMiddleCodeFactory::Loadi(int num)
{
	m_middleCode.push_back(string("LOADI ") + num);
}
void CMiddleCodeFactory::Brf(string label)
{
	m_middleCode.push_back(string("BRF ") + label);
}
void CMiddleCodeFactory::Br(string label)
{
	m_middleCode.push_back(string("BR ") + label);
}
void CMiddleCodeFactory::Setlabel(string label)
{
	m_middleCode.push_back(label + ":");
}
void CMiddleCodeFactory::In()
{
	m_middleCode.push_back(string("IN"));
}
void CMiddleCodeFactory::Out()
{
	m_middleCode.push_back(string("OUT"));
}

//将中间代码写入文本
void CMiddleCodeFactory::OutMiddleCode()
{
	CFileDatabyTxt m_file;
	m_file.FileOpen("./message/middleCode.txt");
	for (auto iter : m_middleCode)
	{
		if (iter.find("LABEL") == 0)
			m_file.FileWrite(iter + "\n");
		else
			m_file.FileWrite("      " + iter + "\n");
	}
	m_file.FileClose();
}
