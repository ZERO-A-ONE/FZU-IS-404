#include<iostream>  
#include<algorithm>  
#include<cmath>  
using namespace std;
struct point
{
	double x, y;
} a[4];
bool cmp(point a, point b)
{
	if (a.x != b.x)
		return a.x < b.x;
	return a.y < b.y;
}
double TwoPointDiatance(point a, point b)
{
	return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}
bool IsRightAngle(point a, point b, point c)
{
	double x;
	x = (a.x - b.x)* (a.x - c.x) + (a.y - b.y)*(a.y - c.y);
	if (x < 0.00001)
		return 1;
	else
		return 0;
}
int main()
{
	int t, k;
	double s1, s2, s3, s4;
	while (cin >> a[0].x)
	{
        cin >> a[0].y;
		for(int i = 1;i < 4;i++)
        {
            cin >> a[i].x >> a[i].y;
        }
		sort(a, a + 4, cmp);
		s1 = TwoPointDiatance(a[0], a[2]);
		s2 = TwoPointDiatance(a[0], a[1]);
		s3 = TwoPointDiatance(a[3], a[1]);
		s4 = TwoPointDiatance(a[2], a[3]);
		if (s1 == s2&&s3 == s4&&s1 == s2&&s1 != 0 && IsRightAngle(a[0], a[1], a[2]))//三个条件同时满足（1：四条边相等，2：边不为0，3：有一个直角）
			cout << "yes" << endl;
		else
			cout << "no" << endl;
	}
	return 0;
}