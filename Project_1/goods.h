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
    void assign(string gid, string gnm, double gprcd, int gnbi, string gds, string gsid, string gtm, string gst);
};

typedef struct goodNode
{
    Good gd;
    goodNode *next;
};
