#include "stdafx.h"
#include "LL_1_Table.h"


CLL_1_Table::CLL_1_Table()
{
}


CLL_1_Table::~CLL_1_Table()
{
}


void CLL_1_Table::Init()
{
	vector<string> vec;
	m_NoumMapSet.Init();
	//line1
	vec = { "{","declaration_list","statement_list","}" };
	ADD_Tablelayer("program", "{", vec);
	vec.clear();
	//line2
	vec = { "A" };
	ADD_Tablelayer("declaration_list", "int", vec);
	vec.clear();
	//line3
	vec = { "B" };
	ADD_Tablelayer("statement_list", "if", vec);
	ADD_Tablelayer("statement_list", "while", vec);
	ADD_Tablelayer("statement_list", "for", vec);
	ADD_Tablelayer("statement_list", "write", vec);
	ADD_Tablelayer("statement_list", "read", vec);
	ADD_Tablelayer("statement_list", "ID", vec);
	ADD_Tablelayer("statement_list", "{", vec);
	ADD_Tablelayer("statement_list", ";", vec);
	vec.clear();
	//line4
	vec = { "declaration_stat","A" };
	ADD_Tablelayer("A", "int", vec);
	vec.clear();

	vec = { "epsilon" };
	ADD_Tablelayer("A", "if", vec);
	ADD_Tablelayer("A", "while", vec);
	ADD_Tablelayer("A", "for", vec);
	ADD_Tablelayer("A", "write", vec);
	ADD_Tablelayer("A", "read", vec);
	ADD_Tablelayer("A", "ID", vec);
	ADD_Tablelayer("A", "NUM", vec);
	ADD_Tablelayer("A", "{", vec);
	ADD_Tablelayer("A", "}", vec);
	ADD_Tablelayer("A", ";", vec);
	vec.clear();
	//line5
	vec = { "int","ID" };
	ADD_Tablelayer("declaration_stat", "int", vec);
	vec.clear();
	//line6
	vec = { "statement","B" };
	ADD_Tablelayer("B", "if", vec);
	ADD_Tablelayer("B", "while", vec);
	ADD_Tablelayer("B", "for", vec);
	ADD_Tablelayer("B", "write", vec);
	ADD_Tablelayer("B", "read", vec);
	ADD_Tablelayer("B", "ID", vec);
	ADD_Tablelayer("B", "NUM", vec);
	ADD_Tablelayer("B", "(", vec);
	ADD_Tablelayer("B", "{", vec);
	ADD_Tablelayer("B", ";", vec);
	vec.clear();

	vec = { "epsilon" };
	ADD_Tablelayer("B", "}", vec);
	vec.clear();
	//line7
	vec = { "if_stat" };
	ADD_Tablelayer("statement", "if", vec);
	vec.clear();
	vec = { "while_stat" };
	ADD_Tablelayer("statement", "while", vec);
	vec.clear();
	vec = { "for_stat" };
	ADD_Tablelayer("statement", "for", vec);
	vec.clear();
	vec = { "write_stat" };
	ADD_Tablelayer("statement", "write", vec);
	vec.clear();
	vec = { "read_stat" };
	ADD_Tablelayer("statement", "read", vec);
	vec.clear();

	vec = { "expr_stat" };
	ADD_Tablelayer("statement", "ID", vec);
	ADD_Tablelayer("statement", "NUM", vec);
	ADD_Tablelayer("statement", "(", vec);
	ADD_Tablelayer("statement", ";", vec);
	vec.clear();

	vec = { "compound_stat" };
	ADD_Tablelayer("statement", "{", vec);
	vec.clear();
	

	//line8,有可能需要特殊处理
	vec = { "if","(","expr",")","statement" };
	ADD_Tablelayer("if_stat", "if", vec);
	vec.clear();
	//line9
	vec = { "while","(","expr",")","statement" };
	ADD_Tablelayer("while_stat", "while", vec);
	vec.clear();
	//line10
	vec = { "for","(",";","expr",";","expr",";","expr",")","statement" };
	ADD_Tablelayer("for_stat", "for", vec);
	//line11
	vec = { "read","ID" };
	ADD_Tablelayer("read_stat", "read", vec);
	vec.clear();
	//line12
	vec = { "write","expr" };
	ADD_Tablelayer("write_stat", "write", vec);
	vec.clear();
	//line13
	vec = { "{","statement_list","}" };
	ADD_Tablelayer("compound_stat", "{", vec);
	vec.clear();
	//line14
	vec = { "expr",";" };
	ADD_Tablelayer("expr_stat", "ID", vec);
	ADD_Tablelayer("expr_stat", "NUM", vec);
	ADD_Tablelayer("expr_stat", "(", vec);
	vec.clear();

	vec = { ";" };
	ADD_Tablelayer("expr_stat", ";", vec);
	vec.clear();
	//line15
	vec = { "ID","=","bool_expr" };
	ADD_Tablelayer("expr", "ID", vec);
	vec.clear();

	vec = { "bool_expr" };
	ADD_Tablelayer("expr", "NUM", vec);
	ADD_Tablelayer("expr", "(", vec);
	vec.clear();

	//line16
	vec = { "additive_expr","E" };
	ADD_Tablelayer("bool_expr", "ID", vec);
	ADD_Tablelayer("bool_expr", "NUM", vec);
	ADD_Tablelayer("bool_expr", "(", vec);
	vec.clear();

	//line17
	vec = { "term","C" };
	ADD_Tablelayer("additive_expr", "ID", vec);
	ADD_Tablelayer("additive_expr", "NUM", vec);
	ADD_Tablelayer("additive_expr", "(", vec);

	//line18
	vec = { "epsilon" };
	ADD_Tablelayer("E", ";", vec);
	vec.clear();

	vec = { ">","<",">=","<=","==","!=","additive_expr" };
	ADD_Tablelayer("E", ">", vec);
	ADD_Tablelayer("E", "<", vec);
	ADD_Tablelayer("E", ">=", vec);
	ADD_Tablelayer("E", "<=", vec);
	ADD_Tablelayer("E", "==", vec);
	ADD_Tablelayer("E", "!=", vec);
	vec.clear();

	//line19
	vec = { "factor","D" };
	ADD_Tablelayer("term", "ID", vec);
	ADD_Tablelayer("term", "NUM", vec);
	ADD_Tablelayer("term", "(", vec);
	vec.clear();

	//line20
	vec = { "epsilon" };
	ADD_Tablelayer("C", ")", vec);
	ADD_Tablelayer("C", ";", vec);
	ADD_Tablelayer("C", ">", vec);
	ADD_Tablelayer("C", "<", vec);
	ADD_Tablelayer("C", ">=", vec);
	ADD_Tablelayer("C", "<=", vec);
	ADD_Tablelayer("C", "==", vec);
	ADD_Tablelayer("C", "!=", vec);
	vec.clear();

	vec = { "+","term","D" };
	ADD_Tablelayer("C", "+", vec);
	vec.clear();

	vec = { "-","term","D" };
	ADD_Tablelayer("C", "-", vec);
	vec.clear();

	//line21
	vec = { "(","expr",")" };
	ADD_Tablelayer("factor", "(", vec);
	vec = { "ID" };
	ADD_Tablelayer("factor", "ID", vec);
	vec = { "NUM" };
	ADD_Tablelayer("factor", "NUM", vec);

	//line22
	vec = { "epsilon" };
	ADD_Tablelayer("D", ")", vec);
	ADD_Tablelayer("D", ";", vec);
	ADD_Tablelayer("D", ">", vec);
	ADD_Tablelayer("D", "<", vec);
	ADD_Tablelayer("D", ">=", vec);
	ADD_Tablelayer("D", "<=", vec);
	ADD_Tablelayer("D", "==", vec);
	ADD_Tablelayer("D", "!=", vec);
	ADD_Tablelayer("D", "+", vec);
	ADD_Tablelayer("D", "-", vec);

	vec.clear();

	vec = { "*","factor","D" };
	ADD_Tablelayer("D", "*", vec);
	vec.clear();

	vec = { "/","factor","D" };
	ADD_Tablelayer("DDD", "/", vec);
	vec.clear();
	OutTable();
}


