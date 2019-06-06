#include<iostream>
#include<cmath>
#include<stdio.h>
using namespace std;
class point
{
	private:
		float x;
		float y;
	public:
		point(float a,float b):x(a),y(b){}
		float showx(){
			return x;
		}
		float showy(){
			return y;
		}
};
class Distance{
	private:
		float x1,y1;
		float x2,y2;
	public:
		Distance(float a1,float a2,float b1,float b2):x1(a1),y1(a2),x2(b1),y2(b2){}
		void math()
		{
			float dis = 0;
			dis=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
			printf("%.3lf",dis);
		}
};
int main()
{
	float x1,y1,x2,y2;
	cin>>x1>>y1>>x2>>y2;
	point p1(x1,y1);
	point p2(x2,y2); 
	Distance dis(p1.showx(),p1.showy(),p2.showx(),p2.showy());
	dis.math();
	return 0;
}