#pragma once
#include "FileDatabyTxt.h"

//词法分析的处理结果
class CProcessedData
{
public:
	//数据类型，名称，所在行数
	string m_type;
	string m_name;

	int m_indexLine;

public:
	CProcessedData(const string& type, const string& name, const int& indexLine)
		:m_type(type), m_name(name), m_indexLine(indexLine) {};
	~CProcessedData() {}
};

class CReceivingData
{
public:
	CReceivingData();
	~CReceivingData();
	vector<CProcessedData> m_ProcessedData;			//词法分析处理结果数据
private:
	CFileDatabyTxt m_file;							//用于输出预处理的数据
public:
	//添加预处理数据
	void ProcessedData_ADD(const int& state_type, const string& name, const int& indexLine);
	void ProcessedDataOut();
};

