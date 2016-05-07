#include "stdafx.h"
#include "SyntaxAnalysis.h"


CSyntaxAnalysis::CSyntaxAnalysis()
{
}


CSyntaxAnalysis::~CSyntaxAnalysis()
{
	m_ReceivingData = nullptr;
	delete m_ReceivingData;
}


void CSyntaxAnalysis::Init(const CReceivingData *ptr)
{
	m_LL1_Table.Init();
	m_ReceivingData = ptr;
	m_isFail = false;
}


void CSyntaxAnalysis::Process()
{
	m_SymbolStack.push("program");
	for (auto iter = m_ReceivingData->m_ProcessedData.begin();;)
	{
		//ջ��Ԫ��Ϊ���ս��
		if (m_SymbolStack.empty())
		{
			if (!m_isFail && iter == m_ReceivingData->m_ProcessedData.end())
				cout << "�﷨�������: ACCEPT\n";
			else cout << "�﷨�������: FAIL\n";
			return;
		}
		else if (!(~m_LL1_Table.m_NoumMapSet.GetIntSymbolIDByName(m_SymbolStack.top())))
		{
			try
			{
				const string nowStat = m_SymbolStack.top();
				int x = m_LL1_Table.m_NoumMapSet.GetSynbolIDByName(m_SymbolStack.top());
				int y = m_LL1_Table.m_NoumMapSet.GetIntSymbolIDByName(iter->m_type);
				m_SymbolStack.pop();
				if (m_LL1_Table.m_Expr[x][y].left == ""&&m_LL1_Table.m_Expr[x][y].right.empty())
				{
					throw runtime_error("ERROR :û�ж�Ӧת����ϵʽ-->");
				}

				if (m_LL1_Table.m_Expr[x][y].right[0] == "epsilon")
					continue;
				if (nowStat == "D"&&iter->m_type != "else")
					continue;
				//����epsilon�滻ʽ��ʽ�ұ߷�����ջ
				auto iter_ = m_LL1_Table.m_Expr[x][y].right.end() - 1;
				for (;iter_ >= m_LL1_Table.m_Expr[x][y].right.begin();iter_--)
				{
					if (nowStat == "expr"&&iter->m_type == "ID")
					{
						auto ptr_ = iter;
						if (ptr_ != m_ReceivingData->m_ProcessedData.end() && (++ptr_)->m_type != "=")
						{
							if (iter_ == m_LL1_Table.m_Expr[x][y].right.begin() + 1)
								break;
						}
					}
					m_SymbolStack.push(*iter_);
					if (iter_ == m_LL1_Table.m_Expr[x][y].right.begin())
						break;
				}
			}
			catch (runtime_error err)
			{
				cout << err.what()
					<< iter->m_type << ' ' << iter->m_name << ' ' << iter->m_indexLine << endl;
				ErrorHint();
			}
		}

		//ջ��Ԫ�����ս����
		else
		{

			if (iter->m_type != m_SymbolStack.top())
			{
				cout << "ERROR :ջ���ս���Ų�ƥ��-->" << m_SymbolStack.top() << ' ' << iter->m_type << ' ' << iter->m_name << ' ' << iter->m_indexLine << endl;
				m_isFail = true;
			}
			++iter;
			m_SymbolStack.pop();
		}
	}
}


void CSyntaxAnalysis::ErrorHint()
{

}
