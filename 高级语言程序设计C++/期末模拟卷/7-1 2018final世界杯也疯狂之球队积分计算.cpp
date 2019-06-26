#include <iostream>
#include <string>
using namespace std;
int main() 
{
	int ty;cin>>ty;
	int score = 0,win = 0;
    int x,y;
	string s;
    getline(cin,s);
    int num = s.size()/4;
	switch (ty)
	{
		case 1:
		{
			for(int i=1;i<s.size();i += 4)
			{
				x = s[i] - '0';
				y = s[i+2] - '0';
				 if(x>y)
			{
				score+=3;
				win+=x-y;
			}
            else if(x==y)
			{score++;}
            else if(x<y)
			{win+= x-y;}
			}
			cout<<score<<" "<<win;
			break;
		}
		case 2:
		{
			for(int i=1;i<s.size();i += 4)
			{
				x = s[i] - '0';
				y = s[i+2] - '0';
			  	if(y>x){score+=3;win+=y-x;}
            	else if(x==y){score++;}
            	else if(y<x){win+=y-x;}
			}
			cout<<score<<" "<<win;
			break;
		}
	}
	
	return 0;
}