#pragma once
class CFileDatabyTxt
{
public:
	CFileDatabyTxt();
	~CFileDatabyTxt();
	void FileOpen(const string& m_txtName);
	void FileFormat(const int& size_);
	void FileWrite(const string &fileData);
	void FileClose();
public:
	ofstream m_file;			            //�ļ�д����
	//const string m_txtName = "./lex.txt";   //�ļ��洢λ��
};

