#include<iostream>
#include<iomanip>
#include<string>
#include<sstream>
#include<stdio.h>
#include<cstring>
#include<cmath>
using namespace std;


//Caesar����ļ��ܺͽ���
//���룺 
//str1 �����ַ�����k ��λ����
//type ���ܻ�������ͣ�0Ϊ���ܣ�1Ϊ���� 
//���أ�
//str2 ���ص��ַ������� 
string Caesar(string str1,int k,int type)
{
	string result;
	int l=str1.length();
	string *str2=new string[l];
	if(type==0)
	{
		for(int i=0;i<l;i++)
	    {
	    	if(str1[i]<='z'&&str1[i]>='a')
	    	    str2[i]=(str1[i]-'a'+k)%26+'a';
	    	else if(str1[i]<='Z'&&str1[i]>='A')
	    	    str2[i]=(str1[i]-'A'+k)%26+'A';
	    	result += str2[i];
	    }
	}
	else if(type=1) 
	{
		for(int i=0;i<l;i++)
	    {
	    	if(str1[i]<='z'&&str1[i]>='a')
	    	    str2[i]=(str1[i]-'a'-k)%26+'a';
	    	else if(str1[i]<='Z'&&str1[i]>='A')
	    	    str2[i]=(str1[i]-'A'-k)%26+'A';
	    	result += str2[i];
	    }
	}
	return result;
}

//ʵ��Playfair����
//���룺��Կ���ʣ��ַ���, ���� 
//�������ƣ���Կ���ʺ��ַ���������ΪӢ��Сд��ĸ��
//���ͣ�0 ���ܣ�1 ���� 
//���� 
struct coors{
	int row;
	int column;
};

//����ָ����ĸ��������е����� 
coors titleFind(char title,char table[5][5])
{
	coors result;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(table[i][j]==title)
			{
				result.row=i;
				result.column=j;
				return result;
			}
		}
	}
} 

//ȥ��string�е��ظ���ĸ 
string dRepeat(string s)
{
	int l=s.length();
	string result;
	for(int i=0;i<l;i++)
	{
		if(s.find(s[i])!=i||s[i]=='j')
             s[i]=0;
	}
	for (int k = 0; k < l; k++)
    {
        
        if (s[k] != 0)
		    result += s[k];
    }
	return result;
}

//���Ĵ���
//����һ����飬ȥ�ظ�
//�ظ��Ͳ�λ����x��x���ظ�x��y��ȱλ��x�� 
string CTP(string clear)
{
	int l=clear.length() ;
	string result;
    string x="x";
    string y="y";
	for(int i=0;i<l;i+=2)
	{
		if(clear[i]==clear[i+1]&&clear[i]!='x')
		{
			clear.insert(i+1,x);
			l += 1;
		}
		else if(clear[i]==clear[i+1]&&clear[i]=='x')
		{
			clear.insert(i+1,y);
			l += 1;
		}
	}
	if(l%2!=0&&clear[l-1]!='x') clear += 'x';
	else if(l%2!=0&&clear[l-1]=='x') clear += 'y';
	return clear;
}

//������Կ���������
//int main()
string tableCreate(string key)
{
//	string key="ijjkkef";
	string list;
	char aph='a';
	for(int i=0;i<25;i++)
	{
		if(i==8)
		{
			list += aph;
			aph += 2;
		}       
		else
		{
			list += aph;
			aph += 1;
		}
	}
	string newkey=dRepeat(key);
//  cout<<list<<endl; 
//	cout<<dRepeat(key);
//	cout<<newkey<<endl;
//	return 0; 
	for(int i=0;i<25;i++)
	{
		for(int j=0;j<newkey.length() ;j++)
		{
			if(list[i]==newkey[j])
			    list[i]=0;
		}    
	}
//	cout<<list<<endl;
	for(int i=0;i<25;i++)
	{
		if(list[i]==0)
		    continue;
		newkey += list[i];
	}
//	cout<<newkey<<endl;
	return newkey;
} 

