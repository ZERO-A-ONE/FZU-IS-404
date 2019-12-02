#include<iostream>
#include<stdlib.h >
using namespace std;
typedef struct DSNode* DStack;
const int MAXSIIZE = 1000;
struct DSNode
{
	int Data[MAXSIIZE];
	int Top1;
	int Top2;
};
void Push(DStack PtrS, int item,int Tag) {
	if (PtrS->Top2 - PtrS->Top1 == 1) {
		cout << "No Empty" << endl;
		return;
	}
	if (Tag == 1) {
		PtrS->Data[++(PtrS->Top1)] = item;
	}
	else
	{
		PtrS->Data[--(PtrS->Top2)] = item;
	}
}
int Pop(DStack PtrS, int Tag) {
	if (Tag == 1) {
		if (PtrS->Top1 == -1) {
			cout << "1 is Empty" << endl;
			return NULL;
		}
		else
		{
			return PtrS->Data[(PtrS->Top1)--];
		}
	}
	else
	{
		if (PtrS->Top2 == MAXSIIZE) {
			cout << "2 is Empty" << endl;
			return NULL;
		}
		else
		{
			return PtrS->Data[(PtrS->Top2)++];
		}
	}
}
int main() {
	cout << "Hello World!" << endl;
	return 0;
}
