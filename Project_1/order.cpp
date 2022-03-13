#include "order.h"
#include "total.h"
#include <cstdio>

void order::setID() {
    char onum[5];
    total.maxOID += 1;
    sprintf_s(onum, "T%03d", total.maxOID);
    ID = onum;
}

void order::assign(string oid, string ogid, double oprcd, int onbi, string otm, string osid, string obid) {
    ID = oid;
    goodID = ogid;
    price = oprcd;
    amount = onbi;
    time = otm;
    sellerID = osid;
    buyerID = obid;
}