#include "head.h"
#include <iostream>
#include <vector>
#include <string.h>

extern int t_k;   //用来表示算数表达式tk中的k
extern string tk;
extern vector<Quadruple> qua_list;
extern struct Quadruple qua;
extern vector<Word> words;
extern int token_i;

int syn0 = 0;
vector<string> A;
vector<string> SEM;

string s = "";
string ss = "";
string connect="";
void reset0()
{
while(!A.empty())
    {
        A.pop_back();
    }
}

void PU(string s)
{
    SEM.push_back(s);
}
void WE()
{
    qua.s[0] = "we";
    qua.s[1] = "_";
    qua.s[2] = "_";
    qua.s[3] = "_";
    out_qua();
}
void WH()
{
    qua.s[0] = "wh";
    qua.s[1] = "_";
    qua.s[2] = "_";
    qua.s[3] = "_";
    out_qua();
}
void DO()
{
    if(SEM.size()>=2)
    {
        tk = "t"+int_to_str(++t_k);
        qua.s[0] = s;
        qua.s[1] = SEM[SEM.size()-2];
        qua.s[2] = SEM.back();
        qua.s[3] = tk;
        out_qua();
        qua.s[0] = "do";
        qua.s[1] = tk;
        qua.s[2] = "_";
        qua.s[3] = "_";
        out_qua();
        SEM.pop_back();
        SEM.pop_back();
    }
    else if(SEM.size()==1)
    {
        qua.s[0] = "do";
        qua.s[1] = SEM[0];
        qua.s[2] = "_";
        qua.s[3] = "_";
        out_qua();
        SEM.pop_back();
    }
}
void GEQ(string ss)
{
    string b[2]={""};
    b[0] = SEM.back();
    SEM.pop_back();
    b[1] = SEM.back();
    SEM.pop_back();
    tk = "t"+int_to_str(++t_k);
    qua.s[0] = ss;
    qua.s[1] = b[1];
    qua.s[2] = b[0];
    qua.s[3] = tk;
    SEM.push_back(tk);
    out_qua();
}
int fun_while()
{

    if(A.back().compare("S")==0&&words[token_i].value.compare("while")==0)
    {
        //cout<<"S->W D F"<<endl;
        A.pop_back();
        A.push_back("WE");
        A.push_back("F");
        A.push_back("D");
        A.push_back("W");
        return 1;
    }
    else if(A.back().compare("F")==0&&words[token_i].value.compare("{")==0)
    {
        //cout<<"F->{f}"<<endl;
        A.pop_back();
        A.push_back("}");
        A.push_back("f");
        A.push_back("{");
        return 1;
    }
    else if(A.back().compare("F")==0&&words[token_i].value.compare("{")!=0)
    {
        //cout<<"F->f"<<endl;
        A.pop_back();
        A.push_back("f");
        return 1;
    }
    else if(A.back().compare("W")==0)
    {
        //cout<<"W->while"<<endl;
        A.pop_back();
        A.push_back("WH");
        A.push_back("while");
        return 1;
    }
    else if(A.back().compare("D")==0&&words[token_i].value.compare("(")==0)
    {
        //cout<<"D->(R)"<<endl;
        A.pop_back();
        A.push_back("DO");
        A.push_back(")");
        A.push_back("R");
        A.push_back("(");
        return 1;
    }
    else if(A.back().compare("R")==0)
    {
        //cout<<"R->I R'"<<endl;
        A.pop_back();
        A.push_back("R'");
        A.push_back("E");
        return 1;
    }
    else if(A.back().compare("R'")==0&&(words[token_i].value.compare(">")==0||words[token_i].value.compare("<")==0||words[token_i].value.compare("==")==0||words[token_i].value.compare(">=")==0||words[token_i].value.compare("<=")==0))
    {
        //cout<<"R'->w I"<<endl;
        A.pop_back();
        A.push_back("E");
        A.push_back(words[token_i].value);
        s = words[token_i].value;
        return 1;
    }
    else if(A.back().compare("R'")==0&&words[token_i].value.compare(">")!=0&&words[token_i].value.compare("<")!=0&&words[token_i].value.compare("==")!=0&&words[token_i].value.compare(">=")!=0&&words[token_i].value.compare("<=")!=0)
    {
        //cout<<"R'->"<<endl;
        A.pop_back();
        return 1;
    }
    else if(A.back().compare("E")==0)
    {
        //cout<<"E->T E'"<<endl;
        A.pop_back();
        A.push_back("E'");
        A.push_back("T");
        return 1;
    }
    else if(A.back().compare("E'")==0&&(words[token_i].value.compare("+")==0||words[token_i].value.compare("-")==0))
    {
        //cout<<"E'->w0 T E'"<<endl;
        connect = "GEQ"+words[token_i].value;
        A.pop_back();
        A.push_back("E'");
        A.push_back(connect);
        A.push_back("T");
        A.push_back(words[token_i].value);
        return 1;
    }
    else if(A.back().compare("E'")==0&&words[token_i].value.compare("+")!=0&&words[token_i].value.compare("-")!=0)
    {
        //cout<<"E'->e"<<endl;
        A.pop_back();
        return 1;
    }
    else if(A.back().compare("T")==0)
    {
        //cout<<"T->P T'"<<endl;
        A.pop_back();
        A.push_back("T'");
        A.push_back("P");
        return 1;
    }
    else if(A.back().compare("T'")==0&&(words[token_i].value.compare("*")==0||words[token_i].value.compare("/")==0))
    {
        //cout<<"T'->w1 P T'"<<endl;
        connect = "GEQ"+words[token_i].value;
        A.pop_back();
        A.push_back("T'");
        A.push_back(connect);
        A.push_back("P");
        A.push_back(words[token_i].value);
        return 1;
    }
     else if(A.back().compare("T'")==0&&words[token_i].value.compare("*")!=0&&words[token_i].value.compare("/")!=0)
    {
        //cout<<"T'->e"<<endl;
        A.pop_back();
        return 1;
    }
     else if(A.back().compare("P")==0&&(words[token_i].type.compare("I")==0||words[token_i].type.compare("c")==0))
    {
        //cout<<"P->I'"<<endl;
        A.pop_back();
        A.push_back("I");
        return 1;
    }
     else if(A.back().compare("P")==0&&words[token_i].value.compare("(")==0)
    {
        //cout<<"P->(E)'"<<endl;
        A.pop_back();
        A.push_back(")");
        A.push_back("E");
        A.push_back("(");
        return 1;
    }
    else if(A.back().compare("f")==0)
    {
        fn_body();
        A.pop_back();
        return 1;
    }
    else if(A.back().compare("WE")==0)
    {
        A.pop_back();
        WE();
        return 1;
    }
    else if(A.back().compare("WH")==0)
    {
        A.pop_back();
        WH();
        return 1;
    }
    else if(A.back().compare("DO")==0)
    {
        A.pop_back();
        DO();
        return 1;
    }
    else if(A.back().compare("GEQ+")==0||A.back().compare("GEQ-")==0||A.back().compare("GEQ*")==0||A.back().compare("GEQ/")==0)
    {

        if(A.back().compare("GEQ+")==0)
            GEQ("+");
        else if(A.back().compare("GEQ-")==0)
            GEQ("-");
        else if(A.back().compare("GEQ*")==0)
            GEQ("*");
        else if(A.back().compare("GEQ/")==0)
            GEQ("/");
        A.pop_back();
        return 1;
    }
    else if(A.back().compare("I")==0&&(words[token_i].type.compare("I")==0||words[token_i].type.compare("c")==0))
    {
        A.pop_back();
        PU(words[token_i].value);
        token_i++;
        return 1;
    }
    else if(A.back().compare("#")==0)
        {
            A.pop_back();
            return 2;
        }
    else{
        if(A.back().compare(words[token_i].value)==0)
        {
          if(A.back().compare(")")==0)
           {
               //cout<<" "<<"D->(R)"<<endl;
           }
           if(A.back().compare("}")==0)
           {
               //cout<<" "<<"F->{f}"<<endl;
           }
            A.pop_back();
            token_i++;
           return 1;
        }
        else
            return 0;
    }
return 1;
}

int fn_while()
{
    if(words[token_i].value.compare("while")!=0)
        return 0;
    else
    {
            A.push_back("#");
            A.push_back("S");
    }
    int a = 1;
    if(syn0==0)
    {
        reset0();
        A.push_back("#");
        A.push_back("S");
        syn0++;
    }

    while(a==1)
    {
        a = fun_while();
		/*
        for(int i=0;i<A.size();i++)
        {
            cout<<A[i];
        }
        cout<<"\t";
        for(int i=0;i<SEM.size();i++)
        {
            cout<<SEM[i];
        }
        cout<<endl;*/
    }
    if(a==2){
        //cout<<"RIGHT"<<endl;
		//token_i++;
		//cout<<token_i;
		return 1;
	}
    else if(a==0){
        cout<<"WRONG"<<endl;
		return 0;
	}
}
