#include "common.h"
#include "account_item.h"
#include<graphics.h>
#include<map>

void setPlan(int goal,int priority)
{
	cout << "您当前的目标为：" << goal << endl;
	cout << "请输入您所要更改的目标：";
	if (priority == 1)
	{
		ofstream output("bubu_settings.txt");
		output << (readAmount(1));
		output.close();
	}
	else
	{
		ofstream output("yier_settings.txt");
		output << (readAmount(1));
		output.close();
	}
	cout << "信息录入完毕" << endl;
	cout << "重启系统以更新信息！！！";
}

int Register()
{
	int key;
	cout << "请输入你的账号：\n";
	while (1)//人员管理与权限管理 
	{
		string name, password;
		getline(cin, name);
		cout << "请输入你的密码：\n";
		getline(cin, password);

		if (name == "管理员" && password == "管理员") {//key来区分用户 
			key = 0; break;
		}
		if (name == "布布" && password == "布布") {
			key = 1; break;
		}
		if (name == "一二" && password == "一二") {
			key = 2; break;
		}
		cout << "用户不存在或密码有误\n";
		cout << "请再次输入你的账号：\n";

	}
	cout << "登录成功\n";
	return key;
}

void loadDataFromFile(vector<AccountItem>& items,string FILENAME,double* sum)//从文件中读取交易记录
{
	ifstream input(FILENAME);

	AccountItem item;
	while (input >> item.itemType >> item.amount >> item.date >> item.datail)
	{
		items.push_back(item);
		if (item.itemType == INCOME)*sum += item.amount;
		else *sum -= item.amount;
	}
	input.close();
}

void querying( vector<AccountItem>&items)//查询
{
	const char key =readMenuSelection(6);

	switch (key)
	{
	case'1':
		queryItems1(items);//总和
		break;
	case'2':
		queryItems2(items, INCOME);//收入
		break;
	case'3':
		queryItems2(items, EXPAND);//支出
		break;
	case'4':
		queryItems3(items);//日期
		break;
	case'5':
		queryItems4(items);//类别
		break;
	default:
		break;
	}

}

void queryItems1(vector<AccountItem>& items)//总和
{
	cout << "-----------查询结果-------" << endl;
	cout << "\n类型\t\t金额\t\t日期\t\t类别\n" << endl;

	for (auto item : items)
	{
		printItem(item);
	}
	cout << "================================" << endl;

	cout << "请按回车键继续..." << endl;
	string str;
	getline(cin, str);

}

void queryItems2(vector<AccountItem>& items,const string itemType)//收入or支出
{
	cout << "-----------查询结果-------" << endl;
	cout << "\n类型\t\t金额\t\t日期\t\t类别\n" << endl;

	double total = 0;
	for (auto item : items)
	if(item.itemType==itemType)
	{
		printItem(item);
		total += item.amount;
	}
	cout << "================================" << endl;
	cout << "总" <<itemType << " ：" << total << endl;
	cout << endl;
	cout << "是否对数据进行分析? (Y/N):";
	if (readQuitConfirm() == 'Y')analysis(items,itemType,total);
}
// ----------------------------
map<string, bool>readCheck;//记录每种类别是否已经展示
void analysis(vector<AccountItem>& items, string itemType,double total)// 针对类别进行数据分析
{
	initgraph(640, 480, SHOWCONSOLE);

	settextstyle(50, 0, _T("微软雅黑"));

	double proData = 0;
	int i = 4,j = 0;
	for(auto item : items)
		if (item.itemType == itemType)
		{
			if (readCheck[item.datail])continue;//该类别是否已经展示
			readCheck[item.datail] = 1;

			double tot = 0;//该类别多少钱
			for (auto item1 : items)
				if (item1.itemType==itemType&&item1.datail == item.datail)
					tot += item1.amount;

			i++;
			i %= 5;
			switch (i)//饼状图用5种颜色进行展示
			{//文字与扇形颜色
			case 0:
				settextcolor(RED); setfillcolor(RED); 
				break;
			case 1:
				settextcolor(YELLOW); setfillcolor(YELLOW);
				break;
			case 2:
				settextcolor(BLUE); setfillcolor(BLUE); 
				break;
			case 3:
				settextcolor(GREEN); setfillcolor(GREEN);
				break;
			case 4:
				settextcolor(BROWN); setfillcolor(BROWN); 
				break;
			}
			
			int size = MultiByteToWideChar(CP_ACP, 0, (item.datail).c_str(), -1, NULL, 0);//类型转换，便于输出
			wchar_t* wchar = new wchar_t[size];
			MultiByteToWideChar(CP_ACP, 0, (item.datail).c_str(), -1, wchar, size);
			outtextxy(0, 50*(j++), wchar);
			delete[] wchar;
			
			if(tot*2*PI/total > 0.005)//处理时的精度
				solidpie(150, 50, 550, 450, proData, proData+tot*2*PI/total);
			proData += tot * 2 * PI / total;
		}
	readCheck.clear();
	cout << "请按回车键继续..." << endl;
	string str;
	getline(cin, str);
	closegraph();
}

