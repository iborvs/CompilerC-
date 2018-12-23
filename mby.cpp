#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "head.h"
//装有四元式转汇编相关代码
using namespace std;
struct SYMBL
{
    string name;
    int L;
};
struct sY
{
    string s[4];
} sY;
struct QT
{
    SYMBL s[4];
};
bool ifDiv(string str);
int optimization();
int divBlock();
int qtOut();
bool ifConst(string str);
bool ifFunc(string str);
extern vector<Quadruple> optdQT;
extern vector<Quadruple> qua_list;
extern vector<vector<Synbl> > sbl;
extern vector<vector<Synbl> > vall;
extern vector<Arr> arrs;
vector<SYMBL>sba;  //伪符号表  //无活跃信息四元式
vector<QT>qtS;      //有活跃信息四元式
string rGroup[3]= {"","",""}; //寄存器组名称 假定三寄存器
int qtPos[2];  //用于存放在寄存器里的元素在四元式栈里的地址
vector<string>cmpCode; //存放汇编指令 没有分号
string cmpTmp="";//汇编代码缓存区 在下一行非标号集合时附在头部
int divCounts[7]= {0};//0为while 1为if 2 为关系符号
int typeSize[4]= {4,2,2,4}; //存放对应占用十六进制数位
vector<string>paras;  //存放参数
vector<vector<Synbl> >  *tabP;
vector<string>funcRe;
string funcName="main";
vector<int>types;
vector<string>indica;
vector<SYMBL>activeVs; //存储活跃的临时变量 存放名称和占用大小
bool buildCodes();
int iCmpFn(string str);
int getFreeR() //找空闲寄存器，多寄存器时使用
{
    int pos=-1,i=0;
    for(i=0; i<3; i++)
        if(rGroup[i]=="")
        {
            pos=i;
            break;
        }
    return pos;
}
string opToCmpil(string str)  //将运算符等转换为汇编语言的指令
{
    string cmpStr="unknown";
    if(str=="+")
        cmpStr="ADD";
    else if(str=="-")
        cmpStr="SUB";
    else if(str=="*")
        cmpStr="MUL";
    else if(str=="/")
        cmpStr="DIV";
    return cmpStr;
}
string addrToType(int i) //根据十六进制数位转换所需单元大小类型
{
    string str;
    switch(i)
    {
    case 8:
        str="DD";
        break;
    case 4:
        str="DW";
        break;
    case 2:
        str="DB";
        break;
    default:
        str="ERROR";
        break;
    }
    return str;
}
int nameToSize(string str) //根据名字寻找大小
{
    int strSize=0,i,j;
    if(ifConst(str))
        return 4;
    if(str[0]!='t')
        for(i=0; i<tabP->size(); i++)
        {
            for(j=0; j<(*tabP)[i].size(); j++)
            {
                if( (*tabP)[i][j].name==str)
                {
                    strSize=typeSize[i];
                    break;
                }
            }
        }
    if(str[0]=='t')
        for(i=0; i<activeVs.size(); i++)
        {
            if(activeVs[i].name==str)
            {
                strSize=activeVs[i].L;
                break;
            }
        }
    return strSize;
}
string nameToAddr(string str) //根据变量名称寻找其在数据段中的地址
{
    string addr="",vType="";
    stringstream stream1;
    int intAddr=-1,xNum; //xnum用于类型转换
    int i=0,j=0;
    if( (str[0]-'0')<=9 && (str[0]-'0')>=0) //检查是否为常数
        return str;
    for(i=0; i<tabP->size(); i++)
    {
        for(j=0; j<(*tabP)[i].size(); j++)
        {
            if( (*tabP)[i][j].name==str)
            {
                intAddr=(*tabP)[i][j].addr/2;
                vType=(*tabP)[i][j].type+"S";
                if(tabP==&vall)
                    vType="vall"+(*tabP)[i][j].type+"S";
                break;
            }
        }
    }
    if(intAddr>=0)
    {
        stream1<<intAddr;
        addr=stream1.str();
        addr="["+vType+"+"+addr+"]";
    }
    else
    {
        addr=str;
    }
    return addr;
}
string opRelation(QT qtEq)
{
    string tmpJMP;
    if(qtEq.s[0].name=="<")
        tmpJMP="JB";
    else if(qtEq.s[0].name==">")
        tmpJMP="JA";
    else if(qtEq.s[0].name=="<=")
        tmpJMP="JBE";
    else if(qtEq.s[0].name==">=")
        tmpJMP="JAE";
    else if(qtEq.s[0].name=="==")
        tmpJMP="JE";
    else if(qtEq.s[0].name=="!=")
        tmpJMP="JNE";
    else
        tmpJMP="ERROR";
    return tmpJMP;
}
int ifSybCodes(QT qtEq,int i) //判断大小的算符编成
{
    string tmpJMP,tmpStr;
    if(qtEq.s[0].name=="<")
        tmpJMP="LT";
    else if(qtEq.s[0].name==">")
        tmpJMP="GT";
    else if(qtEq.s[0].name=="<=")
        tmpJMP="LE";
    else if(qtEq.s[0].name==">=")
        tmpJMP="GE";
    else if(qtEq.s[0].name=="==")
        tmpJMP="EQ";
    else if(qtEq.s[0].name=="!=")
        tmpJMP="NE";
    else
        tmpJMP="ERROR";
    if(tmpJMP!="ERROR")
    {
        if(rGroup[0]!="")
        {
            iCmpFn("        MOV "+nameToAddr(rGroup[0])+",AX");
            rGroup[0]="";
        }
        tmpStr="        MOV AX,"+nameToAddr(qtEq.s[1].name) +" "+tmpJMP+" "+nameToAddr(qtEq.s[2].name);
        iCmpFn(tmpStr);
        rGroup[0]=qtEq.s[3].name;
        qtPos[0]=i;
        qtPos[1]=3;
    }
    return 0;
}
bool buildDSEG()  //建立数据段汇编代码 未完
{
    int tSize=0;
    int i=0;
    string aN[5]; //int转string临时变量
    stringstream stream1;
    string tmpStr="DSEG    SEGMENT"; //汇编语句输出临时变量
    cmpCode.push_back(tmpStr);

    for(i=0; i<sbl.size(); i++) //分配符号表中的空间
    {
        int len=sbl[i].size();
        int maxAddr;
        if(len)
        {
            maxAddr=sbl[i][len-1].addr+typeSize[i];
            maxAddr/=typeSize[i];
            stream1<<maxAddr;
            tmpStr="        "+sbl[i][0].type+"S "+addrToType(typeSize[i])+" "+stream1.str()+" DUP(0)";
            cmpCode.push_back(tmpStr);
        }
    }
    for(i=0; i<vall.size(); i++) //分配子函数符号表中的空间
    {
        int len=vall[i].size();
        int maxAddr;
        stream1.clear();
        stream1.str("");
        if(len)
        {
            maxAddr=vall[i][len-1].addr+typeSize[i];
            maxAddr/=typeSize[i];
            stream1<<maxAddr;
            tmpStr="        vall"+vall[i][0].type+"S "+addrToType(typeSize[i])+" "+stream1.str()+" DUP(0)";
            cmpCode.push_back(tmpStr);
        }
    }
    for(i=0; i<funcRe.size(); i++)
    {
        tmpStr="        "+funcRe[i]+" DW 0";
        cmpCode.push_back(tmpStr);
    }
    for(i=0; i<arrs.size(); i++)
    {
        tSize=arrs[i].length/arrs[i].up;
        stringstream stream2;
        stream2<<arrs[i].up;
        tmpStr="        "+arrs[i].name+" "+addrToType(tSize)+" "+stream2.str()+" DUP(0)";
        cmpCode.push_back(tmpStr);
    }
    for(i=0; i<activeVs.size(); i++) //分配活跃临时变量的空间
    {
        tmpStr="        "+activeVs[i].name+" "+addrToType(activeVs[i].L)+" 0";
        cmpCode.push_back(tmpStr);
    }
    tmpStr="        siz DW 2";
    cmpCode.push_back(tmpStr);
    tmpStr="DSEG    ENDS";
    cmpCode.push_back(tmpStr);
    return true;
}
bool buildCSEG()
{
    string tmpStr="CSEG    SEGMENT";
    cmpCode.push_back(tmpStr);
    tmpStr="        ASSUME  CS:CSEG,DS:DSEG";
    cmpCode.push_back(tmpStr);
    tmpStr="START: 	MOV AX,DSEG";
    cmpCode.push_back(tmpStr);
    tmpStr="        MOV DS,AX";
    cmpCode.push_back(tmpStr);
    tmpStr="        XOR AX,AX";
    cmpCode.push_back(tmpStr);
    buildCodes();
    tmpStr="CSEG    ENDS";
    cmpCode.push_back(tmpStr);
    tmpStr="        END START";
    cmpCode.push_back(tmpStr);
    return true;
}
string divCodes(QT qtEq)
{
    string tmpStr="";
    stringstream stream1;
    if(qtEq.s[0].name=="wh")
    {
        if(cmpTmp=="")
        {
            types.push_back(++divCounts[0]);
            stream1<<divCounts[0];
            cmpTmp="WH"+stream1.str()+":";
            indica.push_back("WH"+stream1.str());
        }
        else
            indica.push_back(cmpTmp.substr(0,cmpTmp.size()-2));
    }
    else if(qtEq.s[0].name=="do")
    {
        iCmpFn("        CMP AX,0");
        if(cmpTmp=="")
        {
            int tmpCnts=types.back();
            stream1<<tmpCnts;
            string tmpJmps="WHE"+stream1.str();
            iCmpFn("        JL  "+tmpJmps);
            indica.push_back(tmpJmps);
        }
        else
        {
            iCmpFn("        JL  "+cmpTmp.substr(0,cmpTmp.size()-2));
            indica.push_back(cmpTmp.substr(0,cmpTmp.size()-2));
        }
    }
    else if(qtEq.s[0].name=="we")
    {
        string tmpJmps=indica[indica.size()-1];
        tmpJmps.erase(remove(tmpJmps.begin(),tmpJmps.end(),'E'),tmpJmps.end());
        iCmpFn("        JMP "+tmpJmps);
        cmpTmp=indica.back()+":";
        types.pop_back();
        indica.pop_back();
        indica.pop_back();
    }
    else if(qtEq.s[0].name=="if")
    {
        iCmpFn("        CMP AX,0");
        if(cmpTmp=="")
        {
            //types.push_back(++divCounts[1]);
            stream1<<++divCounts[1];
            iCmpFn("        JL  IFE"+stream1.str());
            indica.push_back("IFE"+stream1.str());
        }
        else
        {
            iCmpFn("        JL  "+cmpTmp.substr(0,cmpTmp.size()-2));
            indica.push_back(stream1.str());
        }
    }
    else if(qtEq.s[0].name=="el")
    {
        string top;
        top=indica.back();
        indica.pop_back();
        stream1<<++divCounts[1];
        indica.push_back("IFE"+stream1.str());
        indica.push_back(top);
        iCmpFn("        JMP IFE"+stream1.str());
        cmpTmp=indica.back()+":";
        indica.pop_back();
    }
    else if(qtEq.s[0].name=="ie")
    {
        //int tmpCnts=types.back();
        //stream1<<tmpCnts;
        if(cmpTmp!="")
            iCmpFn("         ");
        cmpTmp=indica.back()+":";
        indica.pop_back();
    }
    else if(qtEq.s[0].name=="end" && qtEq.s[1].name=="main")
    {
        iCmpFn("        MOV AH,4CH");
        iCmpFn("        INT 21H");
    }
    else if(qtEq.s[0].name=="start" && qtEq.s[1].name!="main")
    {
        int paraI=0;
        tabP=&vall;
        funcName=qtEq.s[1].name;
        iCmpFn(qtEq.s[1].name+"FC    PROC");
        for(paraI=0; paraI<paras.size(); paraI++)
        {
            stream1.clear();
            stream1.str("");
            stream1<<paraI*2;
            iCmpFn("        MOV BX,"+paras[paraI]);
            iCmpFn("        MOV [vall"+vall[0][paraI].type+"S+"+stream1.str()+"],BX");
        }
        vector<string>().swap(paras);
    }
    else if(qtEq.s[0].name=="end" && qtEq.s[1].name!="main")
    {
        funcName="";
        iCmpFn("        RET");
        iCmpFn(qtEq.s[1].name+"FC    ENDP");
    }
    return tmpStr;
}
int iCmpFn(string str)  //将汇编语言入栈函数 部分汇编代码自动对齐
{
    if(cmpTmp.size()<=8)
        str=cmpTmp+str.substr(cmpTmp.size());
    else
        str=cmpTmp+str.substr(8);
    cmpCode.push_back(str);
    cmpTmp="";
    return 0;
}
bool buildCodes()
{
    int i=0,qtI=0,R=-1;
    string tmpStr; //存放临时汇编语句
    for(i=0; i<qtS.size(); i++)
    {
        if( opToCmpil(qtS[i].s[0].name)!="unknown" ) //操作符
        {
            if(rGroup[0]=="")
            {
                iCmpFn("        MOV AX,"+nameToAddr(qtS[i].s[1].name));
            }
            else if(rGroup[0]==qtS[i].s[1].name)
            {
                if(qtS[i].s[1].L+1)
                    iCmpFn("        MOV "+nameToAddr(qtS[i].s[1].name)+",AX");
            }
            else
            {
                if(qtS[qtPos[0]].s[qtPos[1]].L+1)  //利用实现存在qtpos里的元素位置定位
                    //iCmpFn("        ST AX,"+qtS[qtPos[0]].s[qtPos[1]].name);
                    iCmpFn("        MOV "+nameToAddr(qtS[qtPos[0]].s[qtPos[1]].name)+",AX");
                iCmpFn("        MOV AX,"+nameToAddr(qtS[i].s[1].name));
            }
            if(opToCmpil(qtS[i].s[0].name)!="MUL")
                iCmpFn("        "+opToCmpil(qtS[i].s[0].name)+" AX,"+nameToAddr(qtS[i].s[2].name));
            else
                iCmpFn("        "+opToCmpil(qtS[i].s[0].name)+" "+nameToAddr(qtS[i].s[2].name));
            rGroup[0]=qtS[i].s[3].name;
            qtPos[0]=i;
            qtPos[1]=3;
        }
        else  if(qtS[i].s[0].name=="=") //是赋值语句
        {
            if(rGroup[0]!="")
                if(rGroup[0]!=qtS[i].s[1].name)
                {
                    if(qtS[qtPos[0]].s[qtPos[1]].L+1)
                        iCmpFn("        MOV "+nameToAddr(qtS[qtPos[0]].s[qtPos[1]].name)+",AX");
                }
                else
                {
                    if(qtS[i].s[1].L+1)
                        iCmpFn("        MOV "+nameToAddr(qtS[qtPos[0]].s[qtPos[1]].name)+",AX");
                }
            int p=0,flag=0;
            string str=qtS[i].s[3].name;
            for(p=0; p<str.size(); p++) //检查是否为数组
                if(str[p]=='[')
                {
                    iCmpFn("        MOV AX,"+nameToAddr(str.substr(p+1)));
                    iCmpFn("        MUL siz");
                    iCmpFn("        MOV BX,AX");
                    flag=1;
                    break;
                }
            if(rGroup[0]!=qtS[i].s[1].name)
                iCmpFn("        MOV AX,"+nameToAddr(qtS[i].s[1].name));
            rGroup[0]=qtS[i].s[3].name;
            qtPos[0]=i;
            qtPos[1]=3;
            if(flag)
            {
                iCmpFn("        MOV ["+nameToAddr(str.substr(0,p))+"+BX],AX");
                rGroup[0]="";
            }
        }
        else if( ifDiv(qtS[i].s[0].name) ) //是否为可区分块的四元式
        {
            if(rGroup[0]!="")
            {
                if(qtS[qtPos[0]].s[qtPos[1]].L+1)
                    iCmpFn("        MOV "+nameToAddr(rGroup[0])+",AX");
                rGroup[0]="";
            }
            divCodes(qtS[i]);
        }
        else  if( opRelation(qtS[i])!="ERROR" ) //关系比较符 代码经过优化
        {
            if(rGroup[0]!="") //若寄存器里的数不为空
                if(rGroup[0]==qtS[i].s[1].name)
                {
                    if(qtS[i].s[1].L+1)
                        iCmpFn("        MOV "+nameToAddr(qtS[qtPos[0]].s[qtPos[1]].name)+",AX");
                }
                else if(qtS[qtPos[0]].s[qtPos[1]].L+1) //如果寄存器里的数活跃
                    iCmpFn("        MOV "+nameToAddr(qtS[qtPos[0]].s[qtPos[1]].name)+",AX");
            if(rGroup[0]!=qtS[i].s[1].name) //如果寄存器里的不是s1则更新寄存器
                iCmpFn("        MOV AX,"+nameToAddr(qtS[i].s[1].name));
            iCmpFn("        CMP AX,"+nameToAddr(qtS[i].s[2].name));
            stringstream stream1;
            stream1<<divCounts[2]++;
            iCmpFn("        "+opRelation(qtS[i])+" J"+stream1.str());
            iCmpFn("        NOT AX");
            cmpTmp="J"+stream1.str()+":";
            //iCmpFn("        MOV AX,1");
            rGroup[0]=qtS[i].s[3].name;
            qtPos[0]=i;
            qtPos[1]=3;
        }
        else if(qtS[i].s[0].name=="%")
        {
            if(rGroup[0]!="")
                if(qtS[qtPos[0]].s[qtPos[1]].L+1)  //利用实现存在qtpos里的元素位置定位
                    iCmpFn("        MOV "+nameToAddr(qtS[qtPos[0]].s[qtPos[1]].name)+",AX");
            iCmpFn("        MOV AX,"+nameToAddr(qtS[i].s[1].name));
            iCmpFn("        DIV "+nameToAddr(qtS[i].s[2].name));
            iCmpFn("        MOV AX,DX");
            iCmpFn("        XOR DX,DX");
            rGroup[0]=qtS[i].s[3].name;
            qtPos[0]=i;
            qtPos[1]=3;
            //ifSybCodes(qtS[i],i);
        }
        else
        {
            if(qtS[i].s[0].name=="ret")
            {
                if(!ifConst(qtS[i].s[1].name))
                {
                    if(rGroup[0]!="")
                    {
                        if(rGroup[0]!=qtS[i].s[1].name)
                        {
                            if(qtS[qtPos[0]].s[qtPos[1]].L+1)
                                iCmpFn("        MOV "+nameToAddr(rGroup[0])+",AX");
                            rGroup[0]="";
                            iCmpFn("        MOV AX,"+nameToAddr(rGroup[0]));
                        }
                    }
                    if(rGroup[0]=="")
                        iCmpFn("        MOV AX,"+nameToAddr(qtS[i].s[1].name));
                    iCmpFn("        MOV "+funcName+",AX");
                }
                else
                {
                    if(rGroup[0]!="")
                    {
                        if(rGroup[0]!=qtS[i].s[1].name)
                        {
                            if(qtS[qtPos[0]].s[qtPos[1]].L+1)
                                iCmpFn("        MOV "+nameToAddr(rGroup[0])+",AX");
                            rGroup[0]="";
                        }
                    }
                    iCmpFn("        MOV "+funcName+","+qtS[i].s[1].name);
                }
            }
            else if(qtS[i].s[0].name=="call")
            {
                iCmpFn("        CALL "+qtS[i].s[1].name+"FC");
            }
            else if(qtS[i].s[0].name=="param")
            {
                paras.push_back(nameToAddr(qtS[i].s[1].name));
            }
        }
    }
    return true;
}
int buildCpl() //四元式生成汇编指令 没有分号
{
    int i=0,qtI=0,R=-1;
    string tmpStr; //存放临时汇编语句
    buildDSEG();
    buildCSEG();
    return 0;
}
int findElem(string str)
{
    int order=-1,i=0;
    for(i=0; i<sba.size(); i++)
    {
        if(sba[i].name==str)
        {
            order=i;
            break;
        }
    }
    return order;
}
void initL()
{
    vector <SYMBL>().swap(sba);
    int i=0,j=0;
    for(i=0; i<optdQT.size(); i++)
        for(j=1; j<4; j++)
        {
            if(findElem(optdQT[i].s[j])<0 && optdQT[i].s[j]!="_")
            {
                SYMBL symE;
                symE.name=optdQT[i].s[j];
                if( optdQT[i].s[j][0]!='t')
                    symE.L=0;
                else
                    symE.L=-1;
                sba.push_back(symE);
            }
        }
}

