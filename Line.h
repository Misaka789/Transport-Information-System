#pragma once 
#include<iostream>
#include<iomanip>
using namespace std;

class Time {
    //时间格式: hour:minute,+day

    int hour;
    int minute;
    int day;
public:
    Time(const int h = 0, const int min = 0, const int d = 0) : hour(h), minute(min), day(d) {}  // 构造函数
    Time(const Time& obj) : hour(obj.hour), minute(obj.minute), day(obj.day) {}  //复制构造函数

    void swap_(Time& lt, Time& rt) {
        swap(lt.day, rt.day);
        swap(lt.hour, rt.hour);
        swap(lt.minute, rt.minute);
    }
    Time& operator = (Time robj) {
        swap(*this, robj);
        return *this;
    }  //重载等于号

    int getTotalMintue() const {
        return this->day * 1440 + this->hour * 60 + this->minute;   //返回总共需要的分钟数
    }
    friend istream& operator >> (istream& in, Time& time);//声明为友元函数
    friend ostream& operator <<(ostream& out, Time& time);
};





class Lnode {                      // 线路信息，作为边表的元素

public:
    Lnode(const string scn, const string ecn, const Time st, const Time et, const Time spend_t,
        const float spend_m, const string amt,const int type_ )
        : start_city_name(scn), end_city_name(ecn),
        start_time(st), end_time(et), spend_time(spend_t), spend_money(spend_m), amount(amt),type(type_), 
        next(NULL){}

               //线路类，包含发车城市，目标城市，起始时间，结束时间，花费的时间，花费的钱，班次
              //解释: scn始发城市；ecn目的城市；st出发时间；et抵达时间（二者相减就是所需时间，具体还需要Time结构体的重载）
             //spend_t花费时间;spend_m花费金钱；amt班次编号
    void DispLnode()
    {
        
        cout <<left<< setw(10)<<setfill(' ') << start_city_name << left << setw(10) << end_city_name << amount << "\t" << start_time << " \t" << end_time << " \t" << spend_time << " \t" << spend_money <<"(RMB)" << " \t";
        cout << ((type == 1) ? "飞机" : "列车");
    }
    string start_city_name;
    string end_city_name;
    Time start_time, end_time;
    Time spend_time;
    float spend_money;
    int type;                             //类型，1表示属于飞机航班，0表示属于列车航班
    string amount;                      // 火车或飞机的班次
    Lnode* next;
};

class Vnode {                           // 顶点表中的头结点，存储始发站的信息
public:
    Vnode(string scn):start_city_name(scn),nextV(NULL),nextL(NULL){}
    string start_city_name;  // 头结点只包含始发地名
    Vnode* nextV;Lnode *nextL;
};




Vnode* ReadFile();
void MainMenu();
void ModefyLine();
void DeleteLine();
void BestLine();
void AddLine();
void AddLine1();
void DispAllLines();