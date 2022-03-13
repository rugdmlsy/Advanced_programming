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
    void assign(string oid, string ogid, double oprcd, int onbi, string otm, string osid, string obid);
};

typedef struct orderNode
{
    order odr;
    orderNode *next = NULL;
};