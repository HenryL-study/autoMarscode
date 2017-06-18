#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

ofstream clearcode;
//p5.2
//vector <string> R_type = {"addu","subu"};

vector <string> R_type = {"add","addu","sub","subu","and","or","xor", "bsw"};
vector <string> I_type = {"ori","addi","addiu"};
vector <string> Save = {"sw"};
vector <string> Load = {"lw"};
vector <string> Shift = {"sll","srl"};

//P6
/*
vector <string> R_type = {"addu","subu","sllv","srlv","srav","and","or","xor","nor","slt","sltu"};
vector <string> I_type = {"addiu","andi","ori","xori","slti","sltiu"};
vector <string> Save = {"sb","sh","sw"};
vector <string> Load = {"lb","lbu","lh","lhu","lw"};

vector <string> Shift = {"sll","sra","srl"};
*/
vector <string> Mul_Div = {"mult","multu","div","divu"};
vector <string> Mt = {"mthi","mtlo"};
vector <string> Mf = {"mfhi","mflo"};
//vector <string> B_type1 = {};
//vector <string> B_type2 = {};

int point = 0;

int rdmnum(int width)
{
    if(width == 1)
        return 0;
    else
        return rand()%width;             //用rand产生随机数并设定范围
}

/*
    1 sampling
    2 all
*/
void R_R_AND_R_S(int type)
{
    clearcode.open("P53_2017.txt", ios::app);
    if(type == 1)
    {
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t0 $s0 $s1" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t1 $s0 $t0" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t2 $s0 $t0" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t3 $s0 $t0" << endl;

        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t1 " << point << "($0)" << endl;
        point += 4;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t0 $s0 $s1" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t1 $t0 $s0" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t2 $t0 $s0" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t3 $t0 $s0" << endl;
        clearcode << "sw $t1 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;
    }
    else
    {
        for(unsigned int i = 0; i < R_type.size(); i++)
        {
            string instr_f = R_type.at(i);
            for(unsigned int j = 0; j < R_type.size(); j++)
            {
                string instr_n = R_type.at(j);
                clearcode << instr_f << " $t0 $s0 $s1" << endl;
                clearcode << instr_n << " $t1 $s0 $t0" << endl;
                clearcode << instr_n << " $t2 $s0 $t0" << endl;
                clearcode << instr_n << " $t3 $s0 $t0" << endl;
                clearcode << "sw $t3 " << point << "($0)" << endl;
                point += 4;
                clearcode << "sw $t2 " << point << "($0)" << endl;
                point += 4;
                clearcode << "sw $t1 " << point << "($0)" << endl;
                point += 4;
                clearcode << instr_f << " $t0 $s0 $s1" << endl;
                clearcode << instr_n << " $t1 $t0 $s0" << endl;
                clearcode << instr_n << " $t2 $t0 $s0" << endl;
                clearcode << instr_n << " $t3 $t0 $s0" << endl;
                clearcode << "sw $t1 " << point << "($0)" << endl;
                point += 4;
                clearcode << "sw $t3 " << point << "($0)" << endl;
                point += 4;
                clearcode << "sw $t2 " << point << "($0)" << endl;
                point += 4;
            }
        }
    }
    clearcode.close();

}

void R_I(int type)
{
    clearcode.open("P53_2017.txt", ios::app);
    if(type == 1)
    {
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t0 $s0 $s1" << endl;
        clearcode << I_type.at(rdmnum(I_type.size())) << " $t1 $t0 " << rdmnum(100) << endl;
        clearcode << I_type.at(rdmnum(I_type.size())) << " $t2 $t0 " << rdmnum(100) << endl;
        clearcode << I_type.at(rdmnum(I_type.size())) << " $t3 $t0 " << rdmnum(100) << endl;
        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t1 " << point << "($0)" << endl;
        point += 4;
    }
    else
    {
        for(unsigned int i = 0; i < R_type.size(); i++)
        {
            string instr_f = R_type.at(i);
            for(unsigned int j = 0; j < I_type.size(); j++)
            {
                string instr_n = I_type.at(j);
                clearcode << instr_f << " $t0 $s0 $s1" << endl;
                clearcode << instr_n << " $t1 $t0 " << rdmnum(100) << endl;
                clearcode << instr_n << " $t2 $t0 " << rdmnum(100) << endl;
                clearcode << instr_n << " $t3 $t0 " << rdmnum(100) << endl;
                clearcode << "sw $t3 " << point << "($0)" << endl;
                point += 4;
                clearcode << "sw $t2 " << point << "($0)" << endl;
                point += 4;
                clearcode << "sw $t1 " << point << "($0)" << endl;
                point += 4;
            }
        }
    }
    clearcode.close();
}