void queryItems3(vector<AccountItem>& items)//日期
{
	cout << "请输入日期范围";
	cout << endl<< "起始日期:" << endl;
	string start = readDate();
	cout << endl<< "终止日期:" << endl;
	string end = readDate();

	cout << endl<< "-----------查询结果-------" << endl;
	cout << "\n类型\t\t金额\t\t日期\t\t类别\n" << endl;

	double total = 0, tot = 0;
	for (auto item : items)
	{
		if (checkDate(item.date,start,end))
		{
			printItem(item);
			total += item.amount;
			if (item.itemType == INCOME)tot += item.amount;
		}
	}
	cout << "================================" << endl;
	cout << endl;
	cout << "是否对数据进行分析? (Y/N):";
	if (readQuitConfirm() == 'Y')//针对某个日期范围，按交易类型进行展示
	{
		initgraph(640, 480, SHOWCONSOLE);
		settextstyle(50, 0, _T("微软雅黑"));

		settextcolor(RED); setfillcolor(RED);
		outtextxy(0, 0, _T("INCOME"));
		fillpie(150, 50, 550, 450, 0, tot * 2 * PI / total);
		settextcolor(YELLOW); setfillcolor(YELLOW);
		outtextxy(0, 50, _T("EXPAND"));
		fillpie(150, 50, 550, 450, tot * 2 * PI / total, 2 * PI);

		cout << "请按回车键继续..." << endl;
		string str;
		getline(cin, str);
		closegraph();
	}
}

bool checkDate(string date, string s, string e)//判断是否在该时间范围内
{
	int a = 0, b = 0, c = 0;
	for (int i = 0; i < 10; i++)
	{
		if (date[i] == '-');
		else
		{
			a = a * 10 + date[i] - '0';
			b = b * 10 + s[i] - '0';
			c = c * 10 + e[i] - '0';
		}
		if (a<b || a>c)
			return false;
	}
	return true;
}

void queryItems4(vector<AccountItem>& items)//类别
{
	string str;
	cout << "请输入类别：\n";
	getline(cin, str);

	cout << "-----------查询结果-------" << endl;
	cout << "\n类型\t\t金额\t\t日期\t\t类别\n" << endl;

	for (auto item : items)
		if (item.datail == str)
		{
			printItem(item);
		}

	cout << "请按回车键继续..." << endl;
	getline(cin, str);
}

void printItem(const AccountItem& item)//输出
{
	cout << item.itemType << "\t\t" << item.amount << "\t\t" <<item.date<<"\t" << item.datail << endl;
}



void accounting(vector<AccountItem>& items,string FILENAME,double* sum)//记账
{
	const char key = readMenuSelection(3);
	switch (key)
	{
	case'1':
		income(items,FILENAME,sum);
		break;
	case'2':
		expand(items,FILENAME,sum);
		break;
	default:
		break;
	}
}

void income(vector<AccountItem>& items, string FILENAME,double* sum)//收入
{
	AccountItem item;

	item.itemType = INCOME;

	cout << "\n本次收入：\n";
	cout << "货币类型( 1.人民币；2.美元；3.欧元；4.英镑；5.日元)：";
	int type=readMenuSelection(5)-'0';
	cout << "金额：";
	item.amount = readAmount(type);
	*sum += item.amount;
	cout << "\n日期：";
	item.date = readDate();
	cout << "\n类别：";
	getline(cin, item.datail);

	items.push_back(item);

	insertIntoFile(item,FILENAME);

	cout << "\n---------------记账成功\n" << endl;

	cout << "\n请按回车键返回主菜单..." << endl;

	string line;
	getline(cin, line);
}

void expand(vector<AccountItem>& items, string FILENAME,double* sum)//支出
{
	AccountItem item;

	item.itemType = EXPAND;

	cout << "\n本次支出：";
	item.amount = readAmount(1);
	*sum -= item.amount;
	cout << "\n日期：";
	item.date = readDate();
	cout << "\n类别：";
	getline(cin, item.datail);

	items.push_back(item);

	insertIntoFile(item,FILENAME);

	cout << "\n---------------记账成功\n" << endl;

	warningCheck(items,item.date);

	cout << "\n请按回车键返回主菜单..." << endl;

	string line;
	getline(cin, line);
}

void warningCheck(vector<AccountItem>& items, string Date)//限额预警
{
	double Amount=0;
	for (auto item : items)
	{
		bool flag = 1;
		for (int i = 0; i < 8; i++)
			if (item.date[i] != Date[i])
				flag = 0;
		if (flag)
		{
			Amount += item.amount;
			if (limitation - Amount > 100)continue;
			else
			{
				cout << "您的花销接近本月预算，请注意！\n";
				return;
			}
		}
	}
	return;
}

double exchange(int type)//货币转换
{
	switch (type)
	{
	case 1:
		return 1.0;
	case 2:
		return USD_CNY;
	case 3:
		return EUR_CNY;
	case 4:
		return GBP_CNY;
	case 5:
		return JPY_CNY;
	default:
		break;
	}
}

void insertIntoFile(const AccountItem& item, string FILENAME)//将交易记录输入到文件中
{
	ofstream output(FILENAME, ios::out | ios::app);
	
	output << item.itemType << "\t" << item.amount << "\t" <<item.date<<"\t" << item.datail << endl;

	output.close();
}
