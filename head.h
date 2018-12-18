#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include<bits/stdc++.h>
using namespace std;

//token序列中词法单元信息
struct Word
{
    string type;
    int code;
    string value;
};

//一个四元式序列中的4个值
struct Quadruple
{
    string s[4];
};

//符号表
struct Arr
{
    string name;
    string type;
    int addr;
    int up;
    int length;
};
struct Synbl
{
    string name;
    string type;
    string cat;
    int addr;
};
/*
struct Typel  //只扩充数组，结构体等不扩充，所以类型表没用
{
    string name;
    string typ;
    struct Arr arr;
};
*/
struct Pfinfl
{
    string name;
    int level;     //层次数
    int off;        //区距
    int para_num;  //参数个数
    int entry;
    struct Synbl para[10];
};
struct Vall
{
    int old_sp;    //sp
    int rt_addr;   //返回地址
    int para_num;  //形参个数
    vector<string> formal_para; //形参
};


//词法分析
void lex();
int ch_to_num(char ch);
int state_change(int state, char ch);
Word search(char token[]);
Word state_to_code(int state_before, char token[]);
void reset(char ch, char token[], FILE *fp, int &state, int &j);
void parse(Word word);


//语法分析
int translate();           //语法分析入口
int fn();                  //进入一个函数
int factor();              //赋值语句中右值的因式
int r_value();             //赋值语句右值
int rt();                  //返回语句
int evaluation();          //赋值语句
void fn_body();            //函数主体
void actual_para();        //实参
int first_actual_para();
int other_actual_para();
void formal_para();        //形参
int first_formal_para();
int other_formal_para();
int id();                  //判断该token是不是一个标识符
int type();                //判断此token是不是一个类型变量
void out_qua();            //四元式输出到文件和四元式序列vector
string int_to_str(int& k); //int转字符串

int exp();         //算数表达式
int fn_while();    //while函数
int fn_if();       //if函数
int l_arr();       //数组作为左值

//符号表
void fill_symbol();         //填符号表
void out_symbol();          //符号表输出到vector和文件
int un_def(string name);    //判断该变量是否未定义
int re_def(string name);    //判断该变量是否重定义

//函数
int fn_call();              //函数调用
int fun();                  //函数入口

#endif // HEAD_H_INCLUDED