//type=0 ����
//type=1 ���� 
string Playfair(string key,string clear,int type)
{
	string tableStr=tableCreate(key);
	char table[5][5];
	for(int i=0;i<5;i++)
	{
	    for(int j=0;j<5;j++)
	    {
	   		table[i][j]=tableStr[i*5+j];
	   		//cout<<table[i][j];
	   	}
	   	//cout<<endl;
	}
	if(type==0) 
	{
	    
	    clear=CTP(clear);
//	    cout<<tableStr<<endl;
//	    cout<<clear<<endl;
	    
	    int len=clear.length();
	    char clearlist[len/2][2];
	    for(int i=0;i<len/2;i++)
	    {
	    	for(int j=0;j<2;j++)
	    	{
	     		clearlist[i][j]=clear[i*2+j];
			//cout<<clear[i*2+j]<<endl;
		    }
	    }
	
	    string result;
	    for(int i=0;i<len/2;i++)
	    {
	        coors p,q;
	        p=titleFind(clearlist[i][0],table);
	        q=titleFind(clearlist[i][1],table);
	    
	        if(p.column==q.column)
	        {
	        	result += table[(p.row+1)%5][p.column];
	        	result += table[(q.row+1)%5][q.column];
		    }
	        	
	    	if(p.row==q.row)
	    	{
	            result += table[p.row][(p.column+1)%5];
	            result += table[q.row][(q.column+1)%5];
	    	}
	    	
	    	if(p.row!=q.row&&p.column!=q.column)
	    	{
	        	result += table[p.row][q.column];
	        	result += table[q.row][p.column];
	    	}
        }
        return result;
    }
    else if(type==1)
    {
    	int len=clear.length();
	    char clearlist[len/2][2];
	    for(int i=0;i<len/2;i++)
	    {
	    	for(int j=0;j<2;j++)
	    	{
	     		clearlist[i][j]=clear[i*2+j];
			//cout<<clear[i*2+j]<<endl;
		    }
	    }
	
	    string result;
	    for(int i=0;i<len/2;i++)
	    {
	        coors p,q;
	        p=titleFind(clearlist[i][0],table);
	        q=titleFind(clearlist[i][1],table);
	    
	        if(p.column==q.column)
	        {
	        	result += table[(p.row-1+5)%5][p.column];
	        	result += table[(q.row-1+5)%5][q.column];
		    }
	        	
	    	if(p.row==q.row)
	    	{
	            result += table[p.row][(p.column-1+5)%5];
	            result += table[q.row][(q.column-1+5)%5];
	    	}
	    	
	    	if(p.row!=q.row&&p.column!=q.column)
	    	{
	        	result += table[p.row][q.column];
	        	result += table[q.row][p.column];
	    	}
        }
        return result;
	}
}


//ϣ������ӽ���
//���룺
//int judge�ж����ͣ�0���ܣ�1����
//�����������ⳤ���ַ��� 
//�������볤��Ϊ3�������ַ��� 
string Hill(int judge,string s) 
{
	string ans;
	int k[3][3]={{17,17,5},{21,18,21},{2,2,19}};  //�趨������Կ����K
	int invk[3][3]={{4,9,15},{15,17,6},{24,0,17}};  //������ܾ���K���� ��Ϊ������Կ 
	char p[3]={0};
	char c[3]={0};
	if (judge==0) 
	{
		if(s.length()%3!=0)
	        for(int i=0;i<(s.length())%3;i++) 
	            s+="a";
	    for(int count=0;count<s.length();count+=3)
	    {
	    	for (int i=0;i<3;i++)
	    	    p[i]=s[count+i];
	        int pdig[3]={0};
	        for (int i=0;i<3;i++)
	        	pdig[i]=p[i]-'a';
	        int result[3]={0};
	        for (int i=0;i<3;i++)
	        	for (int j=0;j<3;j++)
	        		result[i] += pdig[j]*k[j][i];
	        for (int i=0;i<3;i++)
		        c[i]='a' + int(result[i])%26;
	        for (int i=0;i<3;i++)
		        ans+=c[i]; 
        }    
	}
    else if (judge==1)
    {
	    for(int count=0;count<s.length();count+=3)
	    {
	        for (int i=0;i<3;i++)
	    	    c[i]=s[count+i];
            int cdig[3]={0};
            for (int i=0;i<3;i++)
	    	    cdig[i]=c[i]-'a';
	        int result2[3]={0};
	        for (int i=0;i<3;i++)
	    	    for (int j=0;j<3;j++)
	    	    	result2[i] += cdig[j]*invk[j][i];
	        for (int i=0;i<3;i++)
	        	p[i]='a' + int(result2[i])%26;
	        for (int i=0;i<3;i++)
	    	    ans+=p[i];
		}
    }
    return ans;
}