void R_Load_AND_I_Load_AND_Load_Save(int type)
{
    clearcode.open("P53_2017.txt", ios::app);
    if(type == 1)
    {
        clearcode << "addi $t0 $s1 100" << endl; //Insure $t0 now is not zero
        string instr_f = R_type.at(rdmnum(R_type.size()-3));
        /*
        if(instr_f == "subu")
            clearcode << instr_f << " $t0 $0 $s0" << endl;
        else
            clearcode << instr_f << " $t0 $0 $0" << endl;
        */
        clearcode << instr_f << " $t0 $0 $0" << endl;
        clearcode << Load.at(rdmnum(Load.size())) << " $t1 0($t0)" << endl;
        clearcode << Load.at(rdmnum(Load.size())) << " $t2 4($t0)" << endl;
        clearcode << Load.at(rdmnum(Load.size())) << " $t3 8($t0)" << endl;
        clearcode << Save.at(rdmnum(Save.size())) << " $t3 " << point << "($0)" << endl;
        point += 4;
        clearcode << Save.at(rdmnum(Save.size())) << " $t2 " << point << "($0)" << endl;
        point += 4;
        clearcode << Save.at(rdmnum(Save.size())) << " $t1 " << point << "($0)" << endl;
        point += 4;
        clearcode << "addi $t0 $s1 100" << endl; //Insure $t0 now is not zero
        instr_f = I_type.at(rdmnum(I_type.size()));
        clearcode << instr_f << " $t0 $0 0" << endl;
        clearcode << Load.at(rdmnum(Load.size())) << " $t1 0($t0)" << endl;
        clearcode << Load.at(rdmnum(Load.size())) << " $t2 4($t0)" << endl;
        clearcode << Load.at(rdmnum(Load.size())) << " $t3 8($t0)" << endl;
        clearcode << Save.at(rdmnum(Save.size())) << " $t3 " << point << "($0)" << endl;
        point += 4;
        clearcode << Save.at(rdmnum(Save.size())) << " $t2 " << point << "($0)" << endl;
        point += 4;
        clearcode << Save.at(rdmnum(Save.size())) << " $t1 " << point << "($0)" << endl;
        point += 4;
    }
    else
    {
        //clearcode << "#NOT IMPLENTED!!!" << endl;
        for(unsigned int i = 0; i < R_type.size(); i++)
        {
            string instr_R = R_type.at(i);
            for(unsigned int j = 0; j < Load.size(); j++)
            {
                string instr_L = Load.at(j);
                for(unsigned int k = 0; k < Save.size(); k++)
                {
                    string instr_S = Save.at(k);
                    clearcode << "addi $t0 $s1 100" << endl; //Insure $t0 now is not zero
                    clearcode << instr_R << " $t0 $0 $0" << endl;
                    clearcode << instr_L << " $t1 0($t0)" << endl;
                    clearcode << instr_L << " $t2 4($t0)" << endl;
                    clearcode << instr_L << " $t3 8($t0)" << endl;
                    clearcode << instr_S << " $t3 " << point << "($0)" << endl;
                    point += 4;
                    clearcode << instr_S << " $t2 " << point << "($0)" << endl;
                    point += 4;
                    clearcode << instr_S << " $t1 " << point << "($0)" << endl;
                    point += 4;
                }
            }
        }
        for(unsigned int i = 0; i < I_type.size(); i++)
        {
            string instr_I = I_type.at(i);
            for(unsigned int j = 0; j < Load.size(); j++)
            {
                string instr_L = Load.at(j);
                for(unsigned int k = 0; k < Save.size(); k++)
                {
                    string instr_S = Save.at(k);
                    clearcode << "addi $t0 $s1 100" << endl; //Insure $t0 now is not zero
                    clearcode << instr_I << " $t0 $0 0" << endl;
                    clearcode << instr_L << " $t1 0($t0)" << endl;
                    clearcode << instr_L << " $t2 4($t0)" << endl;
                    clearcode << instr_L << " $t3 8($t0)" << endl;
                    clearcode << instr_S << " $t2 " << point << "($0)" << endl;
                    point += 4;
                    clearcode << instr_S << " $t1 " << point << "($0)" << endl;
                    point += 4;
                    clearcode << instr_S << " $t3 " << point << "($0)" << endl;
                    point += 4;
                }
            }
        }

    }
    clearcode.close();
}

