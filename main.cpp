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
            return false;   //输入0退出循环
        case 1:
            AddLine();   //增加线路函数
            break;
        case 2:
            ModefyLine();    //修改线路函数
            break;
        case 3:
            DeleteLine();    //删除线路函数
            break;
        case 4:
            BestLine();      ///决策函数
            break;
        default:
            cout << "无效选择，请重试。" << endl;
            break;
        }
    }
    return 0;
}