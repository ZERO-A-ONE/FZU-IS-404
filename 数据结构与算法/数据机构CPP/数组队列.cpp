#include<iostream>
#include<stdlib.h>
#define MaxSize 1000
using namespace std;
typedef struct QNode* Queue;
struct QNode {
	int Data[MaxSize];
	int rear;
	int front;
};
void AddQ(Queue PtrQ, int item) {
	if ((PtrQ->rear + 1) % MaxSize == PtrQ->front) {
		cout << "Max" << endl;
		return;
	}
	PtrQ->rear = (PtrQ->rear + 1) % MaxSize;
	PtrQ->Data[PtrQ->rear] = item;
}
int DeleteQ(Queue PtrQ) {
	if (PtrQ->front == PtrQ->rear) {
		cout << "Max" << endl;
		return 0;
	}
	else {
		PtrQ->front = (PtrQ->front + 1) % MaxSize;
		return PtrQ->Data[PtrQ->front];
	}
}
int main()
{
	return 0;
}