#pragma once
#include"Time.cpp"
#include<fstream>
using namespace std;
ifstream ifs_Train("Train.txt");
ofstream ofs_Train("Train.txt");
class Train
{
    Time start_time;
    Time arrive_time;
    string start_city;
    string arrive_city;



};