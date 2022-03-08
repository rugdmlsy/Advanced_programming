#include "check.h"
#include "total.h"
#include "user.h"
#include <string>
#include <cstdio>
#include "file.h"
#include <iostream>
#include "init.h"
using namespace std;

void user_sign_up()
{
    cout << "Please input your name: ";
    string name = check_str(10);
    while (search_user(name) != nullptr)
    {
        cout << "Your name is occupied. Please input again: ";
        name = check_str(10);
    }
    cout << "Please input your password: ";
    string pass = check_str(20); // Chinese character is allowed
    cout << "Please input your number: ";
    string num = check_num(20);
    cout << "Please input yout address: ";
    string addr = check_str(40);
    total.maxUID += 1;
    string uid = "U";
    char n[4];
    sprintf(n, "%03d", total.maxUID);
    uid += num;

    userNode *q = new userNode;
    q->usr.name = name;
    q->usr.pswd = pass;
    q->usr.number = num;
    q->usr.addr = addr;
    q->usr.ID = uid;
    userNode *p = userHead;
    if (p == nullptr)
        p = q;
    else
    {
        while (p->next != nullptr)
            p = p->next;
        p->next = q;
    }
    update_user();

    cout << "Sign up success!\n\n";
    return init_menu();
}

void user_log_in()
{
}

void user_menu()
{
}