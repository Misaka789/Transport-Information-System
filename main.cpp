#include<iostream>
#include<fstream>
#include"Line.h"
using namespace std;


int main()
{
    while (true) {
        MainMenu();
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 0:
            return false;   //����0�˳�ѭ��
        case 1:
            AddLine();   //������·����
            break;
        case 2:
            ModefyLine();    //�޸���·����
            break;
        case 3:
            DeleteLine();    //ɾ����·����
            break;
        case 4:
            BestLine();      ///���ߺ���
            break;
        default:
            cout << "��Чѡ�������ԡ�" << endl;
            break;
        }
    }
    return 0;
}