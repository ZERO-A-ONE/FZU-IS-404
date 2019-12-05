#include<iostream>
#include<vector>
#include<queue>
using namespace std;
/*
size():返回堆内元素个数
empty():如果堆为空，返回真，否则返回假
top():返回堆顶元素
pop():删除堆顶元素，自动整理
push(x):插入一个元素x，自动整理
大根堆的调用：priority_queue<int>a;
小根堆的调用：priority_queue<int,vector<int>,greater<int> > a;
*/
int main() {
	priority_queue<int, vector<int>, greater<int> > a;
	for (int i = 0; i < 20; i++) {
		a.push(i);
	}
	for (int i = 0; i < 20; i++) {
		cout << a.top() << " ";
		a.pop();
	}
	return 0;
}