void I_R(int type)
{
    clearcode.open("P53_2017.txt", ios::app);
    if(type == 1)
    {
        string instr_f = I_type.at(rdmnum(I_type.size()));
        clearcode << instr_f << " $t0 $s1 " << rdmnum(1000) << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t1 $s0 $t0" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t2 $s0 $t0" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t3 $s0 $t0" << endl;
        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t1 " << point << "($0)" << endl;
        point += 4;

        clearcode << instr_f << " $t0 $s1 " << rdmnum(1000) << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t1 $t0 $s0" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t2 $t0 $s0" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t3 $t0 $s0" << endl;
        clearcode << "sw $t1 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;
    }
    else
    {
        for(unsigned int i = 0; i < I_type.size(); i++)
        {
            string instr_f = I_type.at(i);
            for(unsigned int j = 0; j < R_type.size(); j++)
            {
                string instr_n = R_type.at(j);
                clearcode << instr_f << " $t0 $s1 " << rdmnum(1000);
                clearcode << instr_n << " $t1 $s0 $t0" << endl;
                clearcode << instr_n << " $t2 $s0 $t0" << endl;
                clearcode << instr_n << " $t3 $s0 $t0" << endl;
                clearcode << "sw $t3 " << point << "($0)" << endl;
                point += 4;
                clearcode << "sw $t2 " << point << "($0)" << endl;
                point += 4;
                clearcode << "sw $t1 " << point << "($0)" << endl;
                point += 4;

                clearcode << instr_f << " $t0 $s1 " << rdmnum(1000);
                clearcode << instr_n << " $t1 $t0 $s0" << endl;
                clearcode << instr_n << " $t2 $t0 $s0" << endl;
                clearcode << instr_n << " $t3 $t0 $s0" << endl;
                clearcode << "sw $t1 " << point << "($0)" << endl;
                point += 4;
                clearcode << "sw $t3 " << point << "($0)" << endl;
                point += 4;
                clearcode << "sw $t2 " << point << "($0)" << endl;
                point += 4;
            }
        }
    }
    clearcode.close();
}

void I_I(int type)
{
    clearcode.open("P53_2017.txt", ios::app);
    if(type == 1)
    {
        string instr_f = I_type.at(rdmnum(I_type.size()));
        clearcode << instr_f << " $t0 $s1 " << rdmnum(10) << endl;
        clearcode << I_type.at(rdmnum(I_type.size())) << " $t1 $t0 " << rdmnum(10) << endl;
        clearcode << I_type.at(rdmnum(I_type.size())) << " $t2 $t0 " << rdmnum(10) << endl;
        clearcode << I_type.at(rdmnum(I_type.size())) << " $t3 $t0 " << rdmnum(10) << endl;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t1 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;
    }
    else
    {
        for(unsigned int i = 0; i < I_type.size(); i++)
        {
            string instr_f = I_type.at(i);
            for(unsigned int j = 0; j < I_type.size(); j++)
            {
                string instr_n = I_type.at(j);
                clearcode << instr_f << " $t0 $s1 " << rdmnum(10) << endl;
                clearcode << instr_n << " $t1 $s1 " << rdmnum(10) << endl;
                clearcode << instr_n << " $t2 $s1 " << rdmnum(10) << endl;
                clearcode << instr_n << " $t3 $s1 " << rdmnum(10) << endl;
                clearcode << "sw $t2 " << point << "($0)" << endl;
                point += 4;
                clearcode << "sw $t1 " << point << "($0)" << endl;
                point += 4;
                clearcode << "sw $t3 " << point << "($0)" << endl;
                point += 4;
            }
        }
    }
    clearcode.close();
}

void I_S(int type)
{
    // included in I_I & R_I
    clearcode.open("P53_2017.txt", ios::app);
    if(type == 1)
    {

    }
    else
    {

    }
    clearcode.close();
}

void L_R(int type)
{
    clearcode.open("P53_2017.txt", ios::app);
    if(type == 1)
    {
        string instr_f = Load.at(rdmnum(Load.size()));
        clearcode << instr_f << " $t0 " << rdmnum(point/4)*4 << "($0)" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t1 $s0 $t0" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t2 $s0 $t0" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t3 $s0 $t0" << endl;
        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t1 " << point << "($0)" << endl;
        point += 4;

        clearcode << instr_f << " $t0 " << rdmnum(point/4)*4 << "($0)" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t1 $t0 $s0" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t2 $t0 $s0" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t3 $t0 $s0" << endl;
        clearcode << "sw $t1 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;

    }
    else
    {
        //not implement.
    }
    clearcode.close();
}

void L_I(int type)
{
    clearcode.open("P53_2017.txt", ios::app);
    if(type == 1)
    {
        string instr_f = Load.at(rdmnum(Load.size()));
        clearcode << instr_f << " $t0 " << rdmnum(point/4)*4 << "($0)" << endl;
        clearcode << I_type.at(rdmnum(I_type.size())) << " $t1 $t0 100" << endl;
        clearcode << I_type.at(rdmnum(I_type.size())) << " $t2 $t0 100" << endl;
        clearcode << I_type.at(rdmnum(I_type.size())) << " $t3 $t0 100" << endl;
        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t1 " << point << "($0)" << endl;
        point += 4;

    }
    else
    {
        //not implement.
    }
    clearcode.close();
}

