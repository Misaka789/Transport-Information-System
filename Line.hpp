#pragma once
#include<iomanip>
#include<vector>
#include<algorithm>
#include<string>
#include<map>
#include<queue>
//#include"People.h"
#define Manager_F "Manager.txt"
#define User_F "User.txt"
#define Cities_F "Cities.txt"
#define Lines_F "Lines.txt"
#define INF 99999
class Time {
    //时间格式: hour:minute,+day
public:
    int hour;
    int minute;
    int day;
    Time(const int h = 0, const int min = 0, const int d = 0) : hour(h), minute(min), day(d) {}  // 构造函数
    Time(const Time& obj) : hour(obj.hour), minute(obj.minute), day(obj.day) {}  //复制构造函数

    
    Time& operator = (Time robj) {
        swap(*this, robj);
        return *this;
    }  //重载等于号
    bool operator <(Time& a)
    {
        return this->getTotalMintue() < a.getTotalMintue();
    }
    Time& operator -(Time& a);
    int getTotalMintue() const {
        return this->day * 1440 + this->hour * 60 + this->minute;   //返回总共需要的分钟数
    }
    friend istream& operator >> (istream& in, Time& time);//声明为友元函数
    friend ostream& operator <<(ostream& out, Time& time);
};

Time& Time::operator -(Time& a)
{
    Time t;
    if (*this < a)
        throw "error:时间不能为负值";
    if (this->minute < a.minute)
    {
        t.minute = this->minute + 60 - a.minute;
        t.hour--;
    }
    else t.minute = this->minute - a.minute;
    if(this->hour < a.hour)
    {
        t.hour = this->hour + 12 - a.hour;
        t.day--;
    }
    else t.hour = this->hour - a.hour;
    t.day = this->day - a.day;
    return t;
}

