#include<bits/stdc++.h>
#include"head.h"
using namespace std;
extern vector<Word> words;
extern vector<int> consl; //常数表；
extern vector<string> const_C; //常字符
extern vector<string> const_S; //常字符串

int count1 = 0, count2 = 0, count3 = 0, count4 = 0;
static char K[23][50] = {
    "int", "main", "void", "if", "else", "char",
    "double", "enum", "float", "struct", "for",
    "do", "while", "break", "continue", "goto",
    "switch", "case", "default", "return", "const",
    "string"
};
static char P[20][10] = {
    ">=", "<=", "==", "=", ">", "<", "+", "-", "*", "/",
    "{", "}", ".", ";", "(", ")", ",", "[", "]", "%"
};
vector<string> I;

int ch_to_num(char ch)
{
    if(ch == '\n' || ch == '\r' || ch == '\v' || ch == '\t' || ch == ' ') return 0;
    else if(isalpha(ch)) return 1;
    else if(isdigit(ch)) return 2;
    else if(ch == '>') return 3;
    else if(ch == '<') return 4;
    else if(ch == '=') return 5;
    else if(ch == '"') return 6;
    else if(ch == '\'') return 7;
    else if(ch == ':') return 8;
    else if(ch == ',') return 9;
    else if(ch == '.') return 10;
    else if(ch == '/') return 11;
    else if(ch == '?') return 12;
    else if(ch == '[') return 13;
    else if(ch == ']') return 14;
    else if(ch == '{') return 15;
    else if(ch == '}') return 16;
    else if(ch == '\\') return 17;
    else if(ch == '|') return 18;
    else if(ch == '!') return 19;
    else if(ch == '%') return 20;
    else if(ch == '^') return 21;
    else if(ch == '&') return 22;
    else if(ch == '*') return 23;
    else if(ch == '+') return 24;
    else if(ch == '-') return 25;
    else if(ch == ';') return 26;
    else if(ch == '(') return 27;
    else if(ch == ')') return 28;
}
int state_change(int state, char ch)
{
    int ch_code = ch_to_num(ch);
    if(state == 1) {
        if(ch_code == 0) return 1;
        else if(ch_code == 1) return 2;
        else if(ch_code == 2) return 3;
        else if(ch_code == 7) return 9;
        else if(ch_code == 6) return 11;
        else if(ch_code == 3) return 4;
        else if(ch_code == 4) return 5;
        else if(ch_code == 5) return 6;
        else if(ch_code == 9) return 25;
        else if(ch_code == 13) return 23;
        else if(ch_code == 14) return 24;
        else if(ch_code == 15) return 21;
        else if(ch_code == 16) return 22;
        else if(ch_code == 24) return 26;
        else if(ch_code == 25) return 27;
        else if(ch_code == 26) return 18;
        else if(ch_code == 27) return 19;
        else if(ch_code == 28) return 20;
        else if(ch_code == 10) return 30;
        else if(ch_code == 11) return 31;
        else if(ch_code == 12) return 32;
        else if(ch_code == 17) return 33;
        else if(ch_code == 18) return 34;
        else if(ch_code == 19) return 35;
        else if(ch_code == 20) return 36;
        else if(ch_code == 21) return 37;
        else if(ch_code == 22) return 38;
        else if(ch_code == 23) return 39;
        else return 0;
    }
    else if(state == 2) {
        if(ch_code == 1) return 2;
        else if(ch_code == 2) return 2;
        else return 0;
    }
    else if(state == 3) {
        if(ch_code == 2) return 3;
        else if(ch_code == 10) return 8;
        else return 0;
    }
    else if(state == 8) {
        if(ch_code == 2) return 7;
        else return 0;
    }
    else if(state == 7) {
        if(ch_code == 2) return 7;
        else return 0;
    }
    else if(state == 9) {
        if(ch_code == 1) return 10;
        else return 0;
    }
    else if(state == 10) {
        if(ch_code == 7) return 16;
        else return 0;
    }
    else if(state == 16) {
        return 0;
    }
    else if(state == 11) {
        if(ch_code == 1) return 12;
        else if(ch_code == 6) return 17;
        else return 0;
    }
    else if(state == 12) {
        if(ch_code == 1) return 12;
        else if(ch_code == 6) return 17;
        else return 0;
    }
    else if(state == 17) {
        return 0;
    }
    else if(state == 4) {
        if(ch_code == 5) return 13;
        else return 0;
    }
    else if(state == 13) {
        return 0;
    }
    else if(state == 5) {
        if(ch_code == 5) return 14;
        else return 0;
    }
    else if(state == 14) {
        return 0;
    }
    else if(state == 6) {
        if(ch_code == 5) return 15;
        else return 0;
    }
    else if(state == 15) {
        return 0;
    }
    else if(state == 18) {
        return 0;
    }
    else if(state == 19) {
        return 0;
    }
    else if(state == 20) {
        return 0;
    }
    else if(state == 21) {
        return 0;
    }
    else if(state == 22) {
        return 0;
    }
    else if(state == 23) {
        return 0;
    }
    else if(state == 24) {
        return 0;
    }
    else if(state == 25) {
        return 0;
    }
    else if(state == 26) {
        return 0;
    }
    else if(state == 27) {
        return 0;
    }
    else if(state == 28) {
        return 0;
    }
    else if(state == 30) {
        return 0;
    }
    else if(state == 31) {
        return 0;
    }
    else if(state == 32) {
        return 0;
    }
    else if(state == 33) {
        return 0;
    }
    else if(state == 34) {
        return 0;
    }
    else if(state == 35) {
        return 0;
    }
    else if(state == 36) {
        return 0;
    }
    else if(state == 37) {
        return 0;
    }
    else if(state == 38) {
        return 0;
    }
    else if(state == 39) {
        return 0;
    }
}

