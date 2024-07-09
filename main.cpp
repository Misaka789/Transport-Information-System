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
            return false;   //输入0退出循环
        case 1:
            DispAllLines();  //查看所有线路
            break;
        case 2:
            AddLine1();   //增加线路函数
            break;
        case 3:
            ModefyLine();    //修改线路函数
            break;
        case 4:
            DeleteLine();    //删除线路函数
            break;
        case 5:
            BestLine();      ///决策函数
            break;
        default:
            cout << "无效选择，请重试。" << endl;
            break;
        }
    }
    return 0;
}