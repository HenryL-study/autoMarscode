#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;
//请不要吐槽无注释  T T
string instrn[8][20] = {{"1","addu","subu","slt","sltu","sllv","srlv","srav","and","or","xor","nor","end"},
                        {"0","addiu","subiu","slti","sltiu","andi","ori","xori","end"},
                        {"1","beq","bne","end"},
                        {"0","sb","sh","sw","end"},
                        {"0","mthi","mtlo","end"},
                        {"1","mult","multu","div","divu","end"},
                        {"0","blez","bgtz","bltz","bgez","end"},
                        {"0","sll","sra","srl","end"}};

string instrf[6][20] = {{"addu","subu","slt","sltu","srl","sllv","srlv","srav","and","or","xor","nor","end"},
                        {"addiu","subiu","slti","sltiu","andi","ori","xori","end"},
                        {"lb","lbu","lh","lhu","lw","end"},
                        {"mfhi","mflo","end"},
                        {"lui","end"},
                        {"sll","sra","srl","end"}};

int label = 0;
int offset = 0;

int rdmnum(int width)
{
    return rand()%width;             //用rand产生随机数并设定范围
}

void Nowinstr(string instr, int tag, int type)
{
    ofstream code;
    int rdm1, rdm2, rdm3;
    rdm1 = rdmnum(6);
    rdm2 = rdmnum(6);              //产生0-6的随机数
    rdm3 = rdmnum(65536);
    code.open("code.txt",ios::app);
    switch(type)
    {
        case 2:    //btype-1
            {
                if(tag)
                {
                    code << instr << " $t0 $s" << rdm1 << " to" << label << "\n";
                    code << "nop\n";
                    code << "to" << label << ": addi $t7 $t7 1\nnop\n";
                    label++;
                }
                else
                {
                    code << instr << " $s" << rdm1 << " $t0 to" << label << "\n";
                    code << "nop\n";
                    code << "to" << label << ": addi $t7 $t7 1\nnop\n";
                    label++;
                }
                break;
            }
        case 6:    //btype-2
            {
                code << instr << " $t0  to" << label << "\n";
                code << "nop\n";
                code << "to" << label << ": addi $t7 $t7 1\nnop\n";
                label++;
                break;
            }
        case 0:    //r
            {
                if(tag)
                {
                    code << instr << " $t1 $s" << rdm1 << " $t0" << "\n";
                    code << "sw" << " $t1 " << offset << "($s7)\n";
                    offset+=4;
                }
                else
                {
                    code << instr << " $t1 $t0 $s" << rdm1 << "\n";
                    code << "sw" << " $t1 " << offset << "($s7)\n";
                    offset+=4;
                }
                break;
            }
        case 1:   //i
            {
                code << instr <<  " $t1 $t0 " << rdm3 << "\n";
                code << "sw" << " $t1 " << offset << "($s7)\n";
                offset+=4;
                break;
            }
        case 3:   //store
            {
                code << instr << " $t0 " << offset << "($s7)\n";
                offset+=4;
                break;
            }
        case 4:  //mt
            {
                code << instr << " $t0\n";
                break;
            }
        case 5:  //muldiv
            {
                if(tag)
                {
                    code << instr << " $t0 $s" << rdm1 << "\n";
                }
                else
                {
                    code << instr << " $s" << rdm2 << " $t0\n";
                }
                break;
            }
        case 7:
            {
                code << instr << " $t1 $t0 "<< rdm2 << "\n";
                code << "sw" << " $t1 " << offset << "($s7)\n";
                offset+=4;
                break;
            }
    }
    code.close();
}

