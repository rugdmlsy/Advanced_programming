#include "check.h"
#include "total.h"
#include "user.h"
#include <string>
#include <cstdio>
#include "file.h"
#include <iostream>
#include "init.h"

using namespace std;

User user;
Seller seller;
Buyer buyer;

void User::sign_up()
{
    cout << "Please input your name: ";
    string name = check_str(10);
    while (total.search_user(name) != nullptr)
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
    char n[5];
    sprintf_s(n, "%03d", total.maxUID);
    uid += n;

    userNode *q = new userNode;
    q->usr.name = name;
    q->usr.pswd = pass;
    q->usr.number = num;
    q->usr.addr = addr;
    q->usr.ID = uid;
    userNode *p = total.userHead;
    if (p == nullptr)
        total.userHead = q;
    else
    {
        while (p->next != nullptr)
            p = p->next;
        p->next = q;
    }
    update_users();
    cout << "Sign in success!\n\n";
}

void User::log_in()
{
    cout << "Please input your name: ";
    string nm = check_str(10);
    userNode *p = total.userHead;
    while (p != nullptr)
    {
        if (p->usr.name == nm)
            break;
        p = p->next;
    }
    if (p == nullptr)
    {
        cout << "Not found!\n";
        return;
    }
    cout << "Please input your password: ";
    string pw = check_str(20);
    if (p->usr.pswd != pw)
    {
        cout << "Incorrect password!\n";
        return;
    }
    total.userNow = p;
    cout << "Log in success!\n\n";
    return user.menu();
}

void User::menu()
{
    while (1)
    {
        cout << "=========================================================\n";
        cout << "1.I'm buyer 2.I'm seller 3.Personal information 4.Exit\n";
        cout << "=========================================================\n";
        cout << "Please input your option: ";
        int opt = check_opt(1, 4);
        switch (opt)
        {
        case 1:
            buyer.menu();
            break;
        case 2:
            seller.menu();
            break;
        case 3:
            user.PIM_menu();
            break;
        case 4:
            return init_menu();
        }
    }
}

void User::PIM_menu()
{
    while (1)
    {
        cout << "=================================================================\n";
        cout << "1.View information 2.Modify information 3.Recharge 4.Exit\n";
        cout << "=================================================================\n";
        cout << "Please input your option: ";
        int opt = check_opt(1, 4);
        switch (opt)
        {
        case 1:
            user.view_info();
            break;
        case 2:
            user.modi_info();
            break;
        case 3:
            user.recharge();
            break;
        case 4:
            return user.menu();
        }
    }
}

void User::recharge()
{
    cout << "Current balance: ";
    printf("%.1lf\n", total.userNow->usr.balance);
    cout << "Please input recharge amount: ";
    double amo = check_db();
    total.userNow->usr.balance += amo;
    update_users();
    cout << "Recharge success!\n\n";
}

void User::modi_info()
{
    cout << "Please input your option(1.User name 2.Phone number 3.Address): ";
    int opt = check_opt(1, 3);
    switch (opt)
    {
    case 1:
    {
        cout << "Please input the modified name: ";
        string nm = check_str(10);
        total.userNow->usr.name = nm;
        break;
    }

    case 2:
    {
        cout << "Please input the modified number: ";
        string num = check_num(20);
        total.userNow->usr.number = num;
        break;
    }

    case 3:
    {
        cout << "Please input the modified address: ";
        string ad = check_str(40);
        total.userNow->usr.addr = ad;
        break;
    }
    }
    update_users();
    cout << "Modify success!\n\n";
}

void User::view_info()
{
    cout << "*****************************\n";
    cout << "User name: " << total.userNow->usr.name << endl;
    cout << "Phone number: " << total.userNow->usr.number << endl;
    cout << "Address: " << total.userNow->usr.addr << endl;
    cout << "Balance: " << total.userNow->usr.balance << endl;
    cout << "*****************************\n\n";
}

void Buyer::menu()
{
    while (1)
    {
        cout << "=====================================================================================\n";
        cout << "1.View goods 2.Buy goods 3.Search goods 4.My orders 5.View details 6.Exit\n";
        cout << "=====================================================================================\n";
        cout << "Please input your option: ";
        int opt = check_opt(1, 6);
        switch (opt)
        {
        case 1:
            buyer.see_goods();
            break;
        case 2:
            buyer.buy();
            break;
        case 3:
            buyer.search();
            break;
        case 4:
            buyer.see_orders();
            break;
        case 5:
            buyer.see_details();
            break;
        case 6:
            return user.menu();
        }
    }
}

