#include<iostream>
#include<stack>
using namespace std;
/*
s.push(item);		//将item压入栈顶
s.pop();			//删除栈顶的元素，但不会返回
s.top();			//返回栈顶的元素，但不会删除
s.size();			//返回栈中元素的个数
s.empty();			//检查栈是否为空，如果为空返回true，否则返回false 
*/
int main() {
	stack<int> s;
	int num;
	cin >> num;
	s.push(num);
	cout << "The Stack has " << s.size() << endl;
	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
	cout << "\nNow the size is " << s.size() << endl;
	return 0;
}