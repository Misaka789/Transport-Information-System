#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include"Line.h"
#define  File "data.txt"
using namespace std;
void MainMenu()
{
	cout << "\t" << "欢迎使用交通咨询系统" << endl;
	cout << "\t" << "1.输入城市及相关路线" << endl;
	cout << "\t" << "2.修改相关路线" << endl;
	cout << "\t" << "3.删除相关路线" << endl;
	cout << "\t" << "4.对两地做出最优决策(最短时间 & 最小开销)" << endl;
	cout << "\t" << "0.退出程序" << endl;
}
//主菜单
Vnode* ReadFile()
{
	ifstream ifs(File);
	string scn, ecn, amt;
	Time st, et, spend_t;
	float spend_m;
	int type_;
	ifs >> scn >> ecn >> st >> et >> spend_t >> spend_m >> amt >> type_;
	//出现问题需要重载>>运算符
	Vnode* root = new Vnode();
	while (ifs>>scn>>ecn>>st>>et>>spend_t>>spend_m>>amt>>type_)
	{
	}
}

template<typename T>
void AddLine()
{
	
} 

void AddLine1()
{
	
	
	cout << "已添加";
}

void ModefyLine()
{

}
void DeleteLine()
{

}
void BestLine()
{

}
