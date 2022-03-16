#pragma once
#include <string>
using namespace std;

typedef struct numNode
{
    double num = 0;
    char opr = '@';
    numNode* next = NULL;
    numNode* fore = NULL;
};

void add_num(double doub);
void add_opr(char oper, numNode* numHead);
//void dele_num();
double calculator(string expr);
bool check_calc(string expr);
bool check_oper(string expr);
int brac_move(string expr, int i);
bool check_brac(string expr, int& i);
bool check_dot(string expr);
bool is_oper(char oper);
bool is_num(char num);
void scan_neg(string expr, int& i, numNode* numHead);
void scan_num(string expr, int& i, numNode* numHead);
void add_mini(numNode* numHead);
bool multi_devi(numNode* numHead);
void scan(string expr, numNode* numHead);
