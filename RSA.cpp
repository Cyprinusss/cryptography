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

string lltoString(long long t)
{
    std::string result;
    std::strstream ss;
    ss <<  t;
    ss >> result;
    return result;
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

string RSAenc1 (string message,long long p,long long q)
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
    string newmiwen=lltoString(*code);
    return newmiwen;
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

int main() 
{
	while(true)
    {
    	string message;
    long long p,q;
    cout<<"��������������100�Ĵ�����"<<endl; 
    cin>>p>>q;
    cout<<"��������Ҫ����RSA���ܴ�����ı�(�������ո��ַ�)�� "<<endl; 
    cin>>message;
    long long *ctext = RSAenc(message,p,q);
    cout<<"ʹ�ù�Կ("<<EEE<<","<<NNN<<")"<<endl; 
    cout<<"�Ը����Ľ���RSA���ܺ�ĵõ��� "<< RSAenc1(message,p,q) <<endl;
    
    string ptext = RSAdec(ctext, RSAlength);
    cout<<"ʹ��˽Կ("<<DDD<<","<<NNN<<")"<<endl;
    cout <<"�ٶԸ����Ľ���RSA���ܺ�õ��� "<< ptext << endl;
    
	}
    return 0;
}

