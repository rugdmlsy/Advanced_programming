#include <string>
#include <cmath>
#include <iostream>
#include <calculator.h>
using namespace std;
const string OPER = "+-*/";

numNode *head = new numNode;
numNode *now = head;

double calculator(string expr);

double eval(string expr)
{
    int l = expr.length() - 1;
    double s = 0;
    if (expr.find('.') == string::npos)
    {
        for (int i = 0; l >= 0; l--)
        {
            s += (expr[l] - '0') * pow(10, i);
            i++;
        }
    }
    else
    {
        int dot = expr.find('.') + 1;
        int d = dot - 2;
        for (int i = 0; d >= 0; d--)
        {
            s += (expr[d] - '0') * pow(10, i);
            i++;
        }
        for (int i = -1; dot <= l; dot++)
        {
            s += (expr[dot] - '0') * pow(10, i);
            i--;
        }
    }
    return s;
};

string token(string expr)
{
    int i = 0, l = expr.length();
    numNode *p = new numNode;
    if (expr[0] == '-')
    {
        i++;
        string n = "";
        while (i < l && expr.find(OPER) == string::npos)
        {
            n += expr[i];
            i++;
        }
        p->num = -eval(n);
        now->next = p;
        now = now->next;
    }
    else
    {
        string n = "";
        while (i < l && expr.find(OPER) == string::npos)
        {
            n += expr[i];
            i++;
        }
        p->num = eval(n);
        now->next = p;
        now = now->next;
    }
    if (i < l)
    {
        i++;
        numNode *p = new numNode;
        p->opr = expr[i];
    }
    while (i < l)
    {
    }
}

double operate(char oprt, double para1, double para2)
{
    if (oprt == '+')
        return para1 + para2;
    else if (oprt == '-')
        return para1 - para2;
    else if (oprt == '*')
        return para1 * para2;
    else if (oprt == '/')
    {
        if (para2 == 0)
        {
            cout << "The dividend cannot be zero" << endl;
            exit(-1);
        }
        return para1 / para2;
    }
}

double operate(char neg, double para)
{
    return -para;
}