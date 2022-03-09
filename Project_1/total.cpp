#include <string>
#include "user.h"
#include "total.h"
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
