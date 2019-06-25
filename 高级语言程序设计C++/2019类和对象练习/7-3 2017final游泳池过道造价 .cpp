#include<iostream>
#include<stdio.h>
#define PI 3.14159
using namespace std;
class Circle
{
	private :
		double radius;
		public:
			Circle (double r):radius(r){}
			double area()
			{
				return radius*radius*PI; 
			 } 
};
class Rectangle
{
	private :
	double length,width;
	public:
		Rectangle (double l,double w):length(l),width(w){}
	 	double area()
	 	{
	 		return length*width;
		 }
};
int main()
{
	double radius,length,width;
	cin>>radius>>length>>width;
	Circle circle1(radius);
	Rectangle rectangle1(length,width);
	cout<<(rectangle1.area()-circle1.area())*20;
	
	
	return 0;
}
