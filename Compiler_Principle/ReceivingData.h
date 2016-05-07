#pragma once
#include "FileDatabyTxt.h"

//�ʷ������Ĵ�����
class CProcessedData
{
public:
	//�������ͣ����ƣ���������
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
	vector<CProcessedData> m_ProcessedData;			//�ʷ���������������
private:
	CFileDatabyTxt m_file;							//�������Ԥ���������
public:
	//���Ԥ��������
	void ProcessedData_ADD(const int& state_type, const string& name, const int& indexLine);
	void ProcessedDataOut();
};

