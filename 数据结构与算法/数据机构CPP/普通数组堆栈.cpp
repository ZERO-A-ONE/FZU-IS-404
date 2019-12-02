#include<iostream>
#include<stdlib.h >
using namespace std;
typedef struct SNode* Stack;
const int MAXSIIZE = 1000;
struct SNode
{
	int Data[MAXSIIZE];
	int Top;
};
void Push(Stack PtrS, int item) {
	if (PtrS->Top == MAXSIIZE - 1) {
		cout << "Error" << endl;
		return;
	}
	else
	{
		PtrS->Data[++(PtrS->Top)] = item;
	}
}
int Pop(Stack PtrS) {
	if (PtrS->Top == -1) {
		cout << "Error" << endl;
		return -9999;
	}
	else
	{
		return(PtrS->Data[(PtrS->Top)--]);
	}
}
int main() {
	cout << "Hello World!" << endl;
	return 0;
}
