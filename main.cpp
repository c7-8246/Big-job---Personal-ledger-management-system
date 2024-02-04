#include "common.h"
#include "account_item.h"

int main()
{
	int priority=Register();//��priority���û���������

	string FILENAME,FILENAME_settings;
	double sum = 0;
	int goal = 0;
	vector<AccountItem>items;
	if (priority == 0 || priority == 1) {
		FILENAME = "bubu.txt";
		loadDataFromFile(items,FILENAME,&sum);//��ȡ���׼�¼

		ifstream input("bubu_settings.txt");//��ȡ����ƻ�����
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
		showMainMenu(priority,goal,sum);//չʾ���˵�

		char key = readMenuSelection(4);//��ȡ��ѡ��
		switch (key)
		{
		case'1':
			showAccountingMenu();//չʾ������صĲ˵�
			accounting(items,FILENAME,&sum);//����
			break;
		case'2':
			showQueryMenu();//չʾ��ѯ��صĲ˵�
			querying(items);//��ѯ
			break;
		case'3':
			setPlan(goal, priority);//���Ĵ���ƻ������ӹ��ܣ�
		case'4':
			cout << "\n�Ƿ�ȷ���˳���(Y/N):";//�˳�����
			if (readQuitConfirm() == 'Y')
				quit = true;
		default:
			break;
		}
	}
	return 0;
}