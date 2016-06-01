#pragma once
class Symbol
{
public:
	int m_Add;				//��ַ
	int m_data;				//����ֵ
	string m_name;			//����
	bool m_isHaveData;		//�Ƿ�ֵ

	Symbol::Symbol()
	{
		m_name = "";
		m_isHaveData = false;
	}
	Symbol::Symbol(const string& name, int add)
	{
		m_name = name;
		m_Add = add;
	}
};

class CSymbolTable
{
public:
	CSymbolTable();
	~CSymbolTable();
	bool IsFindSymbol(const string& m_name);
	bool Insert(const string& name);
	bool SetData(const string &m_name, const int& m_dada);
	bool IsHaveData(const string& m_name);
	int GetAddByNmme(const string& m_name);
public:
	int m_NowAddIndex;			//��ǰ�����ַλ��
	map<string, Symbol> m_SymbolTable;
};

