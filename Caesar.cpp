#include<iostream>
#include<string>
#include<cstring>
using namespace std;

//Caesar密码的加密和解密
//输入： 
//str1 输入字符串；k 移位数；
//type 加密或解密类型，0为加密，1为解密 
//返回：
//str2 返回的字符串数组 
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


