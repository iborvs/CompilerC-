#include<bits/stdc++.h>
#include"head.h"
using namespace std;
extern vector<Word> words;
extern vector<Quadruple> qua_list;
extern vector<vector<Synbl> > sbl;
extern vector<vector<Synbl> > vall;
extern vector<Arr> arrs;
extern vector<Arr> sub_arrs;
extern struct Quadruple qua;
extern struct Synbl symbol;
struct Arr ar;
extern int token_i;
extern int t_k;   //用来表示算数表达式tk中的k
extern string tk;
extern int if_subfun;
int arr_i = 0;
int sub_arr_i = 0;
extern ofstream fout5;
extern ofstream fout6;

int l_arr()
{
    //fout5.open("arr_table.txt");
    //fout5<<"名字"<<"\t"<<"类型"<<"\t"<<"地址"<<"\t"<<"上界"<<"\t"<<"长度"<<endl;
    //fout6.open("sub_arr_table.txt");
    //fout6<<"名字"<<"\t"<<"类型"<<"\t"<<"地址"<<"\t"<<"上界"<<"\t"<<"长度"<<endl;
    if(type()) {
        if(id()) {
            if(words[token_i].value == "[") {

                ar.name = words[token_i-1].value;
                ar.type = words[token_i-2].value;

                if(re_def(ar.name))
                    return 0;

                token_i++;
                if(words[token_i].type == "c") {

                     //符号表
                    int k = atoi(words[token_i].value.c_str());
                    ar.up = k;
                    if(ar.type == "int")
                        ar.length = ar.up*4;
                    else if(ar.type == "char")
                        ar.length = ar.up*2;
                    else if(ar.type == "bool")
                        ar.length = ar.up*2;
                    else
                        return 0;

                    if(if_subfun == 0) {
                        if(arr_i == 0)
                            ar.addr = 0;
                        else {
                            string str = arrs[arr_i-1].type;
                            if(str == "int") {
                                ar.addr = arrs[arr_i-1].addr + arrs[arr_i-1].length;
                            }
                            else if(str == "char") {
                                ar.addr = arrs[arr_i-1].addr + arrs[arr_i-1].length;
                            }
                            else if(str == "bool") {
                                ar.addr = arrs[arr_i-1].addr + arrs[arr_i-1].length;
                            }
                            else
                                return 0;
                        }
                        arrs.push_back(ar);
                        //cout<<ar.name<<"\t"<<ar.type<<"\t"<<ar.addr<<"\t"<<ar.up<<"\t"<<ar.length<<endl;
                        fout5<<ar.name<<"\t"<<ar.type<<"\t"<<ar.addr<<"\t"<<ar.up<<"\t"<<ar.length<<endl;
                        arr_i++;
                    }
                    else {
                        if(sub_arr_i == 0)
                            ar.addr = 0;
                        else {
                            string str = sub_arrs[arr_i-1].type;
                            if(str == "int") {
                                ar.addr = sub_arrs[arr_i-1].addr + sub_arrs[arr_i-1].length;
                            }
                            else if(str == "char") {
                                ar.addr = sub_arrs[arr_i-1].addr + sub_arrs[arr_i-1].length;
                            }
                            else if(str == "bool") {
                                ar.addr = sub_arrs[arr_i-1].addr + sub_arrs[arr_i-1].length;
                            }
                            else
                                return 0;
                        }
                        sub_arrs.push_back(ar);
                        //cout<<ar.name<<"\t"<<ar.type<<"\t"<<ar.addr<<"\t"<<ar.up<<"\t"<<ar.length<<endl;
                        fout6<<sub_arrs[sub_arr_i].name<<"\t"<<ar.type<<"\t"<<ar.addr<<"\t"<<ar.up<<"\t"<<ar.length<<endl;
                        sub_arr_i++;
                    }

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
        string s3 = words[token_i-1].value;
        if(words[token_i].value == "[") {

            if(un_def(words[token_i-1].value))
                return 0;

            token_i++;
            if(words[token_i].type == "c" || words[token_i].type == "I") {

                int flag = 0;

                //主函数数组表
                if(if_subfun == 0) {
                    for(int i = 0; i < arrs.size(); i++) {
                        if(arrs[i].name == words[token_i-2].value) {
                            int len = atoi(words[token_i].value.c_str());
                            if(words[token_i].type == "c" && len >= arrs[i].up) {
                                cout<<"数组访问越界"<<endl;
                                return 0;
                            }
                        }
                    }
                }
                //子函数数组表
                else {
                    for(int i = 0; i < sub_arrs.size(); i++) {
                        if(sub_arrs[i].name == words[token_i-2].value) {
                            int len = atoi(words[token_i].value.c_str());
                            if(words[token_i].type == "c" && len >= sub_arrs[i].up) {
                                cout<<"数组访问越界"<<endl;
                                return 0;
                            }
                        }
                    }
                }

                string s2 = words[token_i].value;
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
/*
int r_arr()  //数组作为右值
{
    if(id()) {
        if(un_def(words[token_i-1].value)) return 0;

        if(words[token_i].value == "[") {
            token_i++;
            if(words[token_i].type == "c" || words[token_i].type == "I") {
                token_i++;
                //检查是否越界
                if(words[token_i].type == "c") {
                    for(int i = 0; i < arrs.size(); i++) {
                        if(arrs[i].name == words[token_i-2].value) {
                            int len = atoi(words[token_i].value.c_str());
                            if(len >= arrs[i].up) {
                                cout<<"数组访问越界"<<endl;
                                return 0;
                            }
                        }
                    }
                }
                //检查完成
                if(words[token_i].value == "]")
                    return 1;
            }
        }
    }
    return 0;
}
*/
