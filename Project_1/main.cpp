#include "init.h"
#include "calculator.h"
#include <iostream>
#include <string>
#include "user.h"
#include "admin.h"
int main()
{
	string s="";
	while (s != "exit") {
		cin >> s;
		cout << check_calc(s) << endl;
	}
	
}