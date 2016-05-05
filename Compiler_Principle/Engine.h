#pragma once
#include "CharacterTable.h"
#include "StateManger.h"
#include "TranslateRelation.h"
#include "InformationManager.h"
#include "ReceivingData.h"
#include "LL_1_Table.h"
class CEngine
{
public:
	CEngine();
	~CEngine();
private:
	ifstream m_file;									//文件读取流
	char m_dataBuff[1024];								//逐行读取文本，文本内容缓存
	string m_nowFileData;								//当前处理数据
	CCharacterTable m_CharacterTable;
	CStateManger m_StateManger;
	CTranslateRelation m_TransRelation;
	CInformationManager m_infManager;
	CReceivingData m_ReceivingData;
	CLL_1_Table	m_LL1_Table;

	int m_indexLine;									//当前处理第几行
	int m_nowStateStartline;							//当前状态的处理起始行

	CSTATE m_now_State;									//当前状态
	CSTATE m_last_State;								//当前状态的前一状态
	CSTATE m_pre_State;									//上一个终结状态


	string m_rest_Data;									//当前未终止的状态机的所有已识别字符
	string m_now_Data;									//当前处理数据

	bool m_terminal;									//是否为终结符

	int m_now_index;									//状态机进入终止状态时对应的字符下标
	int m_pre_index;									//进入一个状态机时对应的字符下标
public:
	void Init();
	bool OpenFile(const string& m_filePath);		    //打开待处理文件
	void FileReader();									//读取待处理文本内容
	void DataConduct(const string& nowConductData);		//读取内容处理
	void FinalStateJudge();								//文件处理完成后判断最后一个状态的
	bool NoteSpecialJudge(int ptr);						//对注释的特殊处理（可识别中文）
	void WrongHintManger(int &ptr);						//错误信息统计
	void Right_DataAnalysis(int &ptr, const int& indexLine);					//正确信息的分析
	void CloseFile();									//关闭文件
};
