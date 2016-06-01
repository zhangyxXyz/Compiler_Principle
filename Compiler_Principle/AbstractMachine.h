#pragma once
class CAbstractMachine
{
public:
	CAbstractMachine();
	~CAbstractMachine();
	void Run();
	void LoadCode();
	void SetLabelLayer();
	void Operator(string m_Code, int& m_nowIndex);
private:
	int m_nowIndex;					//用以判断程序是否执行完成
	ifstream m_file;				//文件读取流
	vector<string> m_Codes;			//所有中间代码
	map<int, int> m_labelLayer;		//对应跳转的Lable所在行数
	map<int, int> m_dataBuff;		//对应地址对应数据
	stack<int> OperStack;			//操作栈
};

