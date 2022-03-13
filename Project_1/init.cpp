#include <iostream>
#include <fstream>
#include <string>
#include "user.h"
#include "admin.h"
#include "check.h"
#include "total.h"
using namespace std;

void init() {
    //init user.txt
    ifstream infile("user.txt");
    if (!infile) {
        cout << "Failed to open file!\n";
        exit(-1);
    }
    string uhead;
    getline(infile, uhead);
    double ubad;
    string uid, unm, upw, upn, uad, uba, ust;
    while (getline(infile, uid, ',')) {
        getline(infile, unm, ',');
        getline(infile, upw, ',');
        getline(infile, upn, ',');
        getline(infile, uad, ',');
        getline(infile, uba, ',');
        getline(infile, ust);
        ubad = stod(uba);
        userNode* un = new userNode;
        un->usr.assign(uid, unm, upw, upn, uad, ubad, ust);
        total.add_user(un);
    }
    infile.close();

    //init order.txt
    ifstream infileo("order.txt");
    if (!infileo) {
        cout << "Failed to open file!\n";
        exit(-1);
    }
    string ohead;
    getline(infileo, ohead);
    double oprcd;
    int onbi;
    string oid, ogid, oprc, onb, otm, osid, obid;
    while (getline(infileo, oid, ',')) {
        getline(infileo, ogid, ',');
        getline(infileo, oprc, ',');
        getline(infileo, onb, ',');
        getline(infileo, otm, ',');
        getline(infileo, osid, ',');
        getline(infileo, obid);
        oprcd = stod(oprc);
        onbi = stoi(onb);
        orderNode* on = new orderNode;
        on->odr.assign(oid, ogid, oprcd, onbi, otm, osid, obid);
        total.add_order(on);
    }
    infileo.close();

    //init commodity.txt
    ifstream infileg("commodity.txt");
    if (!infileg) {
        cout << "Failed to open file!\n";
        exit(-1);
    }
    string ghead;
    getline(infileg, ghead);
    double gprcd;
    int gnbi;
    string gid, gnm, gprc, gnb, gds, gsid, gtm, gst;
    while (getline(infileg, gid, ',')) {
        getline(infileg, gnm, ',');
        getline(infileg, gprc, ',');
        getline(infileg, gnb, ',');
        getline(infileg, gds, ','); //The comma has not been converted
        getline(infileg, gsid, ',');
        getline(infileg, gtm, ',');
        getline(infileg, gst);
        gprcd = stod(gprc);
        gnbi = stoi(gnb);
        goodNode* gn = new goodNode;
        gn->gd.assign(gid, gnm, gprcd, gnbi, gds, gsid, gtm, gst);
        total.add_good(gn);
    }
    infileg.close();
}

void init_menu()
{
    while (1) {
        cout << "===================================================================\n";
        cout << "1.Admin log in 2.User log in 3.User sign in 4.Exit\n";
        cout << "===================================================================\n\n";
        cout << "Please input the option: ";
        int opt = check_opt(1, 4);
        switch (opt)
        {
        case 1:
            admin.log_in();
            break;
        case 2:
            user.log_in();
            break;
        case 3:
            user.sign_up();
            break;
        case 4:
            exit(0);
        }
    }
}