void L_L(int type)
{
    clearcode.open("P53_2017.txt", ios::app);
    clearcode << "addi $t0 $0 4" << endl;
    clearcode << "sw $t0 " << point << "($0)" << endl;
    if(type == 1)
    {
        string instr_f = Load.at(rdmnum(Load.size()));
        clearcode << instr_f << " $t0 " << point << "($0)" << endl;
        clearcode << Load.at(rdmnum(Load.size())) << " $t1 0($t0)" << endl;
        clearcode << Load.at(rdmnum(Load.size())) << " $t2 4($t0)" << endl;
        clearcode << Load.at(rdmnum(Load.size())) << " $t3 8($t0)" << endl;
        clearcode << Save.at(rdmnum(Save.size())) << " $t3 " << point << "($0)" << endl;
        point += 4;
        clearcode << Save.at(rdmnum(Save.size())) << " $t2 " << point << "($0)" << endl;
        point += 4;
        clearcode << Save.at(rdmnum(Save.size())) << " $t1 " << point << "($0)" << endl;
        point += 4;

    }
    else
    {
        //not implement.
    }
    clearcode.close();
}

void R_Shift(int type)
{
    clearcode.open("P53_2017.txt", ios::app);
    if(type == 1)
    {
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t0 $s0 $s1" << endl;
        clearcode << Shift.at(rdmnum(Shift.size())) << " $t1 $t0 " << rdmnum(4) << endl;
        clearcode << Shift.at(rdmnum(Shift.size())) << " $t2 $t0 " << rdmnum(4) << endl;
        clearcode << Shift.at(rdmnum(Shift.size())) << " $t3 $t0 " << rdmnum(4) << endl;
        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t1 " << point << "($0)" << endl;
        point += 4;
    }
    else
    {
        for(unsigned int i = 0; i < R_type.size(); i++)
        {
            string instr_f = R_type.at(i);
            for(unsigned int j = 0; j < Shift.size(); j++)
            {
                string instr_n = Shift.at(j);
                clearcode << instr_f << " $t0 $s0 $s1" << endl;
                clearcode << instr_n << " $t1 $t0 3" << endl;
                clearcode << instr_n << " $t2 $t0 3" << endl;
                clearcode << instr_n << " $t3 $t0 3" << endl;
                clearcode << "sw $t3 " << point << "($0)" << endl;
                point += 4;
                clearcode << "sw $t2 " << point << "($0)" << endl;
                point += 4;
                clearcode << "sw $t1 " << point << "($0)" << endl;
                point += 4;
            }
        }
    }
    clearcode.close();
}

void I_Shift(int type)
{
    clearcode.open("P53_2017.txt", ios::app);
    if(type == 1)
    {
        string instr_f = I_type.at(rdmnum(I_type.size()));
        clearcode << instr_f << " $t0 $s1 " << rdmnum(10) << endl;
        clearcode << Shift.at(rdmnum(Shift.size())) << " $t1 $s1 " << rdmnum(4) << endl;
        clearcode << Shift.at(rdmnum(Shift.size())) << " $t2 $s1 " << rdmnum(4) << endl;
        clearcode << Shift.at(rdmnum(Shift.size())) << " $t3 $s1 " << rdmnum(4) << endl;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t1 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;
    }
    else
    {
        for(unsigned int i = 0; i < I_type.size(); i++)
        {
            string instr_f = I_type.at(i);
            for(unsigned int j = 0; j < Shift.size(); j++)
            {
                string instr_n = Shift.at(j);
                clearcode << instr_f << " $t0 $s1 " << rdmnum(10) << endl;
                clearcode << Shift.at(rdmnum(Shift.size())) << " $t1 $s1 " << rdmnum(4) << endl;
                clearcode << Shift.at(rdmnum(Shift.size())) << " $t2 $s1 " << rdmnum(4) << endl;
                clearcode << Shift.at(rdmnum(Shift.size())) << " $t3 $s1 " << rdmnum(4) << endl;
                clearcode << "sw $t2 " << point << "($0)" << endl;
                point += 4;
                clearcode << "sw $t1 " << point << "($0)" << endl;
                point += 4;
                clearcode << "sw $t3 " << point << "($0)" << endl;
                point += 4;
            }
        }
    }
    clearcode.close();
}

void L_Shift(int type)
{
    clearcode.open("P53_2017.txt", ios::app);
    if(type == 1)
    {
        string instr_f = Load.at(rdmnum(Load.size()));
        clearcode << instr_f << " $t0 0($0)" << endl;
        clearcode << Shift.at(rdmnum(Shift.size())) << " $t1 $t0 " << rdmnum(4) << endl;
        clearcode << Shift.at(rdmnum(Shift.size())) << " $t2 $t0 " << rdmnum(4) << endl;
        clearcode << Shift.at(rdmnum(Shift.size())) << " $t3 $t0 " << rdmnum(4) << endl;
        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t1 " << point << "($0)" << endl;
        point += 4;

    }
    else
    {
        //not implement.
    }
    clearcode.close();
}

