#pragma once
#include <string>
using namespace std;
int check_opt(int min, int max);
string check_ID(char opt);
string check_yn();
string check_str(int len);
string check_num(int len);
bool range_in(string str, char min, char max);
double check_db();