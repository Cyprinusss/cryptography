#include<iostream>
#include<cstring>
#include<string>
using namespace std;

//初始64位数据块 
struct Divide{
	string L;
	string R;
};

//初始置换矩阵 
int IP_order[] = 
{58, 50, 42, 34, 26, 18, 10, 2,
 60, 52, 44, 36, 28, 20, 12, 4,
 62, 54, 46, 38, 30, 22, 14, 6,
 64, 56, 48, 40, 32, 24, 16, 8,
 57, 49, 41, 33, 25, 17, 9,  1,
 59, 51, 43, 35, 27, 19, 11, 3,
 61, 53, 45, 37, 29, 21, 13, 5,
 63, 55, 47, 39, 31, 23, 15, 7 };

//结尾置换矩阵 
int IP_reverse[] = 
{40, 8, 48, 16, 56, 24, 64, 32,
 39, 7, 47, 15, 55, 23, 63, 31,
 38, 6, 46, 14, 54, 22, 62, 30,
 37, 5, 45, 13, 53, 21, 61, 29,
 36, 4, 44, 12, 52, 20, 60, 28,
 35, 3, 43, 11, 51, 19, 59, 27,
 34, 2, 42, 10, 50, 18, 58, 26,
3 3, 1, 41,  9, 49, 17, 57, 25 };



//密钥置换矩阵 
int PC_56[] = { 57, 49, 41, 33, 25, 17, 9,
1, 58, 50, 42, 34, 26, 18,
10,  2, 59, 51, 43, 35, 27,
19, 11,  3, 60, 52, 44, 36,
63, 55, 47, 39, 31, 23, 15,
7, 62, 54, 46, 38, 30, 22,
14,  6, 61, 53, 45, 37, 29,
21, 13,  5, 28, 20, 12,  4 }; 

//密钥压缩矩阵 
int PC_48[] = { 14, 17, 11, 24,  1,  5,
3, 28, 15,  6, 21, 10,
23, 19, 12,  4, 26,  8,
16,  7, 27, 20, 13,  2,
41, 52, 31, 37, 47, 55,
30, 40, 51, 45, 33, 48,
44, 49, 39, 56, 34, 53,
46, 42, 50, 36, 29, 32 };

