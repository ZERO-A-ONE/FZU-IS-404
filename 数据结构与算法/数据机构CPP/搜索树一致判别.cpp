#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct TreeNode* Tree;
const int MAXSIIZE = 1000;
struct TreeNode {
	int v;
	Tree Left;
	Tree Right;
	int flag;
};
Tree Insert(int X, Tree BST) {
	if (!BST) {
		BST = new TreeNode;
		BST->v = X;
		BST->Left = BST->Right = NULL;
	}
	else {
		if (X < BST->v) {
			BST->Left = Insert(X, BST->Left);
		}
		else if (X > BST->v) {
			BST->Right = Insert(X, BST->Right);
		}
	}
	return BST;
}
Tree NewNode(int V) {
	Tree T = new TreeNode;
	T->v = V;
	T->Left = T->Right = NULL;
	T->flag = 0;
	return T;
}
Tree MakeTree(int N) {
	Tree T;
	int i, V;
	cin >> V;
	T = NewNode(V);
	for (i = 0; i < N; i++) {
		cin >> V;
		T = Insert(V,T);
	}
	return T;
}
int check(Tree T, int V) {
	if (T->flag) {
		if (V < T->v)
			return check(T->Left, V);
		else if (V > T->v)
			return check(T->Right, V);
	}
	else
	{
		if (V == T->v) {
			T->flag = 1;
			return 1;
		}
		else return 0;
	}
}
void ResetT(Tree T) {
	if (T->Left)
		ResetT(T->Left);
	if (T->Right)
		ResetT(T->Right);
	T->flag = 0;
}void FreeTree(Tree T) {
	if (T->Left)
		FreeTree(T->Left);
	if (T->Right)
		FreeTree(T->Right);
	free(T);
}
int Judge(Tree T, int N) {
	int i, V, flag = 0;
	cin >> V;
	if (V != T->v)
		flag = 1;
	else
	{
		T->flag = 1;
	}
	for (i = 1; i < N; i++) {
		cin >> V;
		if ((!flag) && (!check(T, V)))
			flag = 1;
	}
	if (flag)
		return 0;
	else
	{
		return 1;
	}
}
int main() {
	int N, L, i;
	Tree T;
	cin >> N;
	while (N)
	{
		cin >> L;
		T = MakeTree(L);
		for (i = 0; i < L; i++) {
			if (Judge(T, N))
				cout << "Yes" << endl;
			else
				cout << "No" << endl;
			ResetT(T);
		}
		FreeTree(T);
		cin >> N;
	}
	return 0;
}