void Shift_R(int type)
{
    clearcode.open("P53_2017.txt", ios::app);
    if(type == 1)
    {
        string instr_f = Shift.at(rdmnum(Shift.size()));
        clearcode << instr_f << " $t0 $s0 " << rdmnum(5) << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t1 $s0 $t0" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t2 $s0 $t0" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t3 $s0 $t0" << endl;
        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t1 " << point << "($0)" << endl;
        point += 4;

        clearcode << instr_f << " $t0 $s0 " << rdmnum(5) << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t1 $t0 $s0" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t2 $t0 $s0" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t3 $t0 $s0" << endl;
        clearcode << "sw $t1 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;
    }
    else
    {

    }
    clearcode.close();
}

void Shift_I(int type)
{
    clearcode.open("P53_2017.txt", ios::app);
    if(type == 1)
    {
        string instr_f = Shift.at(rdmnum(Shift.size()));
        clearcode << instr_f << " $t0 $s0 " << rdmnum(5) << endl;
        clearcode << I_type.at(rdmnum(I_type.size())) << " $t1 $t0 " << rdmnum(10) << endl;
        clearcode << I_type.at(rdmnum(I_type.size())) << " $t2 $t0 " << rdmnum(10) << endl;
        clearcode << I_type.at(rdmnum(I_type.size())) << " $t3 $t0 " << rdmnum(10) << endl;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t1 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;
    }
    else
    {

    }
    clearcode.close();
}

void Shift_S(int type)
{
    //no need
    return;
}

void Shift_L(int type)
{
    clearcode.open("P53_2017.txt", ios::app);
    clearcode << "addi $t0 $0 4\n"
                << "addi $t1 $0 256\n"
                << "sll $t2 $t0 2\n";
    clearcode << Load.at(rdmnum(Load.size())) << " $t3 0($t2)" << endl;
    clearcode << Load.at(rdmnum(Load.size())) << " $t4 4($t2)" << endl;
    clearcode << Load.at(rdmnum(Load.size())) << " $t5 8($t2)" << endl;
    clearcode << "sw $t3 " << point << "($0)" << endl;
    point += 4;
    clearcode << "sw $t4 " << point << "($0)" << endl;
    point += 4;
    clearcode << "sw $t5 " << point << "($0)" << endl;
    point += 4;

    clearcode << "srl $t2 $t1 6\n";
    clearcode << Load.at(rdmnum(Load.size())) << " $t3 0($t2)" << endl;
    clearcode << Load.at(rdmnum(Load.size())) << " $t4 4($t2)" << endl;
    clearcode << Load.at(rdmnum(Load.size())) << " $t5 8($t2)" << endl;
    clearcode << "sw $t3 " << point << "($0)" << endl;
    point += 4;
    clearcode << "sw $t4 " << point << "($0)" << endl;
    point += 4;
    clearcode << "sw $t5 " << point << "($0)" << endl;
    point += 4;


    clearcode.close();
}

void RI_MulDiv_AND_Mf_RI_AND_MulDiv_Mf_AND_Mf_Save(int type)
{
    clearcode.open("P53_2017.txt", ios::app);
    if(type == 1)
    {
        clearcode << R_type.at(rdmnum(R_type.size()-3)) << " $t0 $s0 $s1" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t1 $s2 $s3" << endl;
        clearcode << Mul_Div.at(rdmnum(Mul_Div.size())) << " $t1 $t0" << endl;
        // 3 instrs
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t2 $s0 $s1" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t3 $s2 $s3" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t4 $s0 $s1" << endl;

        clearcode << Mf.at(rdmnum(Mf.size())) << " $t5" << endl;

        clearcode << R_type.at(rdmnum(R_type.size())) << " $t1 $t5 $s3" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t6 $t5 $s1" << endl;
        clearcode << I_type.at(rdmnum(I_type.size()-2)) << " $t0 $t5 -100" << endl;
        //end
        clearcode << Mul_Div.at(rdmnum(Mul_Div.size())) << " $t1 $t0" << endl;
        // 3 instrs
        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t4 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t6 " << point << "($0)" << endl;
        point += 4;

        clearcode << Mf.at(rdmnum(Mf.size())) << " $t5" << endl;
        clearcode << I_type.at(rdmnum(I_type.size()-2)) << " $t7 $t5 4" << endl;
        clearcode << I_type.at(rdmnum(I_type.size()-2)) << " $t8 $t5 4" << endl;
        clearcode << R_type.at(rdmnum(R_type.size()-2)) << " $t9 $t5 $s1" << endl;

        clearcode << I_type.at(rdmnum(I_type.size()-2)) << " $t0 $s2 4" << endl;
        clearcode << I_type.at(rdmnum(I_type.size()-2)) << " $t1 $s2 4" << endl;
        clearcode << I_type.at(rdmnum(I_type.size())) << " $t2 $s2 4" << endl;
        clearcode << Mul_Div.at(rdmnum(Mul_Div.size())) << " $t0 $t1" << endl;
        //3 instrs
        clearcode << "sw $t7 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t8 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t9 " << point << "($0)" << endl;
        point += 4;

        clearcode << Mf.at(rdmnum(Mf.size())) << " $t5" << endl;
        clearcode << "sw $t5 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t5 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t5 " << point << "($0)" << endl;
        point += 4;


    }
    else
    {
        //not implement
    }
    clearcode.close();
}

