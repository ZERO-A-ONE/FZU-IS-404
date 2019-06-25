#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	char str[3][20];
	char string[20];
	int i;
	for(i=0;i<3;i++)
	{
		cin >> str[i];
	}
	if(strcmp(str[0],str[1])>0)
		strcpy(string,str[0]);
	else
		strcpy(string,str[1]);
	if(strcmp(str[2],string)>0)
		strcpy(string,str[2]);
	cout << "The largest string is:"<< endl << string;
	return 0;
}
