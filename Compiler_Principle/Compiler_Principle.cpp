// Compiler_Principle.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Engine.h"

int main()
{
	string m_filePath;  //��ȡ�ļ�·�� 
	while (true)
	{
		CEngine *progressEngine = new CEngine();
		cout << "�������������Դ�����ļ�·����\n\t";
		cin >> m_filePath;
		progressEngine->OpenFile(m_filePath);
		progressEngine->Init();
		progressEngine->FileReader();
		progressEngine->CloseFile();
		delete(progressEngine);
	}
	return 0;
}