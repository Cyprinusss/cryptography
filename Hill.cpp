#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;

string Hill(int judge,string s) 
{
	string ans;
	int k[3][3]={{17,17,5},{21,18,21},{2,2,19}};  //设定加密秘钥矩阵K
	int invk[3][3]={{4,9,15},{15,17,6},{24,0,17}};  //求出加密矩阵K的逆 作为解密秘钥 
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

int main()
{
	while(true)
	{
		int i;
	string s;
	cin>>i>>s;
	cout<<Hill(i,s)<<endl;
	}
}
