#include<iostream>
#include <algorithm>
using namespace std;
/*
sort(begin,end);	表示一个范围，数组a按升序排序，默认升序
sort(begin,end,compare);	降序
sort(A, A + 100, greater<int>());	降序排列
sort(A, A + 100, less<int>());	升序排列
*/
bool compare(int a, int b)
{
	return a < b;   //升序排列，如果改为return a>b，则为降序
}
int main() {
	int a[10] = { 2,4,1,23,5,76,0,43,24,65 }, i;
	for (i = 0; i < 10; i++)
		cout << a[i] << " ";
	cout << endl;
	sort(a, a + 10, compare);
	for (i = 0; i < 10; i++)
		cout << a[i] << " ";
	cout << endl;
	return 0;
}