#include "stdafx.h"
#include "GrammarManager.h"

CGrammarManager::CGrammarManager()
{
}


CGrammarManager::~CGrammarManager()
{
}


void CGrammarManager::Init(const CReceivingData *ptr)
{
	m_ReceivingData = ptr;
}



bool CGrammarManager::Process()
{
	cout << "--�﷨&����������\n";
	isWrong = false;
	m_nowIndex = 0;					//��ʼ������Ĳ������ŵ�λ��
	m_isHaveWrong = false;
	m_LableNum = 1;
	Program();
	OutMiddleCode();
	return isWrong;
}

void CGrammarManager::Program()
{

	if (WORDDATA.m_type == "{")
	{
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� ȱʧ '{'" << endl;
		m_isHaveWrong = true;
	}
	Declaration_List();
	Statement_List();
	if (WORDDATA.m_type == "}")
	{
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� ȱʧ '}'" << endl;
		m_isHaveWrong = true;
	}
	m_isHaveWrong = false;
}


void CGrammarManager::Declaration_List()
{
	if (WORDDATA.m_type == "int")
	{
		Declaration_Stat();
		Declaration_List();
	}
	m_isHaveWrong = false;
}


void CGrammarManager::Declaration_Stat()
{
	if (WORDDATA.m_type == "int")
	{
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� ȱʧ 'int'" << endl;
		m_isHaveWrong = true;
	}

	if (WORDDATA.m_type == "ID")
	{
		//���嶯��������ű��ж��Ƿ��ض��壬��ִ�в������
		if (!m_isHaveWrong)
		{
			if (!m_PropertyTable.Insert(WORDDATA.m_name))
			{
				cout << "Line" << WORDDATA.m_indexLine << "�� ���� " << WORDDATA.m_name << " �ض���" << endl;
				isWrong = true;
			}
		}
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� int��ȱʧ��ʶ��" << endl;
		m_isHaveWrong = true;
	}

	if (WORDDATA.m_name == ";")
	{
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� ��ʶ��" << PREWORDDATA.m_name << " ��ȱʧ ';'" << endl;
		m_isHaveWrong = true;
	}
}


void CGrammarManager::Statement_List()
{
	if (WORDDATA.m_type == "ID" || WORDDATA.m_type == "NUM"
		|| WORDDATA.m_name == "(" || WORDDATA.m_name == "{"
		|| WORDDATA.m_name == ";"
		|| WORDDATA.m_name == "if"&&WORDDATA.m_name != "int"
		|| WORDDATA.m_name == "else"&&WORDDATA.m_name != "int"
		|| WORDDATA.m_name == "for"&&WORDDATA.m_name != "int"
		|| WORDDATA.m_name == "while"&&WORDDATA.m_name != "int"
		|| WORDDATA.m_name == "do"&&WORDDATA.m_name != "int"
		|| WORDDATA.m_name == "write"&&WORDDATA.m_name != "int"
		|| WORDDATA.m_name == "read"&&WORDDATA.m_name != "int")
	{
		Statement();
		Statement_List();
	}
}


void CGrammarManager::Statement()
{
	if (WORDDATA.m_name == "if")
	{
		If_Stat();
	}
	else if (WORDDATA.m_name == "while")
	{
		While_Stat();
	}
	else if (WORDDATA.m_name == "for")
	{
		For_Stat();
	}
	else if (WORDDATA.m_name == "write")
	{
		Write_Stat();
	}
	else if (WORDDATA.m_name == "read")
	{
		Read_Stat();
	}
	else if (WORDDATA.m_name == "{")
	{
		Compound_Stat();
	}
	else if (WORDDATA.m_name == "(" || WORDDATA.m_name == ";" || WORDDATA.m_type == "ID" && WORDDATA.m_name != "else" || WORDDATA.m_type == "NUM")
	{
		Expression_Stat();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� ���������˷���" << PREWORDDATA.m_name << endl;
		m_isHaveWrong = true;
	}
}


