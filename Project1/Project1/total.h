#pragma once
#include "user.h"
#include "goods.h"
#include "order.h"
userNode *userHead = NULL, *userNow = NULL;
goodNode *goodHead = NULL;
orderNode *orderHead = NULL;
struct
{
    int maxOID = 0, maxUID = 0, maxMID = 0;
} total;

userNode *search_user(string uid);
goodNode *search_good(string gid);