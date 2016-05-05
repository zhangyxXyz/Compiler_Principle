#pragma once

//×Ö·ûÓ³Éä
class CNounMapSet
{
public:
	CNounMapSet();
	~CNounMapSet();
private:
	map<string, int> m_Symbol;			//±íÇı¶¯·ûºÅ¼¯Ó³Éä
	map<string, int> m_intSymbol;		//±íÇı¶¯ÊäÈë·ûºÅÓ³Éä
public:
	void Init();
	int GetSynbolIDByName(const string& name);
	string GetSymbolNameByID(const int& ID);
	int GetIntSymbolIDByName(const string& name);
	string GetIntSymbolNameByID(const int& ID);
};

