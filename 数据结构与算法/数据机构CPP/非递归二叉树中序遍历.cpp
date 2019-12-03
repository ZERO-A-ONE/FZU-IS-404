#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct TreeNode* BinTree;
typedef struct SNode* Stack;
typedef BinTree Position;
const int MAXSIIZE = 1000;
struct TreeNode {
	int Data;
	BinTree Left;
	BinTree Right;
};
struct SNode
{
	BinTree Data[MAXSIIZE];
	int Top;
};
void Push(Stack PtrS, BinTree item) {
	if (PtrS->Top == MAXSIIZE - 1) {
		cout << "Error" << endl;
		return;
	}
	else
	{
		PtrS->Data[++(PtrS->Top)] = item;
	}
}
BinTree Pop(Stack PtrS) {
	if (PtrS->Top == -1) {
		cout << "Error" << endl;
		return NULL;
	}
	else
	{
		return(PtrS->Data[(PtrS->Top)--]);
	}
}
void InOrderTraversal_ND(BinTree BT) {
	BinTree T = BT;
	Stack S = new SNode;
	S->Top = -1;
	while (T || (S->Top!= -1) ){
		while (T)
		{
			Push(S,T);
			T = T->Left;
		}
		if (S->Top != -1) {
			T = Pop(S);
			cout << T->Data << " ";
			T = T->Right;
		}
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
	InOrderTraversal_ND(BT);
	return 0;
}