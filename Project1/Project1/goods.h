#pragma once
#include <string>
using namespace std;

struct good
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

struct goodNode
{
    good &gd;
    goodNode *next;
};