//DES�ӽ���
//type=0 ���ܣ�type=1������ 
//���볤�ȹ̶�Ϊ16λ�İ������ֺ���ĸ���ַ��������ĺ���Կ��һ���� 
//��ʼ64λ���ݿ� 
struct Divide{
	string L;
	string R;
};

//��ʼ�û����� 
int IP_order[] = 
{58, 50, 42, 34, 26, 18, 10, 2,
 60, 52, 44, 36, 28, 20, 12, 4,
 62, 54, 46, 38, 30, 22, 14, 6,
 64, 56, 48, 40, 32, 24, 16, 8,
 57, 49, 41, 33, 25, 17, 9,  1,
 59, 51, 43, 35, 27, 19, 11, 3,
 61, 53, 45, 37, 29, 21, 13, 5,
 63, 55, 47, 39, 31, 23, 15, 7 };

//��β�û����� 
int IP_reverse[] = 
{40, 8, 48, 16, 56, 24, 64, 32,
 39, 7, 47, 15, 55, 23, 63, 31,
 38, 6, 46, 14, 54, 22, 62, 30,
 37, 5, 45, 13, 53, 21, 61, 29,
 36, 4, 44, 12, 52, 20, 60, 28,
 35, 3, 43, 11, 51, 19, 59, 27,
 34, 2, 42, 10, 50, 18, 58, 26,
 33, 1, 41,  9, 49, 17, 57, 25 };



//��Կ�û����� 
int PC_56[] = { 57, 49, 41, 33, 25, 17, 9,
1, 58, 50, 42, 34, 26, 18,
10,  2, 59, 51, 43, 35, 27,
19, 11,  3, 60, 52, 44, 36,
63, 55, 47, 39, 31, 23, 15,
7, 62, 54, 46, 38, 30, 22,
14,  6, 61, 53, 45, 37, 29,
21, 13,  5, 28, 20, 12,  4 }; 

//��Կѹ������ 
int PC_48[] = { 14, 17, 11, 24,  1,  5,
3, 28, 15,  6, 21, 10,
23, 19, 12,  4, 26,  8,
16,  7, 27, 20, 13,  2,
41, 52, 31, 37, 47, 55,
30, 40, 51, 45, 33, 48,
44, 49, 39, 56, 34, 53,
46, 42, 50, 36, 29, 32 };

