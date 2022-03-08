#pragma once
#include <string>
using namespace std;

struct User
{
	string ID;			//开头字符为大写字母U，后3位为数字
	string name;		//中文汉字或英文字母
	string pswd;		//只由小写字母和数字组成
	string number;		//由数字组成
	string addr;		//中文汉字或英文字母
	double balance = 0; //保留一位小数
	string state = "active";
};

struct userNode
{
	User &usr;
	userNode *next = nullptr;
};

class users
{
public:
	void log_out();
	void rgst(); // register
	void see_info();
	void modi_info();
	void recharge(double amount);
};

class seller : public users
{
public:
	bool release(string ID, string name, double price, int amount, string desc);
	bool unshelve(string ID);
	bool modify(string ID);
	void see_goods();
	void see_orders();
};

class buyer : public users
{
public:
	void see_goods();
	bool buy(string ID);
	void search(string ID);
	void see_orders();
	bool see_detail(string ID);
};

void user_menu();
void user_log_in();
void user_sign_up();