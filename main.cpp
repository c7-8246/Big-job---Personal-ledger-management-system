#include "common.h"
#include "account_item.h"

int main()
{
	int priority=Register();//用priority将用户进行区分

	string FILENAME,FILENAME_settings;
	double sum = 0;
	int goal = 0;
	vector<AccountItem>items;
	if (priority == 0 || priority == 1) {
		FILENAME = "bubu.txt";
		loadDataFromFile(items,FILENAME,&sum);//读取交易记录

		ifstream input("bubu_settings.txt");//读取储蓄计划设置
		input >> goal;
		input.close();
	}
	if (priority == 0 || priority == 2) {
		FILENAME = "yier.txt";
		loadDataFromFile(items,FILENAME,&sum);

		ifstream input("yier_settings.txt");
		input >> goal;
		input.close();
	}
	
	bool quit = false;
	while (!quit)
	{
		showMainMenu(priority,goal,sum);//展示主菜单

		char key = readMenuSelection(4);//读取所选项
		switch (key)
		{
		case'1':
			showAccountingMenu();//展示记账相关的菜单
			accounting(items,FILENAME,&sum);//记账
			break;
		case'2':
			showQueryMenu();//展示查询相关的菜单
			querying(items);//查询
			break;
		case'3':
			setPlan(goal, priority);//更改储蓄计划（附加功能）
		case'4':
			cout << "\n是否确认退出？(Y/N):";//退出程序
			if (readQuitConfirm() == 'Y')
				quit = true;
		default:
			break;
		}
	}
	return 0;
}