//��Կ����λ��
int PC_move[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

//E��չ����
int E[] = 
{32,  1,  2,  3,  4,  5,
 4 ,  5,  6,  7,  8,  9,
 8 ,  9, 10, 11, 12, 13,
 12, 13, 14, 15, 16, 17,
 16, 17, 18, 19, 20, 21,
 20, 21, 22, 23, 24, 25,
 24, 25, 26, 27, 28, 29,
 28, 29, 30, 31, 32,  1 };

//S��
int S[8][4][16] = //S�У���8����ÿ��Ϊ4*16���û�����6*8λ��Ϊ4*8λ 
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

//P�û�����
int P[] = 
{ 16,  7, 20, 21,
  29, 12, 28, 17,
  1 , 15, 23, 26,
  5 , 18, 31, 10,
  2 ,  8, 24, 14,
  32, 27,  3,  9,
  19, 13, 30,  6,
  22, 11,  4, 25  };
 
//16����ת������ 
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

//������ת16���� 
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

//IP�û�
//���룺��ʼ��64λ���ݿ�
//���أ�64λ�û������ݿ飬��32λΪL0����32λΪR0 
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

//��Կ�û�,��Կ��64λ��Ϊ56λ 
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

//�ַ�������nλ��
string moveLeft(string str,int n)
{
	string temp;
	int l=str.length();
    for(int i=0;i<l;i++)
		temp += str[(i+n)%l];
	return temp;
} 

//ѹ���û���56λ��48λ
string Keycompress(Divide key) 
{
	string temp,result;
	temp += key.L;
	temp += key.R;
	for(int i=0;i<48;i++)
		result += temp[PC_48[i]-1];
	return result;
}

//E��չ�����������Ұ벿��32λ��չΪ48λ��4λx8�飩 
string E_estension(string str)
{
	string result;
	for(int i=0;i<48;i++)
		result += str[E[i]-1];
	return result;
}

//���
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

//S���ӱ任 48λ��32λ
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

//P���û� 32λ 
string Pexchange(string str)
{
	string result;
	for(int i=0;i<32;i++)
		result += str[P[i]-1];
	return result; 
}

//ĩ�û�
string lastexchange(string T)
{
	string result;
	for(int i=0;i<64;i++)
		result += T[IP_reverse[i]-1];
	return result;
} 

//f,����32λ���ݺ�48λ��Կ������32λ��� 
string f(string data,string key)
{
	//��һ����E��չ��data��Ϊ48λ 
	data=E_estension(data);
	//�ڶ��������
	string EOR=Exclusive_or(data,key);
	//��������S���û�������32λ��� 
	string s_result=Schange(EOR);
	//���Ĳ���32λ�������P�û�
	return Pexchange(s_result); 
}

//type=0 ���ܣ�type=1������ 
string DES(string clear,string key,int type)
{
    //16�������ĺ���Կת������
	clear=Str2Bin(clear);
	key=Str2Bin(key);
	//��һ����IP�û�
	Divide divideclear;
	divideclear=IPexchange(clear) ;
	string test;
	//�ڶ�������Կ�û�������56λ�û���Կ
	Divide dividekey=Keymove(key); 
	Divide tempkey[16];
	for(int i=0;i<16;i++)
	{
		dividekey.L=moveLeft(dividekey.L,PC_move[i]);
		dividekey.R=moveLeft(dividekey.R,PC_move[i]);	
		tempkey[i].L=dividekey.L;
		tempkey[i].R=dividekey.R;
	}
	//��������16�ε���
	//���� 
	if(type==0) 
	{
		for(int i=0;i<16;i++)
	    {
	    	//���ɵ�ǰ��������Կ	
	    	string newkey=Keycompress(tempkey[i]);
	    	//f����
		    string newleft=divideclear.R;
		    divideclear.R=Exclusive_or(divideclear.L,f(divideclear.R,newkey));
		    divideclear.L=newleft;
	    } 
	}
	//���� 
	else if(type==1)
	{
		for(int i=0;i<16;i++)
	    {
	    	//���ɵ�ǰ��������Կ	
	    	string newkey=Keycompress(tempkey[15-i]);
	    	//f����
		    string newleft=divideclear.R;
		    divideclear.R=Exclusive_or(divideclear.L,f(divideclear.R,newkey));
		    divideclear.L=newleft;
	    } 
	}
	//���Ĳ����ϲ�R16��L16���ϲ���ΪR16L16 
	string current;
	current += divideclear.R;
	current += divideclear.L;
	//���岽����β�û�
	string temp=lastexchange(current);
	//��������2����ת16����
	return Str2BinReverse(temp); 	
} 

//RSA�ӽ���
//RSA��Կ��Կ���ܽ���
//������Ҫ����
//�����Դ������p��q
//���ģ���Ӣ�����ֶ����� 
//����Ϊ RSAenc(����,p,q)
//����Ϊ RSAdec(����, RSAlength)
long long NNN;   //p*q 
long long EEE,DDD;  //��ԿEEE��˽ԿDDD 
int RSAlength;   //���ĳ��� 
//�ж��Ƿ��� 
long long mgcd(long long a,long long b)
{
    long long t;
    if(a<b)
    {
        t=a;a=b;b=t;
    }
    while(a%b)
    {
        t=b;
        b=a%b;
        a=t;
    }
    return b;
}

//��������Ļ���p��q���ɹ�Կ˽Կ 
void createkey(long long p,long long q)
{
    NNN = p*q;
    long long L=(p-1)*(q-1);
    EEE=p-1;
    long long t=10;
    while(t!=1)
    {
    	EEE -= 1;
    	t=mgcd(EEE,L);
	}
	DDD=L/EEE;
	while((EEE*DDD)%L!=1)
	{
		DDD += 1;
	}
    //long long e = 13007, d = 511;  //�ҳ���Կe��˽Կd 
} 

//��a��b����ȡģ m������ȡģ��
long long bigmod(long long a, long long  b, long long m)
{
    long long r = 1;
    for (long long i=0; i<b; i++)
	{
        r = (r*a) % m;   
    }
    return r;
}

//����RSAԭ����м��� 
long long *RSAenc (string message,long long p,long long q)
{
	RSAlength = message.length();
	createkey(p,q);
    int length = message.length();
    long long *asc = new long long[length]; //�洢��Ϣ��ÿ���ַ�
    long long *code = new long long[length];  //�洢ÿ���ַ���rsa����
    for (int i=0; i<length; i++)
	{
        asc[i] = message[i];
    }
 
    for (int i=0; i<length; i++)
	{
        code[i] = bigmod(asc[i], EEE, NNN );   //����C = M^e (mod N)
    }
    
    return code;
}

//����RSAԭ����н��� 
string RSAdec(long long code[], int n)
{  
    long long  *asc = new long long[n];  
    string message;  
    for (int i=0; i<n; i++)
	{  
        asc[i] = bigmod(code[i], DDD, NNN);    //����M = C^d (mod N)  
        message += ( char(asc[i]) );  
    }  
    return message;  
}   

//SHA1��ϣ����
//���������ַ�������Ӣ������
//���ض����ȹ�ϣ�� 
//ѭ����λ���� 
unsigned circleShift(const unsigned& word,const int& bits)
{
    return (word<<bits) | ((word)>>(32-bits));   
}

//�ĸ������Ժ��� 
unsigned sha1Fun(const unsigned& B,const unsigned& C,const unsigned& D,const unsigned& t)
{//����tΪ��ǰ���ܲ��裨ȡֵ0-79�� B C DΪ���� 
    switch (t/20)
	{
        case 0: return (B & C) | ((~B) & D);
        case 1: return B ^ C ^ D;
        case 2: return (B & C) | (B & D) | (C & D);
        case 3: return B ^ C ^ D;
    }
    return t;
}

string SHA(const string& strRaw)
{
    string str(strRaw);
    str+=(unsigned char)(0x80);
    while (str.size()*8 % 512 != 448) // ÿ���ֽ�8λ,����Ҫ��8
        str+=(char)0;  //��0 ʹ��0������ֳ���ģ512��448 
    // д��ԭʼ���ݳ���
    for (int i=56; i>=0; i-=8)
        str+=(unsigned char)((strRaw.size()<<3) >> i);  
        //��str���渽��һ��64λ������ʾԭʼ���ݵĳ��� 
    //4���ؼ�����K[4]  ABCDET 6���ֻ���  80�ֻ�����W[80] 
    const unsigned K[4]={0x5a827999,0x6ed9eba1,0x8f1bbcdc,0xca62c1d6}; 
    unsigned A(0x67452301),B(0xefcdab89),C(0x98badcfe),D(0x10325476),E(0xc3d2e1f0),T(0);
    unsigned W[80]={0};
 
    // ÿ��ȡ64�ֽ�,��512λ
    for (unsigned i=0; i!=str.size(); i+=64)
	{
        // ǰ16����Ϊԭʼ����
        for (unsigned t=0; t!=16; ++t)
		{
            // ��4��8λ���ݷ���һ��32λ������
            //64�ֽ������w[0-15] 
            W[t]=((unsigned)str[i+4*t] & 0xff)<<24 |
                 ((unsigned)str[i+4*t+1] & 0xff)<<16 |
                 ((unsigned)str[i+4*t+2] & 0xff)<<8 |
                 ((unsigned)str[i+4*t+3] & 0xff);
        }
 
        //���W[16-79] 
        for (unsigned t=16; t!=80; ++t)
            W[t]=circleShift(W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16],1);
        //�����ϣ���W����80�ּ��ܼ��� 
        for (unsigned t=0; t!=80; ++t)
		{
            T=circleShift(A,5) + sha1Fun(B,C,D,t) + E + W[t] + K[t/20];
            E=D; 
            D=C; 
            C=circleShift(B,30); 
            B=A; 
            A=T;
        }
        //�ٽ�5��������ABCDE�������ǵ�ԭʼ���� 
        A+=0x67452301;B+=0xefcdab89;C+=0x98badcfe;D+=0x10325476;E+=0xc3d2e1f0;
    }
    stringstream ss;
    ss<<setw(8)<<setfill('0')<<hex<<A<<B<<C<<D<<E;
    ss>>str;
    return str;
}

