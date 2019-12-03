#include<iostream>
#include<stdlib.h>
#define MaxSize 1000
using namespace std;
typedef struct QNode* Queue;
typedef struct TreeNode* BinTree;
struct QNode {
	BinTree Data[MaxSize];
	int rear;
	int front;
};
struct TreeNode {
	int Data;
	BinTree Left;
	BinTree Right;
};
int IsEmpty(Queue PtrQ) {
	if (PtrQ->Data[0] == NULL)
		return 1;
	else {
		return 0;
	}
}
void AddQ(Queue PtrQ, BinTree item) {
	if ((PtrQ->rear + 1) % MaxSize == PtrQ->front) {
		cout << "Max" << endl;
		return;
	}
	PtrQ->rear = (PtrQ->rear + 1) % MaxSize;
	PtrQ->Data[PtrQ->rear] = item;
}
BinTree DeleteQ(Queue PtrQ) {
	if (PtrQ->front = PtrQ->rear) {
		cout << "Max" << endl;
		return NULL;
	}
	else {
		PtrQ->front = (PtrQ->front + 1) % MaxSize;
		return PtrQ->Data[PtrQ->front];
	}
}
void LevelOrderTraversal(BinTree BT) {
	Queue Q = new QNode;
	Q->front = 0;
	Q->rear = 1;
	BinTree T;
	if (!BT)
		return;
	AddQ(Q, BT);
	while (!IsEmpty(Q))
	{
		T = DeleteQ(Q);
		cout << T->Data << endl;
		if (T->Left)
			AddQ(Q, T->Left);
		if (T->Right)
			AddQ(Q, T->Right);
	}
}
int main()
{
	BinTree BT = new TreeNode;
	BinTree BTL = (BinTree)malloc(sizeof(TreeNode));
	BinTree BTR = (BinTree)malloc(sizeof(TreeNode));
	BT->Data = 1;
	BTL->Data = 2;
	BTR->Data = 3;
	BTL->Left = NULL;
	BTL->Right = NULL;
	BTR->Left = NULL;
	BTR->Right = NULL;
	BT->Left = BTL;
	BT->Right = BTR;
	LevelOrderTraversal(BT);
	return 0;
}