void CGrammarManager::If_Stat()
{
	if (WORDDATA.m_name == "if")
	{
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� ȱ�� 'if' " << endl;
		m_isHaveWrong = true;
	}

	if (WORDDATA.m_name == "(")
	{
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� if ��ȱʧ '('" << endl;
		m_isHaveWrong = true;
	}
	Expression();

	if (WORDDATA.m_name == ")")
	{
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "��" << PREWORDDATA.m_name << " ��ȱʧ ')'" << endl;
		m_isHaveWrong = true;
	}

	//�м��������@BRF
	string label1 = newLabel();
	string label2 = newLabel();
	Brf(label1);

	Statement();

	//�м��������@BR
	Br(label2);
	Setlabel(label1);

	if (WORDDATA.m_name == "else")
	{
		GetNextSymbol();
		Statement();
	}
	Setlabel(label2);
}


void CGrammarManager::While_Stat()
{
	if (WORDDATA.m_name == "while")
	{
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� ȱ�� 'while' " << endl;
		m_isHaveWrong = true;
	}

	//�м��������@LABLE
	string label1 = newLabel();
	string label2 = newLabel();
	Setlabel(label1);

	if (WORDDATA.m_name == "(")
	{
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� while ��ȱʧ '('" << endl;
		m_isHaveWrong = true;
	}
	Expression();
	if (WORDDATA.m_name == ")")
	{
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "��" << PREWORDDATA.m_name << " ��ȱʧ ')'" << endl;
		m_isHaveWrong = true;
	}

	//�м��������
	Brf(label2);
	Statement();
	Br(label1);
	Setlabel(label2);
}


void CGrammarManager::For_Stat()
{
	string label1 = newLabel();
	string label2 = newLabel();
	string label3 = newLabel();
	string label4 = newLabel();
	if (WORDDATA.m_name == "for")
	{
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� ȱ�� 'for' " << endl;
		m_isHaveWrong = true;
	}
	if (WORDDATA.m_name == "(")
	{
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� �� for �� ȱ�� '('" << endl;
		m_isHaveWrong = true;
	}
	Expression();

	//�м��������
	Pop();
	if (WORDDATA.m_name == ";")
	{
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� �� " << PREWORDDATA.m_name << " ��ȱ��';'" << endl;
		m_isHaveWrong = true;
	}

	//�м��������
	Setlabel(label1);

	Expression();

	//�м��������
	Brf(label2);
	Br(label3);
	if (WORDDATA.m_name == ";")
	{
		GetNextSymbol();
	}
	else

	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� ���������˷���" << PREWORDDATA.m_name << endl;
		m_isHaveWrong = true;
	}

	//�м��������
	Setlabel(label4);

	Expression();

	//�м��������
	Pop();
	Br(label1);

	if (WORDDATA.m_name == ")")
	{
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� " << PREWORDDATA.m_name << " ��ȱʧ')'" << endl;
		m_isHaveWrong = true;
	}

	//�м��������
	Setlabel(label3);

	Statement();

	//�м��������
	Br(label4);
	Setlabel(label2);
}


void CGrammarManager::Write_Stat()
{
	if (WORDDATA.m_name == "write")
	{
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� ȱʧ 'write' " << endl;
		m_isHaveWrong = true;
	}
	Expression();
	//�м��������
	Out();

	if (WORDDATA.m_name == ";")
	{
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� " << PREWORDDATA.m_name << " ��ȱʧ';'" << endl;
		m_isHaveWrong = true;
	}
}


void CGrammarManager::Read_Stat()
{
	if (WORDDATA.m_name == "read")
	{
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� ȱʧ 'read'" << endl;
		m_isHaveWrong = true;
	}
	string stepword;
	if (WORDDATA.m_type == "ID")
	{
		stepword = WORDDATA.m_name;
		//���嶯���� ����ű���ʶ���Ƿ���,�����Ÿ�ֵ
		if (!m_isHaveWrong)
		{
			if (!m_PropertyTable.IsFindSymbol(WORDDATA.m_name))
			{
				cout << "Line" << WORDDATA.m_indexLine << "�� ���� " << WORDDATA.m_name << " δ����" << endl;
				isWrong = true;
			}
			else
				m_PropertyTable.SetData(WORDDATA.m_name, 0);
		}
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� read ��ȱʧ��ʶ��" << endl;
		m_isHaveWrong = true;
	}

	//�м��������
	In();
	Sto(m_PropertyTable.GetAddByNmme(stepword));
	Pop();

	if (WORDDATA.m_name == ";")
	{
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� " << PREWORDDATA.m_name << " ��ȱʧ ';'" << endl;
		m_isHaveWrong = true;
	}
}


