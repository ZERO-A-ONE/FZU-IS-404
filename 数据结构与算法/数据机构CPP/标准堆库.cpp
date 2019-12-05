#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;
/*
make_heap: 根据指定的迭代器区间以及一个可选的比较函数，来创建一个heap O(N)
push_heap: 把指定区间的最后一个元素插入到heap中 O(logN)
pop_heap: 弹出heap顶元素, 将其放置于区间末尾 O(logN)
sort_heap：堆排序算法，通常通过反复调用pop_heap来实现 N*O(logN)
is_heap: 判断给定区间是否是一个heap O(N)
is_heap_until: 找出区间中第一个不满足heap条件的位置 O(N)
*/
int main() {
	double a1[6] = { 2.5,10.0,3.5,6.5,8.0,12.0 };
	vector<double> test(a1, a1 + 6);
	make_heap(test.begin(), test.end(), greater<int>());
	//greater函数是在 functional 库中的
	//默认使用的为less函数建立大顶堆，greater函数建立小顶堆
	for (int i = 0; i < test.size(); i++) {
		cout<<test[i]<<" ";
	}
	cout << endl;
	test.push_back(0.5);
	push_heap(test.begin(), test.end(), greater<double>());
	for (int i = 0; i < test.size(); i++) {
		cout << test[i] << " ";
	}
	cout << endl;
	pop_heap(test.begin(), test.end(), greater<double>());
	for (int i = 0; i < test.size(); i++) {
		cout << test[i] << " ";
	}
	cout << endl;
	return 0;
}