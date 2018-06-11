#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
 
using namespace std;
//SHA1哈希加密
//输入任意字符串：中英文数字
//返回定长度哈希串 
//循环移位函数 
unsigned circleShift(const unsigned& word,const int& bits)
{
    return (word<<bits) | ((word)>>(32-bits));   
}

//四个非线性函数 
unsigned sha1Fun(const unsigned& B,const unsigned& C,const unsigned& D,const unsigned& t)
{//其中t为当前加密步骤（取值0-79） B C D为数据 
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
    while (str.size()*8 % 512 != 448) // 每个字节8位,所以要乘8
        str+=(char)0;  //补0 使添0后的数字长度模512余448 
    // 写入原始数据长度
    for (int i=56; i>=0; i-=8)
        str+=(unsigned char)((strRaw.size()<<3) >> i);  
        //在str后面附上一个64位数来表示原始数据的长度 
    //4个关键常量K[4]  ABCDET 6个字缓冲  80字缓冲区W[80] 
    const unsigned K[4]={0x5a827999,0x6ed9eba1,0x8f1bbcdc,0xca62c1d6}; 
    unsigned A(0x67452301),B(0xefcdab89),C(0x98badcfe),D(0x10325476),E(0xc3d2e1f0),T(0);
    unsigned W[80]={0};
 
    // 每次取64字节,共512位
    for (unsigned i=0; i!=str.size(); i+=64)
	{
        // 前16个字为原始数据
        for (unsigned t=0; t!=16; ++t)
		{
            // 将4个8位数据放入一个32位变量中
            //64字节填充至w[0-15] 
            W[t]=((unsigned)str[i+4*t] & 0xff)<<24 |
                 ((unsigned)str[i+4*t+1] & 0xff)<<16 |
                 ((unsigned)str[i+4*t+2] & 0xff)<<8 |
                 ((unsigned)str[i+4*t+3] & 0xff);
        }
 
        //填充W[16-79] 
        for (unsigned t=16; t!=80; ++t)
            W[t]=circleShift(W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16],1);
        //填充完毕，对W进行80轮加密计算 
        for (unsigned t=0; t!=80; ++t)
		{
            T=circleShift(A,5) + sha1Fun(B,C,D,t) + E + W[t] + K[t/20];
            E=D; 
            D=C; 
            C=circleShift(B,30); 
            B=A; 
            A=T;
        }
        //再将5个缓冲区ABCDE加上它们的原始数据 
        A+=0x67452301;B+=0xefcdab89;C+=0x98badcfe;D+=0x10325476;E+=0xc3d2e1f0;
    }
    stringstream ss;
    ss<<setw(8)<<setfill('0')<<hex<<A<<B<<C<<D<<E;
    ss>>str;
    return str;
}
 
int main()
{   
    while(true)
    {
    	string str;
    cout<<"请输入需要使用SHA(安全哈希算法)加密的文本 : "<<endl;
    cin>>str; 
    cout<<"通过SHA1算法加密得到的签名:  "<<endl;
	cout<<SHA(str)<<endl;
	}
    return 0;
}