//密钥轮移位表
int PC_move[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

//E扩展矩阵
int E[] = 
{32,  1,  2,  3,  4,  5,
 4 ,  5,  6,  7,  8,  9,
 8 ,  9, 10, 11, 12, 13,
 12, 13, 14, 15, 16, 17,
 16, 17, 18, 19, 20, 21,
 20, 21, 22, 23, 24, 25,
 24, 25, 26, 27, 28, 29,
 28, 29, 30, 31, 32,  1 };

//S盒
int S[8][4][16] = //S盒，共8个，每个为4*16的置换表（将6*8位变为4*8位 
{
    //S1
    {   {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    //S2
    {   {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    //S3
    {   {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    //S4
    {   {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    //S5
    {   {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    //S6
    {   {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    //S7
    {   {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    //S8
    {   {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};

//P置换矩阵
int P[] = 
{ 16,  7, 20, 21,
  29, 12, 28, 17,
  1 , 15, 23, 26,
  5 , 18, 31, 10,
  2 ,  8, 24, 14,
  32, 27,  3,  9,
  19, 13, 30,  6,
  22, 11,  4, 25  };
 
//16进制转二进制 
string Str2Bin(string str)
{
    string result;
    int l=str.length() ;
    for(int i=0;i<l;i++)
    {
    	switch(str[i])
    	{
    		case'0':result += "0000";continue;
    		case'1':result += "0001";continue;
    		case'2':result += "0010";continue;
    		case'3':result += "0011";continue;
    		case'4':result += "0100";continue;
    		case'5':result += "0101";continue;
    		case'6':result += "0110";continue;
    		case'7':result += "0111";continue;
    		case'8':result += "1000";continue;
    		case'9':result += "1001";continue;
    		case'a':case'A':result += "1010";continue;
    		case'b':case'B':result += "1011";continue;
    		case'c':case'C':result += "1100";continue;
    		case'd':case'D':result += "1101";continue;
    		case'e':case'E':result += "1110";continue;
    		case'f':case'F':result += "1111";continue;
		}
	}
	return result;
} 

//二进制转16进制 
string Str2BinReverse(string str)
{
	string result;
	int l=str.length()/4;
	for(int i=0;i<l;i++)
	{
		string temp;
		for(int j=0;j<4;j++)
			temp += str[j+i*4];
		if(temp== "0000"){result += "0";continue;}
    	if(temp== "0001"){result += "1";continue;}
    	if(temp== "0010"){result += "2";continue;}
   		if(temp== "0011"){result += "3";continue;}
   		if(temp== "0100"){result += "4";continue;}
   		if(temp== "0101"){result += "5";continue;}
   		if(temp== "0110"){result += "6";continue;}
   		if(temp== "0111"){result += "7";continue;}
   		if(temp== "1000"){result += "8";continue;}
   		if(temp== "1001"){result += "9";continue;}
   		if(temp== "1010"){result += "a";continue;}
   		if(temp== "1011"){result += "b";continue;}
   		if(temp== "1100"){result += "c";continue;}
   		if(temp== "1101"){result += "d";continue;}
   		if(temp== "1110"){result += "e";continue;}
   		if(temp== "1111"){result += "f";continue;}
	}
	return result;
}

//IP置换
//输入：初始的64位数据块
//返回：64位置换后数据块，左32位为L0，右32位为R0 
Divide IPexchange(string str)
{
	Divide s;
	for(int i=0;i<32;i++)
	{
	    s.L += str[IP_order[i]-1];
	    s.R += str[IP_order[i+32]-1];
	}
    return s;
} 

//密钥置换,密钥从64位变为56位 
Divide Keymove(string str)
{
	Divide result;
	for(int i=0;i<56/2;i++)
	{
		result.L += str[PC_56[i]-1];
		result.R += str[PC_56[i+56/2]-1];
	}
	return result;
} 

//字符串左移n位；
string moveLeft(string str,int n)
{
	string temp;
	int l=str.length();
    for(int i=0;i<l;i++)
		temp += str[(i+n)%l];
	return temp;
} 

//压缩置换，56位变48位
string Keycompress(Divide key) 
{
	string temp,result;
	temp += key.L;
	temp += key.R;
	for(int i=0;i<48;i++)
		result += temp[PC_48[i]-1];
	return result;
}

//E扩展：输入数据右半部分32位扩展为48位（4位x8组） 
string E_estension(string str)
{
	string result;
	for(int i=0;i<48;i++)
		result += str[E[i]-1];
	return result;
}

//异或
string Exclusive_or(string str1,string str2)
{
	int l=str1.length() ;
	string result;
	for(int i=0;i<l;i++)
	{
		if(str1[i]==str2[i])
		    result += "0";
		else 
		    result += "1";
	}
	return result;
}

//S盒子变换 48位变32位
string Schange(string str) 
{
	string result;
	for(int i=0;i<48;i=i+6)
	{
		
 	    string jud1,jud2;
 	    int row,column; 
		jud1 += str[i];
		jud1 += str[i+5];
		jud2 += str[i+1];
		jud2 += str[i+2];
		jud2 += str[i+3];
		jud2 += str[i+4];
		if(jud1== "00") row=0;
		if(jud1== "01") row=1;
		if(jud1== "10") row=2;
		if(jud1== "11") row=3;
		if(jud2== "0000") column = 0;
    	if(jud2== "0001") column = 1;
    	if(jud2== "0010") column = 2;
   		if(jud2== "0011") column = 3;
   		if(jud2== "0100") column = 4;
   		if(jud2== "0101") column = 5;
   		if(jud2== "0110") column = 6;
   		if(jud2== "0111") column = 7;
   		if(jud2== "1000") column = 8;
   		if(jud2== "1001") column = 9;
   		if(jud2== "1010") column = 10;
   		if(jud2== "1011") column = 11;
   		if(jud2== "1100") column = 12;
   		if(jud2== "1101") column = 13;
   		if(jud2== "1110") column = 14;
   		if(jud2== "1111") column = 15;
   		int getnumber=S[i/6][row][column];
   		if(getnumber== 0) result += "0000";
    	if(getnumber== 1) result += "0001";
    	if(getnumber== 2) result += "0010";
   		if(getnumber== 3) result += "0011";
   		if(getnumber== 4) result += "0100";
   		if(getnumber== 5) result += "0101";
   		if(getnumber== 6) result += "0110";
   		if(getnumber== 7) result += "0111";
   		if(getnumber== 8) result += "1000";
   		if(getnumber== 9) result += "1001";
   		if(getnumber== 10) result += "1010";
   		if(getnumber== 11) result += "1011";
   		if(getnumber== 12) result += "1100";
   		if(getnumber== 13) result += "1101";
   		if(getnumber== 14) result += "1110";
   		if(getnumber== 15) result += "1111";
	}
	return result;
}

//P盒置换 32位 
string Pexchange(string str)
{
	string result;
	for(int i=0;i<32;i++)
		result += str[P[i]-1];
	return result; 
}

//末置换
string lastexchange(string T)
{
	string result;
	for(int i=0;i<64;i++)
		result += T[IP_reverse[i]-1];
	return result;
} 

//f,接受32位数据和48位密钥，产生32位输出 
string f(string data,string key)
{
	//第一步：E扩展，data变为48位 
	data=E_estension(data);
	//第二步：异或
	string EOR=Exclusive_or(data,key);
	//第三步：S盒置换，生成32位结果 
	string s_result=Schange(EOR);
	//第四部：32位结果进行P置换
	return Pexchange(s_result); 
}

//type=0 加密；type=1，解密 
string DES(string clear,string key,int type)
{
    //16进制明文和密钥转二进制
	clear=Str2Bin(clear);
	key=Str2Bin(key);
	//第一步：IP置换
	Divide divideclear;
	divideclear=IPexchange(clear) ;
	string test;
	//第二步：密钥置换，生成56位置换密钥
	Divide dividekey=Keymove(key); 
	Divide tempkey[16];
	for(int i=0;i<16;i++)
	{
		dividekey.L=moveLeft(dividekey.L,PC_move[i]);
		dividekey.R=moveLeft(dividekey.R,PC_move[i]);	
		tempkey[i].L=dividekey.L;
		tempkey[i].R=dividekey.R;
	}
	//第三步：16次迭代
	//加密 
	if(type==0) 
	{
		for(int i=0;i<16;i++)
	    {
	    	//生成当前迭代的密钥	
	    	string newkey=Keycompress(tempkey[i]);
	    	//f操作
		    string newleft=divideclear.R;
		    divideclear.R=Exclusive_or(divideclear.L,f(divideclear.R,newkey));
		    divideclear.L=newleft;
	    } 
	}
	//解密 
	else if(type==1)
	{
		for(int i=0;i<16;i++)
	    {
	    	//生成当前迭代的密钥	
	    	string newkey=Keycompress(tempkey[15-i]);
	    	//f操作
		    string newleft=divideclear.R;
		    divideclear.R=Exclusive_or(divideclear.L,f(divideclear.R,newkey));
		    divideclear.L=newleft;
	    } 
	}
	//第四步：合并R16和L16，合并后为R16L16 
	string current;
	current += divideclear.R;
	current += divideclear.L;
	//第五步：结尾置换
	string temp=lastexchange(current);
	//第六步：2进制转16进制
	return Str2BinReverse(temp); 	
}

int main()
{
	string ip="02468aceeca86420";
	string key="0f1571c947d9e859";
	string answer="da02ce3a89ecac3b";
	cout<<DES(ip,key,0)<<endl;
	cout<<DES(answer,key,1)<<endl;
}
