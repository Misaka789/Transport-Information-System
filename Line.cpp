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
	cout << "\t" << "1.添加城市及相关路线" << endl;
	cout << "\t" << "2.修改相关路线" << endl;
	cout << "\t" << "3.删除相关路线" << endl;
	cout << "\t" << "4.对两地做出最优决策(最短时间 & 最小开销)" << endl;
	cout << "\t" << "0.退出程序" << endl;
}
//主菜单

istream& operator >> (istream& in, Time& time) {          //重载右移运算符简化输入
	char c1, c2, c3;
	int hour, minute, day;
	in >> hour >> c1 >> minute >> c2 >> c3 >> day;
	//输入形式为 时：分：+天

	time.day = day;
	time.minute = minute;
	time.hour = hour;
	return in;
}



Vnode* ReadFile()    //将文件中的信息读取并建立邻接表
{
	ifstream ifs(File);
	string scn, ecn, amt;
	Time st, et, spend_t;
	float spend_m;
	int type_;
	ifs >> scn >> ecn >> st >> et >> spend_t >> spend_m >> amt >> type_;
	
	Vnode* rearV = NULL;   //邻接表头结点的尾指针
	//Vnode* rearL = NULL;    //用于选择需要增长的到达地的指针
	Vnode* root = new Vnode(scn);
	rearV = root; //rearL = root;
	Lnode* temp=new Lnode(scn, ecn, st, et, spend_t, spend_m, amt, type_);
	//rearL->nextL = temp;
	while (ifs>>scn>>ecn>>st>>et>>spend_t>>spend_m>>amt>>type_)
	{
		//Vnode* tempV = new Vnode(scn);   不一定需要新建一个节点因为可能原有链表中已经存在包含该起始点的结点
		Lnode* tempL = new Lnode(scn, ecn, st, et, spend_t, spend_m, amt, type_);
		Vnode* to_find = root;
		while (to_find != NULL)
		{
			if (to_find->start_city_name == scn) 
			{
				Lnode* add_L=to_find->nextL;
				if (add_L == NULL)
				{
					to_find->nextL = tempL;
					break;
				}
				while (add_L->next != NULL)
				{
					add_L = add_L->next;
				}
				add_L->next = tempL;
				break;
			}
			to_find = to_find->nextV;
		}
		//循环结束说明要新建一个顶点了
		Vnode* tempV = new Vnode(scn);
		rearV->nextV= tempV;
		rearV = rearV->nextV;
		rearV->nextL = tempL;
	}
	return root;   //返回邻接表的头结点
}

void AddLine(int type_)
{
	
} 

void AddLine1()
{
	Vnode* r = ReadFile();
	cout << "请选择要添加的类别(1:航班；0:列车)" << endl;
	system("pause");
	int type_;
	cin >> type_;
	AddLine(type_);
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
