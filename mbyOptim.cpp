#include <iostream>
#include <vector>
#include <sstream>
#include "head.h"
using namespace std;
extern vector<Quadruple> qua_list;
struct DAGnode
{
    int n;
    string ope;
    string M;
    vector<string>A;
    DAGnode *sblngs[2]= {NULL,NULL};
};
//为了是犯错误操作
vector<DAGnode>DAG;
vector<Quadruple>optdQT; //优化后的四元式
bool ifExist(string str)
{
    int i=0,j=0;
    bool exist=false;
    for(i=0; i<DAG.size() && exist==false; i++)
    {
        if(DAG[i].M==str)
        {
            exist=true;
            break;
        }
        for(j=0; j<DAG[i].A.size(); j++)
        {
            if(DAG[i].A[j]==str)
            {
                exist=true;
                break;
            }
        }
    }
    return exist;
}
int findPos(string str)
{
    int i=0,pos=0;
    for(i=0; i<DAG.size() ; i++)
    {
        if(DAG[i].M==str)
        {
            pos=i;
            break;
        }
    }
    return pos;
}
int delA(string str)
{
    int i=0,j=0;
    for(i=0; i<DAG.size(); i++)
    {
        for(j=0; j<DAG[i].A.size(); j++)
        {
            if(DAG[i].A[j]==str)
            {
                DAG[i].A.erase(DAG[i].A.begin()+j);
                j--;
            }
        }
    }
    return 0;
}
bool ifConst(string str)
{
    bool result=false;
    if( (str[0]-'0')<10 && (str[0]-'0') >0)  //定义一个常数类型第一位必然是数字
        result=true;
    return result;
}
int optimization()
{
    int qtI=0;//读取四元式的位置 从头
    int i=0,j=0,pos=0; //循环临时变量
    bool exist=false;
    DAGnode tmpNode;
    while(qtI<qua_list.size())
    {
        exist=false;
        if(qua_list[qtI].s[0]=="=" && !ifConst(qua_list[qtI].s[1]) ) //A=B
        {
            exist=ifExist(qua_list[qtI].s[1]);
            if(!exist)
            {
                tmpNode.n=DAG.size()+1;
                tmpNode.ope="";
                tmpNode.M=qua_list[qtI].s[1];
            }
            exist=ifExist(qua_list[qtI].s[3]);
            if(exist)
                delA(qua_list[qtI].s[3]);
            tmpNode.A.push_back(qua_list[qtI].s[3]);
            DAG.push_back(tmpNode);
        }
        else if(ifConst(qua_list[qtI].s[1]))   //A=C1?C2 或 A=C1 即第二位为常数
        {
            if(ifConst(qua_list[qtI].s[2]))
            {
                float C,C1,C2;
                stringstream stream1;
                stream1<<qua_list[qtI].s[1]);
                stream1>>C1;
                stream1<<qua_list[qtI].s[1]);
                stream1>>C2;
                //计算C
            }
        }
    }
    return 0;
}
