#pragma once
#include <string>
using namespace std;

typedef struct order
{
    string ID;
    string goodID;
    double price;
    int amount;
    string time;
    string sellerID;
    string buyerID;
};

typedef struct orderNode
{
    order &odr;
    orderNode *next;
};