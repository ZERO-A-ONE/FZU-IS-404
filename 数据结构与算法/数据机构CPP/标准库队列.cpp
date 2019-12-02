#include<iostream>
#include<queue>
using namespace std;
/*
q.push(item)           //将item压入队列尾部
q.pop()                //删除队首元素，但不返回
q.front()              //返回队首元素，但不删除
q.back()               //返回队尾元素，但不删除
q.size()               //返回队列中元素的个数
q.empty()              //检查队列是否为空，如果为空返回true，否则返回false
*/
int main() {
	queue<int> q;
	int num;
	cout << "------Test for Queue-------" << endl;
	cout << "Input number:" << endl;
	while (cin >> num)
	{
		q.push(num);
	}
	cout << "Now the Queue has " << q.size() << " numbers." << endl;
	cout << "The first is " << q.front() << endl;
	cout << "The last is " << q.back() << endl;
	cout << "All numbers：" << endl;
	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	cout << "Now the Queue has " << q.size() << " numbers." << endl;
	return 0;
}