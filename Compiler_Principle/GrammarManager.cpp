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
	Program();
	m_MiddleCodeFactory.OutMiddleCode();
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
			if (!m_MiddleCodeFactory.m_PropertyTable.Insert(WORDDATA.m_name))
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
	string label1 = m_MiddleCodeFactory.newLabel();
	string label2 = m_MiddleCodeFactory.newLabel();
	m_MiddleCodeFactory.Brf(label1);

	Statement();

	//�м��������@BR
	m_MiddleCodeFactory.Br(label2);
	m_MiddleCodeFactory.Setlabel(label1);

	if (WORDDATA.m_name == "else")
	{
		GetNextSymbol();
		Statement();
	}
	m_MiddleCodeFactory.Setlabel(label2);
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
	string label1 = m_MiddleCodeFactory.newLabel();
	string label2 = m_MiddleCodeFactory.newLabel();
	m_MiddleCodeFactory.Setlabel(label1);

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
	m_MiddleCodeFactory.Brf(label2);
	Statement();
	m_MiddleCodeFactory.Br(label1);
	m_MiddleCodeFactory.Setlabel(label2);
}


void CGrammarManager::For_Stat()
{
	string label1 = m_MiddleCodeFactory.newLabel();
	string label2 = m_MiddleCodeFactory.newLabel();
	string label3 = m_MiddleCodeFactory.newLabel();
	string label4 = m_MiddleCodeFactory.newLabel();
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
	m_MiddleCodeFactory.Pop();
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
	m_MiddleCodeFactory.Setlabel(label1);

	Expression();

	//�м��������
	m_MiddleCodeFactory.Brf(label2);
	m_MiddleCodeFactory.Br(label3);
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
	m_MiddleCodeFactory.Setlabel(label4);

	Expression();

	//�м��������
	m_MiddleCodeFactory.Pop();
	m_MiddleCodeFactory.Br(label1);

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
	m_MiddleCodeFactory.Setlabel(label3);

	Statement();

	//�м��������
	m_MiddleCodeFactory.Br(label4);
	m_MiddleCodeFactory.Setlabel(label2);
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
	m_MiddleCodeFactory.Out();

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
			if (!m_MiddleCodeFactory.m_PropertyTable.IsFindSymbol(WORDDATA.m_name))
			{
				cout << "Line" << WORDDATA.m_indexLine << "�� ���� " << WORDDATA.m_name << " δ����" << endl;
				//��ֹ��α���
				//m_MiddleCodeFactory.m_PropertyTable.Insert(WORDDATA.m_name);
				isWrong = true;
			}
			else
				m_MiddleCodeFactory.m_PropertyTable.SetData(WORDDATA.m_name, 0);
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
	m_MiddleCodeFactory.In();
	m_MiddleCodeFactory.Sto(m_MiddleCodeFactory.m_PropertyTable.GetAddByNmme(stepword));
	m_MiddleCodeFactory.Pop();

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
		m_MiddleCodeFactory.Pop();

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
			if (!m_MiddleCodeFactory.m_PropertyTable.IsFindSymbol(WORDDATA.m_name))
			{
				cout << "Line" << WORDDATA.m_indexLine << "�� ���� " << WORDDATA.m_name << " δ����" << endl;
				//��ֹ��α���
				//m_MiddleCodeFactory.m_PropertyTable.Insert(WORDDATA.m_name);
				isWrong = true;
			}
			

		}

		//�м��������@LOOK
		stepWord = WORDDATA.m_name;
		address = m_MiddleCodeFactory.m_PropertyTable.GetAddByNmme(stepWord);

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
		m_MiddleCodeFactory.m_PropertyTable.SetData(stepWord, 0);

		//�м��������
		m_MiddleCodeFactory.Sto(address);
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
		if (stepword == "<") m_MiddleCodeFactory.Les();
		else if (stepword == ">") m_MiddleCodeFactory.Gt();
		else if (stepword == ">=") m_MiddleCodeFactory.Ge();
		else if (stepword == "<=") m_MiddleCodeFactory.Le();
		else if (stepword == "==") m_MiddleCodeFactory.Eq();
		else if (stepword == "!=") m_MiddleCodeFactory.Noteq();
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
		if (stepword == "+") m_MiddleCodeFactory.Add();
		else if (stepword == "-") m_MiddleCodeFactory.Sub();
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
		if (stepword == "*") m_MiddleCodeFactory.Mult();
		else if (stepword == "/") m_MiddleCodeFactory.Div();

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
				if (!m_MiddleCodeFactory.m_PropertyTable.IsFindSymbol(WORDDATA.m_name))
				{
					cout << "Line" << WORDDATA.m_indexLine << "�� ���� " << WORDDATA.m_name << " δ����" << endl;
					//��ֹ��α���
					//m_MiddleCodeFactory.m_PropertyTable.Insert(WORDDATA.m_name);
					isWrong = true;
				}
				else if (!m_MiddleCodeFactory.m_PropertyTable.IsHaveData(WORDDATA.m_name))
				{
					cout << "Line" << WORDDATA.m_indexLine << "�� ���� " << WORDDATA.m_name << " δ��ʼ��" << endl;
					m_MiddleCodeFactory.m_PropertyTable.SetData(WORDDATA.m_name, 0);
					isWrong = true;
				}
			}

			//�м��������
			if (WORDDATA.m_type == "ID") 
				m_MiddleCodeFactory.Load(m_MiddleCodeFactory.m_PropertyTable.GetAddByNmme(WORDDATA.m_name));
			else if (WORDDATA.m_type == "NUM") 
				m_MiddleCodeFactory.Loadi(StringToInt(WORDDATA.m_name));
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