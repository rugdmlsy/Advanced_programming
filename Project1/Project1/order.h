#pragma once
#include <string>
using namespace std;

struct order
{
    string ID;
    string goodID;
    double price;
    int amount;
    string time;
    string sellerID;
    string buyerID;
};

struct orderNode
{
    order &odr;
    orderNode *next;
};