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
	cout << "\t" << "1.�鿴������·" << endl;
	cout << "\t" << "2.��ӳ��м����·��" << endl;
	cout << "\t" << "3.�޸����·��" << endl;
	cout << "\t" << "4.ɾ�����·��" << endl;
	cout << "\t" << "5.�������������ž���(���ʱ�� & ��С����)" << endl;
	cout << "\t" << "0.�˳�����" << endl;
}
//���˵�

istream& operator >> (istream& in, Time& time) {          //�������������������
	char c1, c2, c3;
	int hour, minute, day;
	in >> hour >> c1 >> minute >> c2 >> c3 >> day;
	//������ʽΪ ʱ���֣�+��

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

Vnode* ReadFile()    //���ļ��е���Ϣ��ȡ�������ڽӱ�
{
	ifstream ifs(File);
	if (!ifs.is_open())cout << "�ļ���ȡʧ�ܣ�";
	string scn, ecn, amt;
	Time st, et, spend_t;
	float spend_m;
	int type_;
	ifs >> scn >> ecn >> amt >> st >> et >> spend_t >> spend_m >> type_;
	
	Vnode* rearV = NULL;   //�ڽӱ�ͷ����βָ��
	//Vnode* rearL = NULL;    //����ѡ����Ҫ�����ĵ���ص�ָ��
	Vnode* root = new Vnode(scn);
	rearV = root; //rearL = root;
	Lnode* temp=new Lnode(scn, ecn, st, et, spend_t, spend_m, amt, type_);
	rearV->nextL = temp;
	while (ifs>>scn>>ecn >> amt >>st>>et>>spend_t>>spend_m>>type_)
	{
		//Vnode* tempV = new Vnode(scn);   ��һ����Ҫ�½�һ���ڵ���Ϊ����ԭ���������Ѿ����ڰ�������ʼ��Ľ��
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
		//ѭ������˵��Ҫ�½�һ��������
		Vnode* tempV = new Vnode(scn);
		rearV->nextV= tempV;
		rearV = rearV->nextV;
		rearV->nextL = tempL;
		rearV->nextV = NULL;
	}
	return root;   //�����ڽӱ��ͷ���
}

void AddLine(int type_)
{
	
} 

void AddLine1()
{
	Vnode* r = ReadFile();
	int type_;
	cin >> type_;
	AddLine(type_);
	cout << "�����";
}

void DispAllLines()
{
	Vnode* r = ReadFile();
	Vnode* Vt = r;
	cout << "|" << "ʼ������" << "|" << "�յ����" << "|" << "��α��" << "|" << "ʼ��ʱ��" << "|" << "�ִ�ʱ��" << "|" << "�ܼ���ʱ" << "|" << "�ܼƻ���" << "|" << "������" << "|" << endl;
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
