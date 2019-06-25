#include<iostream>
#include<cmath>
using namespace std;
class point_1d
{
	protected:
		double x;
		public:
			point_1d(double x=0):x(x){}
			double dist(point_1d x0,point_1d x1)
			{
				double d;
				d=x0.x-x1.x;
				return d>0?d:-d;
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
			double dist(point_2d x0,point_2d x1)
			{
				double d;
				d=sqrt((x0.x-x1.x)*(x0.x-x1.x)+(x0.y-x1.y)*(x0.y-x1.y));
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
			double dist(point_3d x0,point_3d x1)
			{
				return sqrt((x0.x-x1.x)*(x0.x-x1.x)+(x0.y-x1.y)*(x0.y-x1.y)+(x0.z-x1.z)*(x0.z-x1.z));
			}
			void disp()
			{
				cout<<"("<<x<<","<<y<<","<<z<<")";
			}
 } ;
int main()
{
	int ty;
	point_1d a1,b1;
	point_2d a2,b2;
	point_3d a3,b3;
	cin>>ty;
	double x0,x1,y0,y1,z0,z1;
	while(ty>0)
	{
		switch(ty)
		{
			case 1: 
			 	cin>>x0>>x1;a1=point_1d(x0);b1=point_1d(x1);
				cout<<"Distance from Point ";a1.disp();cout<<" to Point ";b1.disp();cout<<" is "<<a1.dist(a1,b1)<<endl;
				break;
			case 2: 
				cin>>x0>>y0>>x1>>y1;a2=point_2d(x0,y0);b2=point_2d(x1,y1);
				cout<<"Distance from Point";a2.disp();cout<<" to Point";b2.disp();cout<<" is "<<a2.dist(a2,b2)<<endl;break;
			case 3: 
				cin>>x0>>y0>>z0>>x1>>y1>>z1;a3=point_3d(x0,y0,z0);b3=point_3d(x1,y1,z1);
				cout<<"Distance from Point";a3.disp();cout<<" to Point";b3.disp();cout<<" is "<<a3.dist(a3,b3)<<endl;break;
		
		}
		cin>>ty;
	}
	return 0;
 }
