#pragma once
#include<iostream>
#include<fstream>
#include<cstdio>
#include<string>
#include<vector>
#include<iomanip>

using namespace std;


int Register();

void showMainMenu(int priority,int goal,double sum);
void showAccountingMenu();
void showQueryMenu();

char readMenuSelection(int options);
char readQuitConfirm();
double readAmount(int type);

string readDate();