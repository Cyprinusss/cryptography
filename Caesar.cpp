#include<iostream>
#include<string>
#include<cstring>
using namespace std;

//Caesar����ļ��ܺͽ���
//���룺 
//str1 �����ַ�����k ��λ����
//type ���ܻ�������ͣ�0Ϊ���ܣ�1Ϊ���� 
//���أ�
//str2 ���ص��ַ������� 
string* Caesar(string str1,int k,int type)
{
	
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
	    }
	}
	return str2;
}


int main()
{
	string clear="FGHfghijkl";
	int l=clear.length();
	string *s=Caesar(clear,5,1); 
	for(int i=0;i<l;i++)
	{
		cout<<s[i];
	}
}


