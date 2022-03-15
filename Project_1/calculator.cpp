#include <string>
#include <cmath>
#include <iostream>
#include "calculator.h"
using namespace std;
const string OPER = "+-*/";
const string VALIDCHAR = "+-*/1234567890.()";
numNode numHead;

double calculator(string expr)
{
	numNode *numNow = &numHead;

	// check if wrong syntax

	// remove brackets
	string expr_1 = "";
	int l = expr.length();
	for (int i = 0; i < l; i++)
	{
		if (expr[i] == '(')
		{
			string bra = "";
			for (i++; expr[i] != ')'; i++)
				bra += expr[i];
			numNode *q = new numNode;
			q->num = calculator(bra);
			numNow->next = q;
		}
	}

	// do multi and devide

	// do add and minus
	int index = 0, len = expr.length();
	if (expr[0] == '-')
	{
		string neg_num = "";
		for (index = 1; index < len && expr[index] <= '9' && expr[index] >= '0'; index++)
			neg_num += expr[index];
		if (index < len)
			index++;
		numHead.num = eval(neg_num);
	}
};

bool check_calc(string expr) {
	//check invalid characters
	for (int i = 0; i < expr.length(); i++) {
		if (VALIDCHAR.find(expr[i]) == string::npos) {
			cout << "The input contains invalid characters!\n";
			return false;
		}
	}

	//check brackets
	for (int i = 0; i < expr.length(); i++) {
		if (expr[i] == ')') {
			cout << "Invalid brackets!\n";
			return false;
		}
		if (expr[i] == '(') 
			if (!check_brac(expr, i))
				return false;
	}
	
	//check if operator misuse
	if (OPER.find(expr[0]) != string::npos) {
		if (expr[0] != '-') {
			cout << "Operator misuse!\n";
			return false;
		}

	}
	for (int i = 1; i < expr.length();i++) {
		if (OPER.find(expr[i]) != string::npos) {
			if (i == expr.length() - 1 || OPER.find(expr[i + 1]) != string::npos) {
				cout << "Operator misuse!\n";
				return false;
			}
		}
	}
}

bool check_oper(string expr) {
	if (OPER.find(expr[0]) != string::npos) {
		if (expr[0] != '-') {
			cout << "Operator misuse!\n";
			return false;
		}

	}
	for (int i = 1; i < expr.length();i++) {
		if (OPER.find(expr[i]) != string::npos) {
			if (i == expr.length() - 1 || OPER.find(expr[i + 1]) != string::npos) {
				cout << "Operator misuse!\n";
				return false;
			}
		}
	}
}

bool check_brac(string expr, int& i) {
	int ini = i;
	i++;
	while (i < expr.length()) {
		if (expr[i] == ')') {
			if (i == ini + 1) {
				cout << "Please do not input empty brackets!\n";
				return false;
			}
			string sub(expr, ini + 1, i - 1);
			if(!check_oper(sub))
				return false;
			return true;
		}
		if (expr[i] == '(') 
			if (!check_brac(expr, i))
				return false;
		i++;
	}
	
	cout << "Invalid brackets!\n";
	return false;
}

void scan(string expr) {

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