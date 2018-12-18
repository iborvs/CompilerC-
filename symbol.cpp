#include<bits/stdc++.h>
#include"head.h"
using namespace std;
extern vector<Word> words;
//int flag = 0; //中途是否出错标志
extern vector<Quadruple> qua_list;
//extern vector<Synbl> synbl;
extern vector<vector<Synbl> > sbl;
extern vector<Arr> arrs;
extern struct Quadruple qua;
extern struct Synbl symbol;
extern int token_i;
int symbol_i[4] = {0};
extern int t_k;   //用来表示算数表达式tk中的k
extern string tk;
extern ofstream fout3;

//符号表存到synbl和文件
void out_symbol()
{
    if(symbol.type == "int") {
        sbl[0].push_back(symbol);
        fout3<<symbol.name<<"\t"<<symbol.type<<"\t"<<symbol.cat<<"\t"<<symbol.addr<<endl;
    }
    else if(symbol.type == "char") {
        sbl[1].push_back(symbol);
        fout3<<symbol.name<<"\t"<<symbol.type<<"\t"<<symbol.cat<<"\t"<<symbol.addr<<endl;
    }
    else if(symbol.type == "bool") {
        sbl[2].push_back(symbol);
        fout3<<symbol.name<<"\t"<<symbol.type<<"\t"<<symbol.cat<<"\t"<<symbol.addr<<endl;
    }
    else if(symbol.type == "float") {
        sbl[3].push_back(symbol);
        fout3<<symbol.name<<"\t"<<symbol.type<<"\t"<<symbol.cat<<"\t"<<symbol.addr<<endl;
    }
}

void fill_symbol()
{
    symbol.name = words[token_i-1].value;
    symbol.cat = "v";
    if(symbol.type == "int") {
        symbol.addr = sbl[0].size()*8;
        //symbol_i[0]++;
        out_symbol();
    }
    else if(symbol.type == "char") {
        symbol.addr = sbl[1].size()*2;
        //symbol_i[1]++;
        out_symbol();
    }
    else if(symbol.type == "bool") {
        symbol.addr = sbl[2].size()*2;
        //symbol_i[2]++;
        out_symbol();
    }
    else if(symbol.type == "float") {
        symbol.addr = sbl[3].size()*8;
        //symbol_i[3]++;
        out_symbol();
    }
}

int re_def(string name)
{
    int flag = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < sbl[i].size(); j++) {
            if(sbl[i][j].name == name) {
                flag = 1;
                break;
            }
        }
    }
    for(int i = 0; i < arrs.size(); i++) {
        if(arrs[i].name == name) {
            flag = 1;
            break;
        }
    }
    if(flag == 1) {
        cout<<"变量重定义"<<endl;
        return 1;
    }
    return 0;
}

int un_def(string name)
{
    int flag = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < sbl[i].size(); j++) {
            if(sbl[i][j].name == name) {
                flag = 1;
                break;
            }
        }
    }
    for(int i = 0; i < arrs.size(); i++) {
        if(arrs[i].name == name) {
            flag = 1;
            break;
        }
    }
    if(flag == 0) {
        cout<<"变量还未声明"<<endl;
        return 1;
    }
    return 0;
}