void CLL_1_Table::ADD_Tablelayer(const string& name, const string& symbol, const vector<string> &vec)
{
	try
	{
		int x = m_NoumMapSet.GetSynbolIDByName(name);
		int y = m_NoumMapSet.GetIntSymbolIDByName(symbol);
		if (!~x || !~y)
			throw runtime_error("ERROR:");
		m_Expr[x][y].left = name;
		m_Expr[x][y].right = vec;
	}
	catch (runtime_error err)
	{
		cout << err.what()
			<< "无法建立在 '" << name << "' 状态下处理 '" << symbol << "' 对应的转换关系式\n";
		return;
	}
	//cout << name << ' ' << symbol << ' '<< name << ' ' << vec[0] << endl;
}


void CLL_1_Table::OutTable()
{
	m_file.FileOpen("./message/LL(1)_Table.txt");
	for (int i = 0;i < 25;++i)
		for (int j = 0;j < 27;++j)
		{
			if (m_Expr[i][j].left != ""&&(!m_Expr[i][j].right.empty()))
			{
				m_file.FileFormat(20);
				m_file.FileWrite(m_NoumMapSet.GetSymbolNameByID(i));
				m_file.FileFormat(10);
				m_file.FileWrite(m_NoumMapSet.GetIntSymbolNameByID(j));
				m_file.FileFormat(30);
				m_file.FileWrite(m_Expr[i][j].left);
				string str;
				for (auto iter : m_Expr[i][j].right)
				{
					str += iter + ' ';
				}
				m_file.FileWrite(str+'\n');

			}
		}
	m_file.FileClose();
}
