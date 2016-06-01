#include "stdafx.h"
#include "Engine.h"

CEngine::CEngine()
{
}


CEngine::~CEngine()
{
	m_ReceivingData = nullptr;
	delete m_ReceivingData;
}


void CEngine::Init()
{
	m_indexLine = 0;
	m_ReceivingData = new CReceivingData();
	m_terminal = false;
	m_now_Data = m_rest_Data = "";
	m_nowStateStartline = 1;
	m_now_index = m_pre_index = -1;
	m_now_State = CSTATE("START", false);
	m_CharacterTable.CharacterTableInit();
	m_StateManger.StateInit();
	m_TransRelation.TranslateRelationInit(m_CharacterTable, m_StateManger);
	m_infManager.Init();
	m_GrammarManager.Init(m_ReceivingData);				//递归下降分析
	//m_SySyntaxAnalysis.Init(m_ReceivingData);			  //LL(1)分析表分析
}


bool CEngine::OpenFile(const string& m_filePath)
{
	m_file.open(m_filePath, std::ios::in);
	if (m_file.fail())
	{
		cout << "文件读取失败，请重新输入：\n\t";
		return false;
	}
	return true;
}


void CEngine::FileReader()
{
	while (m_file.getline(m_dataBuff, sizeof(m_dataBuff)))
	{
		m_nowFileData.clear();
		m_nowFileData.append(m_dataBuff);
		m_nowFileData += "\n";
		DataConduct(m_nowFileData);
	}
	FinalStateJudge();
	m_infManager.WrongHintInfo();
	m_ReceivingData->ProcessedDataOut();
	cout << "--词法分析完成\n";
	/*if (m_rest_Data.length())
		cout << "----词法分析成功识别的内容如下:\n";
	m_infManager.IdentifierHintInfo();
	m_infManager.ReservedWordHintInfo();
	m_infManager.UnsignedNumHintInfo();
	m_infManager.DelimiterHintInfo();
	m_infManager.OperatorHintInfo();
	m_infManager.NoteHintInfo();*/
}


void CEngine::DataConduct(const string& nowConductData)
{
	m_indexLine++;															//记录当前行
	m_pre_index = -1;														//当前状态机识别表示符开始位置的前一位
	m_now_Data = m_rest_Data + nowConductData;
	for (int i = m_rest_Data.length(), k = m_now_Data.length();i < k;i++)		//循环处理当前的每一位
	{
		m_pre_State = m_now_State;											//状态切换前吧当前状态赋值给前一个状态
		if (NoteSpecialJudge(i) == false)									//状态切换，寻找下一个状态
			m_now_State = m_TransRelation.GetNextState(m_now_State, m_now_Data[i]);
		if (m_now_State.m_isEnd == true)									//判断是否处于终态
		{
			m_now_index = i;												//记录下终态是识别的字符位置
			m_last_State = m_now_State;										//记录上一次的终态，用于判断类型
			m_terminal = true;
		}
		if (m_now_State == CSTATE("WRONG", false))							//当前状态机如果进入Error状态进行输出判断
		{
			(m_terminal == false) ? WrongHintManger(i) : Right_DataAnalysis(i, m_indexLine);
			m_pre_State = m_now_State;
			m_now_State = CSTATE("START", false);							//状态重置
			m_nowStateStartline = m_indexLine;

		}
	}
	m_rest_Data = string(m_now_Data, m_pre_index + 1, m_now_Data.length());//把当前行的未终结的状态机识别字符放入下一行
	m_now_index -= (m_pre_index + 1);
}


bool CEngine::NoteSpecialJudge(int ptr)
{
	if (m_now_State == CSTATE("NOTE_START", false) && m_now_Data[ptr] != '*') return true;
	else if (m_now_State == CSTATE("NOTE_END_BUFF", false))
	{
		if (m_now_Data[ptr] != '/')  m_now_State = CSTATE("NOTE_START", false);
		else m_now_State = CSTATE("NOTE_END", true);
		return true;
	}
	return false;
}


void CEngine::FinalStateJudge()
{
	if (m_now_State.m_isEnd == true) return;
	stringstream s;
	s << m_nowStateStartline;
	string str = "Line " + s.str();
	int case_ptr = m_StateManger.GetNumByState(m_now_State);
	switch (case_ptr)
	{
	case 10:
	case 11:
		if (m_nowStateStartline == m_indexLine)
			str += ":错误的使用了注释\n";
		else str += ":从本行开始的注释没有注释结尾\n";
		str += "错误注释内容如下\n" + m_rest_Data;
		m_infManager.PushWrongHint(str);break;
	default:break;
	}
}



void CEngine::WrongHintManger(int &ptr)
{
	stringstream s;
	string str = "";
	s << m_indexLine;
	if (m_CharacterTable.JudgeCharacter(m_now_Data[ptr]) == false)
		str = "Line " + s.str() + ":出现无法识别的符号 " + m_now_Data[ptr];

	else
		str = "Line " + s.str() + ":错误的使用了 " + m_now_Data[--ptr];
	m_infManager.PushWrongHint(str);
	m_pre_index = m_now_index = ptr;
}


void CEngine::Right_DataAnalysis(int &ptr, const int& indexLine)
{
	if (m_last_State != CSTATE("SPACE", true))
	{
		string str = string(m_now_Data, m_pre_index + 1, m_now_index - m_pre_index);
		int k = m_StateManger.GetNumByState(m_pre_State);
		m_infManager.StateReSet(k, str);
		m_infManager.Hint_Category(k, str);
		if (k < 10)
		{
			m_ReceivingData->ProcessedData_ADD(k, str, indexLine);
		}
		//cout << "识别成功: " << str << endl;
	}
	m_terminal = false;
	m_pre_index = m_now_index;
	ptr = m_now_index;				//当前处理字符下标回切
}

void CEngine::CloseFile()
{
	if (m_file.fail())
		return;
	m_file.close();
}


bool CEngine::SyntaxAnalysisProcess()
{
	return m_GrammarManager.Process();			//运行语法&语义分析
	//m_SySyntaxAnalysis.Process();
}
