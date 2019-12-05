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
BinTree Find(int X, BinTree BST) {
	if (!BST)
		return NULL;
	if (X > BST->Data)
		return Find(X, BST->Right);
	else if(X< BST->Data)
	{
		return Find(X, BST->Left);
	}
	else
	{
		return BST;
	}
}
BinTree R_Find(int X, BinTree BST) {
	while (BST)
	{
		if (X > BST->Data)
			return BST = BST->Right;
		else if (X < BST->Data)
		{
			return BST = BST->Left;
		}
		else
		{
			return BST;
		}
	}
	return NULL;
}
BinTree FindMin(BinTree BST) 
{
	if (!BST)
		return NULL;
	else if(!BST->Left)
	{
		return BST;
	}
	else
	{
		return FindMin(BST->Left);
	}
}
BinTree FindMax(BinTree BST)
{
	if (BST)
		while (BST->Right)
		{
			BST = BST->Right;
		}
	return BST;
}
BinTree Insert(int X, BinTree BST) {
	if (!BST) {
		BST = new TreeNode;
		BST->Data = X;
		BST->Left = BST->Right = NULL;
	}
	else {
		if (X < BST->Data) {
			BST->Left = Insert(X, BST->Left);
		}
		else if (X > BST->Data) {
			BST->Right = Insert(X, BST->Right);
		}
	}
	return BST;
}
BinTree Delete(int X, BinTree BST) {
	BinTree Tmp;
	if (!BST) {
		cout << "Error" << endl;
	}
	else if (X < BST->Data) {
		BST->Left = Delete(X, BST->Left);
	}
	else if (X > BST->Data) {
		BST->Right = Delete(X, BST->Right);
	}
	else {
		if (BST->Left && BST->Right) {
			Tmp = FindMin(BST->Right);
			BST->Data = Tmp->Data;
			BST->Right = Delete(BST->Data, BST->Right);
		}
		else
		{
			Tmp = BST;
			if (!BST->Left) {
				BST = BST->Right;
			}
			else if(!BST->Right)
			{
				BST = BST->Left;
			}
			free(Tmp);
		}
	}
	return BST;
}
int main()
{
	BinTree BT = new TreeNode;
	BinTree BTL = (BinTree)malloc(sizeof(TreeNode));
	BinTree BTR = (BinTree)malloc(sizeof(TreeNode));
	BinTree NBT = new TreeNode;
	BT->Data = 2;
	BTL->Data = 1;
	BTR->Data = 3;
	BTL->Left = NULL;
	BTL->Right = NULL;
	BTR->Left = NULL;
	BTR->Right = NULL;
	BT->Left = BTL;
	BT->Right = BTR;
	NBT = Find(2, BT);
	cout << NBT->Data << endl;
	NBT = R_Find(2, BT);
	cout << NBT->Data << endl;
	NBT = FindMin(BT);
	cout << NBT->Data << endl;
	NBT = FindMax(BT);
	cout << NBT->Data << endl;
	NBT = Insert(5, BT);
	NBT = FindMax(NBT);
	cout << NBT->Data << endl;
	NBT = Delete(5, BT);
	NBT = FindMax(NBT);
	cout << NBT->Data << endl;
	return 0;
}