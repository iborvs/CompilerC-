#include<bits/stdc++.h>
#include"head.h"
using namespace std;

extern vector<Quadruple> qua_list;
extern struct Quadruple qua;
extern vector<Word> words;
extern int token_i;
extern int t_k;
extern string tk;

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
