#pragma once
#include <string>
using namespace std;

class Good
{
    string ID;
    string name;
    double price;
    int amount;
    string desc;
    string sellerID;
    string time;
    string state;
public:
    Good();
    friend class Seller;
    friend class Total;
    friend class Buyer;
    friend class Admin;
    friend void update_goods();
};

typedef struct goodNode
{
    Good gd;
    goodNode *next;
};
