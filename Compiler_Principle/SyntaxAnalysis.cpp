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
	string _state;
	for (auto iter = m_ReceivingData->m_ProcessedData.begin();;)
	{
		//ջ��Ԫ��Ϊ���ս��
		if (m_SymbolStack.empty())
		{
			if (!m_isFail && iter == m_ReceivingData->m_ProcessedData.end())
				cout << "�﷨�������: ACCEPT\n";
			else if (iter != m_ReceivingData->m_ProcessedData.end())
			{
				cout << "Line " << ((--iter)->m_indexLine) << ":��������������������׸��" << endl;
				cout << "�﷨�������: FAIL\n";
			}
			else cout << "�﷨�������: FAIL\n";
			return;
		}
		//Դ�����������������ȱʡ
		else if (iter == m_ReceivingData->m_ProcessedData.end() && !m_SymbolStack.empty())
		{
			cout << "Line " << ((--iter)->m_indexLine) << ":���������������������ȱ��" << endl;
			return;
		}
		//����������
		else if (!(~m_LL1_Table.m_NoumMapSet.GetIntSymbolIDByName(m_SymbolStack.top())))
		{
			try
			{
				const string nowStat = m_SymbolStack.top();
				_state = nowStat;
				int x = m_LL1_Table.m_NoumMapSet.GetSynbolIDByName(m_SymbolStack.top());
				int y = m_LL1_Table.m_NoumMapSet.GetIntSymbolIDByName(iter->m_type);
				m_SymbolStack.pop();
				if (nowStat == "D"&&iter->m_type != "else")
					continue;
				if (m_LL1_Table.m_Expr[x][y].left == ""&&m_LL1_Table.m_Expr[x][y].right.empty())
				{
					throw runtime_error("ERROR :û�ж�Ӧת����ϵʽ-->");
				}
				if (m_LL1_Table.m_Expr[x][y].right[0] == "epsilon")
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
				//����ָ�
				//cout << err.what()
				//	<< iter->m_type << ' ' << iter->m_name << ' ' << iter->m_indexLine << endl;

				auto iter__ = iter;
				int x_ = m_LL1_Table.m_NoumMapSet.GetSynbolIDByName(_state);
				int y_ = m_LL1_Table.m_NoumMapSet.GetIntSymbolIDByName(iter__->m_type);

				//LL(1)����û�ж�Ӧ��ת����ϵʽ��FOLLOW���в��ң����в���ʵ�ִ���ָ�
				if (m_LL1_Table.m_First_Follow.Search_Follow(x_, iter->m_type))
				{
					cout << "Line " << iter->m_indexLine << ":�� '" << iter->m_type << "' ǰȱʧ����﷨�ṹ" << endl;
					//m_SymbolStack.pop();�ڶ�ȡʱ�Ѿ�����
					m_isFail = true;
				}
				else
				{
					cout << "Line " << iter->m_indexLine << ": '" << iter->m_type << "' �Ƿ�����" << endl;
					++iter;
					m_SymbolStack.push(_state);
					m_isFail = true;
				}
			}
		}

		//ջ��Ԫ�����ս����
		else
		{

			if (iter->m_type != m_SymbolStack.top())
			{
				auto iter__ = iter;
				string ptr, ptr_;
				if (m_SymbolStack.size() > 1)
				{
					ptr = m_SymbolStack.top();
					m_SymbolStack.pop();
					ptr_ = m_SymbolStack.top();
					m_SymbolStack.push(ptr);
				}
				//���Ŵ�λ����
				if (ptr != ""&&ptr_ != "" && (iter__ + 1) != m_ReceivingData->m_ProcessedData.end()
					&& ptr == (iter + 1)->m_type&&ptr_ == iter->m_type)
				{
					cout << "Line " << iter->m_indexLine << ": '" << ptr << "' �� '" << ptr_ << "' ��λ" << endl;
					iter += 2;
					m_SymbolStack.pop(), m_SymbolStack.pop();
				}
				//�ഩ���Ŵ���
				else if ((iter__ + 1) != m_ReceivingData->m_ProcessedData.end() && (iter__ + 1)->m_type == m_SymbolStack.top())
				{
					cout << "Line " << iter->m_indexLine << ":��������� '" << iter->m_type << "' " << endl;
					++iter;
				}
				//�����Ŵ���
				else if ((iter__ + 1) != m_ReceivingData->m_ProcessedData.end()
					&& !~m_LL1_Table.m_NoumMapSet.GetSynbolIDByName((iter__ + 1)->m_type) && m_SymbolStack.size() > 1 && ptr_ == (iter__ + 1)->m_type)
				{
					cout << "Line " << iter->m_indexLine << ": '" << iter->m_type << "' �Ƿ�����!" << endl;
					++iter;
					m_SymbolStack.pop();
				}
				//©�����Ŵ���
				else if (m_SymbolStack.size() > 1)
				{
					int m_indexLine;
					m_indexLine = ((iter__ - 1)->m_indexLine != iter->m_indexLine ? (iter__ - 1)->m_indexLine : iter->m_indexLine);

					//����Ƿ��ս����
					if (!(~m_LL1_Table.m_NoumMapSet.GetIntSymbolIDByName(ptr_)))
					{
						int _ID = m_LL1_Table.m_NoumMapSet.GetSynbolIDByName(ptr_);
						if (m_LL1_Table.m_First_Follow.Search_First(_ID, iter->m_type) || m_LL1_Table.m_First_Follow.Search_Follow(_ID, iter->m_type))
						{
							cout << "Line " << m_indexLine << ":ȱʧ '" << ptr << "'" << endl;
						}
					}
					else if (ptr_ == iter->m_type)
					{
						cout << "Line " << m_indexLine << ":ȱʧ '" << ptr << "'" << endl;
					}
					m_SymbolStack.pop();
				}
				//��������eg:������Ų�ƥ�䣩
				else
				{
					m_SymbolStack.pop();
					cout << "Line " << iter->m_indexLine << "ERROR~~" << endl;
				}

				m_isFail = true;
			}
			else
			{
				++iter;
				m_SymbolStack.pop();
			}
		}
	}
}