void Load_MulDiv_AND_Shift_MulDiv_AND_Mf_Shift(int type)
{
    clearcode.open("P53_2017.txt", ios::app);
    if(type == 1)
    {
        clearcode << "lui $t0 0xffff\nadd $t0 $t0 $s6\nsw $t0 " << point << "($0)\n";
        clearcode << Load.at(rdmnum(Load.size())) << " $t0 " << point << "($0)" << endl;
        clearcode << Load.at(rdmnum(Load.size())) << " $t1 " << point << "($0)" << endl;
        clearcode << Mul_Div.at(rdmnum(Mul_Div.size())) << " $t1 $t0" << endl;
        // 3 instrs
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t2 $s0 $s1" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t3 $s2 $s3" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t4 $s0 $s1" << endl;

        clearcode << Mf.at(rdmnum(Mf.size())) << " $t5" << endl;

        clearcode << Load.at(rdmnum(Load.size())) << " $t0 " << point << "($0)" << endl;
        clearcode << Shift.at(rdmnum(Shift.size())) << " $t6 $t5 3" << endl;
        clearcode << Shift.at(rdmnum(Shift.size())) << " $t1 $t5 4" << endl;
        //end
        clearcode << Mul_Div.at(rdmnum(Mul_Div.size())) << " $t1 $t0" << endl;
        // 3 instrs
        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t4 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t6 " << point << "($0)" << endl;
        point += 4;

        clearcode << Mf.at(rdmnum(Mf.size())) << " $t5" << endl;
        clearcode << Shift.at(rdmnum(Shift.size())) << " $t7 $t5 4" << endl;
        clearcode << I_type.at(rdmnum(I_type.size())) << " $t8 $t5 7" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t9 $t5 $s1" << endl;

        clearcode << Shift.at(rdmnum(Shift.size())) << " $t1 $s0 2" << endl;
        clearcode << Shift.at(rdmnum(Shift.size())) << " $t0 $s0 3" << endl;
        clearcode << I_type.at(rdmnum(I_type.size())) << " $t2 $s2 4" << endl;
        clearcode << Mul_Div.at(rdmnum(Mul_Div.size())) << " $t0 $t1" << endl;
        //3 instrs
        clearcode << "sw $t7 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t8 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t9 " << point << "($0)" << endl;
        point += 4;

        clearcode << Mf.at(rdmnum(Mf.size())) << " $t5" << endl;
        clearcode << "sw $t5 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t5 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t5 " << point << "($0)" << endl;
        point += 4;


    }
    else
    {
        //not implement
    }
    clearcode.close();
}

