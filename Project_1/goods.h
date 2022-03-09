#pragma once
#include <string>
using namespace std;

typedef struct good
{
    string ID;
    string name;
    double price;
    unsigned int amount;
    string desc;
    string sellerID;
    string time;
    string state = "onSale";
};

typedef struct goodNode
{
    good &gd;
    goodNode *next;
};
