#include <iostream>
#include<string>
#include <algorithm>
using namespace std;
int check(string str,string wd);
void trim(string &s);
void clen(string &s);
int main()
{
	string word,str1,str2,str3;
	cin >> word;
	cin.get();
	getline(cin,str1);
	cin.clear();
	getline(cin,str2);
	cin.clear();
	getline(cin,str3);
	cin.clear();
	clen(word);
	transform(word.begin(),word.end(),word.begin(),::tolower);
	transform(str1.begin(),str1.end(),str1.begin(),::tolower);
	transform(str2.begin(),str2.end(),str2.begin(),::tolower);
	transform(str3.begin(),str3.end(),str3.begin(),::tolower);
	trim(str1);
	trim(str2);
	trim(str3);
	int number1 = check(str1,word);
	int number2 = check(str2,word);
	int number3 = check(str3,word);
	cout<<number1<<endl;
	cout<<number2<<endl;
	cout<<number3<<endl;
	return 0;
}
void trim(string &s)//清理只剩字母 
{
	int index = 0;
	if( !s.empty())
 	{
		while( (index = s.find(' ',index)) != string::npos)
		{
			s.erase(index,1);
		}
		index = 0;
		while( (index = s.find(',',index)) != string::npos)
		{
			s.erase(index,1);
		}
		index = 0;
		while( (index = s.find('.',index)) != string::npos)
		{
			s.erase(index,1);
		}
		index = 0;
		while( (index = s.find('!',index)) != string::npos)
		{
			s.erase(index,1);
		}
		index = 0;
		while( (index = s.find('?',index)) != string::npos)
		{
			s.erase(index,1);
		}
		index = 0;
		while( (index = s.find('\'',index)) != string::npos)
		{
			s.erase(index,1);
		}
	}
}
void clen(string &s)//清理重复字符 
{
	int sz[123]={0};
	int len = s.length();
	for(int i = 0;i<len;i++)
	{
		sz[(int)s[i]]++;
	}
	for(int i = 0;i<123;i++)
	{
		if(sz[i]>1)
		{
			int index = 0;
			while( ((index = s.find((char)i,index)) != string::npos) && sz[i]>1)
			{
				s.erase(index,1);
				sz[i]--;
			}
		}
	}
}
int check(string str,string wd){
	int wdlen = wd.length();
	int strlen = str.length();
	int number = 0;
	int number1 = 0;
	int number2 = 0;
	if(strlen < 20){
		for(int i = 0;i<wdlen;i++)
		{
			for(int j = 0;j<strlen;j++)
			{
				if(str[j]==wd[i])
				{
					number++;
				}
			}
		}
	}
	else{
		for(int i = 0;i<wdlen;i++)
		{
			for(int j = 0;j<20;j++)
			{
				if(str[j]==wd[i])
				{
					number1++;
				}
			}
		}
		for(int i = 0;i<wdlen;i++)
		{
			for(int j = strlen-20;j<strlen;j++)
			{
				if(str[j]==wd[i])
				{
					number2++;
				}
			}
		}
		if(number1>number2)
			number = number1;
		else
			number = number2;
	} 
	return number;
}