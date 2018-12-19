#include<bits/stdc++.h>
#include"head.h"
using namespace std;
extern vector<Word> words;
//int flag = 0; //中途是否出错标志
extern vector<Quadruple> qua_list;
//extern vector<Synbl> synbl;
extern vector<vector<Synbl> > sbl;
extern vector<vector<Synbl> > vall;
extern vector<Arr> arrs;
extern vector<Arr> sub_arrs;
extern struct Quadruple qua;
extern struct Synbl symbol;
extern int token_i;
int symbol_i[4] = {0};
extern int t_k;   //用来表示算数表达式tk中的k
extern int if_subfun;
extern string tk;
extern ofstream fout3;
extern ofstream fout4;

//符号表存到synbl和文件
void out_symbol()
{
    if(symbol.type == "int") {
        if(if_subfun == 0) {
            sbl[0].push_back(symbol);
            fout3<<symbol.name<<"\t"<<symbol.type<<"\t"<<symbol.cat<<"\t"<<symbol.addr<<endl;
        }
        else {
            vall[0].push_back(symbol);
            fout4<<symbol.name<<"\t"<<symbol.type<<"\t"<<symbol.cat<<"\t"<<symbol.addr<<endl;
        }
    }
    else if(symbol.type == "char") {
        if(if_subfun == 0) {
            sbl[1].push_back(symbol);
            fout3<<symbol.name<<"\t"<<symbol.type<<"\t"<<symbol.cat<<"\t"<<symbol.addr<<endl;
        }
        else {
            vall[1].push_back(symbol);
            fout4<<symbol.name<<"\t"<<symbol.type<<"\t"<<symbol.cat<<"\t"<<symbol.addr<<endl;
        }
    }
    else if(symbol.type == "bool") {
        if(if_subfun == 0) {
            sbl[2].push_back(symbol);
            fout3<<symbol.name<<"\t"<<symbol.type<<"\t"<<symbol.cat<<"\t"<<symbol.addr<<endl;
        }
        else {
            vall[2].push_back(symbol);
            fout4<<symbol.name<<"\t"<<symbol.type<<"\t"<<symbol.cat<<"\t"<<symbol.addr<<endl;
        }
    }
    else if(symbol.type == "float") {
        if(if_subfun == 0) {
            sbl[3].push_back(symbol);
            fout3<<symbol.name<<"\t"<<symbol.type<<"\t"<<symbol.cat<<"\t"<<symbol.addr<<endl;
        }
        else {
            vall[3].push_back(symbol);
            fout4<<symbol.name<<"\t"<<symbol.type<<"\t"<<symbol.cat<<"\t"<<symbol.addr<<endl;
        }
    }
}

void fill_symbol()
{
    symbol.name = words[token_i-1].value;
    symbol.cat = "v";
    if(symbol.type == "int") {   //symbol.tyoe在type()函数中获得
        if(if_subfun == 0) {
            symbol.addr = sbl[0].size()*4;
        }
        else {
            symbol.addr = vall[0].size()*4;
        }
        out_symbol();
    }
    else if(symbol.type == "char") {
        if(if_subfun == 0) {
            symbol.addr = sbl[1].size()*2;
        }
        else {
            symbol.addr = vall[1].size()*2;
        }
        out_symbol();
    }
    else if(symbol.type == "bool") {
        if(if_subfun == 0) {
            symbol.addr = sbl[2].size()*2;
        }
        else {
            symbol.addr = vall[2].size()*2;
        }
        out_symbol();
    }
    else if(symbol.type == "float") {
        if(if_subfun == 0) {
            symbol.addr = sbl[3].size()*4;
        }
        else {
            symbol.addr = vall[3].size()*4;
        }
        out_symbol();
    }
}

int find_name(string name)
{
    if(if_subfun == 0) {
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
        return flag;
    }

    else  {
        int flag = 0;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < vall[i].size(); j++) {
                if(vall[i][j].name == name) {
                    flag = 1;
                    break;
                }
            }
        }
        for(int i = 0; i < sub_arrs.size(); i++) {
            if(sub_arrs[i].name == name) {
                flag = 1;
                break;
            }
        }
        return flag;
    }
}

int re_def(string name)
{
    if(find_name(name)) {
        cout<<"变量重定义"<<endl;
        return 1;
    }
    return 0;
}

int un_def(string name)
{
    if(!find_name(name)) {
        cout<<"变量未定义"<<endl;
        return 1;
    }
    return 0;
}