Word search(char token[])
{
    Word word;
    for(int i = 0; i < 22; i++) {
        if(strcmp(K[i], token) == 0) {
            word.type = "K";
            word.code = i + 1;
            word.value = K[i];
            return word;
        }
    }
    for(int i = 0; i < 20; i++) {
        if(strcmp(P[i], token) == 0) {
            word.type = "P";
            word.code = i + 1;
            word.value = P[i];
            return word;
        }
    }
    word.type = "none";
    word.code = 0;
    word.value = token;
    return word;
}
Word state_to_code(int state_before, char token[])
{
    Word word;
    //word.value = token;
    word = search(token);
    if(word.code != 0)
        return word;
    if(state_before == 2) {
        word.type = "I";
        int flag = 0;
        for(int i = 0; i < I.size(); i++) {
            if(I[i] == token) {
                word.code = i + 1;
                flag = 1;
                break;
            }
        }
        if(flag == 0) {
            I.push_back(token);
            word.code = I.size();
        }
        return word;
    }
    else if(state_before == 3 || state_before == 7) {
        word.type = "c";
        count4++;
        word.code = count4;
        int tmp = atoi(word.value.c_str()); //调用atio库函数转string为int
        vector<int>::iterator result = find(consl.begin(), consl.end(), tmp);
        if(result == consl.end()) {
            consl.push_back(tmp);
        }
        return word;
    }
    else if(state_before == 16) {
        word.type = "C";
        count2++;
        word.code = count2;
        vector<string>::iterator result = find(const_C.begin(), const_C.end(), word.value);
        if(result == const_C.end()) {
            const_C.push_back(word.value);
        }
        return word;
    }
    else if(state_before == 17) {
        word.type = "S";
        count3++;
        word.code = count3;
        vector<string>::iterator result = find(const_S.begin(), const_S.end(), word.value);
        if(result == const_S.end()) {
            const_S.push_back(word.value);
        }
        return word;
    }
    else {
        cout<<"error"<<endl;
        word.type = "error";
        word.code = 0;
        return word;
    }
}
void reset(char ch, char token[], FILE *fp, int &state, int &j)
{
    for(int i = 0; i < 20; i++)
        token[i] = '\0';
    if(ch != '\n' && ch != '\r' && ch != '\v' && ch != '\t' && ch != ' ')
        fseek(fp, -1, SEEK_CUR);
    state = 1;
    j = 0;
}
void parse(Word word)
{
    words.push_back(word);
}

void lex()
{
    FILE *fp;
    if((fp = fopen("fun.txt", "r")) == NULL) {
        cout<<"can't open the file";
        exit(0);
    }
    int state = 1, state_before;
    char token[20];
    for(int i = 0; i < 20; i++)
        token[i] = '\0';
    char ch;
    int i = 0, j = 0;
    while((ch = getc(fp)) != '#') {
        state_before = state;
        state = state_change(state, ch);
        if(state_before == 1 && state == 1)
            continue;
        if(state) token[j++] = ch;
        else {
            Word word;
            word = state_to_code(state_before, token);
            parse(word);
            //cout<<'{'<<words[i++].type<<','<<words[i].code<<','<<words[i].value<<'}'<<endl;
            reset(ch, token, fp, state, j);
        }
    }
    //for(int i = 0; i < words.size(); i++)
    //    cout<<'{'<<words[i].type<<','<<words[i].code<<','<<words[i].value<<'}'<<endl;
    //return words;
    fclose(fp);

    ofstream fout;
    fout.open("const.txt");
    fout<<"常数表:"<<endl;
    for(int i = 0; i < consl.size(); i++) {
        fout<<consl[i]<<"  ";
        if(i % 10 == 0 && i != 0)
            fout<<endl;
    }
    fout<<endl<<endl;
    fout<<"常字符表:"<<endl;
    for(int i = 0; i < const_C.size(); i++) {
        fout<<const_C[i]<<"  ";
        if(i % 10 == 0 && i != 0)
            fout<<endl;
    }
    fout<<endl<<endl;
    fout<<"常字符串表:"<<endl;
    for(int i = 0; i < const_S.size(); i++) {
        fout<<const_S[i]<<"  ";
        if(i % 10 == 0 && i != 0)
            fout<<endl;
    }
    fout<<endl<<endl;
    fout.close();
}
