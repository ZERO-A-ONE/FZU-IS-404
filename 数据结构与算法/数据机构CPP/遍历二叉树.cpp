#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct TreeNode* BinTree;
typedef BinTree Position;
struct TreeNode {
	int Data;
	BinTree Left;
	BinTree Right;
};
void PreOrderTraversal(BinTree BT) {
	if (BT) {
		cout << BT->Data <<" ";
		PreOrderTraversal(BT->Left);
		PreOrderTraversal(BT->Right);
	}
}
void InOrderTraversal(BinTree BT) {
	if (BT) {
		InOrderTraversal(BT->Left);
		cout << BT->Data << " ";
		InOrderTraversal(BT->Right);
	}
}
void PostOrderTraversal(BinTree BT) {
	if (BT) {
		PostOrderTraversal(BT->Left);
		PostOrderTraversal(BT->Right);
		cout << BT->Data << " ";
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
	PreOrderTraversal(BT);
	cout << endl;
	InOrderTraversal(BT);
	cout << endl;
	PostOrderTraversal(BT);
	cout << endl;
	return 0;
}