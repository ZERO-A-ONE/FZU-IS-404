#include<stdio.h>
int main()
{
	char s[1000];
	gets(s);
	int i=0;
	while(s[i]!='\0')
	{
		if(i==0)
		{
			if((int)s[i]>=97&&(int)s[i]<=122)
			{
				int c=(int)s[i];
				c=c-32;
				s[i]=c;	
			}	
		}
		else
		{
			int k=i-1;
			if((int)s[k]==32)
			{
				if((int)s[i]>=97&&(int)s[i]<=122)
				{
					int c=(int)s[i];
					c=c-32;
					s[i]=c;
				}
			}
			else
			{
				if((int)s[i]>=65&&(int)s[i]<=90)
				{
					int c=(int)s[i];
					c=c+32;
					s[i]=c;
				}
			}		
		}
		i++;	
	}
	i=0;
	while(s[i]!='\0')
	{
		printf("%c",s[i]);
		i++;	
	}	
	return 0;
} 
