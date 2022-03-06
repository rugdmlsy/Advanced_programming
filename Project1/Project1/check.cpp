#include <iostream>
#include <string>
using namespace std;

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