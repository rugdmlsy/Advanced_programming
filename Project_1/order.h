#pragma once
#include <string>
using namespace std;
class order
{
    string ID;
    string goodID;
    double price;
    int amount = 0;
    string time;
    string sellerID;
    string buyerID;
public:
    friend class User;
    friend class Buyer;
    friend class Seller;
    friend class Admin;
    friend void update_order();
    void setID();
};

typedef struct orderNode
{
    order odr;
    orderNode *next = NULL;
};