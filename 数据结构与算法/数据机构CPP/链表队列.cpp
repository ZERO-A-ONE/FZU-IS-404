#include<iostream>
#include<stdlib.h>
#define MaxSize 1000
using namespace std;
typedef struct QNode* Queue;
struct Node {
	int Data;
	Node* Next;
};
struct QNode {
	Node* rear;
	Node* front;
};
int DeleteQ(Queue PtrQ) {
	Node* FrontCell;
	int FrontElem;
	if (PtrQ->front == NULL) {
		cout << "ERROR" << endl;
	}
	FrontCell = PtrQ->front;
	if (PtrQ->front == PtrQ->rear) {
		PtrQ->front = PtrQ->rear = NULL;
	}
	else
	{
		PtrQ->front = PtrQ->front->Next;
	}
	FrontElem = FrontCell->Data;
	free(FrontCell);
	return FrontElem;
}
int main()
{
	return 0;
}