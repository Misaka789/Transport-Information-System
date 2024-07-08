#pragma once 
#include<iostream>
using namespace std;

struct Time {
    //ʱ���ʽ: hour:minute,+day
    int hour;
    int minute;
    int day;

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

};

struct LineNode {                      // ��·��Ϣ����Ϊ�߱��Ԫ��

    LineNode(const string scn, const string ecn, const Time st, const Time et, const Time spend_t,
        const float spend_m, const string amt,const int type_ )
        : start_city_name(scn), end_city_name(ecn),
        start_time(st), end_time(et), spend_time(spend_t), spend_money(spend_m), amount(amt),type(type_) {}

               //��·�࣬�����������У�Ŀ����У���ʼʱ�䣬����ʱ�䣬���ѵ�ʱ�䣬���ѵ�Ǯ�����
              //����: scnʼ�����У�ecnĿ�ĳ��У�st����ʱ�䣻et�ִ�ʱ�䣨���������������ʱ�䣬���廹��ҪTime�ṹ������أ�
             //spend_t����ʱ��;spend_m���ѽ�Ǯ��amt��α��

    string start_city_name;
    string end_city_name;
    Time start_time, end_time;
    Time spend_time;
    float spend_money;
    int type;                             //���ͣ�1��ʾ���ڷɻ����࣬0��ʾ�����г�����
    string amount;                      // �𳵻�ɻ��İ��
};

struct Vnode {                           // ������е�ͷ��㣬�洢ʼ��վ����Ϣ

    Vnode(const std::string scn, const int cid) : start_city_name(scn), city_id(cid) {}
    Vnode(const char* scn, const int cid) : start_city_name(scn), city_id(cid) {}
    Vnode(const std::string scn) : start_city_name(scn), city_id(-1) {}
    Vnode(const char* scn) : start_city_name(scn), city_id(-1) {}
    //��ͬ����ĳ�ʼ���ֱ�Ϊ����ʼ�ص����ֵ��ַ������ַ��͵�����
    string start_city_name;  // ����
    int city_id;  // ���б��,��0��ʼ������ƥ��

};

Vnode* ReadFile();
void MainMenu();
void ModefyLine();
void DeleteLine();
void BestLine();
void AddLine();
void AddLine1();