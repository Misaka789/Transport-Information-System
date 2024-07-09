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
	cout << "\t" << "1.查看所有线路" << endl;
	cout << "\t" << "2.添加城市及相关路线" << endl;
	cout << "\t" << "3.修改相关路线" << endl;
	cout << "\t" << "4.删除相关路线" << endl;
	cout << "\t" << "5.对两地做出最优决策(最短时间 & 最小开销)" << endl;
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

ostream& operator <<(ostream& out, Time& time)
{
	out <<right<< setw(2)<<setfill('0')<<time.hour << ":" <<right<< setw(2) << setfill('0')<< time.minute << ",+" <<right<< setw(2) << setfill('0')<< time.day;
	return out;
}

bool is_exist(string amt)
{
	Vnode* tV = ReadFile();
	while (tV != NULL)
	{
		Lnode* tL = tV->nextL;
		while (tL != NULL)
		{
			if (tL->amount == amt)
				return true;

			tL = tL->next;
		}
		tV = tV->nextV;
	}
	return false;
}

Vnode* Catch_amt(string amt)    //根据班次号查找，返回对应的起始城市
{
	Vnode* tV = ReadFile();
	while (tV != NULL)
	{
		Lnode* tL = tV->nextL;
		while (tL != NULL)
		{
			if (tL->amount == amt)
				return tV;
			tL = tL->next;
		}
		tV = tV->nextV;
	}
}

Vnode* ReadFile()    //将文件中的信息读取并建立邻接表
{
	ifstream ifs(File);
	if (!ifs.is_open())cout << "文件读取失败！";
	string scn, ecn, amt;
	Time st, et, spend_t;
	float spend_m;
	int type_;
	ifs >> scn >> ecn >> amt >> st >> et >> spend_t >> spend_m >> type_;
	
	Vnode* rearV = NULL;   //邻接表头结点的尾指针
	//Vnode* rearL = NULL;    //用于选择需要增长的到达地的指针
	Vnode* root = new Vnode(scn);
	rearV = root; //rearL = root;
	Lnode* temp=new Lnode(scn, ecn, st, et, spend_t, spend_m, amt, type_);
	rearV->nextL = temp;
	while (ifs>>scn>>ecn >> amt >>st>>et>>spend_t>>spend_m>>type_)
	{
		//Vnode* tempV = new Vnode(scn);   不一定需要新建一个节点因为可能原有链表中已经存在包含该起始点的结点
		Lnode* tempL = new Lnode(scn, ecn, st, et, spend_t, spend_m, amt, type_);
		Vnode* to_find = root;
		bool is_in = 0;   //判断是否进入循环
		while (to_find != NULL)
		{
			if (to_find->start_city_name == scn) 
			{
				is_in = 1;
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
		//is_in==0 说明要新建一个顶点了
		if (is_in == 0) {
			Vnode* tempV = new Vnode(scn);
			rearV->nextV = tempV;
			rearV = rearV->nextV;
			rearV->nextL = tempL;
		}
	}
	ifs.close();
	return root;   //返回邻接表的头结点
}      //从文件读入数据存入邻接表

void Save_to_File(Vnode* r)  //将邻接表信息存入文件
{
	ofstream ofs(File);
	Vnode* Vt = r;
	while (Vt != NULL)
	{
		Lnode* Lt = Vt->nextL;
		while (Lt != NULL)
		{
			ofs << left << setw(10) << setfill(' ') << Lt->start_city_name
				<< left << setw(10) << Lt->end_city_name << Lt->amount << "\t" << Lt->start_time
				<< " \t" << Lt->end_time << " \t" << Lt->spend_time << " \t" << Lt->spend_money << " \t" << Lt->type << endl;
			Lt = Lt->next;
		}
		Vt = Vt->nextV;
	}
	ofs.close();
}

void AddLine(int type_)
{
	Vnode* r = ReadFile();
	string scn, ecn, amt;
	Time st, et, spend_t;
	float spend_m;
	cout << "起始城市:" << endl;
	cin >> scn;
	cout << "目的城市:" << endl;
	cin >> ecn;
	cout << "班次:" << endl;
	cin >> amt;
	if (is_exist(amt)) {
		cout << "\u001b[31merror:" << "\u001b[0m"<<"该班次已存在，请重新输入!" << endl;
		system("pause");
		system("cls");
			return;
	}
	cout << "出发时间(hour:minute,+day)" << endl;
	cin >> st;
	cout << "抵达时间(hour:minute,+day)" << endl;
	cin >> et;
	cout << "花费时间(hour:minute,+day)" << endl;
	cin >> spend_t;
	cout << "金钱花费" << endl;
	cin >> spend_m;
	Lnode* tempL = new Lnode(scn, ecn, st, et, spend_t, spend_m, amt, type_);
	Vnode* to_find = r;
	bool is_in = 0;   //判断是否进入循环
	while (to_find != NULL)
	{
		if (to_find->start_city_name == scn)
		{
			is_in = 1;
			Lnode* add_L = to_find->nextL;
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
	//is_in==0 说明要新建一个顶点了
	if (is_in == 0) {
		Vnode* tempV = new Vnode(scn);
		Vnode* rear = r;
		while (rear->nextV != NULL)
		{
			rear = rear->nextV;
		}
		rear->nextV = tempV;
		tempV->nextL = tempL;
	}
	Save_to_File(r);
} 

void AddLine1()
{
	Vnode* r = ReadFile();
	int type_;
	cout << "请选择需要加入的线路类型(1:航班；0:列车)" << endl;
	cin >> type_;
	AddLine(type_);
	cout << "已添加" << endl;
	system("pause");
	system("cls");
}

void DispAllLines()
{
	Vnode* r = ReadFile();
	Vnode* Vt = r;
	system("cls");
	cout << "|" << "始发城市" << "|" << "终点城市" << "|" << "班次编号" << "|" << "始发时间" << "|" << "抵达时间" << "|" << "总计用时" << "|" << "总计花费" << "|" << "班次类别" << "|" << endl;
	while (Vt != NULL)
	{
		Lnode* Lt = Vt->nextL;
		while (Lt != NULL)
		{
			Lt->DispLnode();
			cout << endl;
			Lt = Lt->next;
		}
		Vt = Vt->nextV;
	}
	system("pause");
	system("cls");
}

void ModefyLine()
{
	Vnode* r = ReadFile();
	cout << "请输入要修改的班次(唯一):" << endl;
	string amt;
	cin >> amt;
	if (!is_exist(amt))
	{
		cout << "\u001b[31merror:" << "\u001b[0m" << "该班次不存在，请重新输入!" << endl;
		system("pause");
		system("cls");
		return;
	}
	system("cls");


	Save_to_File(r);
}
void DeleteLine()
{
	Vnode* r = ReadFile();
	cout << "请输入要删除的班次(唯一):" << endl;
	string amt;
	cin >> amt;
	if (!is_exist(amt))
	{
		cout << "\u001b[31merror:" << "\u001b[0m" << "该班次不存在，请重新输入!" << endl;
		system("pause");
		system("cls");
		return;
	}
	Vnode* to_deleteV = Catch_amt(amt);   //拿到要删除的起始城市
	Lnode* to_deleteL = to_deleteV->nextL;
	while (to_deleteL != NULL)
	{

	}

	Save_to_File(r);
}
void BestLine()
{

}
