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

void CFileDatabyTxt::FileFormat(const int& size_)
{
	m_file.setf(ios::left, ios::adjustfield);
	m_file.width(size_);
}

void CFileDatabyTxt::FileWrite(const string &fileData)
{
	m_file << fileData;
}

void CFileDatabyTxt::FileClose()
{
	m_file.close();
}
