#include <iostream>
#include <string>
#include "check.h"
using namespace std;

double check_db() {
    double i;
    while (!(cin >> i) || i <= 0)
        cout << "Invalid input! Please input again: ";
    return i;
}

int check_opt(int min, int max)
{
    int i;
    while (!(cin >> i) || i < min || i > max)
        cout << "Invalid input! Please input again: ";
    return i;
}

string check_ID(char opt)
{
    string id;
    while (!(cin >> id) || id.length() != 4 || id[0] != opt || id[1] < '0' ||
           id[1] > '9' || id[2] < '0' || id[2] > '9' || id[3] < '0' || id[3] > '9')
        cout << "Invalid ID! Please input again: ";
    return id;
}

string check_yn()
{
    string opt = "";
    cin >> opt;
    while (opt != "y" && opt != "n")
    {
        cout << "Please input y or n: ";
        cin >> opt;
    }
    return opt;
}

string check_num(int len)
{
    string ret;
    cin >> ret;
    while (ret.length() > len || !range_in(ret, '0', '9'))
    {
        if (ret.length() > len)
            cout << "Please enter a maximum of " << len << " characters: ";
        else
            cout << "Invalid input! Please enter numbers: ";
        cin >> ret;
    }
    return ret;
}

string check_str(int len)
{
    string ret;
    cin >> ret;
    while (ret.length() > len || ret.find(",") != string::npos)
    {
        if (ret.length() > len)
            cout << "Please enter a maximum of " << len << " characters: ";
        else
            cout << "Please do not enter comma symbol.\n";
        cin >> ret;
    }
    return ret;
}

bool range_in(string str, char min, char max)
{
    for (int i = 0, len = str.length(); i < len; i++)
        if (str[i] < min || str[i] > max)
            return false;
    return true;
}

int check_amo() {
    int amo;
    while (!(cin >> amo) || amo <= 0) 
        cout << "Invalid input! Please input again: ";
    return amo;
}