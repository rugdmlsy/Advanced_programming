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

void Good::assign(string gid, string gnm, double gprcd, int gnbi, string gds, string gsid, string gtm, string gst) {
	ID = gid;
	name = gnm;
	price = gprcd;
	amount = gnbi;
	desc = gds;
	sellerID = gsid;
	time = gtm;
	state = gst;
}