#include "common.h"

void showMainMenu(int priority,int goal,double sum)
{
	system("cls");
	if (priority) 
	{
		int percent = round(sum * 100 / goal);
		cout << "*******************************" << endl;
		cout << "您已经完成储蓄计划的" << percent << "%" << endl;
		if (percent<50)					   cout << "您急需努力了！！！" << endl;
		if (50 <= percent && percent < 80) cout << "坚持就是胜利！！！" << endl;
		if (80 <= percent && percent < 100)cout << "成功就在眼前！！！" << endl;
		if (percent >= 100)                cout << "恭喜您完成目标！！！" << endl;
		cout << "*******************************" << endl;
		cout << endl;
	}
	cout << "-------------------------------" << endl;
	cout << "|========== 1.记账 ===========|" << endl;
	cout << "|========== 2.查询 ===========|" << endl;
	cout << "|====== 3.更改储蓄计划 =======|" << endl;
	cout << "|========== 4.退出 ===========|" << endl;
	cout << "|                             |" << endl;
	cout << "请选择（1-4）:";
	cout << "\n";
}

void showAccountingMenu()
{

	cout << "-------------------------------" << endl;
	cout << "|========== 1.收入 ===========|" << endl;
	cout << "|========== 2.支出 ===========|" << endl;
	cout << "|========== 3.返回 ===========|" << endl;
	cout << "|                             |" << endl;
	cout << "请选择（1-3）:";
	cout << "\n";
}

void showQueryMenu()
{

	cout << "-------------------------------" << endl;
	cout << "|========== 1.总和 ===========|" << endl;
	cout << "|========== 2.收入 ===========|" << endl;
	cout << "|========== 3.支出 ===========|" << endl;
	cout << "|========== 4.日期 ===========|" << endl;
	cout << "|========== 5.类别 ===========|" << endl;
	cout << "|========== 6.返回 ===========|" << endl;
	cout << "|                             |" << endl;
	cout << "请选择（1-6）:";
	cout << "\n";
}