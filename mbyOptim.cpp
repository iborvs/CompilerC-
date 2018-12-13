#include <iostream>
#include <vector>
#include <sstream>
#include "head.h"
//四元式优化相关代码 入口是已生成的四元式序列:qua_list
//出口是同类型的optdQT
//没有其他方面可以借用的函数 可以不看
using namespace std;
extern vector<Quadruple> qua_list;
int qtOut();
int rebuildQT();
struct DAGnode
{
    int n;
    string ope="";
    string M="";
    vector<string>A;
    DAGnode *sblngs[2]= {NULL,NULL};
};
vector<DAGnode>DAG;
vector<Quadruple>optdQT; //优化后的四元式
int xyPos[2]= {-2,-2}; //用于存储ifExists后寻找的二元位置 第二位位-1则是在主元素上
float preCompute(float a,float b,string ope)
{
    float c=0;
    switch(ope[0])
    {
    case '+':
        c=a+b;
        break;
    case '-':
        c=a-b;
        break;
    case '*':
        c=a*b;
        break;
    case '/':
        c=a/b;
        break;
    default:
        c=-19999;
    }
    return c;
}
bool ifExist(string str)
{
    int i=0,j=0;
    bool exist=false;
    for(i=0; i<DAG.size() && exist==false; i++)
    {
        if(DAG[i].M==str)
        {
            exist=true;
            xyPos[0]=i;
            xyPos[1]=-1;
            break;
        }
        for(j=0; j<DAG[i].A.size(); j++)
        {
            if(DAG[i].A[j]==str)
            {
                exist=true;
                xyPos[0]=i;
                xyPos[1]=j;
                break;
            }
        }
    }
    return exist;
}
int findPos(string str) //寻找主元素的位置
{
    int i=0,pos=-1;
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
int findOpPos(string str) //寻找操作符的位置
{
    int i=0,pos=-1;
    for(i=0; i<DAG.size() ; i++)
    {
        if(DAG[i].ope==str)
        {
            pos=i;
            break;
        }
    }
    return pos;
}
int findBC(string str,DAGnode *sblngs)  //用于判断是否存在A=B?C时 对B和C的单独判断
{
    int i=0,pos=-2; //-1为主元素 0到以上是附加 -2为不存在
    if(sblngs->M==str)
        pos=-1;
    else
    {
        for(i=0; i<sblngs->A.size(); i++)
        {
            if(sblngs->A[i]==str)
            {
                pos=i;
                break;
            }
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
int buildNode(string str)
{
    DAGnode tmpNode;
    tmpNode.n=DAG.size()+1;
    tmpNode.ope="";
    tmpNode.M=str;
    DAG.push_back(tmpNode);
    return tmpNode.n-1;
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
        if(qua_list[qtI].s[0]=="=") //A=B 或 A=C1  规范见第八章优化ppt
        {
            exist=ifExist(qua_list[qtI].s[1]);
            if(!exist)  //不存在B则为B建立节点 然后将节点入栈
            {
                tmpNode.n=DAG.size()+1;
                tmpNode.ope="";
                tmpNode.M=qua_list[qtI].s[1];
                exist=ifExist(qua_list[qtI].s[3]);
                if(exist)
                    delA(qua_list[qtI].s[3]);
                tmpNode.A.push_back(qua_list[qtI].s[3]);
                DAG.push_back(tmpNode);
                tmpNode.A.clear();
            }
            else   //存在B则在B上附上A 待优化
            {
                int Bpos=findPos((qua_list[qtI].s[1]));
                exist=ifExist(qua_list[qtI].s[3]);
                if(exist)
                    delA(qua_list[qtI].s[3]);
                DAG[Bpos].A.push_back(qua_list[qtI].s[3]);
            }
        }
        else if(ifConst(qua_list[qtI].s[1]) && ifConst(qua_list[qtI].s[2]))   //A=C1?C2  即第二三位为常数
        {
            if(!ifExist(qua_list[qtI].s[1]))
                buildNode(qua_list[qtI].s[1]);
            if(!ifExist(qua_list[qtI].s[2]))
                buildNode(qua_list[qtI].s[2]);
            float C,C1,C2;
            stringstream stream1;
            stream1<<qua_list[qtI].s[1];
            stream1>>C1;
            stream1<<qua_list[qtI].s[1];
            stream1>>C2;
            //计算C
            C=preCompute(C1,C2,qua_list[qtI].s[0]);
            stream1<<C;
            delA(qua_list[qtI].s[3]);
            //cout<<stream1.str()<<endl;
            int tPos=findPos(stream1.str());
            if(tPos==-1)
            {
                tPos=buildNode(stream1.str()); //指向新节点的位置
            }
            DAG[tPos].A.push_back(qua_list[qtI].s[3]);
        }
        else if(qua_list[qtI].s[0].size()==1)  //暂定只有运算符是一位 只考虑二元
        {
            if(!ifExist(qua_list[qtI].s[1]))
                buildNode(qua_list[qtI].s[1]);
            if(!ifExist(qua_list[qtI].s[2]))
                buildNode(qua_list[qtI].s[2]);
            int tPos=findOpPos(qua_list[qtI].s[0]);
            delA(qua_list[qtI].s[3]); //先清空作为附加的所有A
            if(tPos!=-1)
            {
                int j=0;
                for(j=tPos; j<DAG.size(); j++)
                {
                    if( findBC(qua_list[qtI].s[1],DAG[j].sblngs[0])!=-2 && findBC(qua_list[qtI].s[2],DAG[j].sblngs[1]) ) //在操作符节点下自带分别为B和C
                    {
                        DAG[j].A.push_back(qua_list[qtI].s[0]); //把A附加上去
                        tPos=-2;
                        break;
                    }
                }
            }
            if(tPos!=-2)  //未完成A附加操作 即没有符合条件的式子
            {
                tmpNode.M=qua_list[qtI].s[3];
                tmpNode.ope=qua_list[qtI].s[0];
                tmpNode.n=DAG.size()+1;
                //B和C的位置
                if(ifExist(qua_list[qtI].s[1]))
                    tmpNode.sblngs[0]=&DAG[xyPos[0]];
                if(ifExist(qua_list[qtI].s[2]))
                    tmpNode.sblngs[1]=&DAG[xyPos[0]];
                DAG.push_back(tmpNode);
            }
        }
        qtI++;
    }
    rebuildQT();
    qua_list=optdQT;
    qtOut();
    return 0;
}
int qtOut()
{
    int i=0;
    for(i=0; i<qua_list.size(); i++)
    {
        cout<<"("<<qua_list[i].s[0]<<","<<qua_list[i].s[1]<<","<<qua_list[i].s[2]<<","<<qua_list[i].s[3]<<")"<<endl;;
    }
}
int rebuildQT()  //输出四元式到新栈
{
    int i=0,j=0;
    Quadruple tmpQT;
    for(i=0; i<DAG.size(); i++)
    {
        if(DAG[i].sblngs[0]!=NULL && DAG[i].sblngs[1]!=NULL)
        {
            tmpQT.s[0]=DAG[i].ope;
            tmpQT.s[1]=DAG[i].sblngs[0]->M;
            tmpQT.s[2]=DAG[i].sblngs[1]->M;
            tmpQT.s[3]=DAG[i].M;
            optdQT.push_back(tmpQT);
        }
        else if(DAG[i].sblngs[0]!=NULL)
        {
            tmpQT.s[0]=DAG[i].ope;
            tmpQT.s[1]=DAG[i].sblngs[0]->M;
            tmpQT.s[2]="_";
            tmpQT.s[3]=DAG[i].M;
            optdQT.push_back(tmpQT);
        }
        for(j=0; j<DAG[i].A.size(); j++)
        {
            tmpQT.s[0]="=";
            tmpQT.s[1]=DAG[i].M;
            tmpQT.s[2]="_";
            tmpQT.s[3]=DAG[i].A[j];
            optdQT.push_back(tmpQT);
        }
    }
    return 0;
}
