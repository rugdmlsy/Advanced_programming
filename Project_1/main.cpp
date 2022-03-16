#include "init.h"
#include "calculator.h"
#include <iostream>
#include <string>
#include "user.h"
#include "admin.h"
int main()
{
	string str = "1+1";
	cout << is_oper(str[1]) << endl;
	string s="";
	while (s != "exit") {
		getline(cin, s);
		cout<<calculator(s)<<endl;
	}
	
}