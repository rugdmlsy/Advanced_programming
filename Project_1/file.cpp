#include <cstdio>
#include <fstream>
#include <iostream>
#include "total.h"
#define UHead "userID,username,password,phoneNumber,address,balance,userState\n"
#define COMMODITYHEAD "commodityID,commodityName,price,number,description,sellerID,addedDate,state\n"
#define OHead "orderID,commodityID,unitPrice,number,date,sellerID,buyerID\n"
using namespace std;

void update_users()
{
    ofstream outfile("user.txt", ios::out | ios::trunc);
    if (!outfile.is_open())
    {
        cout << "Failed to open user.txt!\n";
        exit(-1);
    }
    outfile << UHead;
    userNode *p = total.userHead;
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
        cout << "Failed to open commodity.txt!\n";
        exit(-1);
    }
    outfile << COMMODITYHEAD;
    goodNode *p = total.goodHead;
    while (p != nullptr)
    {
        outfile << p->gd.ID << "," << p->gd.name << "," << p->gd.price << "," << p->gd.amount << "," << p->gd.desc << "," << p->gd.sellerID << "," << p->gd.time << "," << p->gd.state << "\n";
        p = p->next;
    }
    outfile.close();
}

void update_order() {
    ofstream outfile("order.txt", ios::out | ios::trunc);
    if (!outfile.is_open()) {
        cout << "Failed to open order.txt!\n";
        exit(-1);
    }
    outfile << OHead;
    orderNode* p = total.orderHead;
    while (p != NULL) {
        outfile << p->odr.ID << "," << p->odr.goodID << "," << p->odr.price << "," << p->odr.amount << "," << p->odr.time << "," << p->odr.sellerID << "," << p->odr.buyerID << "\n";
        p = p->next;
    }
    outfile.close();
}