#include<bits/stdc++.h>
#include"head.h"
using namespace std;
int runCompil();
vector<Word> words;  //token序列
vector<Quadruple> qua_list;  //四元式序列
//vector<Synbl> synbl; //符号表
vector<vector<Synbl> > sbl(4);  //
vector<Arr> arrs;    //数组表
vector<int> consl; //常数表；
vector<string> const_C; //常字符
vector<string> const_S; //常字符串
//int token_i = 0;
//int qua_i;

int main()
{
    lex();
    //for(int i = 0; i < words.size(); i++)
    //    cout<<words[i].type<<" "<<words[i].value<<endl;
    if(translate()) {
        cout<<"success"<<endl;
    }
    else
        cout<<"fail"<<endl;
    runCompil();
    //assembly();
}