void ALL_Mt_AND_Mf_Load(int type)
{
    clearcode.open("P53_2017.txt", ios::app);
    if(type == 1)
    {
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t0 $s0 $s1" << endl;
        clearcode << "nop" << endl;
        clearcode << "nop" << endl;
        clearcode << "mthi $t0" << endl;
        clearcode << "mfhi $t1" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t0 $s0 $s1" << endl;
        clearcode << "nop" << endl;
        clearcode << "mtlo $t0" << endl;
        clearcode << "mflo $t2" << endl;
        clearcode << R_type.at(rdmnum(R_type.size())) << " $t0 $s0 $s1" << endl;
        clearcode << "mthi $t0" << endl;
        clearcode << "mfhi $t3" << endl;
        clearcode << "sw $t1 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;

        clearcode << I_type.at(rdmnum(I_type.size())) << " $t0 $s1 " << rdmnum(1000) << endl;
        clearcode << "nop" << endl;
        clearcode << "nop" << endl;
        clearcode << "mthi $t0" << endl;
        clearcode << "mfhi $t1" << endl;
        clearcode << I_type.at(rdmnum(I_type.size())) << " $t0 $s1 " << rdmnum(1000) << endl;
        clearcode << "nop" << endl;
        clearcode << "mtlo $t0" << endl;
        clearcode << "mflo $t2" << endl;
        clearcode << I_type.at(rdmnum(I_type.size())) << " $t0 $s1 " << rdmnum(1000) << endl;
        clearcode << "mthi $t0" << endl;
        clearcode << "mfhi $t3" << endl;
        clearcode << "sw $t1 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;

        clearcode << Shift.at(rdmnum(Shift.size())) << " $t0 $s0 " << rdmnum(5) << endl;
        clearcode << "nop" << endl;
        clearcode << "nop" << endl;
        clearcode << "mthi $t0" << endl;
        clearcode << "mfhi $t1" << endl;
        clearcode << Shift.at(rdmnum(Shift.size())) << " $t0 $s0 " << rdmnum(5) << endl;
        clearcode << "nop" << endl;
        clearcode << "mtlo $t0" << endl;
        clearcode << "mflo $t2" << endl;
        clearcode << Shift.at(rdmnum(Shift.size())) << " $t0 $s0 " << rdmnum(5) << endl;
        clearcode << "mthi $t0" << endl;
        clearcode << "mfhi $t3" << endl;
        clearcode << "sw $t1 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;

        clearcode << Load.at(rdmnum(Load.size())) << " $t0 0($0)" << endl;
        clearcode << "nop" << endl;
        clearcode << "nop" << endl;
        clearcode << "mthi $t0" << endl;
        clearcode << "mfhi $t1" << endl;
        clearcode << Load.at(rdmnum(Load.size())) << " $t0 0($0)" << endl;
        clearcode << "nop" << endl;
        clearcode << "mtlo $t0" << endl;
        clearcode << "mflo $t2" << endl;
        clearcode << Load.at(rdmnum(Load.size())) << " $t0 0($0)" << endl;
        clearcode << "mthi $t0" << endl;
        clearcode << "mfhi $t3" << endl;
        clearcode << "sw $t1 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;

        clearcode << "addi $t0 $0 4" << endl;
        clearcode << "mthi $t0" << endl;
        clearcode << "mfhi $t5" << endl;
        clearcode << "nop" << endl;
        clearcode << "nop" << endl;
        clearcode << Load.at(rdmnum(Load.size())) << " $t1 0($t5)" << endl;
        clearcode << "addi $t0 $0 0" << endl;
        clearcode << "mthi $t0" << endl;
        clearcode << "mfhi $t5" << endl;
        clearcode << "nop" << endl;
        clearcode << Load.at(rdmnum(Load.size())) << " $t2 0($t5)" << endl;
        clearcode << "addi $t0 $0 8" << endl;
        clearcode << "mthi $t0" << endl;
        clearcode << "mfhi $t5" << endl;
        clearcode << Load.at(rdmnum(Load.size())) << " $t3 0($t5)" << endl;
        clearcode << "sw $t1 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t2 " << point << "($0)" << endl;
        point += 4;
        clearcode << "sw $t3 " << point << "($0)" << endl;
        point += 4;
    }
    else
    {

    }
    clearcode.close();
}

void lui_special()
{
    clearcode.open("P53_2017.txt", ios::app);
    clearcode << "lui $t0 " << rdmnum(1000) << endl;
    clearcode << R_type.at(rdmnum(R_type.size())) << " $t1 $s0 $t0" << endl;
    clearcode << R_type.at(rdmnum(R_type.size())) << " $t2 $s0 $t0" << endl;
    clearcode << R_type.at(rdmnum(R_type.size())) << " $t3 $s0 $t0" << endl;
    clearcode << "sw $t3 " << point << "($0)" << endl;
    point += 4;
    clearcode << "sw $t2 " << point << "($0)" << endl;
    point += 4;
    clearcode << "sw $t1 " << point << "($0)" << endl;
    point += 4;

    clearcode << "lui $t0 " << rdmnum(1000) << endl;
    clearcode << R_type.at(rdmnum(R_type.size())) << " $t1 $t0 $s0" << endl;
    clearcode << R_type.at(rdmnum(R_type.size())) << " $t2 $t0 $s0" << endl;
    clearcode << R_type.at(rdmnum(R_type.size())) << " $t3 $t0 $s0" << endl;
    clearcode << "sw $t1 " << point << "($0)" << endl;
    point += 4;
    clearcode << "sw $t3 " << point << "($0)" << endl;
    point += 4;
    clearcode << "sw $t2 " << point << "($0)" << endl;
    point += 4;

    clearcode << "lui $t0 " << rdmnum(1000) << endl;
    clearcode << I_type.at(rdmnum(I_type.size())) << " $t1 $t0 " << rdmnum(100) << endl;
    clearcode << I_type.at(rdmnum(I_type.size())) << " $t2 $t0 " << rdmnum(100) << endl;
    clearcode << I_type.at(rdmnum(I_type.size())) << " $t3 $t0 " << rdmnum(100) << endl;
    clearcode << "sw $t1 " << point << "($0)" << endl;
    point += 4;
    clearcode << "sw $t3 " << point << "($0)" << endl;
    point += 4;
    clearcode << "sw $t2 " << point << "($0)" << endl;
    point += 4;

    clearcode << "lui $t0 " << rdmnum(1000) << endl;
    clearcode << "sw $t0 " << point << "($0)" << endl;
    point += 4;
    clearcode << "sw $t0 " << point << "($0)" << endl;
    point += 4;
    clearcode << "sw $t0 " << point << "($0)" << endl;
    point += 4;

    clearcode.close();
}

