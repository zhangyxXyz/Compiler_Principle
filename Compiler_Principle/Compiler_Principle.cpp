// Compiler_Principle.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Engine.h"

int main()
{
	string m_filePath;  //读取文件路径 
	while (true)
	{
		CEngine *progressEngine = new CEngine();
		cout << "请输入待处理的源程序文件路径：\n\t";
		cin >> m_filePath;
		progressEngine->OpenFile(m_filePath);
		progressEngine->Init();
		progressEngine->FileReader();
		progressEngine->CloseFile();
		delete(progressEngine);
	}
	return 0;
}