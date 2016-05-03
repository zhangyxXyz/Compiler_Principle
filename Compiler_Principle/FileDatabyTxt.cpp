#include "stdafx.h"
#include "FileDatabyTxt.h"


CFileDatabyTxt::CFileDatabyTxt()
{
}


CFileDatabyTxt::~CFileDatabyTxt()
{
}


void CFileDatabyTxt::FileOpen(const string& m_txtName)
{
	m_file.open(m_txtName, ofstream::out);
}

void CFileDatabyTxt::FileFormat()
{
	m_file.setf(ios::left, ios::adjustfield);
	m_file.width(10);
}

void CFileDatabyTxt::FileWrite(const string &fileData)
{
	m_file << fileData;
}

void CFileDatabyTxt::FileClose()
{
	m_file.close();
}
