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
	cout << "--语法&语义分析完成\n";
	isWrong = false;
	m_nowIndex = 0;					//初始化处理的操作符号的位置
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
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： 缺失 '{'" << endl;
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
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： 缺失 '}'" << endl;
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
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： 缺失 'int'" << endl;
		m_isHaveWrong = true;
	}

	if (WORDDATA.m_type == "ID")
	{
		//语义动作：查符号表判断是否重定义，并执行插入操作
		if (!m_isHaveWrong)
		{
			if (!m_PropertyTable.Insert(WORDDATA.m_name))
			{
				cout << "Line" << WORDDATA.m_indexLine << "： 变量 " << WORDDATA.m_name << " 重定义" << endl;
				isWrong = true;
			}
		}
		GetNextSymbol();
	}
	else
	{
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： int后缺失标识符" << endl;
		m_isHaveWrong = true;
	}

	if (WORDDATA.m_name == ";")
	{
		GetNextSymbol();
	}
	else
	{
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： 标识符" << PREWORDDATA.m_name << " 后缺失 ';'" << endl;
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
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： 错误引用了符号" << PREWORDDATA.m_name << endl;
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
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： 缺少 'if' " << endl;
		m_isHaveWrong = true;
	}

	if (WORDDATA.m_name == "(")
	{
		GetNextSymbol();
	}
	else
	{
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： if 后缺失 '('" << endl;
		m_isHaveWrong = true;
	}
	Expression();

	if (WORDDATA.m_name == ")")
	{
		GetNextSymbol();
	}
	else
	{
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "：" << PREWORDDATA.m_name << " 后缺失 ')'" << endl;
		m_isHaveWrong = true;
	}

	//中间代码生成@BRF
	string label1 = newLabel();
	string label2 = newLabel();
	Brf(label1);

	Statement();

	//中间代码生成@BR
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
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： 缺少 'while' " << endl;
		m_isHaveWrong = true;
	}

	//中间代码生成@LABLE
	string label1 = newLabel();
	string label2 = newLabel();
	Setlabel(label1);

	if (WORDDATA.m_name == "(")
	{
		GetNextSymbol();
	}
	else
	{
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： while 后缺失 '('" << endl;
		m_isHaveWrong = true;
	}
	Expression();
	if (WORDDATA.m_name == ")")
	{
		GetNextSymbol();
	}
	else
	{
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "：" << PREWORDDATA.m_name << " 后缺失 ')'" << endl;
		m_isHaveWrong = true;
	}

	//中间代码生成
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
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： 缺少 'for' " << endl;
		m_isHaveWrong = true;
	}
	if (WORDDATA.m_name == "(")
	{
		GetNextSymbol();
	}
	else
	{
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： 在 for 后 缺少 '('" << endl;
		m_isHaveWrong = true;
	}
	Expression();

	//中间代码生成
	Pop();
	if (WORDDATA.m_name == ";")
	{
		GetNextSymbol();
	}
	else
	{
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： 在 " << PREWORDDATA.m_name << " 后缺少';'" << endl;
		m_isHaveWrong = true;
	}

	//中间代码生成
	Setlabel(label1);

	Expression();

	//中间代码生成
	Brf(label2);
	Br(label3);
	if (WORDDATA.m_name == ";")
	{
		GetNextSymbol();
	}
	else

	{
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： 错误引用了符号" << PREWORDDATA.m_name << endl;
		m_isHaveWrong = true;
	}

	//中间代码生成
	Setlabel(label4);

	Expression();

	//中间代码生成
	Pop();
	Br(label1);

	if (WORDDATA.m_name == ")")
	{
		GetNextSymbol();
	}
	else
	{
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： " << PREWORDDATA.m_name << " 后缺失')'" << endl;
		m_isHaveWrong = true;
	}

	//中间代码生成
	Setlabel(label3);

	Statement();

	//中间代码生成
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
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： 缺失 'write' " << endl;
		m_isHaveWrong = true;
	}
	Expression();
	//中间代码生成
	Out();

	if (WORDDATA.m_name == ";")
	{
		GetNextSymbol();
	}
	else
	{
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： " << PREWORDDATA.m_name << " 后缺失';'" << endl;
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
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： 缺失 'read'" << endl;
		m_isHaveWrong = true;
	}
	string stepword;
	if (WORDDATA.m_type == "ID")
	{
		stepword = WORDDATA.m_name;
		//语义动作： 查符号表看标识符是否定义,给符号赋值
		if (!m_isHaveWrong)
		{
			if (!m_PropertyTable.IsFindSymbol(WORDDATA.m_name))
			{
				cout << "Line" << WORDDATA.m_indexLine << "： 变量 " << WORDDATA.m_name << " 未定义" << endl;
				isWrong = true;
			}
			else
				m_PropertyTable.SetData(WORDDATA.m_name, 0);
		}
		GetNextSymbol();
	}
	else
	{
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： read 后缺失标识符" << endl;
		m_isHaveWrong = true;
	}

	//中间代码生成
	In();
	Sto(m_PropertyTable.GetAddByNmme(stepword));
	Pop();

	if (WORDDATA.m_name == ";")
	{
		GetNextSymbol();
	}
	else
	{
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： " << PREWORDDATA.m_name << " 后缺失 ';'" << endl;
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
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： 缺失'{'" << endl;
		m_isHaveWrong = true;
	}
	Statement_List();
	if (WORDDATA.m_name == "}")
	{
		GetNextSymbol();
	}
	else
	{
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： " << PREWORDDATA.m_name << " 后缺失'}'" << endl;
		m_isHaveWrong = true;
	}
}


