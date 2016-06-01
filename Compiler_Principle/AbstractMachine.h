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
	int m_nowIndex;					//�����жϳ����Ƿ�ִ�����
	ifstream m_file;				//�ļ���ȡ��
	vector<string> m_Codes;			//�����м����
	map<int, int> m_labelLayer;		//��Ӧ��ת��Lable��������
	map<int, int> m_dataBuff;		//��Ӧ��ַ��Ӧ����
	stack<int> OperStack;			//����ջ
};

