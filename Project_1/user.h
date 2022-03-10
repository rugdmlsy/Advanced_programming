#pragma once
#include <string>
using namespace std;

class User
{
	string ID;			//开头字符为大写字母U，后3位为数字
	string name;		//中文汉字或英文字母
	string pswd;		//只由小写字母和数字组成
	string number;		//由数字组成
	string addr;		//中文汉字或英文字母
	double balance = 0; //保留一位小数
	string state = "active";

public:
	friend class Admin;
	friend void update_users();
	friend class Total;
	friend class Buyer;
	friend class Seller;
	friend class Good;

	void setID();
	void menu();
	void log_in();
	void sign_up();
	void PIM_menu();
	void recharge();
	void modi_info();
	void view_info();
};

typedef struct userNode
{
	User usr;
	userNode *next = nullptr;
};

class Seller : public User
{
public:
	void menu();
	void see_goods();
	void see_orders();
	void unshelve();
	void modi();
	void launch();
};

class Buyer : public User
{
public:
	void menu();
	void search();
	void see_details();
	void see_orders();
	void see_goods();
	void buy();
};

extern User user;
extern Seller seller;
extern Buyer buyer;
