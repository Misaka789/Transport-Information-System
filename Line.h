#pragma once 
#include<iostream>
#include<iomanip>
using namespace std;

class Time {
    //ʱ���ʽ: hour:minute,+day

    int hour;
    int minute;
    int day;
public:
    Time(const int h = 0, const int min = 0, const int d = 0) : hour(h), minute(min), day(d) {}  // ���캯��
    Time(const Time& obj) : hour(obj.hour), minute(obj.minute), day(obj.day) {}  //���ƹ��캯��

    void swap_(Time& lt, Time& rt) {
        swap(lt.day, rt.day);
        swap(lt.hour, rt.hour);
        swap(lt.minute, rt.minute);
    }
    Time& operator = (Time robj) {
        swap(*this, robj);
        return *this;
    }  //���ص��ں�

    int getTotalMintue() const {
        return this->day * 1440 + this->hour * 60 + this->minute;   //�����ܹ���Ҫ�ķ�����
    }
    friend istream& operator >> (istream& in, Time& time);//����Ϊ��Ԫ����
    friend ostream& operator <<(ostream& out, Time& time);
};





class Lnode {                      // ��·��Ϣ����Ϊ�߱��Ԫ��

public:
    Lnode(const string scn, const string ecn, const Time st, const Time et, const Time spend_t,
        const float spend_m, const string amt,const int type_ )
        : start_city_name(scn), end_city_name(ecn),
        start_time(st), end_time(et), spend_time(spend_t), spend_money(spend_m), amount(amt),type(type_), 
        next(NULL){}

               //��·�࣬�����������У�Ŀ����У���ʼʱ�䣬����ʱ�䣬���ѵ�ʱ�䣬���ѵ�Ǯ�����
              //����: scnʼ�����У�ecnĿ�ĳ��У�st����ʱ�䣻et�ִ�ʱ�䣨���������������ʱ�䣬���廹��ҪTime�ṹ������أ�
             //spend_t����ʱ��;spend_m���ѽ�Ǯ��amt��α��
    void DispLnode()
    {
        
        cout <<left<< setw(10)<<setfill(' ') << start_city_name << left << setw(10) << end_city_name << amount << "\t" << start_time << " \t" << end_time << " \t" << spend_time << " \t" << spend_money <<"(RMB)" << " \t";
        cout << ((type == 1) ? "�ɻ�" : "�г�");
    }
    string start_city_name;
    string end_city_name;
    Time start_time, end_time;
    Time spend_time;
    float spend_money;
    int type;                             //���ͣ�1��ʾ���ڷɻ����࣬0��ʾ�����г�����
    string amount;                      // �𳵻�ɻ��İ��
    Lnode* next;
};

class Vnode {                           // ������е�ͷ��㣬�洢ʼ��վ����Ϣ
public:
    Vnode(string scn):start_city_name(scn),nextV(NULL),nextL(NULL){}
    string start_city_name;  // ͷ���ֻ����ʼ������
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