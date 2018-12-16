#include<bits/stdc++.h>
#include"head.h"
using namespace std;
extern vector<Word> words;
extern vector<Quadruple> qua_list;
extern vector<Synbl> synbl;
extern struct Quadruple qua;
extern struct Synbl symbol;
extern int token_i;
extern int symbol_i;
extern int t_k;   //用来表示算数表达式tk中的k
extern string tk;

int arr()
{
    if(type()) {
        if(id()) {
            if(words[token_i].value == "[") {

                int flag = 0;
                for(int i = 0; i < synbl.size(); i++) {
                    if(words[token_i-1].value == synbl[i].name)
                        flag = 1;
                }
                if(flag == 1) {
                    cout<<"变量重定义"<<endl;
                    return 0;
                }

                symbol.name = words[token_i-1].value;

                token_i++;
                if(words[token_i].type == "c") {

                     //符号表
                    symbol.ar.elem_type = symbol.type;
                    symbol.type = "arr";
                    symbol.cat = "v";
                    int k = atoi(words[token_i].value.c_str());
                    symbol.ar.up = k;
                    if(symbol.ar.elem_type == "int")
                        symbol.ar.length = symbol.ar.up*8;
                    else if(symbol.ar.elem_type == "char")
                        symbol.ar.length = symbol.ar.up*2;
                    else if(symbol.ar.elem_type == "bool")
                        symbol.ar.length = symbol.ar.up*2;
                    else
                        return 0;
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
                        if(str == "int") {
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
                    out_symbol();
                    symbol_i++;
                    //完成符号表

                    token_i++;
                    if(words[token_i].value == "]") {
                        token_i++;
                        if(words[token_i].value == ";") {
                            token_i++;
                            return 1;
                        }
                    }
                }
            }

        }
    }
    else if(id()) {
        string s2 = words[token_i-1].value;
        if(words[token_i].value == "[") {

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

            token_i++;
            if(words[token_i].type == "c" || words[token_i].type == "I") {
                string s3 = words[token_i].value;
                token_i++;
                if(words[token_i].value == "]") {
                    token_i++;
                    if(words[token_i].value == "=") {
                        token_i++;
                        int tmp_i = token_i;
                        if(exp()) {
                            if(words[token_i].value == ";") {
                                qua.s[0] = "=";
                                qua.s[1] = "t"+int_to_str(t_k);
                                qua.s[2] = s2;
                                qua.s[3] = s3;
                                out_qua;
                                token_i++;
                                return 1;
                            }
                        }
                        else {
                            token_i = tmp_i;
                            if(words[token_i].type == "I" || words[token_i].type == "c") {
                                token_i++;
                                if(words[token_i].value == ";") {
                                    qua.s[0] = "=";
                                    qua.s[1] = words[token_i-1].value;
                                    qua.s[2] = s2;
                                    qua.s[3] = s3;
                                    out_qua();
                                    token_i++;
                                    return 1;
                                }
                            }
                        }
                    }
                }
            }

        }
    }
    return 0;
}

