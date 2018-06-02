#include<iostream>
#include<string>
#include<cstring>
using namespace std;

//ʵ��playfair����
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

int main()
{
	string s="monarchy";
//	string result=tableCreate(s);
//	cout<<result<<endl;
	
	string str="ibsupmna";
//	cout<<CTP(str)<<endl;
	cout<<Playfair(s,str,1)<<endl;
	//balloon
	//ibsupmna
	return 0;
}
