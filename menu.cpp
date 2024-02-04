#include "common.h"

void showMainMenu(int priority,int goal,double sum)
{
	system("cls");
	if (priority) 
	{
		int percent = round(sum * 100 / goal);
		cout << "*******************************" << endl;
		cout << "���Ѿ���ɴ���ƻ���" << percent << "%" << endl;
		if (percent<50)					   cout << "������Ŭ���ˣ�����" << endl;
		if (50 <= percent && percent < 80) cout << "��־���ʤ��������" << endl;
		if (80 <= percent && percent < 100)cout << "�ɹ�������ǰ������" << endl;
		if (percent >= 100)                cout << "��ϲ�����Ŀ�꣡����" << endl;
		cout << "*******************************" << endl;
		cout << endl;
	}
	cout << "-------------------------------" << endl;
	cout << "|========== 1.���� ===========|" << endl;
	cout << "|========== 2.��ѯ ===========|" << endl;
	cout << "|====== 3.���Ĵ���ƻ� =======|" << endl;
	cout << "|========== 4.�˳� ===========|" << endl;
	cout << "|                             |" << endl;
	cout << "��ѡ��1-4��:";
	cout << "\n";
}

void showAccountingMenu()
{

	cout << "-------------------------------" << endl;
	cout << "|========== 1.���� ===========|" << endl;
	cout << "|========== 2.֧�� ===========|" << endl;
	cout << "|========== 3.���� ===========|" << endl;
	cout << "|                             |" << endl;
	cout << "��ѡ��1-3��:";
	cout << "\n";
}

void showQueryMenu()
{

	cout << "-------------------------------" << endl;
	cout << "|========== 1.�ܺ� ===========|" << endl;
	cout << "|========== 2.���� ===========|" << endl;
	cout << "|========== 3.֧�� ===========|" << endl;
	cout << "|========== 4.���� ===========|" << endl;
	cout << "|========== 5.��� ===========|" << endl;
	cout << "|========== 6.���� ===========|" << endl;
	cout << "|                             |" << endl;
	cout << "��ѡ��1-6��:";
	cout << "\n";
}