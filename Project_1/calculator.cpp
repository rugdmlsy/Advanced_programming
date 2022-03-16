#include <string>
#include <cmath>
#include <iostream>
#include "calculator.h"
#include "total.h"
using namespace std;
const string OPER = "+-*/";
const string VALIDCHAR = "+-*/1234567890.()";



double calculator(string expr)
{
	numNode *numHead = NULL;
	// check if wrong syntax
	if (!check_calc(expr))
		exit(-1);

	// scan expression
	scan(expr, numHead);

	// test
	numNode *p = numHead;
	while (p != NULL)
	{
		if (p->opr == '@')
			cout << p->num << " ";
		else
			cout << p->opr << " ";
		p = p->next;
	}
	return 0;

	// do multi and devide
	if (!multi_devi(numHead))
		exit(-1);

	// do add and minus
	add_mini(numHead);
	double ret = numHead->num;
	delete numHead;
	numHead = NULL;

	// delete the linked list
	// dele_num();

	return ret;
}

// void dele_num() {
//	while (numHead != NULL) {
//		numHead = numHead->next;
//		free(numHead->fore);
//	}
// }

bool multi_devi(numNode* numHead)
{
	numNode *now = numHead;
	while (now != NULL)
	{
		if (now->opr == '*')
		{
			double db = now->fore->num * now->next->num;
			now->fore->num = db;
			now->fore->next = now->next->next;
			numNode *p = now->fore;
			now = p;
		}
		else if (now->opr == '/')
		{
			if (now->next->num == 0)
				return false;
			double db = now->fore->num / now->next->num;
			now->fore->num = db;
			now->fore->next = now->next->next;
			numNode *p = now->fore;
			now = p;
		}
		now = now->next;
	}
	return true;
}

void add_mini(numNode* numHead)
{
	numNode *now = numHead;
	while (now != NULL)
	{
		if (now->opr == '+' && now->fore != NULL)
		{
			double db = now->fore->num + now->next->num;
			now->fore->num = db;
			now->fore->next = now->next->next;
			numNode *p = now->fore;
			now = p;
		}
		else if (now->opr == '-')
		{
			double db = now->fore->num - now->next->num;
			now->fore->num = db;
			now->fore->next = now->next->next;
			numNode *p = now->fore;
			now = p;
		}
		now = now->next;
	}
}

bool check_calc(string expr)
{

	// ***the order can't be changed!***

	// check invalid characters
	for (int i = 0; i < expr.length(); i++)
	{
		if (VALIDCHAR.find(expr[i]) == string::npos)
		{
			cout << "The input contains invalid characters!\n";
			return false;
		}
	}

	// check brackets
	for (int i = 0; i < expr.length(); i++)
	{
		if (expr[i] == ')')
		{
			cout << "i: " << i << "len: " << expr.length() << "expr: " << expr << endl; // test
			cout << "Invalid brackets!\n";
			return false;
		}
		if (expr[i] == '(')
		{
			if (i != 0)
				if (!is_oper(expr[i - 1]))
				{
					cout << "Operator misuse!\n";
					return false;
				}
			if (!check_brac(expr, i))
				return false;
			cout << "test i:" << i << endl; // test
		}
	}

	// check if operator misuse
	if (!check_oper(expr))
		return false;

	// check the dot
	if (!check_dot(expr))
		return false;

	return true;
}

bool is_num(char num)
{
	if ('0' <= num && num <= '9')
		return true;
	return false;
}

bool is_oper(char oper)
{
	if (OPER.find(oper) == string::npos)
		return false;
	return true;
}

bool check_dot(string expr)
{
	if (expr[0] == '.' || expr[expr.length() - 1] == '.')
	{
		cout << "Number format error!\n";
		return false;
	}
	int i = 1;
	while (i < expr.length())
	{
		if (expr[i] == '.')
		{
			if (!is_num(expr[i - 1]) || !is_num(expr[i + 1]))
			{
				cout << "Number format error!\n";
				return false;
			}
			i++;
			while (i < expr.length())
			{
				if (is_oper(expr[i]) || expr[i] == '(')
					break;
				else if (expr[i] == '.')
				{
					cout << "Number format error!\n";
					return false;
				}
				i++;
			}
		}
		if (expr[i] == '(')
			i = brac_move(expr, i);
		i++;
	}
	return true;
}

bool check_oper(string expr)
{
	int i = 0, len = expr.length();
	if (expr[0] == '-')
	{
		if (len == 1 || is_oper(expr[1]))
		{
			cout << "Operator misuse!\n";
			return false;
		}
		i = 1;
	}
	else if (is_oper(expr[0]))
	{
		cout << "Operator misuse!\n";
		return false;
	}
	while (i < len)
	{
		if (is_oper(expr[i]))
		{
			if (i == len - 1 || is_oper(expr[i + 1]))
			{
				// cout <<"test2: "<<expr<<" "<< i << " " << expr[i + 1] << len << endl; //test
				cout << "Operator misuse!\n";
				return false;
			}
		}
		else if (expr[i] == '(')
			i = brac_move(expr, i);
		i++;
	}
	return true;
}

