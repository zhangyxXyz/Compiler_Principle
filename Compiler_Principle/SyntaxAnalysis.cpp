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
		//栈顶元素为非终结符
		if (m_SymbolStack.empty())
		{
			if (!m_isFail && iter == m_ReceivingData->m_ProcessedData.end())
				cout << "语法分析完成: ACCEPT\n";
			else if (iter != m_ReceivingData->m_ProcessedData.end())
			{
				cout << "Line " << ((--iter)->m_indexLine) << ":程序语句块结束，后续语句赘余" << endl;
				cout << "语法分析完成: FAIL\n";
			}
			else cout << "语法分析完成: FAIL\n";
			return;
		}
		//源代码最后语句多余或语句缺省
		else if (iter == m_ReceivingData->m_ProcessedData.end() && !m_SymbolStack.empty())
		{
			cout << "Line " << ((--iter)->m_indexLine) << ":程序语句非正常结束，语句缺损" << endl;
			return;
		}
		//正常查表分析
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
					throw runtime_error("ERROR :没有对应转换关系式-->");
				}
				if (m_LL1_Table.m_Expr[x][y].right[0] == "epsilon")
					continue;

				//不是epsilon替换式等式右边反序入栈
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
				//错误恢复
				//cout << err.what()
				//	<< iter->m_type << ' ' << iter->m_name << ' ' << iter->m_indexLine << endl;

				auto iter__ = iter;
				int x_ = m_LL1_Table.m_NoumMapSet.GetSynbolIDByName(_state);
				int y_ = m_LL1_Table.m_NoumMapSet.GetIntSymbolIDByName(iter__->m_type);

				//LL(1)表中没有对应的转换关系式在FOLLOW集中查找，进行操作实现错误恢复
				if (m_LL1_Table.m_First_Follow.Search_Follow(x_, iter->m_type))
				{
					cout << "Line " << iter->m_indexLine << ":在 '" << iter->m_type << "' 前缺失相关语法结构" << endl;
					//m_SymbolStack.pop();在读取时已经弹出
					m_isFail = true;
				}
				else
				{
					cout << "Line " << iter->m_indexLine << ": '" << iter->m_type << "' 非法定义" << endl;
					++iter;
					m_SymbolStack.push(_state);
					m_isFail = true;
				}
			}
		}

		//栈顶元素是终结符号
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
				//符号错位错误
				if (ptr != ""&&ptr_ != "" && (iter__ + 1) != m_ReceivingData->m_ProcessedData.end()
					&& ptr == (iter + 1)->m_type&&ptr_ == iter->m_type)
				{
					cout << "Line " << iter->m_indexLine << ": '" << ptr << "' 与 '" << ptr_ << "' 错位" << endl;
					iter += 2;
					m_SymbolStack.pop(), m_SymbolStack.pop();
				}
				//多穿符号错误
				else if ((iter__ + 1) != m_ReceivingData->m_ProcessedData.end() && (iter__ + 1)->m_type == m_SymbolStack.top())
				{
					cout << "Line " << iter->m_indexLine << ":出现冗余的 '" << iter->m_type << "' " << endl;
					++iter;
				}
				//错穿符号错误
				else if ((iter__ + 1) != m_ReceivingData->m_ProcessedData.end()
					&& !~m_LL1_Table.m_NoumMapSet.GetSynbolIDByName((iter__ + 1)->m_type) && m_SymbolStack.size() > 1 && ptr_ == (iter__ + 1)->m_type)
				{
					cout << "Line " << iter->m_indexLine << ": '" << iter->m_type << "' 非法定义!" << endl;
					++iter;
					m_SymbolStack.pop();
				}
				//漏穿符号错误
				else if (m_SymbolStack.size() > 1)
				{
					int m_indexLine;
					m_indexLine = ((iter__ - 1)->m_indexLine != iter->m_indexLine ? (iter__ - 1)->m_indexLine : iter->m_indexLine);

					//如果是非终结符号
					if (!(~m_LL1_Table.m_NoumMapSet.GetIntSymbolIDByName(ptr_)))
					{
						int _ID = m_LL1_Table.m_NoumMapSet.GetSynbolIDByName(ptr_);
						if (m_LL1_Table.m_First_Follow.Search_First(_ID, iter->m_type) || m_LL1_Table.m_First_Follow.Search_Follow(_ID, iter->m_type))
						{
							cout << "Line " << m_indexLine << ":缺失 '" << ptr << "'" << endl;
						}
					}
					else if (ptr_ == iter->m_type)
					{
						cout << "Line " << m_indexLine << ":缺失 '" << ptr << "'" << endl;
					}
					m_SymbolStack.pop();
				}
				//其他错误（eg:多个符号不匹配）
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