#define ADMINNAME "admin"
#define ADMINPASSWORD "123456"
#include <iostream>
#include <string>
#include <cstdio>
#include "init.h"
#include "admin.h"
#include "check.h"
#include "goods.h"
#include "total.h"
#include "file.h"
#include "user.h"
using namespace std;

void admin_log_in()
{
    cout << "Please input the admin name: ";
    string n, p;
    cin >> n;
    cout << "Please input the password: ";
    cin >> p;
    if (n != ADMINNAME || p != ADMINPASSWORD)
    {
        cout << "The name or the password is wrong! Log in failed!\n\n";
        init_menu();
    }
    else
    {
        cout << "\n------------Log in success!------------\n\n";
        admin_menu();
    }
}

void admin_see_goods()
{
    goodNode *p = total.goodHead;
    cout << "*****************************************************************************\n";
    cout << "ID\tName\tPrice\tLaunch date\tSeller ID\tAmount\tState\n";
    while (p != nullptr)
    {
        cout << p->gd.ID << "\t" << p->gd.name << "\t";
        printf("%.1lf\t", p->gd.price);
        cout << p->gd.time << "\t" << p->gd.sellerID << "\t" << p->gd.amount << "\t" << p->gd.state << "\n";
        p = p->next;
    }
    cout << "*****************************************************************************\n\n";
}

void admin_see_orders()
{
    orderNode *p = total.orderHead;
    cout << "*****************************************************************************\n";
    cout << "Order ID\tCommodity ID\tUnit price\tAmount\tDate\tSeller ID\tBuyer ID\n";
    while (p != nullptr)
    {
        cout << p->odr.ID << "\t" << p->odr.goodID << "\t";
        printf("%.1lf\t", p->odr.price);
        cout << p->odr.time << "\t" << p->odr.sellerID << "\t" << p->odr.buyerID << "\n";
        p = p->next;
    }
    cout << "*****************************************************************************\n\n";
}

void admin_see_users()
{
    userNode *p = total.userHead;
    cout << "***********************************************************************************\n";
    cout << "ID\tName\tPhone number\tAddress\tBalance\tState\n";
    
    if (p == nullptr) // for test
        cout << "test\n";
    if (total.userHead == nullptr)
        cout << "test total\n";
    
    while (p != nullptr)
    {
        cout << p->usr.ID << "\t" << p->usr.name << "\t" << p->usr.number << "\t" << p->usr.addr << "\t";
        printf("%.1lf\t", p->usr.balance);
        cout << p->usr.state << "\n";
        p = p->next;
    }
    cout << "***********************************************************************************\n\n";
}

void admin_ban()
{
    cout << "Please input the ID of the user you want to ban: ";
    string uid = check_ID('U');
    userNode *p = search_user(uid);
    if (p == nullptr)
    {
        cout << "Not found!\n";
        return;
    }
    cout << "Please confirm the information:\n";
    cout << "*************************************************************************************\n";
    cout << p->usr.ID << "\t" << p->usr.name << "\t" << p->usr.number << "\t" << p->usr.addr << "\t";
    printf("%.1lf\n", p->usr.balance);
    cout << "*************************************************************************************\n\n";
    cout << "Are you sure to ban the user?(y/n): ";
    string opt = check_yn();
    if (opt == "y")
    {
        p->usr.state = "inactive";
        update_users();
        cout << "Banning success!\n\n";
    }
    else
        cout << "Banning cancelled.\n\n";
}

void admin_unshelve()
{
    cout << "Please input the ID of the commodity you want to unshelve: ";
    string mid = check_ID('M');
    goodNode *p = search_good(mid);
    if (p == nullptr)
    {
        cout << "Not found!\n\n";
        return;
    }
    cout << "Please confirm the information:\n";
    cout << "*********************************************************************\n";
    cout << "ID\tName\tPrice\tLaunch date\tAmount\tSeller ID\tState\n";
    cout << p->gd.ID << "\t" << p->gd.name << "\t";
    printf("%.1lf\t", p->gd.price);
    cout << p->gd.time << "\t" << p->gd.amount << "\t" << p->gd.sellerID << "\t" << p->gd.state << "\n";
    cout << "*********************************************************************\n";
    cout << "Are you sure to unshelve it?(y/n): ";
    string opt = check_yn();
    if (opt == "y")
    {
        p->gd.state = "soldOut";
        update_goods();
        cout << "Unshelve success!\n\n";
    }
    else
        cout << "Unshelve cancelled.\n\n";
}

void admin_search_goods()
{
    cout << "Please input the commodity name: ";
    string n;
    cin >> n;
    goodNode *p = total.goodHead;
    cout << "*************************************************************************\n";
    cout << "ID\tName\tPrice\tLaunch time\tSeller ID\tAmount\tState\n";
    while (p != nullptr)
    {
        if (p->gd.name.find(n) != string::npos)
        {
            cout << p->gd.ID << "\t" << p->gd.name << "\t";
            printf("%.1lf\t", p->gd.price);
            cout << p->gd.time << "\t" << p->gd.sellerID << "\t" << p->gd.amount << "\t" << p->gd.state << "\n";
        }
        p = p->next;
    }
    cout << "*************************************************************************\n\n";
}

void admin_menu()
{
    while (1)
    {
        cout << "============================================================================================\n";
        cout << "1.View goods 2.Search goods 3.Unshelve goods 4.View orders 5.View users 6.Ban a user 7.Exit\n";
        cout << "============================================================================================\n\n";
        cout << "Please input the option: ";
        int opt = check_opt(1, 7);
        switch (opt)
        {
        case 1:
            admin_see_goods();
            break;
        case 2:
            admin_search_goods();
            break;
        case 3:
            admin_unshelve();
            break;
        case 4:
            admin_see_orders();
            break;
        case 5:
            admin_see_users();
            break;
        case 6:
            admin_ban();
            break;
        case 7:
            init_menu();
            break;
        }
    }
}