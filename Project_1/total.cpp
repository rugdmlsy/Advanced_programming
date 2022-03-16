#include <string>
#include <ctime>
#include "user.h"
#include "total.h"
#pragma warning(disable:4996)
using namespace std;

Total total;

userNode *Total::search_user(string uid)
{
    userNode *p = total.userHead, *q = nullptr;
    while (p != nullptr)
    {
        if (p->usr.ID == uid || p->usr.name == uid)
            return p;
        p = p->next;
    }
    return q;
}

goodNode *Total::search_good(string gid)
{
    goodNode *p = total.goodHead, *q = nullptr;
    while (p != nullptr)
    {
        if (p->gd.ID == gid)
        {
            q = p;
            break;
        }
        p = p->next;
    }
    return q;
}

string Total::gettime() {
    char tmnow[11];
    time_t rawtime;
    time(&rawtime);
    struct tm* peach = localtime(&rawtime);
    strftime(tmnow, 11, "%F", peach);
    string ret = tmnow;
    return ret;
}

void Total::add_order(orderNode* o) {
    orderNode* p = orderHead;
    if (p == NULL) 
        orderHead = o;
    else {
        while (p->next != NULL)
            p = p->next;
        p->next = o;
    }
}

void Total::add_user(userNode* u) {
    userNode* p = userHead;
    if (p == NULL)
        userHead = u;
    else {
        while (p->next != NULL)
            p = p->next;
        p->next = u;
    }
}

void Total::add_good(goodNode* g) {
    goodNode* p = goodHead;
    if (p == NULL)
        goodHead = g;
    else {
        while (p->next != NULL)
            p = p->next;
        p->next = g;
    }
}

