#pragma once
#include<iomanip>
#include<vector>
#include<algorithm>
#include<string>
//#include"People.h"
#define Manager_F "Manager.txt"
#define User_F "User.txt"
#define Cities_F "Cities.txt"
#define Lines_F "Lines.txt"

class Time {
    //ʱ���ʽ: hour:minute,+day
public:
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
    friend istream& operator >> (istream& in, Time& time);//����Ϊ��Ԫ����
    friend ostream& operator <<(ostream& out, Time& time);
};


istream& operator >> (istream& in, Time& time) {          //�������������������
    char c1, c2, c3;
    int hour, minute, day;
    in >> hour >> c1 >> minute >> c2 >> c3 >> day;
    //������ʽΪ ʱ���֣�+��

    time.day = day;
    time.minute = minute;
    time.hour = hour;
    return in;
}

ostream& operator <<(ostream& out, Time& time)
{
    out << right << setw(2) << setfill('0') << time.hour << ":" << right << setw(2) << setfill('0') << time.minute << ",+" << right << setw(2) << setfill('0') << time.day;
    return out;
}
struct Node
{
public:
    Node(const string scn, const string ecn, const Time st, const Time et, const Time spend_t,
        const float spend_m, const string amt, const int type_)
        : start_city_name(scn), end_city_name(ecn),
        start_time(st), end_time(et), spend_time(spend_t), spend_money(spend_m), amount(amt), type(type_),
        next(NULL) {}

    //��·�࣬�����������У�Ŀ����У���ʼʱ�䣬����ʱ�䣬���ѵ�ʱ�䣬���ѵ�Ǯ�����
   //����: scnʼ�����У�ecnĿ�ĳ��У�st����ʱ�䣻et�ִ�ʱ�䣨���������������ʱ�䣬���廹��ҪTime�ṹ������أ�
  //spend_t����ʱ��;spend_m���ѽ�Ǯ��amt��α��
    void DispNode()
    {
        cout << left << setw(10) << setfill(' ') << start_city_name << left << setw(10) << end_city_name << amount << "\t" << start_time << " \t" << end_time << " \t" << spend_time << " \t" << spend_money << "(RMB)" << " \t";
        cout << ((type == 1) ? "�ɻ�" : "�г�");
    }
    string start_city_name;
    string end_city_name;
    Time start_time, end_time;
    Time spend_time;
    float spend_money;
    int type;                             //���ͣ�1��ʾ���ڷɻ����࣬0��ʾ�����г�����
    string amount;                      // �𳵻�ɻ��İ��
    Node* next;
};

struct Vnode 
{
public:
    Node* next;
    string start_city_name;
    Vnode(string str):start_city_name(str),next(NULL){}
};

class Lines
{
public:
    vector<string> Cities;  //�洢���г�����
    int num;
    vector <Vnode> graph;   //ͼ��ͷ���
    vector <Vnode> ReadFromFile();
    void SaveToFile();
    void AddLine();
    void DeleteLine();
    void Disp() ;
    bool is_exist(string amt);
    void ModefyLine();
    Lines() { graph = ReadFromFile(); }

};
bool Lines::is_exist(string amt)
{
   
    for (auto it = graph.begin(); it != graph.end(); it++)
    {
        Node* tL = it->next;
        while (tL != NULL)
        {
            if (tL->amount == amt)
                return true;
            tL = tL->next;
        }
    }
    return false;
}
vector <Vnode> Lines::ReadFromFile()
{
    ifstream ifs_L(Lines_F);
    string scn, ecn, amt;
    Time st, et, spend_t;
    float spend_m;
    int type_;
    ifs_L >> scn >> ecn >> amt >> st >> et >> spend_t >> spend_m >> type_;
    vector<Vnode> graph;
    Vnode* tempV = new Vnode(scn);
    graph.push_back(*tempV);
    Node* tempL = new Node(scn, ecn, st, et, spend_t, spend_m, amt, type_);
    graph[0].next = tempL;
    while (ifs_L >> scn >> ecn >> amt >> st >> et >> spend_t >> spend_m >> type_)
    {
        
        Node* tempL = new Node(scn, ecn, st, et, spend_t, spend_m, amt, type_);
        auto it = graph.begin();
        for (; it != graph.end(); it++)
        {
            if (it->start_city_name == scn)break;
        }
        if (it != graph.end())
        {
            if (it->next == NULL)
            {
                it->next = tempL;
            }
            else 
            {
                Node* temp = it->next;
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = tempL;
            }
        }
        else
        {
            Vnode* tempV = new Vnode(scn);
            graph.push_back(*tempV);
            it = graph.end();
            it--;
            it->next = tempL;
        }
    }
    return graph;
}  

void Lines::SaveToFile()
{
    ofstream ofs(Lines_F);
    for(auto it=graph.begin();it!=graph.end();it++)
    {
        Node* Lt = it->next;
        while (Lt != NULL)
        {
            ofs << left << setw(10) << setfill(' ') << Lt->start_city_name
                << left << setw(10) << Lt->end_city_name << Lt->amount << "\t" << Lt->start_time
                << " \t" << Lt->end_time << " \t" << Lt->spend_time << " \t" << Lt->spend_money << " \t" << Lt->type << endl;
            Lt = Lt->next;
        }
    }
    ofs.close();
}

