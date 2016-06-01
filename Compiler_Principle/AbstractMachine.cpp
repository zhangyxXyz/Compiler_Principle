#include "stdafx.h"
#include "AbstractMachine.h"


CAbstractMachine::CAbstractMachine()
{
}


CAbstractMachine::~CAbstractMachine()
{
}


void CAbstractMachine::Run()
{
	cout << "用户输入TEST程序正在执行..........\n";
	m_nowIndex = 0;
	m_file.open("./message/middleCode.txt");
	if (m_file.fail()) cout << "文件打开失败\n";
	LoadCode();
	SetLabelLayer();
	int ptr = m_Codes.size();
	while (m_nowIndex < ptr)
	{
		string nowIndexCode = m_Codes[m_nowIndex++];
		Operator(nowIndexCode, m_nowIndex);
	}
	m_file.close();
}


void CAbstractMachine::LoadCode()
{
	string m_dataBuff;
	while (getline(m_file, m_dataBuff))
		m_Codes.push_back(m_dataBuff);
	for (auto &iter : m_Codes)
	{
		int ptr = m_Codes.size(), i;
		for (i = 0;i < ptr;++i)
		{
			if (iter[i] != ' ')
				break;
		}
		iter = string(iter, i, iter.size());
	}
}


void CAbstractMachine::SetLabelLayer()
{
	int ptr = m_Codes.size();
	for (int i = 0; i < ptr; ++i)
	{
		if (m_Codes[i].find("LABEL") == 0)
		{
			int labelnum = 0;
			for (int j = 5; j < m_Codes[i].size(); ++j)
				if (m_Codes[i][j] >= '0' && m_Codes[i][j] <= '9')
					labelnum = labelnum * 10 + (m_Codes[i][j] - '0');
			m_labelLayer.insert(pair<int, int>(labelnum, i));
		}
	}
}


void CAbstractMachine::Operator(string m_Code, int& m_nowIndex)
{
	if (m_Code.find("LABEL") == 0) return;
	if (m_Code.find("LOADI") == 0)
	{
		OperStack.push(atoi(m_Code.c_str() + 6));
	}
	else if (m_Code.find("LOAD") == 0)

	{
		OperStack.push(m_dataBuff[atoi(m_Code.c_str() + 5)]);
	}
	else if (m_Code.find("STO") == 0)
	{
		m_dataBuff[atoi(m_Code.c_str() + 4)] = OperStack.top();
	}
	else if (m_Code.find("POP") == 0)
	{
		OperStack.pop();
	}
	else if (m_Code.find("ADD") == 0)
	{
		int ptr = 0;
		ptr += OperStack.top();
		OperStack.pop();
		ptr += OperStack.top();
		OperStack.pop();
		OperStack.push(ptr);
	}
	else if (m_Code.find("SUB") == 0)
	{
		int ptr = 0;
		ptr -= OperStack.top();
		OperStack.pop();
		ptr += OperStack.top();
		OperStack.pop();
		OperStack.push(ptr);
	}
	else if (m_Code.find("MULT") == 0)
	{
		int ptr = 1;
		ptr *= OperStack.top();
		OperStack.pop();
		ptr *= OperStack.top();
		OperStack.pop();
		OperStack.push(ptr);
	}
	else if (m_Code.find("DIV") == 0)
	{
		int ptr = OperStack.top();
		OperStack.pop();
		ptr = OperStack.top() / ptr;
		OperStack.pop();
		OperStack.push(ptr);
	}
	else if (m_Code.find("BRF") == 0)
	{
		if (OperStack.top() == 0)
			m_nowIndex = m_labelLayer[atoi(m_Code.c_str() + 9)];
		OperStack.pop();
	}
	else if (m_Code.find("BR") == 0)
	{
		m_nowIndex = m_labelLayer[atoi(m_Code.c_str() + 8)];
	}
	else if (m_Code.find("EQ") == 0)
	{
		int num1 = OperStack.top();
		OperStack.pop();
		int num2 = OperStack.top();
		OperStack.pop();
		OperStack.push((num1 == num2 ? 1 : 0));
	}
	else if (m_Code.find("NOTEQ") == 0)
	{
		int num1 = OperStack.top();
		OperStack.pop();
		int num2 = OperStack.top();
		OperStack.pop();
		OperStack.push((num1 != num2 ? 1 : 0));
	}
	else if (m_Code.find("GT") == 0)
	{
		int num1 = OperStack.top();
		OperStack.pop();
		int num2 = OperStack.top();
		OperStack.pop();
		OperStack.push((num1 < num2 ? 1 : 0));
	}
	else if (m_Code.find("LES") == 0)
	{
		int num1 = OperStack.top();
		OperStack.pop();
		int num2 = OperStack.top();
		OperStack.pop();
		OperStack.push((num1 > num2 ? 1 : 0));
	}
	else if (m_Code.find("GE") == 0)
	{
		int num1 = OperStack.top();
		OperStack.pop();
		int num2 = OperStack.top();
		OperStack.pop();
		OperStack.push((num1 <= num2 ? 1 : 0));
	}
	else if (m_Code.find("LE") == 0)
	{
		int num1 = OperStack.top();
		OperStack.pop();
		int num2 = OperStack.top();
		OperStack.pop();
		OperStack.push((num1 >= num2 ? 1 : 0));
	}
	else if (m_Code.find("IN") == 0)
	{
		int ptr;
		cin >> ptr;
		OperStack.push(ptr);
	}
	else if (m_Code.find("OUT") == 0)
	{
		int ptr = OperStack.top();
		OperStack.pop();
		cout << ptr << endl;
	}
}