int main()
{
	int select;
	while(true)
	{
		cout<<"��������ܷ�ʽ"<<endl;
		cout<<" 1---Caesar����  2---Playfair����"<<endl; 
		cout<<" 3---Hill����    4---DES����     "<<endl;
		cout<<" 5---RSA����     6---HSA1����    "<<endl;
		cout<<" 0---�˳�ϵͳ" <<endl; 
		cin>>select;
		switch(select) 
		{
			case 1:{
				cout<<"�����������Լ��ƶ�λ��(���ı���ΪӢ����ĸ)"<<endl;
				string clear;int number;
				string miwen=Caesar(clear,number,0);
				cout<<"���ܺ�Ľ��Ϊ:"<<endl;
				cout<<miwen<<endl;
				cout<<"���ܺ�Ľ��Ϊ����Сд��������:"<<endl;
				cout<<Caesar(miwen,number,1)<<endl;
				break;
			}
			case 2:{
				cout<<"���������ģ�����ΪСдӢ����ĸ��"<<endl;
				string clear;string key;
				cin>>clear;
				cout<<"���������뵥��"<<endl;
				cin>>key;
				cout<<"���ܺ�Ľ��Ϊ:"<<endl;
				string miwen=Playfair(key,clear,0);
				cout<<miwen<<endl;
				cout<<"���ܺ�Ľ��Ϊ:"<<endl;
				cout<<Playfair(key,miwen,1)<<endl;
				break;
			}
			case 3:{
				cout<<"���������ģ�����ΪСдӢ����ĸ��"<<endl;
				string clear;
				cin>>clear;
				cout<<"���ܺ�Ľ��Ϊ:"<<endl;
				string miwen=Hill(0,clear);
				cout<<miwen<<endl;
				cout<<"���ܺ�Ľ��Ϊ:"<<endl;
				cout<<Hill(1,miwen)<<endl;
				break;
			}
			case 4:{
				cout<<"�����볤��Ϊ16�����ģ�СдӢ����ĸ�����֣����硰02468aceeca86420����"<<endl;
				string clear;string key;
				cin>>clear;
				cout<<"�������Ϊ16��Կ��СдӢ����ĸ�����֣����硰0f1571c947d9e859����"<<endl;
				cin>>key;
				cout<<"���ܺ�Ľ��Ϊ:"<<endl;
				string miwen=DES(clear,key,0);
				cout<<miwen<<endl;
				cout<<"���ܺ�Ľ��Ϊ:"<<endl;
				cout<<DES(miwen,key,1)<<endl;
				break;
			} 
			case 5:{
				cout<<"���������ģ������ַ�����"<<endl;
				string clear;long long p,q;
				cin>>clear;
				cout<<"���������������������"<<endl;
				cin>>p>>q;
                cout<<"ʹ�ù�Կ("<<EEE<<","<<NNN<<")"<<endl; 
				cout<<"���ܺ�Ľ��Ϊ:"<<endl;
				long long *miwen=RSAenc(clear,p,q);
				cout<<miwen<<endl;
                cout<<"ʹ��˽Կ("<<DDD<<","<<NNN<<")"<<endl;
				cout<<"���ܺ�Ľ��Ϊ:"<<endl;
				cout<<RSAdec(miwen,RSAlength)<<endl;
				break;
			}
			case 6:{
				cout<<"���������ģ������ַ�����"<<endl;
				string clear;
				cin>>clear;
				cout<<"��ϣ���ܺ�Ĺ��ܴ�Ϊ:"<<endl; 
				cout<<SHA(clear)<<endl;
				break;
			}
			case 0:{
				return 0;
				break;
			}
		}
		cout<<endl<<"--------------------------"<<endl<<endl;
	}
 
} 
