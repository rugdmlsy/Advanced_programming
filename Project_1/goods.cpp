#include "goods.h"
#include "total.h"

Good::Good() {
	total.maxMID += 1;
	char newid[5];
	sprintf_s(newid, "M%03d", total.maxMID);
	time = total.gettime();
	ID = newid;
	sellerID = total.userNow->usr.ID;
	state = "onSale";
}