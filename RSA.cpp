#include <string>
#include<iomanip>
#include<string>
#include<sstream>
#include<stdio.h>
#include<cstring>
#include<cmath>
#include <strstream>
#include<iostream>
using namespace std;

//RSA公钥密钥加密解密
//加密需要输入
//两个稍大的质数p，q
//密文：中英文数字都可以 
//加密为 RSAenc(明文,p,q)
//解密为 RSAdec(密文, RSAlength)
long long NNN;   //p*q 
long long EEE,DDD;  //公钥EEE和私钥DDD 
int RSAlength;   //明文长度 
//判断是否互质 
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

string lltoString(long long t)
{
    std::string result;
    std::strstream ss;
    ss <<  t;
    ss >> result;
    return result;
}

//根据输入的互质p，q生成公钥私钥 
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
    //long long e = 13007, d = 511;  //找出公钥e和私钥d 
} 

//对a的b次幂取模 m（大数取模）
long long bigmod(long long a, long long  b, long long m)
{
    long long r = 1;
    for (long long i=0; i<b; i++)
	{
        r = (r*a) % m;   
    }
    return r;
}

//利用RSA原理进行加密 
long long *RSAenc (string message,long long p,long long q)
{
	RSAlength = message.length();
	createkey(p,q);
    int length = message.length();
    long long *asc = new long long[length]; //存储信息的每个字符
    long long *code = new long long[length];  //存储每个字符的rsa编码
    for (int i=0; i<length; i++)
	{
        asc[i] = message[i];
    }
 
    for (int i=0; i<length; i++)
	{
        code[i] = bigmod(asc[i], EEE, NNN );   //密文C = M^e (mod N)
    }
    
    return code;
}

string RSAenc1 (string message,long long p,long long q)
{
	RSAlength = message.length();
	createkey(p,q);
    int length = message.length();
    long long *asc = new long long[length]; //存储信息的每个字符
    long long *code = new long long[length];  //存储每个字符的rsa编码
    for (int i=0; i<length; i++)
	{
        asc[i] = message[i];
    }
 
    for (int i=0; i<length; i++)
	{
        code[i] = bigmod(asc[i], EEE, NNN );   //密文C = M^e (mod N)
    }
    string newmiwen=lltoString(*code);
    return newmiwen;
}

//利用RSA原理进行解密 
string RSAdec(long long code[], int n)
{  
    long long  *asc = new long long[n];  
    string message;  
    for (int i=0; i<n; i++)
	{  
        asc[i] = bigmod(code[i], DDD, NNN);    //明文M = C^d (mod N)  
        message += ( char(asc[i]) );  
    }  
    return message;  
}  

int main() 
{
	while(true)
    {
    	string message;
    long long p,q;
    cout<<"请输入两个超过100的大质数"<<endl; 
    cin>>p>>q;
    cout<<"请输入需要进行RSA加密处理的文本(不包含空格字符)： "<<endl; 
    cin>>message;
    long long *ctext = RSAenc(message,p,q);
    cout<<"使用公钥("<<EEE<<","<<NNN<<")"<<endl; 
    cout<<"对该明文进行RSA加密后的得到： "<< RSAenc1(message,p,q) <<endl;
    
    string ptext = RSAdec(ctext, RSAlength);
    cout<<"使用私钥("<<DDD<<","<<NNN<<")"<<endl;
    cout <<"再对该密文进行RSA解密后得到： "<< ptext << endl;
    
	}
    return 0;
}