void pushActive(int L,string str,int elsize)
{
    int i=0,flag=0;
    if(L+1)
        if(str[0]=='t')
        {
            for(i=0; i<activeVs.size(); i++)
                if(activeVs[i].name==str)
                {
                    flag=1;
                    break;
                }
            if(!flag)
            {
                SYMBL tmpT;
                tmpT.name=str;
                tmpT.L=elsize;
                activeVs.push_back(tmpT);
            }
        }
}
void qtScanL() //生成带有活跃信息的四元式表 并提交活跃临时变量
{
    tabP=&vall;
    int i=0,j=0,p=0,elemSize=0; //elemsize用于存储四元式单个元素的大小
    for(i=optdQT.size()-1; i>=0; i--)
    {
        QT qtElem;
        for(j=0; j<4; j++)
        {
            qtElem.s[j].name=optdQT[i].s[j];
        }
        if(!ifDiv(optdQT[i].s[0]))
        {
            for(p=1; p<4; p++)
                if(nameToSize(optdQT[i].s[p])!=0)
                {
                    elemSize=nameToSize(optdQT[i].s[p]);
                    break;
                }
            int order=0;

            if(optdQT[i].s[3]!="_")
            {
                order=findElem(optdQT[i].s[3]);
                qtElem.s[3].L=sba[order].L;
                sba[order].L=-1;
            }
            if(optdQT[i].s[2]!="_")
            {
                order=findElem(optdQT[i].s[2]);
                qtElem.s[2].L=sba[order].L;
                sba[order].L=i;
            }
            if(optdQT[i].s[1]!="_")
            {
                order=findElem(optdQT[i].s[1]);
                qtElem.s[1].L=sba[order].L;
                sba[order].L=i;
            }

            for(p=1; p<4; p++)
                pushActive(qtElem.s[p].L,qtElem.s[p].name,elemSize);
        }
        else
        {
            if(optdQT[i].s[0]=="start")
                funcRe.push_back(optdQT[i].s[1]);
            if(optdQT[i].s[0]=="end"&&optdQT[i].s[1]=="main")
                tabP=&sbl;
            initL();
        }
        qtS.push_back(qtElem);
    }
    reverse(qtS.begin(),qtS.end());
    tabP=&sbl;
}
int runCompil()
{
    ofstream out;
    out.open("compileCodes.ASM");
    tabP=&sbl;
    divBlock();
    initL();
    qtScanL();
    qtOut();
    buildCpl();
    int i=0;
    for(i=0; i<cmpCode.size(); i++)
    {
        out<<cmpCode[i]<<endl;
    }
    return 0;
}
