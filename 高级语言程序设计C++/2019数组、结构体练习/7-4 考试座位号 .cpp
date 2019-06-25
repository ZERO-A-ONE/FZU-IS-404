#include<iostream>
#include<string>
using namespace std;
struct Pooks
{
   	char zk[17];
  	int sj;
  	int zw;
};
int main()
{
  int N=0,M=0;
  cin >> N;
  Pooks list[N];
  for(int i = 0;i < N;i++)
  {
  		cin >> list[i].zk;
  		cin >> list[i].sj;
  		cin >> list[i].zw;
  }
  cin >> M;
  for(int i = 0;i < M;i++)
  {
  		int temp;
		cin >> temp;
		for(int i = 0;i < N;i++)
		{
			if(list[i].sj == temp)
			{
				cout << list[i].zk << ' '<< list[i].zw << endl;
			}
		}
  }
  return 0;
}