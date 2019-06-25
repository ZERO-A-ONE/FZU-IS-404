 #include<iostream>
#include<cmath>
using namespace std;
class point_1d
{
	protected:
		double x;
		public:
			point_1d(double x=0):x(x){}
			double dist()
			{
				return x>0?x:-x;
			}
			void disp()
			{
				cout<<x;
			}
			
};
class point_2d:public point_1d
{
	protected:
		double y;
		public:
			point_2d(double x1=0,double y1=0):point_1d(x1)
			{
				y=y1;
			}
			double dist()
			{
				double d;
				d=sqrt(x*x+y*y);
				return d;
			}
			void disp()
			{
				cout<<"("<<x<<","<<y<<")";
			}
};
class point_3d:public point_2d
{
	protected:
		double z;
		public:
			point_3d(double x1=0,double y1=0,double z1=0):point_2d(x1,y1)
			{
				z=z1;
			}
			double dist()
			{
				return sqrt(x*x+y*y+z*z);
			}
			void disp()
			{
				cout<<"("<<x<<","<<y<<","<<z<<")";
			}
 } ;
int main()
{
	int ty;
	point_1d a1;
	point_2d a2;
	point_3d a3;
	cin>>ty;
	double x,y,z;
	while(ty>0)
	{
		switch(ty)
		{
			case 1: cin>>x;a1=point_1d(x);cout<<"Distance from Point ";a1.disp();cout<<" to original point is "<<a1.dist()<<endl;break;
			case 2: cin>>x>>y;a2=point_2d(x,y);cout<<"Distance from Point";a2.disp();cout<<" to original point is "<<a2.dist()<<endl;break;
			case 3: cin>>x>>y>>z;a3=point_3d(x,y,z);cout<<"Distance from Point";a3.disp();cout<<" to original point is "<<a3.dist()<<endl;break;
		
		}
		cin>>ty;
	}
	return 0;
 }