int main()
{
    srand((unsigned)time(NULL));     //用于保证是随机数
    clearcode.open("P53_2017.txt");
    clearcode << "#initial\n";
    clearcode << "addi $s0 $0 131071\naddi $s1 $0 5\naddi $s2 $0 65535\naddi $s3 $0 8\nlui $s5 0xABCD\nadd $s6 $t0 0xffff\n";
    clearcode << "#initial done\n";
    clearcode.close();
    int func;                             //  输入func码决定功能
    cout << "-------------------CODE AUTO MAKER------------------------------------------\n";
    cout << "|                Powered By Henry Liu                                      |\n";
    cout << "|                  From Padio Planet                                       |\n";
    cout << "|                                                    Version 2.9           |\n";
    cout << "|                                               Contact 583448542@qq.com   |\n";
    cout << "----------------------------------------------------------------------------\n";
    cout << "\n\nPlease read the README.txt first.";
    cout << "\n\nPlease input the function code: (1|2)\n";
    cout << "\n\nWARNING 2nd func has not been implemented.\n";
    cin >> func;
    while(func<1||func>2)
    {
        cout << "function code is wrong. Please input 1|2\n";
        cin >> func;
    }
    if(func == 1)
    {
        //P5.3

        R_R_AND_R_S(1);
        R_I(1);
        R_Load_AND_I_Load_AND_Load_Save(1);
        I_R(1);
        I_I(1);
        I_S(1);
        L_R(1);
        L_I(1);
        L_L(1);
        R_Shift(1);
        I_Shift(1);
        L_Shift(1);
        Shift_R(1);
        Shift_I(1);
        Shift_L(1);

        R_R_AND_R_S(1);
        R_I(1);
        R_Load_AND_I_Load_AND_Load_Save(1);
        I_R(1);
        I_I(1);
        I_S(1);
        L_R(1);
        L_I(1);
        L_L(1);
        R_Shift(1);
        I_Shift(1);
        L_Shift(1);
        Shift_R(1);
        Shift_I(1);
        Shift_L(1);

        R_R_AND_R_S(1);
        R_I(1);
        R_Load_AND_I_Load_AND_Load_Save(1);
        I_R(1);
        I_I(1);
        I_S(1);
        L_R(1);
        L_I(1);
        L_L(1);
        R_Shift(1);
        I_Shift(1);
        L_Shift(1);
        Shift_R(1);
        Shift_I(1);
        Shift_L(1);

        R_R_AND_R_S(1);
        R_I(1);
        R_Load_AND_I_Load_AND_Load_Save(1);
        I_R(1);
        I_I(1);
        I_S(1);
        L_R(1);
        L_I(1);
        L_L(1);
        R_Shift(1);
        I_Shift(1);
        L_Shift(1);
        Shift_R(1);
        Shift_I(1);
        Shift_L(1);

        //P6
/*
        R_R_AND_R_S(1);
        R_I(1);
        R_Load_AND_I_Load_AND_Load_Save(1);
        I_R(1);
        I_I(1);
        I_S(1);
        L_R(1);
        L_I(1);
        L_L(1);
        R_Shift(1);
        I_Shift(1);
        L_Shift(1);
        Shift_R(1);
        Shift_I(1);
        Shift_L(1);
        RI_MulDiv_AND_Mf_RI_AND_MulDiv_Mf_AND_Mf_Save(1);
        Load_MulDiv_AND_Shift_MulDiv_AND_Mf_Shift(1);
        ALL_Mt_AND_Mf_Load(1);

        R_R_AND_R_S(1);
        R_I(1);
        R_Load_AND_I_Load_AND_Load_Save(1);
        I_R(1);
        I_I(1);
        I_S(1);
        L_R(1);
        L_I(1);
        L_L(1);
        R_Shift(1);
        I_Shift(1);
        L_Shift(1);
        Shift_R(1);
        Shift_I(1);
        Shift_L(1);
        RI_MulDiv_AND_Mf_RI_AND_MulDiv_Mf_AND_Mf_Save(1);
        Load_MulDiv_AND_Shift_MulDiv_AND_Mf_Shift(1);
        ALL_Mt_AND_Mf_Load(1);

        R_R_AND_R_S(1);
        R_I(1);
        R_Load_AND_I_Load_AND_Load_Save(1);
        I_R(1);
        I_I(1);
        I_S(1);
        L_R(1);
        L_I(1);
        L_L(1);
        R_Shift(1);
        I_Shift(1);
        L_Shift(1);
        Shift_R(1);
        Shift_I(1);
        Shift_L(1);
        RI_MulDiv_AND_Mf_RI_AND_MulDiv_Mf_AND_Mf_Save(1);
        Load_MulDiv_AND_Shift_MulDiv_AND_Mf_Shift(1);
        ALL_Mt_AND_Mf_Load(1);
*/
        lui_special();
    }
    else
    {
        cout << "NOT IMPLEMENTED!!!" << endl;
        //R_Load_AND_I_Load_AND_Load_Save(2);
        //R_R_AND_R_S(2);
        //cout << "NOT IMPLENTED!!!" << endl;
    }
    return 0;
}
