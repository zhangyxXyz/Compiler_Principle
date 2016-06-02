// Compiler_Principle.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Engine.h"
#include "AbstractMachine.h"

int main()
{
	string m_filePath;		//读取文件路径
	string userOper;		//用户操作是否执行抽象机代码
	bool DontRunMachine;	//是否有错，是否启动操作
	while (true)
	{
		CEngine *progressEngine = new CEngine();
		CAbstractMachine m_AbstractMachine;
		cout << "请输入待处理的源程序文件路径：\n\t";
		cin >> m_filePath;
		/*************************************
		*词法分析
		*
		*语法&语义&中间代码生成:	SyntaxAnalysisProcess
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
			cout << "输入代码分析时出错,请排除错误再次尝试!!!\n";
			continue;
		}
		cout << "分析结束，是否启动抽象机执行代码：Y : N ?\n";
		cin >> userOper;
		if (userOper == "Y")
			m_AbstractMachine.Run();
	}
	return 0;
}