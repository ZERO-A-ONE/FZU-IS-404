#include <iostream>
#include <cstdio>
using namespace std;
 
int main()
{
    string complex;
	cin>>complex;
	if(complex[complex.length()-1]!='i')//判断输入的复数虚部是否为0，只需判断末尾字符有无"i"
	{
		cout<<"complex "<<complex<<endl<<"the real part is "<<complex<<endl;
		cout<<"and the imaginary part is 0";
		return 0;
	}
	int flag = 0;
	for(int i=1;complex[i];i++)//判断输入的复数实部是否为0，转化为判断字符中有无"+"/"-"
		if(complex[i]=='+'||complex[i]=='-')
		{
			flag = 1;
			break;
		}
	if(flag==0)
	{
		cout<<"complex "<<complex<<endl<<"the real part is 0"<<endl;
		cout<<"and the imaginary part is ";
		if(complex[0]=='i')
			cout<<"1";
		else if(complex[0]=='-'&&complex[1]=='i')
			cout<<"-1";
		else
			for(int i=0;i<complex.length()-1;i++)
				cout<<complex[i];
 
		return 0;
	}
 
	//正常情况下实部虚部的提取
    char real[100] = {0},imag[100] = {0};
    real[0] = complex[0];//把最开始的正负号避开
    int i = 1;
    while(1)//以"+"、"-" 为结尾提取实部
    {
        if(complex[i]=='+'||complex[i]=='-') break;
        real[i] = complex[i];
		i++;
    }
    int j = 0;
    while(1)//以"i"结尾提取虚部
    {
    	if(complex[i]=='i')break;
        imag[j++] = complex[i++];
    }
    cout<<"complex "<<complex<<endl<<"the real part is "<<real<<endl;
    cout<<"and the imaginary part is ";
	if(imag[0]=='+'&&imag[1]=='\0')
		printf("1");
	else if(imag[0]=='-'&&imag[1]=='\0')
		printf("-1");
	else if(imag[0]=='+')
		printf("%s",imag+1);
	else
		printf("%s",imag);
}
//“输入保证合法”还是有几个小坑的：
//1、实部为0；
//2、虚部为0；
//3、直接输0.