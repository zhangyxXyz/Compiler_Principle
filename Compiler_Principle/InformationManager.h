#pragma once
#include "StateManger.h"
#include "FileDatabyTxt.h"
class CInformationManager
{
public:
	CInformationManager();
	~CInformationManager();
private:
	vector<string> m_Reservedword;						//标准关键字
	vector<string> m_keyWord;							//识别的关键字
	vector<string> m_UnsignedNum;						//无符号整数
	vector<string> m_Identifier;						//标识符
	vector<string> m_Delimiter;							//分界符
	vector<string> m_Operator;							//运算符
	vector<string> m_Note;								//注释
	vector<string> m_WrongHint;							//错误信息
	
	CFileDatabyTxt m_filebyTxt;							//内容存贮类对象
	string m_fileData;									//将要写入的文本信息
public:
	void Init();
	void Hint_Category(const int &stateNum, const string& str);			//信息分类

	void PushString(vector<string> & vec, const string& str);		//存贮各类信息
	void PushWrongHint(const string & str);
	//输出各类信息
	void IdentifierHintInfo();
	void ReservedWordHintInfo();
	void UnsignedNumHintInfo();
	void DelimiterHintInfo();
	void OperatorHintInfo();
	void NoteHintInfo();
	void WrongHintInfo();
	void StateReSet(int &stateNum, const string& str);
};
