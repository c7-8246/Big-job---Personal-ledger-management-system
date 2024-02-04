#pragma once

#include "common.h"

#define INCOME "����"
#define EXPAND "֧��"

#define limitation 2000
#define PI 3.1415926
#define USD_CNY 7.15//��Ԫ
#define EUR_CNY 7.72//ŷԪ
#define GBP_CNY 9.00//Ӣ��
#define JPY_CNY 0.05//��Ԫ


struct AccountItem
{
	string itemType;
	double amount=0;
	string date;
	string datail;
};

void loadDataFromFile(vector<AccountItem>& items,string FILENAME,double* sum);

void accounting(vector<AccountItem>& items, string FILENAME,double* sum);
void income(vector<AccountItem>& items, string FILENAME,double* sum);
void expand(vector<AccountItem>& items, string FILENAME,double* sum);
double exchange(int type);
void insertIntoFile(const AccountItem& item, string FILENAME);
void warningCheck(vector<AccountItem>& items,string Date);


void querying(vector<AccountItem>& items); 
void queryItems1(vector<AccountItem>& items);
void queryItems2(vector<AccountItem>& items, const string itemType);
void queryItems3(vector<AccountItem>& items);
void queryItems4(vector<AccountItem>& items);
void printItem(const AccountItem& item);
bool checkDate(string data, string s, string e);

void analysis(vector<AccountItem>& items, string itemType,double total);

void setPlan(int goal,int priority);