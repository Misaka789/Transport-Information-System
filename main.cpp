#include<iostream>
#include<fstream>
#include"Line.h"
#include"Time.h"
using namespace std;


int main()
{
    //DispAllLines();
    while (true) {
        MainMenu();
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 0:
            return false;   //����0�˳�ѭ��
        case 1:
            DispAllLines();  //�鿴������·
            break;
        case 2:
            AddLine1();   //������·����
            break;
        case 3:
            ModefyLine();    //�޸���·����
            break;
        case 4:
            DeleteLine();    //ɾ����·����
            break;
        case 5:
            BestLine();      ///���ߺ���
            break;
        default:
            cout << "��Чѡ�������ԡ�" << endl;
            break;
        }
    }
    return 0;
}