#pragma once
#include <string>
using namespace std;

 typedef struct numNode
{
    double num;
    char opr = '@';
    numNode *next = NULL;
    numNode* fore = NULL;
};

 bool check_calc(string expr);
 bool check_oper(string expr);
 int brac_move(string expr, int i);
 bool check_brac(string expr, int& i);
 bool check_dot(string expr);
 bool is_oper(char oper);
 bool is_num(char num);


double calculator(string expr);                        // the main fuction
double operate(char oprt, double para1, double para2); // operate the parameters
double operate(char neg, double para);                 // reload the negative sign
string token(string expr);                             // divide the string
double eval(string expr);                              // turn string to number