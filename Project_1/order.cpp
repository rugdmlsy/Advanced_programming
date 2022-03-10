#include "order.h"
#include "total.h"
#include <cstdio>

void order::setID() {
    char onum[5];
    total.maxOID += 1;
    sprintf_s(onum, "T%03d", total.maxOID);
    ID = onum;
}