void CGrammarManager::Compound_Stat()
{

	if (WORDDATA.m_name == "{")
	{
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� ȱʧ'{'" << endl;
		m_isHaveWrong = true;
	}
	Statement_List();
	if (WORDDATA.m_name == "}")
	{
		GetNextSymbol();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� " << PREWORDDATA.m_name << " ��ȱʧ'}'" << endl;
		m_isHaveWrong = true;
	}
}


void CGrammarManager::Expression_Stat()
{

	if (WORDDATA.m_name != ";")
	{
		Expression();

		//�м��������@POP
		Pop();

		if (WORDDATA.m_name == ";")
		{
			GetNextSymbol();
		}
		else
		{
			//����
			cout << "Line" << PREWORDDATA.m_indexLine << "�� " << PREWORDDATA.m_name << " ��ȱʧ';'" << endl;
			m_isHaveWrong = true;
		}
	}
	else
	{
		GetNextSymbol();
	}
}


void CGrammarManager::Expression()
{
	string stepWord;
	int address;
	//��ǰ��ȡ�ַ�
	if (WORDDATA.m_type == "ID" && m_ReceivingData->m_ProcessedData[m_nowIndex + 1].m_name == "=")
	{
		//���嶯���� �����ű��ж��Ƿ��и�ID
		if (!m_isHaveWrong)
		{
			if (!m_PropertyTable.IsFindSymbol(WORDDATA.m_name))
			{
				cout << "Line" << WORDDATA.m_indexLine << "�� ���� " << WORDDATA.m_name << " δ����" << endl;
				//m_PropertyTable.Insert(WORDDATA.m_name);
				isWrong = true;
			}
			

		}

		//�м��������@LOOK
		stepWord = WORDDATA.m_name;
		address = m_PropertyTable.GetAddByNmme(stepWord);

		GetNextSymbol();


		if (WORDDATA.m_name == "=")
		{
			GetNextSymbol();
		}
		else
		{
			//����
			cout << "Line" << PREWORDDATA.m_indexLine << "�� " << PREWORDDATA.m_name << " ��ȱʧ '='" << endl;
			m_isHaveWrong = true;
		}
		Bool_Expr();

		//���嶯������������ֵ
		m_PropertyTable.SetData(stepWord, 0);

		//�м��������
		Sto(address);
	}
	else if (WORDDATA.m_name == "(" || WORDDATA.m_type == "NUM" || WORDDATA.m_type == "ID")
	{
		Bool_Expr();
	}
	else
	{
		//����
		cout << "Line" << PREWORDDATA.m_indexLine << "�� ���������˷���" << PREWORDDATA.m_name << endl;
		m_isHaveWrong = true;
	}
}


void CGrammarManager::Bool_Expr()
{
	Additive_Expr();
	Oper_Additive_Expr();
}


void CGrammarManager::Oper_Additive_Expr()
{
	if (WORDDATA.m_name == "<" || WORDDATA.m_name == ">" || WORDDATA.m_name == "<=" || WORDDATA.m_name == ">=" || WORDDATA.m_name == "==" || WORDDATA.m_name == "!=")
	{
		string stepword = WORDDATA.m_name;
		GetNextSymbol();
		Additive_Expr();

		//�м��������
		if (stepword == "<") Les();
		else if (stepword == ">") Gt();
		else if (stepword == ">=") Ge();
		else if (stepword == "<=") Le();
		else if (stepword == "==") Eq();
		else if (stepword == "!=") Noteq();
	}
}


void CGrammarManager::Additive_Expr()
{
	Term();
	Oper_Term();
}


void CGrammarManager::Oper_Term()
{
	if (WORDDATA.m_name == "+" || WORDDATA.m_name == "-")
	{
		string stepword = WORDDATA.m_name;
		GetNextSymbol();
		Term();
		//�м��������
		if (stepword == "+") Add();
		else if (stepword == "-") Sub();
		Oper_Term();
	}
}


void CGrammarManager::Term()
{
	Factor();
	Oper_Factor();
}


void CGrammarManager::Oper_Factor()
{
	if (WORDDATA.m_name == "*" || WORDDATA.m_name == "/")
	{
		string stepword = WORDDATA.m_name;
		GetNextSymbol();

		Factor();

		//�м��������
		if (stepword == "*") Mult();
		else if (stepword == "/") Div();

		Oper_Factor();
	}
}