void CGrammarManager::Expression_Stat()
{

	if (WORDDATA.m_name != ";")
	{
		Expression();

		//中间代码生成@POP
		Pop();

		if (WORDDATA.m_name == ";")
		{
			GetNextSymbol();
		}
		else
		{
			//报错
			cout << "Line" << PREWORDDATA.m_indexLine << "： " << PREWORDDATA.m_name << " 后缺失';'" << endl;
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
	//超前读取字符
	if (WORDDATA.m_type == "ID" && m_ReceivingData->m_ProcessedData[m_nowIndex + 1].m_name == "=")
	{
		//语义动作： 检查符号表判断是否含有该ID
		if (!m_isHaveWrong)
		{
			if (!m_PropertyTable.IsFindSymbol(WORDDATA.m_name))
			{
				cout << "Line" << WORDDATA.m_indexLine << "： 变量 " << WORDDATA.m_name << " 未定义" << endl;
				//m_PropertyTable.Insert(WORDDATA.m_name);
				isWrong = true;
			}
			

		}

		//中间代码生成@LOOK
		stepWord = WORDDATA.m_name;
		address = m_PropertyTable.GetAddByNmme(stepWord);

		GetNextSymbol();


		if (WORDDATA.m_name == "=")
		{
			GetNextSymbol();
		}
		else
		{
			//报错
			cout << "Line" << PREWORDDATA.m_indexLine << "： " << PREWORDDATA.m_name << " 后缺失 '='" << endl;
			m_isHaveWrong = true;
		}
		Bool_Expr();

		//语义动作：给变量赋值
		m_PropertyTable.SetData(stepWord, 0);

		//中间代码生成
		Sto(address);
	}
	else if (WORDDATA.m_name == "(" || WORDDATA.m_type == "NUM" || WORDDATA.m_type == "ID")
	{
		Bool_Expr();
	}
	else
	{
		//报错
		cout << "Line" << PREWORDDATA.m_indexLine << "： 错误引用了符号" << PREWORDDATA.m_name << endl;
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

		//中间代码生成
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
		//中间代码生成
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

		//中间代码生成
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
			//报错
			cout << "Line" << PREWORDDATA.m_indexLine << "： " << PREWORDDATA.m_name << " 后缺失')'" << endl;
			m_isHaveWrong = true;
		}
	}
	else {
		if (WORDDATA.m_type == "ID" || WORDDATA.m_type == "NUM")
		{
			//语义动作： 检查是否赋初值
			if (!m_isHaveWrong && WORDDATA.m_type == "ID")
			{
				if (!m_PropertyTable.IsFindSymbol(WORDDATA.m_name))
				{
					cout << "Line" << WORDDATA.m_indexLine << "： 变量 " << WORDDATA.m_name << " 未定义" << endl;
					//m_PropertyTable.Insert(WORDDATA.m_name);
					isWrong = true;
				}
				else if (!m_PropertyTable.IsHaveData(WORDDATA.m_name))
				{
					cout << "Line" << WORDDATA.m_indexLine << "： 变量 " << WORDDATA.m_name << " 未初始化" << endl;
					m_PropertyTable.SetData(WORDDATA.m_name, 0);
					isWrong = true;
				}
			}

			//中间代码生成
			if (WORDDATA.m_type == "ID") Load(m_PropertyTable.GetAddByNmme(WORDDATA.m_name));
			else if (WORDDATA.m_type == "NUM") Loadi(StringToInt(WORDDATA.m_name));
			GetNextSymbol();
			return;
		}
		else
		{
			//报错
			cout << "Line" << PREWORDDATA.m_indexLine << "： 错误引用了符号" << PREWORDDATA.m_name << endl;
			m_isHaveWrong = true;
		}

	}
}

//将中间代码写入文本
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



//具体的属性文法及动作

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
