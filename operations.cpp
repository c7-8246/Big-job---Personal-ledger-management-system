#include "common.h"
#include "account_item.h"
#include<graphics.h>
#include<map>

void setPlan(int goal,int priority)
{
	cout << "����ǰ��Ŀ��Ϊ��" << goal << endl;
	cout << "����������Ҫ���ĵ�Ŀ�꣺";
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
	cout << "��Ϣ¼�����" << endl;
	cout << "����ϵͳ�Ը�����Ϣ������";
}

int Register()
{
	int key;
	cout << "����������˺ţ�\n";
	while (1)//��Ա������Ȩ�޹��� 
	{
		string name, password;
		getline(cin, name);
		cout << "������������룺\n";
		getline(cin, password);

		if (name == "����Ա" && password == "����Ա") {//key�������û� 
			key = 0; break;
		}
		if (name == "����" && password == "����") {
			key = 1; break;
		}
		if (name == "һ��" && password == "һ��") {
			key = 2; break;
		}
		cout << "�û������ڻ���������\n";
		cout << "���ٴ���������˺ţ�\n";

	}
	cout << "��¼�ɹ�\n";
	return key;
}

void loadDataFromFile(vector<AccountItem>& items,string FILENAME,double* sum)//���ļ��ж�ȡ���׼�¼
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

void querying( vector<AccountItem>&items)//��ѯ
{
	const char key =readMenuSelection(6);

	switch (key)
	{
	case'1':
		queryItems1(items);//�ܺ�
		break;
	case'2':
		queryItems2(items, INCOME);//����
		break;
	case'3':
		queryItems2(items, EXPAND);//֧��
		break;
	case'4':
		queryItems3(items);//����
		break;
	case'5':
		queryItems4(items);//���
		break;
	default:
		break;
	}

}

void queryItems1(vector<AccountItem>& items)//�ܺ�
{
	cout << "-----------��ѯ���-------" << endl;
	cout << "\n����\t\t���\t\t����\t\t���\n" << endl;

	for (auto item : items)
	{
		printItem(item);
	}
	cout << "================================" << endl;

	cout << "�밴�س�������..." << endl;
	string str;
	getline(cin, str);

}

