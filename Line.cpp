#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include"Line.h"
#define  File "data.txt"
using namespace std;
void MainMenu()
{
	cout << "\t" << "��ӭʹ�ý�ͨ��ѯϵͳ" << endl;
	cout << "\t" << "1.������м����·��" << endl;
	cout << "\t" << "2.�޸����·��" << endl;
	cout << "\t" << "3.ɾ�����·��" << endl;
	cout << "\t" << "4.�������������ž���(���ʱ�� & ��С����)" << endl;
	cout << "\t" << "0.�˳�����" << endl;
}
//���˵�
Vnode* ReadFile()
{
	ifstream ifs(File);
	string scn, ecn, amt;
	Time st, et, spend_t;
	float spend_m;
	int type_;
	ifs >> scn >> ecn >> st >> et >> spend_t >> spend_m >> amt >> type_;
	//����������Ҫ����>>�����
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
	
	
	cout << "�����";
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
