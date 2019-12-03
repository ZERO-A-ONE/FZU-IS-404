#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct SNode* Stack;
const int MAXSIIZE = 1000;
struct SNode
{
	int Data;
	Stack Next;
};
Stack CreateStack() {
	Stack S;
	S = (Stack)malloc(sizeof(SNode));
	S->Next = NULL;
	return S;
}
int IsEmpty(Stack S) {
	return (S->Next == NULL);
}
void Push(int item, Stack S) {
	Stack Tmpcell;
	Tmpcell = (Stack)malloc(sizeof(SNode));
	Tmpcell->Data = item;
	Tmpcell->Next = S->Next;      
	S->Next = Tmpcell;
}
int Pop(Stack S) {
	Stack FirstCell;
	int TopElem;
	if (IsEmpty(S)) {
		cout << "Empty" << endl;
		return NULL;
	}
	else
	{
		FirstCell = S->Next;
		S->Next = FirstCell->Next;
		TopElem = FirstCell->Data;
		free(FirstCell);
		return TopElem;
	}
}
int main() {
	cout << "Hello World!" << endl;
	return 0;
}
