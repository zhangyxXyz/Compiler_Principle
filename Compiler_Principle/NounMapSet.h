#pragma once

//�ַ�ӳ��
class CNounMapSet
{
public:
	CNounMapSet();
	~CNounMapSet();
private:
	map<string, int> m_Symbol;			//���������ż�ӳ��
	map<string, int> m_intSymbol;		//�������������ӳ��
public:
	void Init();
	int GetSynbolIDByName(const string& name);
	string GetSymbolNameByID(const int& ID);
	int GetIntSymbolIDByName(const string& name);
	string GetIntSymbolNameByID(const int& ID);
};

