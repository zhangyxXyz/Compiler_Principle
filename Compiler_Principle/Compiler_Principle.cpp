// Compiler_Principle.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Engine.h"
#include "AbstractMachine.h"

int main()
{
	string m_filePath;		//��ȡ�ļ�·��
	string userOper;		//�û������Ƿ�ִ�г��������
	bool DontRunMachine;	//�Ƿ��д��Ƿ���������
	while (true)
	{
		CEngine *progressEngine = new CEngine();
		CAbstractMachine m_AbstractMachine;
		cout << "������������Դ�����ļ�·����\n\t";
		cin >> m_filePath;
		/*************************************
		*�ʷ�����
		*
		*�﷨&����&�м��������:	SyntaxAnalysisProcess
		**************************************/
		if (progressEngine->OpenFile(m_filePath))
		{
			progressEngine->Init();
			progressEngine->FileReader();
			progressEngine->CloseFile();
			DontRunMachine=progressEngine->SyntaxAnalysisProcess();
			delete(progressEngine);
		}
		if (DontRunMachine == true)
		{
			cout << "����������ʱ����,���ų������ٴγ���!!!\n";
			continue;
		}
		cout << "�����������Ƿ����������ִ�д��룺Y : N ?\n";
		cin >> userOper;
		if (userOper == "Y")
			m_AbstractMachine.Run();
	}
	return 0;
}