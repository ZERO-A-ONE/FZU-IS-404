#include<iostream>
#include<stdlib.h >
using namespace std;
typedef struct LNode* List;
const int MAXSIIZE = 1000;
struct LNode
{
	int Data;
	List Next;
};
int Length(List PtrL) {
	List p = PtrL;
	int j = 0;
	while (p)
	{
		p = p->Next;
		j++;
	}
	return j;
}
List FindKth(int K, List PtrL) {
	List p = PtrL;
	int i = 1;
	while (p != NULL && i < K)
	{
		p = p->Next;
		i++;
	}
	if (i == K)
		return p;
	else return NULL;
}
List Find(int X, List PtrL) {
	List p = PtrL;
	while (p!=NULL && p->Data != X)
	{
		p = p->Next;
	}
	return p;
}
List Insert(int X, int i, List PtrL) {
	List p, s;
	if (i == 1) {
		s = (List)malloc(sizeof(LNode));
		s->Data = X;
		s->Next = PtrL;
		return s;
	}
	p = FindKth(i - 1, PtrL);
	if (p == NULL) {
		cout << "Error argv" << endl;
		return NULL;
	}
	else {
		s = (List)malloc(sizeof(LNode));
		s->Data = X;
		s->Next = p->Next;
		p->Next = s;
		return PtrL;
	}
}
List Delete(int i, List PtrL) {
	List p, s;
	if (i == 1) {
		s = PtrL;
		if (PtrL != NULL)
			PtrL = PtrL->Next;
		else
		{
			return NULL;
		}
		free(s);
		return PtrL;
	}
	p = FindKth(i - 1, PtrL);
	if (p == NULL) {
		cout << "Error i-1 NULL" << endl;
		return NULL;
	}
	else if(p->Next==NULL){
		return NULL;
	}
	else
	{
		s = p->Next;
		p->Next = s->Next;
		free(s);
		return PtrL;
	}
}
int main() {
	cout << "Hello World!" << endl;
	return 0;
}
