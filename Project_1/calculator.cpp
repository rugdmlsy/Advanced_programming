#include <string>
#include <cmath>
#include <iostream>
#include "calculator.h"
using namespace std;
const string OPER = "+-*/";
const string VALIDCHAR = "+-*/1234567890.()";
numNode numHead;

//double calculator(string expr)
//{
//	numNode *numNow = &numHead;
//
//	// check if wrong syntax
//
//	// remove brackets
//	string expr_1 = "";
//	int l = expr.length();
//	for (int i = 0; i < l; i++)
//	{
//		if (expr[i] == '(')
//		{
//			string bra = "";
//			for (i++; expr[i] != ')'; i++)
//				bra += expr[i];
//			numNode *q = new numNode;
//			q->num = calculator(bra);
//			numNow->next = q;
//		}
//	}
//
//	// do multi and devide
//
//	// do add and minus
//	int index = 0, len = expr.length();
//	if (expr[0] == '-')
//	{
//		string neg_num = "";
//		for (index = 1; index < len && expr[index] <= '9' && expr[index] >= '0'; index++)
//			neg_num += expr[index];
//		if (index < len)
//			index++;
//		numHead.num = eval(neg_num);
//	}
//	return 0;//for test
//}

bool check_calc(string expr) {
	
	// ***the order can't be changed!***
	
	//check invalid characters
	for (int i = 0; i < expr.length(); i++) {
		if (VALIDCHAR.find(expr[i]) == string::npos) {
			cout << "The input contains invalid characters!\n";
			return false;
		}
	}

	// check brackets 
	for (int i = 0; i < expr.length(); i++) {
		if (expr[i] == ')') {
			cout << "Invalid brackets!\n";
			return false;
		}
		if (expr[i] == '(') {
			if (i != 0)
				if (!is_oper(expr[i - 1])) {
					cout << "Operator misuse!\n";
					return false;
				}
			if (!check_brac(expr, i))
				return false;
		}
	}
	
	//check if operator misuse
	if (!check_oper(expr))
		return false;

	//check the dot
	if (!check_dot(expr))
		return false;

	return true;
}

bool is_num(char num) {
	if ('0' <= num && num <= '9')
		return true;
	return false;
}

bool is_oper(char oper) {
	if (OPER.find(oper) == string::npos)
		return false;
	return true;
}

bool check_dot(string expr) {
	if (expr[0] == '.' || expr[expr.length() - 1] == '.') {
		cout << "Number format error!\n";
		return false;
	}
	int i = 1;
	while (i < expr.length()) {
		if (expr[i] == '.') {
			if (!is_num(expr[i - 1]) || !is_num(expr[i + 1])) {
				cout << "Number format error!\n";
				return false;
			}
			i++;
			while (i < expr.length()) {
				if (is_oper(expr[i]) || expr[i] == '(')
					break;
				else if (expr[i] == '.') {
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

bool check_oper(string expr) {
	int i = 0;
	if (expr[0] == '-') {
		if (expr.length() == 1 || OPER.find(expr[1]) != string::npos) {
			cout << "Operator misuse!\n";
			return false;
		}
		i = 1;
	}
	else if (OPER.find(expr[0]) != string::npos) {
		cout << "Operator misuse!\n";
		return false;
	}
	while (i < expr.length()) {
		if (OPER.find(expr[i]) != string::npos) {
			if (i == expr.length() - 1 || OPER.find(expr[i + 1]) != string::npos) {
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

int brac_move(string expr, int i) {
	int j = i + 1;
	while (expr[j] != ')') {
		if (expr[j] == '(')
			j = brac_move(expr, j) + 1;
		j++;
	}
	return j;
}

bool check_brac(string expr, int& i) //must do first
{
	int ini = i;
	i++;
	while (i < expr.length()) {
		if (expr[i] == ')') {
			if (i == ini + 1) {
				cout << "Please do not input empty brackets!\n";
				return false;
			}
			if (i != expr.length() - 1)
				if (!is_oper(expr[i + 1])) {
					cout << "Operator misuse!\n";
					return false;
				}
			string sub(expr, ini + 1, i - 1);
			if(!check_oper(sub) || !check_dot(sub))
				return false;
			return true;
		}
		if (expr[i] == '(') {
			if (i != 0) 
				if (!is_oper(expr[i - 1])) {
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