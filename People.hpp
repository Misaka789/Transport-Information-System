#pragma once
#include<iostream>
#define Users_F "Users.txt"
#include<fstream>
#include<vector>
using namespace std;
class People
{
public :
	string id;
	string pwd;
	People(){}
	People(string id_, string pwd_) :id(id_), pwd(pwd_) {}
	//Lines lines;
};

class User : public People
{
public:
	void Menu()
	{
		cout << "\t" << "��½�ɹ�" << endl;
		cout << "\t" << "1.�������������ž���(���ʱ�� & ��С����)" << endl;
		cout << "\t" << "0.�˳�����" << endl;
	}
	User(string id_, string pwd_) :People(id_, pwd_) {}
	User() {}
};

class Manager :public People
{
public:
	vector<User> users;
	void Menu()
	{
		cout << "\t" << "��ӭʹ�ý�ͨ��ѯϵͳ" << endl;
		cout << "\t" << "1.�鿴������·" << endl;
		cout << "\t" << "2.��ӳ��м����·��" << endl;
		cout << "\t" << "3.�޸����·��" << endl;
		cout << "\t" << "4.ɾ�����·��" << endl;
		cout << "\t" << "5.�޸��û�����" << endl;
		cout << "\t" << "0.�˳�����" << endl;
	}
	Manager()
	{
		ifstream ifs(Users_F);
		string id_, pwd_;
		while (ifs >> id_ >> pwd_)
		{
			User u(id_, pwd_);
			users.push_back(u);
		}
		ifs.close();
	}

	void Disp();  //��ʾ�����û��˺ż�����

	void Modefy();  //�޸�����

	void SaveToFile();

	void Register();
};

void Manager::SaveToFile()
{
	ofstream ofs(Users_F);
	for (auto it = users.begin(); it != users.end(); it++)
	{
		ofs << it->id << " " << it->pwd << " ";
	}
	ofs.close();
}

void Manager::Disp()
{
	for (auto it = users.begin(); it != users.end(); it++)
	{
		cout << "User ID:" << endl;
		cout << it->id;
		cout << "User PassWord" << endl;
		cout << it->pwd;
	}
}

void Manager::Modefy()
{
	cout << "�����û���:" << endl;
	string id_;
	cin >> id_;
	cout << "��������:" << endl;
	string pwd1, pwd2;
	cin >> pwd1;
	cout << "�ٴ�ȷ������:" << endl;
	cin >> pwd2;
	if (pwd1 != pwd2)
	{
		cout << "\u001b[31merror:" << "\u001b[0m" << "�������벻һ�£�����������!" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (auto it = users.begin(); it != users.end(); it++)
	{
		if (it->id == id_)
		{
			it->pwd = pwd1;
			cout << "�޸����!" << endl;
			SaveToFile();
			system("pause");
			system("cls");
			break;
		}
	}
}

void Manager::Register()
{
	cout << "�����û���:" << endl;
	string id_;
	cin >> id_;
	for (auto it = users.begin(); it != users.end(); it++)
	{
		if (it->id == id_)
		{
			cout << "\u001b[31merror:" << "\u001b[0m" << "�û����Ѵ��ڣ�����������:" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	cout << "��������:" << endl;
	string pwd1, pwd2;
	cin >> pwd1;
	cout << "�ٴ�ȷ������:" << endl;
	cin >> pwd2;
	if (pwd1 != pwd2)
	{
		cout << "\u001b[31merror:" << "\u001b[0m" << "�������벻һ�£�����������!" << endl;
		system("pause");
		system("cls");
		return;
	}
	User u(id_, pwd1);
	users.push_back(u);
	SaveToFile();
	cout << "�˺�ע����ɣ��뷵�ص�¼" << endl;
	system("pause");
	system("cls");
}