void Lines::Disp()
{
    system("cls");
    cout << "|" << "ʼ������" << "|" << "�յ����" << "|" << "��α��" << "|" << "ʼ��ʱ��" << "|" << "�ִ�ʱ��" << "|" << "�ܼ���ʱ" << "|" << "�ܼƻ���" << "|" << "������" << "|" << endl;
    for (auto it = graph.begin(); it != graph.end(); it++)
    {
        Node* Lt = it->next;
        while (Lt != NULL)
        {
            Lt->DispNode();
            cout << endl;
            Lt = Lt->next;
        }
    }
    system("pause");
    system("cls");
}

void Lines::AddLine()
{
    int type_;
    string scn, ecn, amt;
    Time st, et, spend_t;
    float spend_m;
    cout << "��ʼ����:" << endl;
    cin >> scn;
    cout << "Ŀ�ĳ���:" << endl;
    cin >> ecn;
    cout << "���:" << endl;
    cin >> amt;
    if (is_exist(amt)) {
        cout << "\u001b[31merror:" << "\u001b[0m" << "�ð���Ѵ��ڣ�����������!" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "����ʱ��(hour:minute,+day)" << endl;
    cin >> st;
    cout << "�ִ�ʱ��(hour:minute,+day)" << endl;
    cin >> et;
    cout << "����ʱ��(hour:minute,+day)" << endl;
    cin >> spend_t;
    cout << "��Ǯ����" << endl;
    cin >> spend_m;
    cout << "������(1:����;0:�г�):" << endl;
        cin >> type_;
    Node* tempL = new Node(scn, ecn, st, et, spend_t, spend_m, amt, type_);
    auto it = graph.begin();
    for (; it != graph.end(); it++)
    {
        if (it->start_city_name == scn)break;
    }
    if (it != graph.end())
    {
        if (it->next == NULL)
        {
            it->next = tempL;
        }
        else
        {
            Node* t = it->next;
            while (t->next != NULL)
                t = t->next;
            t->next = tempL;
        }
    }
    else
    {
        Vnode* t = new Vnode(scn);
        graph.push_back(*t);
        it = graph.end();
        it--;
        it->next = tempL;
    }
    SaveToFile();
    cout << "��·���ӳɹ�" << endl;
}

void Lines::DeleteLine()
{
    cout << "������Ҫɾ���İ��(Ψһ):" << endl;
    string amt;
    cin >> amt;
    if (!is_exist(amt))
    {
        cout << "\u001b[31merror:" << "\u001b[0m" << "�ð�β����ڣ�����������!" << endl;
        system("pause");
        system("cls");
        return;
    }
    auto it = graph.begin();
    bool flag = false;
    for (; it != graph.end(); it++)
    {
        Node* L = it->next;
        while (L != NULL)
        {
            if (L->amount == amt) 
            {
                flag = true;
                break;
            }
            L = L->next;
        }
        if (flag)break;  //��������ѭ��
    }  
    Node* L = it->next;
    if (L->amount == amt)
        it->next = it->next->next;
    else
    {
        while (L->next != NULL)
        {
            if (L->next->amount == amt)
            {
                L->next = L->next->next;
                break;
            }
            L = L->next;
        }
    }
    if (it->next == NULL)
        graph.erase(it);
    SaveToFile();
    cout << "��·ɾ���ɹ�" << endl;
    system("pause");
    system("cls");
}

void Lines::ModefyLine()
{
    cout << "������Ҫɾ���İ��(Ψһ):" << endl;
    string amt;
    cin >> amt;
    if (!is_exist(amt))
    {
        cout << "\u001b[31merror:" << "\u001b[0m" << "�ð�β����ڣ�����������!" << endl;
        system("pause");
        system("cls");
        return;
    }
    auto it = graph.begin();
    bool flag = false;
    Node* L = it->next;
    for (; it != graph.end(); it++)
    {
        Node* L = it->next;
        while (L != NULL)
        {
            if (L->amount == amt)
            {
                flag = true;
                break;
            }
            L = L->next;
        }
        if (flag)break;  //��������ѭ��
    }
    cout << "��ʼ����:" << endl;
    cin >> L->start_city_name;
    cout << "Ŀ�ĳ���:" << endl;
    cin >> L->end_city_name;
    cout << "����ʱ��(hour:minute,+day)" << endl;
    cin >> L->start_time;
    cout << "�ִ�ʱ��(hour:minute,+day)" << endl;
    cin >> L->end_time;
    cout << "����ʱ��(hour:minute,+day)" << endl;
    cin >> L->spend_time;
    cout << "��Ǯ����" << endl;
    cin >> L->spend_money;
    cout << "������:" << endl;
    cin >> L->type;
    SaveToFile();
    cout << "�޸����" << endl;
    system("pause");
    system("cls");
}