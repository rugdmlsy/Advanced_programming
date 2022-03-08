#include <string>
#include "user.h"
#include "total.h"
using namespace std;

userNode *search_user(string uid)
{
    userNode *p = userHead, *q = nullptr;
    while (p != nullptr)
    {
        if (p->usr.ID == uid || p->usr.name == uid)
        {
            q = p;
            break;
        }
        p = p->next;
    }
    return q;
}

goodNode *search_good(string gid)
{
    goodNode *p = goodHead, *q = nullptr;
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
