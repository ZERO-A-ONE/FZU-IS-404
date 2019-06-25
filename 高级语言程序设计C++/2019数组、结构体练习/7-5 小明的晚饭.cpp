#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
struct Pooks
{
   	string name;
  	int price;
};
int main()
{
  int N=0,M=0;
  cin >> N;
  cin >> M;
  int flag = 0;
  Pooks list[M],sk;
  for(int i = 0;i < M;i++)
  {
  		cin >> list[i].name;
  		cin >> list[i].price;
  }
  for(int i=0; i<M-1; i++)
	{
    	for(int j=0; j<M-1-i; j++)
    	{
    		if(list[j].price<list[j+1].price) 
			{
                sk = list[j];
                list[j]=list[j+1];
                list[j+1]=sk;
            }
		}     
	}
  for(int i = 0;i < M;i++)
  {
		if(N < list[M-1].price&&i==0)
    	{
    		cout << "chitu";
    		break;
		}
    	if(N >= list[i].price) 
		{
            N = N - list[i].price;
            cout << list[i].name << endl;
        }
  }
  return 0;
}