void queryItems2(vector<AccountItem>& items,const string itemType)//����or֧��
{
	cout << "-----------��ѯ���-------" << endl;
	cout << "\n����\t\t���\t\t����\t\t���\n" << endl;

	double total = 0;
	for (auto item : items)
	if(item.itemType==itemType)
	{
		printItem(item);
		total += item.amount;
	}
	cout << "================================" << endl;
	cout << "��" <<itemType << " ��" << total << endl;
	cout << endl;
	cout << "�Ƿ�����ݽ��з���? (Y/N):";
	if (readQuitConfirm() == 'Y')analysis(items,itemType,total);
}
// ----------------------------
map<string, bool>readCheck;//��¼ÿ������Ƿ��Ѿ�չʾ
void analysis(vector<AccountItem>& items, string itemType,double total)// ������������ݷ���
{
	initgraph(640, 480, SHOWCONSOLE);

	settextstyle(50, 0, _T("΢���ź�"));

	double proData = 0;
	int i = 4,j = 0;
	for(auto item : items)
		if (item.itemType == itemType)
		{
			if (readCheck[item.datail])continue;//������Ƿ��Ѿ�չʾ
			readCheck[item.datail] = 1;

			double tot = 0;//��������Ǯ
			for (auto item1 : items)
				if (item1.itemType==itemType&&item1.datail == item.datail)
					tot += item1.amount;

			i++;
			i %= 5;
			switch (i)//��״ͼ��5����ɫ����չʾ
			{//������������ɫ
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
			
			int size = MultiByteToWideChar(CP_ACP, 0, (item.datail).c_str(), -1, NULL, 0);//����ת�����������
			wchar_t* wchar = new wchar_t[size];
			MultiByteToWideChar(CP_ACP, 0, (item.datail).c_str(), -1, wchar, size);
			outtextxy(0, 50*(j++), wchar);
			delete[] wchar;
			
			if(tot*2*PI/total > 0.005)//����ʱ�ľ���
				solidpie(150, 50, 550, 450, proData, proData+tot*2*PI/total);
			proData += tot * 2 * PI / total;
		}
	readCheck.clear();
	cout << "�밴�س�������..." << endl;
	string str;
	getline(cin, str);
	closegraph();
}

void queryItems3(vector<AccountItem>& items)//����
{
	cout << "���������ڷ�Χ";
	cout << endl<< "��ʼ����:" << endl;
	string start = readDate();
	cout << endl<< "��ֹ����:" << endl;
	string end = readDate();

	cout << endl<< "-----------��ѯ���-------" << endl;
	cout << "\n����\t\t���\t\t����\t\t���\n" << endl;

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
	cout << "�Ƿ�����ݽ��з���? (Y/N):";
	if (readQuitConfirm() == 'Y')//���ĳ�����ڷ�Χ�����������ͽ���չʾ
	{
		initgraph(640, 480, SHOWCONSOLE);
		settextstyle(50, 0, _T("΢���ź�"));

		settextcolor(RED); setfillcolor(RED);
		outtextxy(0, 0, _T("INCOME"));
		fillpie(150, 50, 550, 450, 0, tot * 2 * PI / total);
		settextcolor(YELLOW); setfillcolor(YELLOW);
		outtextxy(0, 50, _T("EXPAND"));
		fillpie(150, 50, 550, 450, tot * 2 * PI / total, 2 * PI);

		cout << "�밴�س�������..." << endl;
		string str;
		getline(cin, str);
		closegraph();
	}
}

bool checkDate(string date, string s, string e)//�ж��Ƿ��ڸ�ʱ�䷶Χ��
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

void queryItems4(vector<AccountItem>& items)//���
{
	string str;
	cout << "���������\n";
	getline(cin, str);

	cout << "-----------��ѯ���-------" << endl;
	cout << "\n����\t\t���\t\t����\t\t���\n" << endl;

	for (auto item : items)
		if (item.datail == str)
		{
			printItem(item);
		}

	cout << "�밴�س�������..." << endl;
	getline(cin, str);
}

void printItem(const AccountItem& item)//���
{
	cout << item.itemType << "\t\t" << item.amount << "\t\t" <<item.date<<"\t" << item.datail << endl;
}



void accounting(vector<AccountItem>& items,string FILENAME,double* sum)//����
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

void income(vector<AccountItem>& items, string FILENAME,double* sum)//����
{
	AccountItem item;

	item.itemType = INCOME;

	cout << "\n�������룺\n";
	cout << "��������( 1.����ң�2.��Ԫ��3.ŷԪ��4.Ӣ����5.��Ԫ)��";
	int type=readMenuSelection(5)-'0';
	cout << "��";
	item.amount = readAmount(type);
	*sum += item.amount;
	cout << "\n���ڣ�";
	item.date = readDate();
	cout << "\n���";
	getline(cin, item.datail);

	items.push_back(item);

	insertIntoFile(item,FILENAME);

	cout << "\n---------------���˳ɹ�\n" << endl;

	cout << "\n�밴�س����������˵�..." << endl;

	string line;
	getline(cin, line);
}

void expand(vector<AccountItem>& items, string FILENAME,double* sum)//֧��
{
	AccountItem item;

	item.itemType = EXPAND;

	cout << "\n����֧����";
	item.amount = readAmount(1);
	*sum -= item.amount;
	cout << "\n���ڣ�";
	item.date = readDate();
	cout << "\n���";
	getline(cin, item.datail);

	items.push_back(item);

	insertIntoFile(item,FILENAME);

	cout << "\n---------------���˳ɹ�\n" << endl;

	warningCheck(items,item.date);

	cout << "\n�밴�س����������˵�..." << endl;

	string line;
	getline(cin, line);
}

void warningCheck(vector<AccountItem>& items, string Date)//�޶�Ԥ��
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
				cout << "���Ļ����ӽ�����Ԥ�㣬��ע�⣡\n";
				return;
			}
		}
	}
	return;
}

double exchange(int type)//����ת��
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

void insertIntoFile(const AccountItem& item, string FILENAME)//�����׼�¼���뵽�ļ���
{
	ofstream output(FILENAME, ios::out | ios::app);
	
	output << item.itemType << "\t" << item.amount << "\t" <<item.date<<"\t" << item.datail << endl;

	output.close();
}
