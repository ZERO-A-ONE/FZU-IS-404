#include<iostream>
#include<math.h>
using namespace std;
class complex
{
	private:
		int real,imag;
		public:
			complex(int r=0,int i=0)
			{
				real=r;;
				imag=i;
			}
			void set(int r,int i)
			{
				real=r;
				imag=i;
				
			}
			bool operator>(complex &a)
			{
				double m1,m2;
				m1=real*real+imag*imag;
				m2=a.real*a.real+a.imag*a.imag;
				if(m1>m2)
				return true;
				else
				return false;
			}
};
int main()
{
	int r1,i1,r2,i2;
	complex a1,a2;
	cin>>r1>>i1>>r2>>i2;
	while(1)
	{
		if(r1==r2&&i1==i2&&r1==i1&&r1==0)
		break;
		a1.set(r1,i1);
		a2.set(r2,i2);
		if(a1>a2)
		cout<<"true"<<endl;
		else
		cout<<"false"<<endl;
		cin>>r1>>i1>>r2>>i2;
	}
	return 0;
}
