#include <iostream>
#include <fstream>
#include <string>
#include "user.h"
#include "admin.h"
#include "check.h"
using namespace std;

void init() {
    ifstream infile("user.txt");
    string uhead;
    getline(infile, uhead);

    infile.close();
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