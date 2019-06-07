#include<iostream>
#include<math.h>
using namespace std;
template <class T>
class point
{
	private:
		T a,b;
		public:
			point(T a1=0,T b1=0)
			{
				a=a1;
				b=b1;
			}
			void distance()
			{
				T d;
				d=sqrt(a*a+b*b);
				cout<<d;
			}
};
int main()
{
	int ty;
	cin>>ty;
	if(ty==1)
	{
		int a,b;
		cin>>a>>b;
		point <int>a1(a,b);
		a1.distance();
	 } 
	 if(ty==2)
	 {
	 	float a,b;
	 	cin>>a>>b;
	 	point<float>a2(a,b);
	 	a2.distance();
	 }
	 if(ty==3)
	 {
	 	double a,b;
	 	cin>>a>>b;
	 	point<double>a3(a,b);
	 	a3.distance();
	 }
	return 0;
}
