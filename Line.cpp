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

Vnode* Catch_amt(string amt)    //���ݰ�κŲ��ң����ض�Ӧ����ʼ����
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
		bool is_in = 0;   //�ж��Ƿ����ѭ��
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
		//is_in==0 ˵��Ҫ�½�һ��������
		if (is_in == 0) {
			Vnode* tempV = new Vnode(scn);
			rearV->nextV = tempV;
			rearV = rearV->nextV;
			rearV->nextL = tempL;
		}
	}
	ifs.close();
	return root;   //�����ڽӱ��ͷ���
}      //���ļ��������ݴ����ڽӱ�

void Save_to_File(Vnode* r)  //���ڽӱ���Ϣ�����ļ�
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
	cout << "��ʼ����:" << endl;
	cin >> scn;
	cout << "Ŀ�ĳ���:" << endl;
	cin >> ecn;
	cout << "���:" << endl;
	cin >> amt;
	if (is_exist(amt)) {
		cout << "\u001b[31merror:" << "\u001b[0m"<<"�ð���Ѵ��ڣ�����������!" << endl;
		system("pause");
		system("cls");
			return;
	}
	cout << "����ʱ��(hour:minute,+day)" << endl;
	cin >> st;
	cout << "�ִ�ʱ��(hour:minute,+day)" << endl;
	cin >> et;
	cout << "����ʱ��(hour:minute,+day)" << endl;
	cin >> spend_t;
	cout << "��Ǯ����" << endl;
	cin >> spend_m;
	Lnode* tempL = new Lnode(scn, ecn, st, et, spend_t, spend_m, amt, type_);
	Vnode* to_find = r;
	bool is_in = 0;   //�ж��Ƿ����ѭ��
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
	//is_in==0 ˵��Ҫ�½�һ��������
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
	cout << "��ѡ����Ҫ�������·����(1:���ࣻ0:�г�)" << endl;
	cin >> type_;
	AddLine(type_);
	cout << "�����" << endl;
	system("pause");
	system("cls");
}

void DispAllLines()
{
	Vnode* r = ReadFile();
	Vnode* Vt = r;
	system("cls");
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
	system("pause");
	system("cls");
}

void ModefyLine()
{
	Vnode* r = ReadFile();
	cout << "������Ҫ�޸ĵİ��(Ψһ):" << endl;
	string amt;
	cin >> amt;
	if (!is_exist(amt))
	{
		cout << "\u001b[31merror:" << "\u001b[0m" << "�ð�β����ڣ�����������!" << endl;
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
	cout << "������Ҫɾ���İ��(Ψһ):" << endl;
	string amt;
	cin >> amt;
	if (!is_exist(amt))
	{
		cout << "\u001b[31merror:" << "\u001b[0m" << "�ð�β����ڣ�����������!" << endl;
		system("pause");
		system("cls");
		return;
	}
	Vnode* to_deleteV = Catch_amt(amt);   //�õ�Ҫɾ������ʼ����
	Lnode* to_deleteL = to_deleteV->nextL;
	while (to_deleteL != NULL)
	{

	}

	Save_to_File(r);
}
void BestLine()
{

}
