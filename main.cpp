#include<iostream>
#include<fstream>
#include"People.hpp"
#include"Line.hpp"
using namespace std;

void Login()
{
    cout << "\t" << "��ӭʹ�ý�ͨ��ѯϵͳ" << endl;
    cout << "\t" << "��ѡ��������" << endl;
    cout << "\t" << "1.����Ա��¼:" << endl;
    cout << "\t" << "2.�û���¼:" << endl;
    cout << "\t" << "3.�û�ע��" << endl;
}

bool CheckM()
{
    string id, pwd, id_, pwd_;
    cout << "���������Ա�˺�:" << endl;
    cin >> id;
    cout << " ����������:" << endl;
    cin >> pwd;
    ifstream ifs_M(Manager_F);
    while (ifs_M >> id_>>pwd_)
    {
        if (id == id_ && pwd == pwd_)
        {
            ifs_M.close();
            return true;
        }
    }
    ifs_M.close();
    return false;
}

bool CheckU()
{
    string id, pwd, id_, pwd_;
    cout << "�������û��˺�:" << endl;
    cin >> id;
    cout << " ����������:" << endl;
    cin >> pwd;
    ifstream ifs_U(Users_F);
    while (ifs_U>> id_ >> pwd_)
    {
        if (id == id_ && pwd == pwd_)
        {
            ifs_U.close();
            return true;
        }
    }
    ifs_U.close();
    return false;
}

int main()
{
    //DispAllLines();
    Lines line;
    line.SaveToFile();
    while (true) {
        Login();
        int choice1;
        cin >> choice1;
        if (choice1 == 1)
        {
            if (CheckM())
            {
                while (true) {
                    system("cls");
                    cout << "��¼�ɹ�����ӭʹ��" << endl;
                    Manager manager;
                    manager.Menu();
                    int choice;
                    cin >> choice;
                    Lines line;
                    switch (choice)
                    {

                    case 0:break;
                    case 1:
                    {
                        line.Disp();
                        break;
                    }
                    case 2:
                    {
                        line.AddLine();
                        break;
                    }
                    case 3:
                    {
                        line.ModefyLine();
                        break;
                    }
                    case 4:
                    {
                        line.DeleteLine();
                        break;
                    }
                    case 5:
                    {
                        manager.Modefy();
                        break;
                    }
                    }
                }
            }
            else
            {
                cout << "\u001b[31merror:" << "\u001b[0m" << "�˺Ż�����������������룡" << endl;
                system("pause");
                system("cls");
            }
        }
        else if (choice1==2)
        {
            if (CheckU())
            {
                User user;
                system("cls");
                user.Menu();
                int choice;
                cin >> choice;
                Lines line;
                switch (choice)
                {
                case 0:return 0;
                case 1:
                {
                    string scn, ecn;
                    cout << "������:";
                    cin >> scn;
                    cout << "�յ����:";
                    cin >> ecn;
                    line.BestLine_m(scn, ecn);
                    break;
                }
                case 2:
                {
                    string scn, ecn;
                    cout << "������:";
                    cin >> scn;
                    cout << "�յ����:";
                    cin >> ecn;
                    line.BestLine_t(scn, ecn);
                    break;
                }
                }
            }
            else
            {
                cout << "\u001b[31merror:" << "\u001b[0m" << "�˺Ż�����������������룡" << endl;
                system("pause");
                system("cls");
            }
        }
        else // (choice1 == 3)
        {
            Manager m;
            m.Register();
        }
    }
    return 0;
}