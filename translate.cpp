#include<bits/stdc++.h>
#include"head.h"
using namespace std;
extern vector<Word> words;
//int flag = 0; //中途是否出错标志
extern vector<Quadruple> qua_list;
extern vector<Synbl> synbl;
struct Quadruple qua;
struct Synbl symbol;
int token_i = 0;
int qua_i = 0;
int offset = 0;
ofstream fout1;
ofstream fout2;

string int_to_str(int& k)
{
    string s;
    stringstream ss;
    ss<<k;
    return ss.str();
}

//四元式存到qua_list和文件
void out_qua()
{
    qua_list.push_back(qua);
    fout1<<"("<<qua.s[0]<<","<<qua.s[1]<<","<<qua.s[2]<<","<<qua.s[3]<<")"<<endl;
}
//符号表存到synbl和文件
void out_symbol()
{
    synbl.push_back(symbol);
    fout2<<symbol.name<<"\t"<<symbol.type<<"\t"<<symbol.cat<<"\t"<<symbol.addr<<endl;
}

int type()
{
    string s = words[token_i].value;
    if(s == "int" || s == "string" || s == "void" || s == "char" || s == "float") {
        token_i++;
        return 1;
    }
    else {
        return 0;
    }
}

int id()
{
    if(words[token_i].type == "I") {
        token_i++;
        return 1;
    }
    else {
        return 0;
    }
}

int para()
{

}

void fn_body()
{
    int token_i_tmp = token_i;
    if(evaluation()) {
        fn_body();
    }
    else
        token_i = token_i_tmp;
    token_i_tmp = token_i;
    if(rt()) {
        fn_body();
    }
    else
        token_i = token_i_tmp;
 }

int evaluation()
{
    if(type()) {
        if(id()) {
            if(words[token_i].value == "=") {
                token_i++;
                if(r_value()) {
                    if(words[token_i].value == ";") {
                        token_i++;
                        //四元式
                        qua.s[0] = "=";
                        qua.s[1] = words[token_i-2].value;
                        qua.s[2] = " ";
                        qua.s[3] = words[token_i-4].value;
                        out_qua();
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int rt()
{
    if(words[token_i].value == "return") {
        token_i++;
        if(factor()) {
            if(words[token_i].value == ";") {
                token_i++;
                return 1;
            }
        }
    }
    return 0;
}

int r_value()
{
    if(factor()){
        symbol.name = words[token_i-3].value;
        symbol.type = "identify";
        symbol.cat =  words[token_i-4].value;
        symbol.addr = "offset"+int_to_str(offset);
        offset += 4;
        out_symbol();
        return 1;
    }
    else {
        return 0;
    }
}

int factor()
{
    if(id()) {
        return 1;
    }
    else if(words[token_i].type == "c") {
        token_i++;
        return 1;
    }
    else {
        return 0;
    }
}

int fn()
{
    type();
    if(words[token_i].type == "I" || words[token_i].value == "main") {
        token_i++;
        if(words[token_i].value == "(") {
            token_i++;
            para();
            if(words[token_i].value == ")") {
                token_i++;
                if(words[token_i].value == "{") {
                    token_i++;
                    fn_body();
                    if(words[token_i].value == "}") {
                        token_i++;
                        //四元式
                        qua.s[0] = "end";
                        qua.s[1] = " ";
                        qua.s[2] = " ";
                        qua.s[3] = " ";
                        out_qua();
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int translate()
{
    fout1.open("quadruple.txt");
    fout2.open("symbol.txt");
    if(fn()) {
        fout1.close();
        fout2.close();
        return 1;
    }
    else {
        fout1.close();
        fout2.close();
        return 0;
    }
}