istream& operator >> (istream& in, Time& time) {          //重载右移运算符简化输入
    char c1, c2, c3;
    int hour, minute, day;
    in >> hour >> c1 >> minute >> c2 >> c3 >> day;
    //输入形式为 时：分：+天

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
class Node
{
public:
    Node(const string scn, const string ecn, const Time st, const Time et, const Time spend_t,
        const float spend_m, const string amt, const int type_)
        : start_city_name(scn), end_city_name(ecn),
        start_time(st), end_time(et), spend_time(spend_t), spend_money(spend_m), amount(amt), type(type_),
        next(NULL) {}

    //线路类，包含发车城市，目标城市，起始时间，结束时间，花费的时间，花费的钱，班次
   //解释: scn始发城市；ecn目的城市；st出发时间；et抵达时间（二者相减就是所需时间，具体还需要Time结构体的重载）
  //spend_t花费时间;spend_m花费金钱；amt班次编号
    void DispNode()
    {
        cout << left << setw(10) << setfill(' ') << start_city_name << left << setw(10) << end_city_name << amount << "\t" << start_time << " \t" << end_time << " \t" << spend_time << " \t" << spend_money << "(RMB)" << " \t";
        cout << ((type == 1) ? "飞机" : "列车");
    }
    string start_city_name;
    string end_city_name;
    Time start_time, end_time;
    Time spend_time;
    float spend_money;
    int type;                             //类型，1表示属于飞机航班，0表示属于列车航班
    string amount;                      // 火车或飞机的班次
    Node* next;
};

class Vnode 
{
public:
    Node* next;
    string start_city_name;
    Vnode(string str):start_city_name(str),next(NULL){}
};

class Lines
{
public:
    vector<string> Cities;  //存储所有城市名
    int num;
    vector <Vnode> graph;   //图的头结点
    vector <Vnode> ReadFromFile();
    void SaveToFile();
    void AddLine();
    void DeleteLine();
    void Disp() ;
    bool is_exist(string amt);
    void ModefyLine();
    void BestLine_m(string scn, string ecn);
    void BestLine_t(string scn, string ecn);
    Lines() 
    {
        graph = ReadFromFile(); 
        for (auto it = graph.begin(); it != graph.end(); it++)
        {
            Cities.push_back(it->start_city_name);
        }
    }

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
    cout << "|" << "始发城市" << "|" << "终点城市" << "|" << "班次编号" << "|" << "始发时间" << "|" << "抵达时间" << "|" << "总计用时" << "|" << "总计花费" << "|" << "班次类别" << "|" << endl;
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
    cout << "起始城市:" << endl;
    cin >> scn;
    cout << "目的城市:" << endl;
    cin >> ecn;
    cout << "班次:" << endl;
    cin >> amt;
    if (is_exist(amt)) {
        cout << "\u001b[31merror:" << "\u001b[0m" << "该班次已存在，请重新输入!" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "出发时间(hour:minute,+day)" << endl;
    cin >> st;
    cout << "抵达时间(hour:minute,+day)" << endl;
    cin >> et;
    cout << "花费时间(hour:minute,+day)" << endl;
    cin >> spend_t;
    cout << "金钱花费" << endl;
    cin >> spend_m;
    cout << "班次类别(1:航班;0:列车):" << endl;
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
    cout << "线路添加成功" << endl;
}

void Lines::DeleteLine()
{
    cout << "请输入要删除的班次(唯一):" << endl;
    string amt;
    cin >> amt;
    if (!is_exist(amt))
    {
        cout << "\u001b[31merror:" << "\u001b[0m" << "该班次不存在，请重新输入!" << endl;
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
        if (flag)break;  //跳出两层循环
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
    cout << "线路删除成功" << endl;
    system("pause");
    system("cls");
}

void Lines::ModefyLine()
{
    cout << "请输入要删除的班次(唯一):" << endl;
    string amt;
    cin >> amt;
    if (!is_exist(amt))
    {
        cout << "\u001b[31merror:" << "\u001b[0m" << "该班次不存在，请重新输入!" << endl;
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
        if (flag)break;  //跳出两层循环
    }
    cout << "起始城市:" << endl;
    cin >> L->start_city_name;
    cout << "目的城市:" << endl;
    cin >> L->end_city_name;
    cout << "出发时间(hour:minute,+day)" << endl;
    cin >> L->start_time;
    cout << "抵达时间(hour:minute,+day)" << endl;
    cin >> L->end_time;
    cout << "花费时间(hour:minute,+day)" << endl;
    cin >> L->spend_time;
    cout << "金钱花费" << endl;
    cin >> L->spend_money;
    cout << "班次类别:" << endl;
    cin >> L->type;
    SaveToFile();
    cout << "修改完成" << endl;
    system("pause");
    system("cls");
}

struct cmp
{
    bool operator()(const Node& a, const Node& b) const
    {
        return a.spend_money < b.spend_money; // 小根堆，spend_money小的优先级高,便于优先队列的比较
    }
};

struct QNode
{
    string city;
    int money;
    QNode(string c,int s):city(c),money(s){}

    bool operator < (const QNode& s)const
    {
        return money > s.money;
    }
};

void Lines::BestLine_m(string scn,string ecn)   //最小花费
{
    map<string,bool> visited;
    map<string, string > path;
    priority_queue<QNode> pq;
    map<string, int> spend;
    auto it = graph.begin();
    for (; it != graph.end(); it++)
        if (it->start_city_name == scn) //it拿到起点节点
            break;
    visited[it->start_city_name] = true;
    Node* temp = it->next;
    for (auto it = Cities.begin(); it!= Cities.end(); it++)
    {
        spend[*it] = INF;
        visited.insert(make_pair(*it, false));
    }
   
    spend[scn] = 0;
   
    pq.push(QNode(scn, 0));  //初始化spend数组
    for(int i=0;i<Cities.size();i++)
    {
        QNode t = pq.top(); pq.pop();
        string u = t.city;
        visited[u] = true;
        auto it = graph.begin();
        for (; it != graph.end(); it++)
            if (it->start_city_name == u)   //it拿到起点节点5
                break;
        Node* p = it->next;
        while (p != NULL)
        {
            string w = p->end_city_name;
            if (visited[w] == 0 && spend[w] > spend[u] + p->spend_money)
            {
                spend[w] = spend[u] + p->spend_money;
                pq.push(QNode(w, spend[w]));
                path[w] = u;
            }
            p = p->next;
        }
    }
    cout << "从" << scn << "到" << ecn << "花费最少的路线为:" << endl;
    string str=path[ecn];
    vector<string> p;
    p.push_back(ecn);
    while (str!=scn)
    {
        p.push_back(str);
        str = path[str];
    }
    p.push_back(scn);
    vector<Node> p2;
    /*for (auto a : p)
    {
        cout << a << " ";
        cout << endl;
    }*/
    for (auto it = p.begin(); it != p.end()-1; it++)
    {
        auto it2 = graph.begin();
        while (it2 != graph.end())
        {
            if (it2->start_city_name == *(it+1))break;
            it2++;
        }
        Node* t = it2->next;
        while (t->end_city_name != *(it))
        {
            t = t->next;
        }
        p2.push_back(*t);
    }
    for (auto it = p2.end()-1; it != p2.begin(); it--)
    {
        it->DispNode(); cout << endl;
    }
    auto it2 = p2.begin();
    it2->DispNode(); cout << endl;
    cout << "总花费为:" << endl;
    cout << spend[ecn]<<"(RMB)" << endl;
    system("pause");
    system("cls");
}
void Lines::BestLine_t(string scn, string ecn)
{


    system("pause");
    system("cls");
}