void CGrammarManager::Factor()
{
	if (WORDDATA.m_name == "(")
	{
		GetNextSymbol();

		Expression();


		if (WORDDATA.m_name == ")")
		{
			GetNextSymbol();
		}
		else
		{
			//����
			cout << "Line" << PREWORDDATA.m_indexLine << "�� " << PREWORDDATA.m_name << " ��ȱʧ')'" << endl;
			m_isHaveWrong = true;
		}
	}
	else {
		if (WORDDATA.m_type == "ID" || WORDDATA.m_type == "NUM")
		{
			//���嶯���� ����Ƿ񸳳�ֵ
			if (!m_isHaveWrong && WORDDATA.m_type == "ID")
			{
				if (!m_PropertyTable.IsFindSymbol(WORDDATA.m_name))
				{
					cout << "Line" << WORDDATA.m_indexLine << "�� ���� " << WORDDATA.m_name << " δ����" << endl;
					//m_PropertyTable.Insert(WORDDATA.m_name);
					isWrong = true;
				}
				else if (!m_PropertyTable.IsHaveData(WORDDATA.m_name))
				{
					cout << "Line" << WORDDATA.m_indexLine << "�� ���� " << WORDDATA.m_name << " δ��ʼ��" << endl;
					m_PropertyTable.SetData(WORDDATA.m_name, 0);
					isWrong = true;
				}
			}

			//�м��������
			if (WORDDATA.m_type == "ID") Load(m_PropertyTable.GetAddByNmme(WORDDATA.m_name));
			else if (WORDDATA.m_type == "NUM") Loadi(StringToInt(WORDDATA.m_name));
			GetNextSymbol();
			return;
		}
		else
		{
			//����
			cout << "Line" << PREWORDDATA.m_indexLine << "�� ���������˷���" << PREWORDDATA.m_name << endl;
			m_isHaveWrong = true;
		}

	}
}

//���м����д���ı�
void CGrammarManager::OutMiddleCode()
{
	CFileDatabyTxt m_file;
	m_file.FileOpen("./message/middleCode.txt");
	for (auto iter : m_middleCode)
	{
		if (iter.find("LABEL") == 0)
			m_file.FileWrite(iter + "\n");
		else
			m_file.FileWrite("      " + iter + "\n");
	}
	m_file.FileClose();
}



//����������ķ�������

string CGrammarManager::newLabel()
{
	return string("LABEL") + m_LableNum++;
}
void CGrammarManager::Pop()
{
	m_middleCode.push_back(string("POP"));
}
int CGrammarManager::Look(string word)
{
	return m_PropertyTable.GetAddByNmme(word);
}
void CGrammarManager::Sto(int address)
{
	m_middleCode.push_back(string("STO ") + address);
}
void CGrammarManager::Gt()
{
	m_middleCode.push_back(string("GT"));
}
void CGrammarManager::Les()
{
	m_middleCode.push_back(string("LES"));
}
void CGrammarManager::Ge()
{
	m_middleCode.push_back(string("GE"));
}
void CGrammarManager::Le()
{
	m_middleCode.push_back(string("LE"));
}
void CGrammarManager::Eq()
{
	m_middleCode.push_back(string("EQ"));
}
void CGrammarManager::Noteq()
{
	m_middleCode.push_back(string("NOTEQ"));
}
void CGrammarManager::Add()
{
	m_middleCode.push_back(string("ADD"));
}
void CGrammarManager::Sub()
{
	m_middleCode.push_back(string("SUB"));
}
void CGrammarManager::Mult()
{
	m_middleCode.push_back(string("MULT"));
}
void CGrammarManager::Div()
{
	m_middleCode.push_back(string("DIV"));
}
void CGrammarManager::Load(int address)
{
	m_middleCode.push_back(string("LOAD ") + address);
}
void CGrammarManager::Loadi(int num)
{
	m_middleCode.push_back(string("LOADI ") + num);
}
void CGrammarManager::Brf(string label)
{
	m_middleCode.push_back(string("BRF ") + label);
}
void CGrammarManager::Br(string label)
{
	m_middleCode.push_back(string("BR ") + label);
}
void CGrammarManager::Setlabel(string label)
{
	m_middleCode.push_back(label + ":");
}
void CGrammarManager::In()
{
	m_middleCode.push_back(string("IN"));
}
void CGrammarManager::Out()
{
	m_middleCode.push_back(string("OUT"));
}
