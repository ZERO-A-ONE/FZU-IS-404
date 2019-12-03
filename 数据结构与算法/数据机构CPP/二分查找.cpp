#include<iostream>
#include<vector>
using namespace std;
int BinarySearch(vector<int> &vec, int K) {
	int left, right, mid, NoFound = -1;
	left = 0;
	right = vec.size()-1;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (K < vec[mid]) {
			right = mid - 1;
		}
		else if(K > vec[mid]){
			left = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return NoFound;
}
int main()
{
	int a[5] = { 1, 2, 3, 4, 5 };
	vector<int> vec(a, a + 5);
	int b = BinarySearch(vec, 3);
	cout << b;
	return 0;
}