void Forwardinstr(string instr, int type)
{
    ofstream code;
    int rdm1, rdm2, rdm3;
    rdm1 = rdmnum(6);
    rdm2 = rdmnum(6);                 //产生0-6的随机数
    rdm3 = rdmnum(65536);              //2^16
    code.open("code.txt",ios::app);
    switch(type)
    {
        case 0:    //r
            {
               code << instr << " $t0 $s" << rdm1 << " $s" << rdm2 << "\n";
               break;
            }
        case 1:    //i
            {
                code << instr << " $t0 $s" << rdm1 << " " << rdm3 << "\n";
                break;
            }
        case 3:    //mf
            {
                code << instr << " $t0" << "\n";
                break;
            }
        case 2:  //load
            {
                if(offset==0)
                    code << instr << " $t0 "<< offset <<"($s7)\n";
                else
                    code << instr << " $t0 "<< offset-4 <<"($s7)\n";
                break;
            }
        case 4:
            {
                code << instr << " $t0 " << rdm3 << "\n";
                break;
            }
        case 5:
            {
                code << instr << " $t0 $s" << rdm1 << " " << rdm2 << "\n";
                break;
            }
    }
    code.close();
}


int main()
{
    srand((unsigned)time(NULL));     //用于保证是随机数
    ofstream clearcode;
    clearcode.open("code.txt");
    clearcode << "#initial\n";
    clearcode << "addi $s0 $0 100\naddi $s1 $0 1234\naddi $s2 $0 134345\naddi $s3 $0 111111\nlui $s5 0xABCD\nlui $s6 0x1A24\n";
    clearcode << "#initial done\n";
    clearcode.close();
    int func;                             //  输入func码决定功能
    cout << "-------------------CODE AUTO MAKER------------------------------------------\n";
    cout << "|                Powered By Henry Liu                                      |\n";
    cout << "|                  From Padio Planet                                       |\n";
    cout << "|                                                    Version 0.1           |\n";
    cout << "|                                               Contact 583448542@qq.com   |\n";
    cout << "----------------------------------------------------------------------------\n";
    cout << "\n\nPlease read the README.txt first.";
    cout << "\n\nPlease input the function code: (0|1|2)";
    cin >> func;
    while(func<0||func>2)
    {
        cout << "function code is wrong. Please input 0|1|2\n";
        cin >> func;
    }
    switch(func)
    {
        case 0:
            {
                for(int i=0; i<6; i++)
                {
                    int indexi = 0;               //每一行中的列下标
                    while(instrf[i][indexi] != "end")
                    {
                        for(int j=0; j<8; j++)
                        {
                            int indexj = 1;
                            int tag;              //tag = 1 则rs,rt均冲突
                            if(instrn[j][0] == "0")
                                tag = 0;
                            else
                                tag = 1;
                            while(instrn[j][indexj] != "end")
                            {
                                while(tag >= 0)
                                {
                                    ofstream insertnop;
                                    Forwardinstr(instrf[i][indexi],i);
                                    Nowinstr(instrn[j][indexj],tag,j);
                                    insertnop.open("code.txt",ios::app);
                                    insertnop << "\n";
                                    insertnop.close();
                                    Forwardinstr(instrf[i][indexi],i);
                                    insertnop.open("code.txt",ios::app);
                                    insertnop << "nop\n";
                                    insertnop.close();
                                    Nowinstr(instrn[j][indexj],tag,j);
                                    insertnop.open("code.txt",ios::app);
                                    insertnop << "\n";
                                    insertnop.close();
                                    Forwardinstr(instrf[i][indexi],i);
                                    insertnop.open("code.txt",ios::app);
                                    insertnop << "nop\n";
                                    insertnop << "nop\n";
                                    insertnop.close();
                                    Nowinstr(instrn[j][indexj],tag,j);
                                    insertnop.open("code.txt",ios::app);
                                    insertnop << "\n";
                                    insertnop.close();
                                    tag--;
                                }
                                indexj++;
                            }
                            if(offset >= 100)
                            {
                                ofstream insertnop;
                                insertnop.open("code.txt",ios::app);
                                insertnop << "\n\n\n#-----------------------------------------华丽的分割线---------------------------------------------\n";
                                insertnop << "\n\n\n";
                                insertnop.close();
                                offset = 0;
                            }
                        }
                        indexi++;
                    }
                }
                break;
            }
        case 1:
            {
                for(int i=0; i<6; i++)
                {
                    int indexi = 0;               //每一行中的列下标
                    while(indexi != 2)
                    {
                        for(int j=0; j<8; j++)
                        {
                            int indexj = 1;
                            int tag;              //tag = 1 则rs,rt均冲突
                            if(instrn[j][0] == "0")
                                tag = 0;
                            else
                                tag = 1;
                            while(indexj != 2)
                            {
                                while(tag >= 0)
                                {
                                    ofstream insertnop;
                                    Forwardinstr(instrf[i][indexi],i);
                                    Nowinstr(instrn[j][indexj],tag,j);
                                    insertnop.open("code.txt",ios::app);
                                    insertnop << "\n";
                                    insertnop.close();
                                    Forwardinstr(instrf[i][indexi],i);
                                    insertnop.open("code.txt",ios::app);
                                    insertnop << "nop\n";
                                    insertnop.close();
                                    Nowinstr(instrn[j][indexj],tag,j);
                                    insertnop.open("code.txt",ios::app);
                                    insertnop << "\n";
                                    insertnop.close();
                                    Forwardinstr(instrf[i][indexi],i);
                                    insertnop.open("code.txt",ios::app);
                                    insertnop << "nop\n";
                                    insertnop << "nop\n";
                                    insertnop.close();
                                    Nowinstr(instrn[j][indexj],tag,j);
                                    insertnop.open("code.txt",ios::app);
                                    insertnop << "\n";
                                    insertnop.close();
                                    tag--;
                                }
                                indexj++;
                            }
                        }
                        indexi++;
                    }
                }
                break;
            }
        case 2:
            {
                int number;
                cout << "Please input the number of instruction pairs you needed: ";
                cin >> number;
                for(int i=0; i<number; i++)
                {
                    ofstream insertnop;
                    int fline, fcolumn, nline, ncolumn, nopnum, tag;
                    fline = rdmnum(6);
                    nline = rdmnum(8);
                    nopnum = rdmnum(3);
                    tag = rdmnum(2);
                    switch(fline)
                    {
                        case 0:
                        {
                            fcolumn = rdmnum(11);
                            break;
                        }
                        case 1:
                        {
                            fcolumn = rdmnum(7);
                            break;
                        }
                        case 2:
                        {
                            fcolumn = rdmnum(4);
                            break;
                        }
                        case 3:
                        {
                            fcolumn = rdmnum(2);
                            break;
                        }
                        case 4:
                        {
                            fcolumn = 0;
                            break;
                        }
                        case 5:
                        {
                            fcolumn = rdmnum(3);
                            break;
                        }
                    }
                    switch(nline)
                    {
                        case 0:
                        {
                            ncolumn = rdmnum(11)+1;
                            break;
                        }
                        case 1:
                        {
                            ncolumn = rdmnum(7)+1;
                            break;
                        }
                        case 2:
                        {
                            ncolumn = rdmnum(2)+1;
                            break;
                        }
                        case 3:
                        {
                            ncolumn = rdmnum(3)+1;
                            break;
                        }
                        case 4:
                        {
                            ncolumn = rdmnum(2)+1;
                            break;
                        }
                        case 5:
                        {
                            ncolumn = rdmnum(4)+1;
                            break;
                        }
                        case 6:
                        {
                            ncolumn = rdmnum(4)+1;
                            break;
                        }
                        case 7:
                        {
                            ncolumn = rdmnum(3)+1;
                            break;
                        }
                    }
                    Forwardinstr(instrf[fline][fcolumn],fline);
                    insertnop.open("code.txt",ios::app);
                    for(int j=0;j<nopnum;j++)
                    {
                        insertnop << "nop\n";
                    }
                    insertnop.close();
                    Nowinstr(instrn[nline][ncolumn],tag,nline);
                }
                break;
            }

    }

    cout << "\nThe generating is done, Please check your code.txt\n";
    return 0;
}
