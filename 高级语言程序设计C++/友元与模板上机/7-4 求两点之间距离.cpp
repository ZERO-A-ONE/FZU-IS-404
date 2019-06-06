#include<iostream>
#include<cmath>
#include<stdio.h>
using  namespace std;
int main()
{
	double x1,y1,x2,y2;
	cin >> x1 >> y1 >> x2 >> y2;
	double end = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	printf("%.2lf",end);
}