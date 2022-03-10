#pragma once
#include "user.h"
#include "goods.h"
#include "order.h"
#include <string>
using namespace std;


class Total
{
    userNode *userHead;
    userNode *userNow;
    goodNode *goodHead;
    orderNode *orderHead;
    int maxOID, maxUID, maxMID;

public:
    Total() : userHead(NULL), userNow(NULL), goodHead(NULL), orderHead(NULL), maxOID(0), maxUID(0), maxMID(0) {}

    friend class Admin;
    friend void update_users();
    friend void update_goods();
    friend void update_order();
    userNode *search_user(string uid);
    goodNode *search_good(string gid);
    friend class User;
    friend class Buyer;
    friend class Seller;
    friend class order;
    friend class Good;
    string gettime();
    void add_order(orderNode* o);
    void add_user(userNode* u);
    void add_good(goodNode* g);
};

extern Total total;