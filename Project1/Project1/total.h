#pragma once
#include "user.h"
#include "goods.h"
#include "order.h"

struct
{
    userNode* userHead = nullptr, * userNow = nullptr;
    goodNode *goodHead = nullptr;
    orderNode* orderHead = nullptr;
    int maxOID = 0, maxUID = 0, maxMID = 0;
} total;

userNode *search_user(string uid);
goodNode *search_good(string gid);