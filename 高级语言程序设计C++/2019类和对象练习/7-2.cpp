#include<iostream>
using  namespace std;
class Point
{
	private :
		int x,y;
		public:
			Point(int x1,int y1):x(x1),y(y1){}
			int xi(int x2)
			{
				return x2+x;
			}
			int yi(int y2)
			{
				return y2+y;
			}
};
int main()
{
	int x1,x2,y1,y2;
	cin>>x1>>y1;
	Point point1(x1,y1);
	cin>>x2>>y2;
	cout<<point1.xi(x2)<<" "<<point1.yi(y2);
	return 0;
}
