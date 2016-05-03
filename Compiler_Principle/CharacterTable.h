#pragma once
class CCharacterTable
{
public:
	CCharacterTable();
	~CCharacterTable();
	void CharacterTableInit();
private:
	map<char, int> m_letter;													//字符映射为数字编号
	pair<map<char, int>::iterator, map<char, int>::iterator> m_Search;  		//查找索引
public:
	int GetTableSize();															//返回字符表大小，用于建立关系表
	bool JudgeCharacter(const char& ptr);										//判断字符是否在映射表内
	int GetNumByChar(const char& ptr);											//通过字符索引编号
	char GetCharByNum(const int& ptr);											//通过编号索引字符
};