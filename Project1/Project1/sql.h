#pragma once
#include <string>
using namespace std;

struct sqlNode
{
    string val;
    sqlNode *next = nullptr;
};

void lexical(string expr);
void insert_into(string name, string val, ...);
void update_set(string name, string col, string val, ...);
void select(string sel, string name, string col, string val);