#pragma once
#include<iostream>
#define Users_F "Users"
#include<fstream>
#include<vector>
//#include"Line.h"
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

class Manager :public People
{
public:
	vector<User> users;
	void Menu()
	{
		cout << "\t" << "欢迎使用交通咨询系统" << endl;
		cout << "\t" << "1.查看所有线路" << endl;
		cout << "\t" << "2.添加城市及相关路线" << endl;
		cout << "\t" << "3.修改相关路线" << endl;
		cout << "\t" << "4.删除相关路线" << endl;
		cout << "\t" << "0.退出程序" << endl;
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

	void Disp();  //显示所有用户账号及密码

	void Modefy();  //修改密码

	void SaveToFile();
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
	cout << "输入用户名:" << endl;
	string id_;
	cin >> id_;
	cout << "输入密码:" << endl;
	string pwd1, pwd2;
	cin >> pwd1;
	cout << "再次确认密码:" << endl;
	cin >> pwd2;
	if (pwd1 != pwd2)
	{
		cout << "\u001b[31merror:" << "\u001b[0m" << "两次密码不一致，请重新输入!" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (auto it = users.begin(); it != users.end(); it++)
	{
		if (it->id == id_)
		{
			it->pwd = pwd1;
			cout << "修改完成!" << endl;
			SaveToFile();
			system("pause");
			system("cls");
			break;
		}
	}
}

class User : public People
{
public:
	void Menu()
	{
		cout << "\t" << "1.对两地做出最优决策(最短时间 & 最小开销)" << endl;
		cout << "\t" << "0.退出程序" << endl;
	}
	User(string id_,string pwd_):People(id_,pwd_){}
	void Login();
};