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
int translate();
int fn();
int factor();
int r_value();
int rt();
int evaluation();
void fn_body();
int para();
int id();
int type();
void out_qua();
string int_to_str(int& k);

int exp();
int fn_while();
int fn_if();
int arr();

//符号表
void fill_symbol();
void out_symbol();
int un_def();
int re_def();
void file_symbol();

#endif // HEAD_H_INCLUDED