void Buyer::buy() {
    cout << "Please input the commodity ID: ";
    string mid = check_ID('M');
    goodNode* p = total.search_good(mid);
    if (p == NULL) {
        cout << "Not found!\n";
        return;
    }
    cout << "Please input the amount: ";
    int amo = check_amo();
    string tm = total.gettime();
    cout << "************************************************\n";
    cout << "Please check the information of the commodity!\n";
    cout << "Date: " << tm << endl;
    cout << "Unit price: ";
    printf("%.1lf\n", p->gd.price);
    cout << "Amount: " << amo << endl;
    cout << "Your balance: ";
    printf("%.1lf\n", total.userNow->usr.balance);
    cout << "************************************************\n";
    cout << "Are you sure to buy?(y/n): ";
    string opt = check_yn();
    if (opt == "n") {
        cout << "Deal cancelled.\n\n";
        return;
    }
    if (amo > p->gd.amount) {
        cout << "The quantity of  is insufficient. The deal is cancelled.\n";
        return;
    }
    double amou = amo * p->gd.price;
    if (total.userNow->usr.balance < amou) {
        cout << "Your balance is insufficient. Please recharge first.\n";
        return;
    }
    total.userNow->usr.balance -= amou;
    p->gd.amount -= amo;
    if (p->gd.amount == 0)
        p->gd.state = "soldOut";
    userNode* slr = total.search_user(p->gd.sellerID);
    slr->usr.balance += amou;
    total.add_order();
    update_goods();
    update_order();
    update_users();
}

void Buyer::search()
{
    cout << "Please input the name of the commodity: ";
    string nm = check_str(20);
    goodNode *p = total.goodHead;
    cout << "****************************************************************\n";
    cout << "Commodity ID\tName\tPrice\tLaunch time\tSeller ID\n";
    while (p != nullptr)
    {
        if (p->gd.name.find(nm) != string::npos)
        {
            cout << p->gd.ID << "\t" << p->gd.name << "\t";
            printf("%.1lf\t", p->gd.price);
            cout << p->gd.time << "\t" << p->gd.sellerID << "\n";
        }
        p = p->next;
    }
    cout << "****************************************************************\n\n";
}

void Buyer::see_details()
{
    cout << "Please input the ID of the commodity you want to view: ";
    string mid = check_ID('M');
    goodNode *p = total.search_good(mid);
    if (p == nullptr)
    {
        cout << "Not found!\n";
        return;
    }
    cout << "***************************************\n";
    cout << "Commodity ID: " << p->gd.ID << "\n";
    cout << "Name: " << p->gd.name << "\n";
    cout << "Price: ";
    printf("%.1lf\n", p->gd.price);
    cout << "Launch time: " << p->gd.time << "\n";
    cout << "Description: " << p->gd.desc << "\n";
    cout << "Seller ID: " << p->gd.sellerID << "\n";
    cout << "***************************************\n\n";
}

void Buyer::see_orders()
{
    orderNode *p = total.orderHead;
    cout << "**************************************************************************\n";
    cout << "Order ID\tCommodity ID\tUnit price\tAmount\tDate\tSeller ID\n";
    while (p != nullptr)
    {
        if (p->odr.buyerID == total.userNow->usr.ID)
        {
            cout << p->odr.ID << "\t" << p->odr.goodID << "\t";
            printf("%.1lf\t", p->odr.price);
            cout << p->odr.amount << "\t" << p->odr.time << "\t" << p->odr.sellerID << "\n";
        }
        p = p->next;
    }
    cout << "**************************************************************************\n";
}

void Buyer::see_goods()
{
    goodNode *p = total.goodHead;
    cout << "**********************************************************************\n";
    cout << "Commodity ID\tName\tPrice\tLaunch time\tSeller ID\n";
    while (p != nullptr)
    {
        if (p->gd.state == "onSale")
        {
            cout << p->gd.ID << "\t" << p->gd.name << "\t";
            printf("%.1lf\t", p->gd.price);
            cout << p->gd.time << "\t" << p->gd.sellerID << "\n";
        }
        p = p->next;
    }
    cout << "**********************************************************************\n\n";
}

void Seller::menu()
{
    while (true)
    {
        cout << "=====================================================================================\n";
        cout << "1.Launch goods 2.View goods 3.Modify goods 4.Unshelve goods 5.View orders 6.Exit\n";
        cout << "=====================================================================================\n";
        cout << "Please input your option: ";
        int opt = check_opt(1, 6);
        switch (opt)
        {
        // case 1:
        //     seller_launch();
        //     break;
        // case 2:
        //     seller_see_goods();
        //     break;
        // case 3:
        //     seller_modi();
        //     break;
        // case 4:
        //     seller_unshelve();
        //     break;
        // case 5:
        //     seller_see_orders();
        //     break;
        case 6:
            return user.menu();
        }
    }
}