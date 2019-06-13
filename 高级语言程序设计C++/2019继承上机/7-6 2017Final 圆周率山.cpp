#include <iostream>
#include <string>
using namespace std;
string pi = "314159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196";
int main()
{
	int n;
    cin>>n;
    int count=0;
    for(int i=0;i<n;i++)
    {
    	for(int j=0;j<n-1-i;j++)
    	cout<<" ";
    	for(int j=0;j<2*i+1;j++)
    	{
    		cout<<pi[count];
    		count++;
    	}
    	cout<<endl;
    }
    return 0;
}