int brac_move(string expr, int i)
{
	int j = i + 1;
	while (expr[j] != ')')
	{
		if (expr[j] == '(')
			j = brac_move(expr, j);
		j++;
	}
	return j;
}

bool check_brac(string expr, int &i) // must do first
{
	int ini = i;
	i++;
	while (i < expr.length())
	{
		if (expr[i] == ')')
		{
			if (i == ini + 1)
			{
				cout << "Please do not input empty brackets!\n";
				return false;
			}
			if (i != expr.length() - 1 && !is_oper(expr[i + 1]) && expr[i + 1] != ')')
			{
				cout << "Operator misuse!\n";
				return false;
			}
			string sub(expr, ini + 1, i - 1 - ini);
			// cout <<"test1: "<< sub <<" "<<i<<" "<<ini << endl;		//test
			if (!check_oper(sub) || !check_dot(sub))
				return false;
			return true;
		}
		if (expr[i] == '(')
		{
			if (i != 0)
				if (!is_oper(expr[i - 1]) && expr[i - 1] != '(')
				{
					cout << "Operator misuse!\n";
					return false;
				}
			if (!check_brac(expr, i))
				return false;
		}
		i++;
	}
	cout << "Invalid brackets!\n";
	return false;
}

void scan(string expr, numNode* numHead)
{
	int i = 0;
	if (expr[0] == '-')
		scan_neg(expr, i, numHead);
	while (i < expr.length())
	{

		if (is_num(expr[i]))
		{
			scan_num(expr, i, numHead);
			i--;
		}
		else if (expr[i] == '(')
		{
			string sub(expr, i + 1, brac_move(expr, i) - 1 - i);
			cout << "sub:" << sub << endl; // test
			add_num(calculator(sub));
		}
		else
			add_opr(expr[i], numHead);

		i++;
	}
}

void scan_num(string expr, int &i, numNode* numHead)
{
	string sub = "";
	while (i < expr.length())
	{
		if (is_num(expr[i]) || expr[i] == '.')
			sub += expr[i];
		else
			break;
		i++;
	}
	double db = stod(sub);
	add_num(db);
}

void scan_neg(string expr, int &i, numNode* numHead)
{
	i++;
	string sub = "";
	while (i < expr.length())
	{
		if (is_num(expr[i]) || expr[i] == '.')
			sub += expr[i];
		else
			break;
		i++;
	}
	double db = -1 * stod(sub);
	add_num(db);
}

void add_num(double doub)
{
	extern numNode* numHead;
	numNode *q = new numNode;
	q->num = doub;
	numNode *p = numHead;
	if (numHead == NULL)
	{
		numHead = q;
		return;
	}
	while (p->next != NULL)
		p = p->next;
	p->next = q;
	q->fore = p;
}

void add_opr(char oper, numNode* numHead)
{
	numNode *q = new numNode;
	q->opr = oper;
	numNode *p = numHead;
	while (p->next != NULL)
		p = p->next;
	p->next = q;
	q->fore = p;
}

// double eval(string expr)
//{
//     int l = expr.length() - 1;
//     double s = 0;
//     if (expr.find('.') == string::npos)
//     {
//         for (int i = 0; l >= 0; l--)
//         {
//             s += (expr[l] - '0') * pow(10, i);
//             i++;
//         }
//     }
//     else
//     {
//         int dot = expr.find('.') + 1;
//         int d = dot - 2;
//         for (int i = 0; d >= 0; d--)
//         {
//             s += (expr[d] - '0') * pow(10, i);
//             i++;
//         }
//         for (int i = -1; dot <= l; dot++)
//         {
//             s += (expr[dot] - '0') * pow(10, i);
//             i--;
//         }
//     }
//     return s;
// };
//
// string token(string expr)
//{
//     int i = 0, l = expr.length();
//     numNode *p = new numNode;
//     if (expr[0] == '-')
//     {
//         i++;
//         string n = "";
//         while (i < l && expr.find(OPER) == string::npos)
//         {
//             n += expr[i];
//             i++;
//         }
//         p->num = -eval(n);
//         now->next = p;
//         now = now->next;
//     }
//     else
//     {
//         string n = "";
//         while (i < l && expr.find(OPER) == string::npos)
//         {
//             n += expr[i];
//             i++;
//         }
//         p->num = eval(n);
//         now->next = p;
//         now = now->next;
//     }
//     if (i < l)
//     {
//         i++;
//         numNode *p = new numNode;
//         p->opr = expr[i];
//     }
//     while (i < l)
//     {
//     }
// }
//
// double operate(char oprt, double para1, double para2)
//{
//     if (oprt == '+')
//         return para1 + para2;
//     else if (oprt == '-')
//         return para1 - para2;
//     else if (oprt == '*')
//         return para1 * para2;
//     else if (oprt == '/')
//     {
//         if (para2 == 0)
//         {
//             cout << "The dividend cannot be zero" << endl;
//             exit(-1);
//         }
//         return para1 / para2;
//     }
// }
//
// double operate(char neg, double para)
//{
//     return -para;
// }