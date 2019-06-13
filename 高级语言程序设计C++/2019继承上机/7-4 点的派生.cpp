#include <iostream>
#include <string>
using namespace std;
class Point
{
	private:
		int x,y;
	public:
		Point(int x,int y){
			this->x = x;
			this->y = y;
		}
		int getX(){
			return x;
		}
		int getY(){
			return y;
		}
};
class Rectangle:public Point
{
	private:
		int w,h;
	public:
		Rectangle(int x,int y,int w,int h):Point(x,y){
			this->w = w;
			this->h = h;
		}
		int getH(){
			return h;
		}
		int getW(){
			return w;
		}
		void getRightUpPoint(int *xx,int *yy)
		{
			*xx = getX()+getW();
			*yy = getY()+getH();
		}
};
int main()
{
	int x,y,lenght,width;
	int xx,yy;
	cin >> x >> y >> lenght >> width;
	Rectangle R1(x,y,lenght,width);
	Rectangle R2(R1);
	R2.getRightUpPoint(&xx,&yy);
	cout << xx <<" " << yy << endl;
	return 0;
}