#include "check.h"
#include "total.h"
#include "user.h"
#include <string>
#include <cstdio>
#include "file.h"
#include <iostream>
#include "init.h"
#include <ctime>

using namespace std;

User user;
Seller seller;
Buyer buyer;

void User::assign(string uid, string unm, string upw, string upn, string uad, double ubad, string ust) {
    ID = uid;
    name = unm;
    pswd = upw;
    number = upn;
    addr = uad;
    balance = ubad;
    state = ust;
}

void User::setID() {
    total.maxUID += 1;
    char n[5];
    sprintf_s(n, "U%03d", total.maxUID);
    ID = n;
}

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
    

    userNode *q = new userNode;
    q->usr.name = name;
    q->usr.pswd = pass;
    q->usr.number = num;
    q->usr.addr = addr;
    q->usr.setID();

    total.add_user(q);
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

    orderNode* o = new orderNode;
    o->odr.setID();
    o->odr.amount = amo;
    o->odr.goodID = p->gd.ID;
    o->odr.price = p->gd.price;
    o->odr.time = total.gettime();
    o->odr.sellerID = p->gd.sellerID;
    o->odr.buyerID = total.userNow->usr.ID;

    total.add_order(o);
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
         case 1:
             seller.launch();
             break;
         case 2:
             seller.see_goods();
             break;
         case 3:
             seller.modi();
             break;
         case 4:
             seller.unshelve();
             break;
         case 5:
             seller.see_orders();
             break;
        case 6:
            return user.menu();
        }
    }
}

void Seller::launch() {
    cout << "Please input the name: ";
    string lname = check_str(20);
    cout << "Please input the price: ";
    double lprice = check_db();
    cout << "Please input the amount: ";
    int lamount = check_amo();
    cout << "Please input the description: ";
    string ldesc = check_str(200);
    cout << "Please confirm to launch(y/n): ";
    string lopt = check_yn();
    if (lopt == "n") {
        cout << "Launch cancelled.\n\n";
        return;
    }

    goodNode* p = new goodNode;
    p->gd.name = lname;
    p->gd.price = lprice;
    p->gd.desc = ldesc;
    p->gd.amount = lamount;
    total.add_good(p);
    update_goods();

    cout << "Launch success!\n\n";
}

void Seller::modi() {
    cout << "Please input the commodity ID: ";
    string mid = check_ID('M');
    goodNode* p = total.search_good(mid);
    if (p == NULL) {
        cout << "Not found!\n\n";
        return;
    }
    cout << "Please choose the arribute you want to modify(1.Price 2.Description): ";
    int opt = check_opt(1, 2);
    if (opt == 1) {
        cout << "Please input the modified price: ";
        double prc = check_db();
        cout << "Please check the modified information of the commodity:\n";
        cout << "*****************************************************\n";
        cout << "Commodity ID: " << p->gd.ID << endl;
        cout << "Name: " << p->gd.name << endl;
        printf("Price: %.1lf\n", prc);
        cout << "Description: " << p->gd.desc << endl;
        cout << "*****************************************************\n";
        cout << "Please confirm the modification(y/n): ";
        string yn = check_yn();
        if (yn == "n") {
            cout << "Modification cancelled.\n\n";
            return;
        }
        p->gd.price = prc;
        update_goods();
        cout << "Modify success!\n\n";
    }
    else if (opt == 2) {
        cout << "Please input the modified description: ";
        string des = check_str(200);
        cout << "Please check the modified information of the commodity:\n";
        cout << "*****************************************************\n";
        cout << "Commodity ID: " << p->gd.ID << endl;
        cout << "Name: " << p->gd.name << endl;
        printf("Price: %.1lf\n", p->gd.price);
        cout << "Description: " << des << endl;
        cout << "*****************************************************\n";
        cout << "Please confirm the modification(y/n): ";
        string yn = check_yn();
        if (yn == "n") {
            cout << "Modification cancelled.\n\n";
            return;
        }
        p->gd.desc = des;
        update_goods();
        cout << "Modify success!\n\n";
    }
}

void Seller::unshelve() {
    cout << "Please input the ID of the commodity you want to unshelve: ";
    string mid = check_ID('M');
    goodNode* p = total.search_good(mid);
    if (p == NULL) {
        cout << "Not found!\n";
        return;
    }
    cout << "Please check the commodity information:\n";
    cout << "************************************\n";
    cout << "Commodity ID: " << p->gd.ID<<endl;
    cout << "Name: " << p->gd.name << endl;
    printf("Price: %.1lf\n", p->gd.price);
    cout << "Launch time: " << p->gd.time << endl;
    cout << "Amount: " << p->gd.amount << endl;
    cout << "Seller ID: " << p->gd.sellerID << endl;
    cout << "State: " << p->gd.state << endl;
    cout << "************************************\n";
    cout << "Please choose(y/n): ";
    string opt = check_yn();
    if (opt == "y") {
        cout << "Unshelve cancelled.\n\n";
        return;
    }
    p->gd.state = "soldOut";
    update_goods();
    cout << "Unshelve success!\n\n";
}

void Seller::see_orders() {
    cout << "********************************************************************\n";
    cout << "Order ID\tCommodity ID\tUnit price\tAmount\tDate\tBuyer ID\n";
    orderNode* p = total.orderHead;
    while (p != NULL) {
        if (p->odr.sellerID == total.userNow->usr.ID) {
            cout << p->odr.ID << "\t" << p->odr.goodID << "\t";
            printf("%.1lf\t", p->odr.price);
            cout << p->odr.amount << "\t" << p->odr.time << "\t" << p->odr.buyerID << "\n";
        }
        p = p->next;
    }
    cout << "********************************************************************\n\n";
}

void Seller::see_goods() {
    goodNode* p = total.goodHead;
    cout << "******************************************************************\n";
    cout << "Commodity ID\tName\tPrice\tAmount\tLaunch time\tState\n";
    while (p != NULL) {
        if (p->gd.sellerID == total.userNow->usr.ID) {
            cout << p->gd.ID << "\t" << p->gd.name << "\t";
            printf("%.1lf\t", p->gd.price);
            cout << p->gd.amount << "\t" << p->gd.time << "\t" << p->gd.state;
        }
        p = p->next;
    }
    cout << "******************************************************************\n\n";
}