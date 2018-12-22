#include<bits/stdc++.h>
#include"head.h"
using namespace std;

extern vector<Quadruple> qua_list;
extern struct Quadruple qua;
extern vector<Word> words;
extern int token_i;
extern int t_k;
extern string tk;
extern Synbl symbol;

int fn_if()
{
    if(words[token_i].value == "if") {
        token_i++;
        if(words[token_i].value == "(") {
            token_i++;
            if(exp()) {
                string s1 = "t"+int_to_str(t_k);
                string str = words[token_i].value;
                if(str == ">" || str == "<" || str == "==" || str == ">=" || str == "<=") {
                    string s0 = words[token_i].value;
                    token_i++;
                    if(words[token_i].type == "I" || words[token_i].type == "c") {
                        string s2 = words[token_i].value;
                        token_i++;
                        if(words[token_i].value == ")") {
                            token_i++;
                            if(words[token_i].value == "{") {
                                token_i++;
                                qua.s[0] = s0;
                                qua.s[1] = s1;
                                qua.s[2] = s2;
                                qua.s[3] = "t"+int_to_str(++t_k);
                                out_qua();
                                qua.s[0] = "if";
                                qua.s[1] = "t"+int_to_str(t_k);
                                qua.s[2] = "_";
                                qua.s[3] = "_";
                                out_qua();
                                fn_body();
                                if(words[token_i].value == "}") {
                                    token_i++;
                                    if(words[token_i].value == "else") {
                                        token_i++;
                                        if(words[token_i].value == "{") {
                                            token_i++;
                                            qua.s[0] = "el";
                                            qua.s[1] = "_";
                                            qua.s[2] = "_";
                                            qua.s[3] = "_";
                                            out_qua();
                                            fn_body();
                                            if(words[token_i].value == "}") {
                                                token_i++;
                                                qua.s[0] = "ie";
                                                qua.s[1] = "_";
                                                qua.s[2] = "_";
                                                qua.s[3] = "_";
                                                out_qua();
                                                return 1;
                                            }
                                        }
                                        else {
                                            return 0;  //else中出错
                                        }
                                    }
                                    else {
                                        qua.s[0] = "ie";
                                        qua.s[1] = "_";
                                        qua.s[2] = "_";
                                        qua.s[3] = "_";
                                        out_qua();
                                        return 1;  //扫完if且接下来没有else
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if(words[token_i].type == "I" || words[token_i].type == "c") {
                string s1 = words[token_i].value;
                token_i++;
                string str = words[token_i].value;
                if(str == ">" || str == "<" || str == "==" || str == ">=" || str == "<=") {
                    string s0 = words[token_i].value;
                    token_i++;
                    if(words[token_i].type == "I" || words[token_i].type == "c") {
                        string s2 = words[token_i].value;
                        token_i++;
                        if(words[token_i].value == ")") {
                            token_i++;
                            if(words[token_i].value == "{") {
                                token_i++;
                                qua.s[0] = s0;
                                qua.s[1] = s1;
                                qua.s[2] = s2;
                                qua.s[3] = "t"+int_to_str(++t_k);
                                out_qua();
                                qua.s[0] = "if";
                                qua.s[1] = "t"+int_to_str(t_k);
                                qua.s[2] = "_";
                                qua.s[3] = "_";
                                out_qua();
                                fn_body();
                                if(words[token_i].value == "}") {
                                    token_i++;
                                    if(words[token_i].value == "else") {
                                        token_i++;
                                        if(words[token_i].value == "{") {
                                            token_i++;
                                            qua.s[0] = "el";
                                            qua.s[1] = "_";
                                            qua.s[2] = "_";
                                            qua.s[3] = "_";
                                            out_qua();
                                            fn_body();
                                            if(words[token_i].value == "}") {
                                                token_i++;
                                                qua.s[0] = "ie";
                                                qua.s[1] = "_";
                                                qua.s[2] = "_";
                                                qua.s[3] = "_";
                                                out_qua();
                                                return 1;
                                            }
                                        }
                                        else {
                                            return 0;  //else中出错
                                        }
                                    }
                                    else {
                                        qua.s[0] = "ie";
                                        qua.s[1] = "_";
                                        qua.s[2] = "_";
                                        qua.s[3] = "_";
                                        out_qua();
                                        return 1;  //扫完if且接下来没有else
                                    }
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

void formal_para()
{
    if(first_formal_para()) {
        other_formal_para();
    }
}

int first_formal_para()
{
    int token_i_tmp = token_i;
    if(type()) {
        if(id()) {
            fill_symbol();
            return 1;
        }
    }
    token_i = token_i_tmp;
    return 0;
}
int other_formal_para()
{
    int token_i_tmp = token_i;
    if(words[token_i].value == ",") {
        token_i++;
        if(type()) {
            if(id()) {
                fill_symbol();
                if(other_formal_para())
                    return 1;
            }
            else {
                token_i = token_i_tmp;
                return 0;
            }
        }
        else {
            token_i = token_i_tmp;
            return 0;
        }
    }
    else {
        token_i = token_i_tmp;
        return 0;
    }
}

void actual_para()
{
    if(first_actual_para()) {
        other_actual_para();
    }
}

int first_actual_para()
{
    int token_i_tmp = token_i;
    if(id()) {
        if(un_def(words[token_i-1].value)) return 0;
        qua.s[0] = "param";
        qua.s[1] = words[token_i-1].value;
        qua.s[2] = "_";
        qua.s[3] = "_";
        out_qua();
        return 1;
    }
    token_i =  token_i_tmp;
    return 0;
}
int other_actual_para()
{
    int token_i_tmp = token_i;
    if(words[token_i].value == ",") {
        token_i++;
        if(id()) {
            if(un_def(words[token_i-1].value)) return 0;
            qua.s[0] = "param";
            qua.s[1] = words[token_i-1].value;
            qua.s[2] = "_";
            qua.s[3] = "_";
            out_qua();
            if(other_actual_para())
                return 1;
        }
        else {
            token_i = token_i_tmp;
            return 0;
        }
    }
    else {
        token_i = token_i_tmp;
        return 0;
    }
}

int type()
{
    string s = words[token_i].value;
    if(s == "int" || s == "char" || s == "float" || s == "bool" || s == "void") {
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

int rt()
{
    if(words[token_i].value == "return") {
        token_i++;
        if(words[token_i].type == "c" || words[token_i].type == "I") {
            qua.s[0] = "ret";
            qua.s[1] = words[token_i].value;
            qua.s[2] = "_";
            qua.s[3] = "_";
            out_qua();
            token_i++;
            if(words[token_i].value == ";") {
                token_i++;
                return 1;
            }
        }
    }
    return 0;
}
