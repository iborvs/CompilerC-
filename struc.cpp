#include<bits/stdc++.h>
#include"head.h"
using namespace std;
extern vector<Word> words;
extern vector<Quadruple> qua_list;
extern vector<vector<Synbl> > sbl;
extern vector<vector<Synbl> > vall;
extern struct Quadruple qua;
extern struct Synbl symbol;
extern int token_i;
extern int t_k;   //用来表示算数表达式tk中的k
extern string tk;
extern ofstream fout7;
extern vector<string> struc_symbol;   //第一个值是结构体名字，第二个开始是结构体中变量名

 int stru()
 {
     if(words[token_i].value == "struct") {
        token_i++;
        if(id()) {
            if(words[token_i].value == "{") {
                token_i++;
                stru_v();
                if(words[token_i].value == "}") {
                    token_i++;
                    if(id()) {
                        struc_symbol.push_back(words[token_i-1].value);
                        fout7<<words[token_i-1].value<<endl;
                        if(words[token_i].value == ";") {
                            token_i++;
                            return 1;
                        }
                    }
                }
            }
        }
     }
     return 0;
 }
 int stru_v()
 {
     int token_i_tmp = token_i;
     if(type()) {
        if(id()) {
            struc_symbol.push_back(words[token_i-1].value);
            fout7<<words[token_i-1].value<<endl;
            if(words[token_i].value == ";") {
                token_i++;
                if(stru_v()) {
                    return 1;
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
     else {
        token_i = token_i_tmp;
        return 0;
     }
     return 0;
 }
