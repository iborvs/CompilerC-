#include<bits/stdc++.h>
#include"head.h"
using namespace std;
extern vector<Word> words;
//int flag = 0; //中途是否出错标志
extern vector<Quadruple> qua_list;
struct Quadruple qua;
struct Synbl symbol;
int token_i = 0;
ofstream fout1;
ofstream fout2;
ofstream fout3;
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


int type()
{
    string s = words[token_i].value;
    if(s == "int" || s == "char" || s == "float" || s == "bool") {
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

                symbol.name = words[token_i-1].value;
                if(re_def())
                    return 0;
                fill_symbol();

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
                return 0;
            }
            else {
                if(words[token_i].value == ";") {

                    fill_symbol();

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

                symbol.name = words[token_i-1].value;
                if(un_def())
                    return 0;

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
    else if(words[token_i].type == "c" || words[token_i].type == "C" || words[token_i].type == "S") {
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
    fout3.open("symbol.txt");
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
