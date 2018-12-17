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
int symbol_i = 0;
ofstream fout1;
ofstream fout2;
int t_k = 0;   //用来表示算数表达式tk中的k
string tk;
//四元式存到qua_list和文件
string int_to_str(int& k) //输出tk
{
    string s;
    stringstream ss;
    ss<<k;
    return ss.str();
}

void out_qua()
{
    qua_list.push_back(qua);
    fout1<<"("<<qua.s[0]<<","<<qua.s[1]<<","<<qua.s[2]<<","<<qua.s[3]<<")"<<endl;
}
//符号表存到synbl和文件
void out_symbol()
{
    synbl.push_back(symbol);
    if(symbol.type != "arr")
        fout2<<symbol.name<<"\t"<<symbol.type<<"\t"<<symbol.cat<<"\t"<<symbol.addr<<endl;
    else
        fout2<<symbol.name<<"\t"<<symbol.type<<"\t"<<symbol.cat<<"\t"<<symbol.addr<<
            "\t"<<symbol.ar.elem_type<<"\t"<<"  "<<symbol.ar.up<<"\t"<<"    "<<symbol.ar.length<<endl;
}


int type()
{
    string s = words[token_i].value;
    if(s == "int" || s == "void" || s == "char" || s == "float" || s == "bool") {
        symbol.type = s;
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
    else {
        token_i = token_i_tmp;
    }
    token_i_tmp = token_i;
    if(rt()) {
        fn_body();
    }
    else {
        token_i = token_i_tmp;
    }
    token_i_tmp = token_i;
    if(fn_while()) {
        fn_body();
    }
    else {
        token_i = token_i_tmp;
    }
    token_i_tmp = token_i;
    if(fn_if()) {
        fn_body();
    }
    else {
        token_i = token_i_tmp;
    }
    token_i_tmp = token_i;
    if(arr()) {
        fn_body();
    }
    else {
        token_i = token_i_tmp;
    }
 }

int evaluation()
{
    if(type()) {
        if(id()) {
            if(words[token_i].value == "=") {

                //填符号表
                int flag = 0;
                for(int i = 0; i < synbl.size(); i++) {
                    if(words[token_i-1].value == synbl[i].name)
                        flag = 1;
                }
                if(flag == 1) {
                    cout<<"变量重定义"<<endl;
                    return 0;
                }
                symbol.ar.elem_type = "none";
                symbol.ar.up = 0;
                symbol.ar.length = 0;
                symbol.name = words[token_i-1].value;
                symbol.cat = "v";
                if(symbol_i == 0)
                    symbol.addr = "0";
                else {
                    string str = synbl[symbol_i-1].type;
                    int len;
                    if(str == "arr") {
                        len = synbl[symbol_i-1].ar.length;
                        int k = atoi(synbl[symbol_i-1].addr.c_str()) + len;
                        symbol.addr = int_to_str(k);
                    }
                    else if(str == "int") {
                        len = 8;
                        int k = atoi(synbl[symbol_i-1].addr.c_str()) + len;
                        symbol.addr = int_to_str(k);
                    }
                    else if(str == "char") {
                        len = 2;
                        int k = atoi(synbl[symbol_i-1].addr.c_str()) + len;
                        symbol.addr = int_to_str(k);
                    }
                    else if(str == "bool") {
                        len = 2;
                        int k = atoi(synbl[symbol_i-1].addr.c_str()) + len;
                        symbol.addr = int_to_str(k);
                    }
                    else if(str == "void") {
                        len = 4;
                        int k = atoi(synbl[symbol_i-1].addr.c_str()) + len;
                        symbol.addr = int_to_str(k);
                    }
                    else
                        return 0;
                }
                //填完符号表

                string tmp_value = words[token_i-1].value;  //用于定位需要四元式中需要输出的变量
                token_i++;
                if(r_value()) {
                    if(words[token_i].value == ";") {
                        token_i++;
                        //四元式
                        qua.s[0] = "=";
                        qua.s[3] = tmp_value;
                        qua.s[2] = "_";
                        out_qua();
                        //符号表
                        out_symbol();
                        symbol_i++;
                        return 1;
                    }
                }
                return 0;
            }
            else {
                if(words[token_i].value == ";") {

                    //填符号表
                    int flag = 0;
                    for(int i = 0; i < synbl.size(); i++) {
                        if(words[token_i-1].value == synbl[i].name)
                            flag = 1;
                    }
                    if(flag == 1) {
                        cout<<"变量重定义"<<endl;
                        return 0;
                    }
                    symbol.ar.elem_type = "none";
                    symbol.ar.up = 0;
                    symbol.ar.length = 0;
                    symbol.name = words[token_i-1].value;
                    symbol.cat = "v";
                    if(symbol_i == 0)
                        symbol.addr = "0";
                    else {
                        string str = synbl[symbol_i-1].type;
                        int len;
                        if(str == "arr") {
                            len = synbl[symbol_i-1].ar.length;
                            int k = atoi(synbl[symbol_i-1].addr.c_str()) + len;
                            symbol.addr = int_to_str(k);
                        }
                        else if(str == "int") {
                            len = 8;
                            int k = atoi(synbl[symbol_i-1].addr.c_str()) + len;
                            symbol.addr = int_to_str(k);
                        }
                        else if(str == "char") {
                            len = 2;
                            int k = atoi(synbl[symbol_i-1].addr.c_str()) + len;
                            symbol.addr = int_to_str(k);
                        }
                        else if(str == "bool") {
                            len = 2;
                            int k = atoi(synbl[symbol_i-1].addr.c_str()) + len;
                            symbol.addr = int_to_str(k);
                        }
                        else if(str == "void") {
                            len = 4;
                            int k = atoi(synbl[symbol_i-1].addr.c_str()) + len;
                            symbol.addr = int_to_str(k);
                        }
                        else
                            return 0;
                    }
                    //填完符号表

                    out_symbol();
                    symbol_i++;
                    token_i++;
                    return 1;
                }
            }
        }
        return 0;
    }
    else {
        if(id()) {
            if(words[token_i].value == "=") {

                //符号表中检查
                int flag = 0;
                for(int i = 0; i < synbl.size(); i++) {
                    if(words[token_i-1].value == synbl[i].name)
                        flag = 1;
                }
                if(flag == 0) {
                    cout<<"变量还未被声明"<<endl;
                    return 0;
                }
                //符号表中检查结束

                string tmp_value = words[token_i-1].value;  //用于定位需要四元式中需要输出的变量
                token_i++;
                if(r_value()) {
                    if(words[token_i].value == ";") {
                        token_i++;
                        //四元式
                        qua.s[0] = "=";
                        qua.s[3] = tmp_value;
                        qua.s[2] = "_";
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
        return 1;
    }
    else {
        return 0;
    }
}

int factor()
{
    if(exp()) {
        qua.s[1] = tk;
        return 1;
    }
    else if(id()) {
        qua.s[1] = words[token_i-1].value;
        return 1;
    }
    else if(words[token_i].type == "c") {
        qua.s[1] = words[token_i].value;
        token_i++;
        return 1;
    }
    else {
        return 0;
    }
}

int fn()
{
    if(type()) {
        if(words[token_i].type == "I" || words[token_i].value == "main") {
            qua.s[0] = "start";
            string fn_name = words[token_i].value;
            qua.s[1] = fn_name;
            qua.s[2] = "_";
            qua.s[3] = "_";
            out_qua();
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
                            qua.s[1] = fn_name;
                            qua.s[2] = "_";
                            qua.s[3] = "_";

                            out_qua();
                            return 1;
                        }
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
    fout2<<"变量名"<<"\t"<<"类型"<<"\t"<<"种类"<<"\t"<<"地址"<<
            "\t"<<"元素类型"<<"  "<<"数组上界"<<"  "<<"空间大小"<<endl;
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
