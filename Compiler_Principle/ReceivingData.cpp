#include "stdafx.h"
#include "ReceivingData.h"


CReceivingData::CReceivingData()
{
}


CReceivingData::~CReceivingData()
{
}

void CReceivingData::ProcessedData_ADD(const int& state_type, const string& name, const int& indexLine)
{
	string m_type = "";
	switch (state_type)
	{
	case 1:m_type = "ID";break;
	case 2:m_type = name;break;
	case 3:
	case 4:m_type = "NUM";break;
	case 5:
	case 6:
	case 8:
	case 9:m_type = name;break;
	default:break;
	}
	m_ProcessedData.push_back(CProcessedData(m_type, name, indexLine));
}


void CReceivingData::ProcessedDataOut()
{
	m_file.FileOpen("test_.txt");
	for (auto iter : m_ProcessedData)
	{
		stringstream s;
		s << iter.m_indexLine;
		m_file.FileFormat();
		//string str = iter.m_type + ' ' + iter.m_name + ' ' + s.str() + '\n';
		m_file.FileWrite(iter.m_type+' ');
		m_file.FileFormat();
		m_file.FileWrite(iter.m_name + ' ');
		m_file.FileWrite(s.str() + '\n');
	}
	m_file.FileClose();
}
