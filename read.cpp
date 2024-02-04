#include "common.h"
#include "account_item.h"

char readMenuSelection(int options)//��ȡ�Ƿ��˳�
{
	string str;
	while (true)
	{
		getline(cin, str);
		if (str.size() != 1 || str[0] - '0' < 1 || str[0] - '0' > options)
			cout << "�������������ѡ��";
		else
			break;
	}
	return str[0];
}

char readQuitConfirm()//��ȡ����/���˳���
{
	string s;
	while (true)
	{
		getline(cin, s);
		if (s.size() == 1 && ( toupper(s[0])=='Y' || toupper(s[0])=='N' ) )
			break;
		cout<< "�������������ѡ��";
	}
	return toupper(s[0]);
}


double readAmount(int type)//��ȡ����Ľ���ת���� RMB
{
	string str;
	bool quit = false;
	while (!quit)
	{
		quit = true;
		getline(cin, str);
		for(int i=0;i<str.size();i++)
			if (!isdigit(str[i]))
			{
				quit=false;
				cout << "����������ٴ����룺";
				break;
			}
		if (str.size() == 0)quit = false;
	}
	return exchange(type)*stoi(str);
}

int Month[15] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

string readDate()
{
	string str;
	bool quit = false;
	
	while (!quit)
	{
		quit = true;
		getline(cin, str);
		if (str.size() == 10)
		{
			for (int i = 0; i < 10; i++)
			{
				if ((i == 4 || i == 7) && (str[i] != '-')) {
					quit = false; break;
				}
				if ((i != 4 && i != 7) && (!isdigit(str[i]))) {
					quit = false; break;
				}
			}
			if (quit)
			{
				int year = 0, month = 0, day = 0;
				for (int i = 0; i < 4; i++)
					year = year * 10 + str[i] - '0';
				for (int i = 5; i < 7; i++)
					month = month * 10 + str[i] - '0';
				for (int i = 8; i < 10; i++)
					day = day * 10 + str[i] - '0';

				if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))year = 1;
				else year = 0;

				if (month == 2)
				{
					if (day <= Month[month] + year && day > 0);
					else quit = false;
				}
				else
				{
					if (day <= Month[month] && day > 0);
					else quit = false;
				}

			}
		}
		else
			quit = false;

		if (!quit)
			cout << "����������ٴ�����:";
	}
	return str;
}