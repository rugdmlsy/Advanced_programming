#include <cstdio>
#include <fstream>
#include <iostream>
#include "total.h"
#define USERHEAD "userID,username,password,phoneNumber,address,balance,userState\n"
#define COMMODITYHEAD "commodityID,commodityName,price,number,description,sellerID,addedDate,state\n"
#define ORDERHEAD "orderID,commodityID,unitPrice,number,date,sellerID,buyerID\n"
using namespace std;

void update_users()
{
    ofstream outfile("user.txt", ios::out | ios::trunc);
    if (!outfile.is_open())
    {
        cout << "Failed to open file!\n";
        exit(-1);
    }
    outfile << USERHEAD;
    userNode *p = userHead;
    while (p != nullptr)
    {
        outfile << p->usr.ID << "," << p->usr.name << "," << p->usr.pswd << "," << p->usr.number << "," << p->usr.addr << "," << p->usr.balance << "," << p->usr.state << "\n";
        p = p->next;
    }
    outfile.close();
}

void update_goods()
{
    ofstream outfile("commodity.txt", ios::out | ios::trunc);
    if (!outfile.is_open())
    {
        cout << "Failed to open file!\n";
        exit(-1);
    }
    outfile << COMMODITYHEAD;
    goodNode *p = goodHead;
    while (p != nullptr)
    {
        outfile << p->gd.ID << "," << p->gd.name << "," << p->gd.price << "," << p->gd.amount << "," << p->gd.desc << "," << p->gd.sellerID << "," << p->gd.time << "," << p->gd.state << "\n";
        p = p->next;
    }
    outfile.close();
}