#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct LNode* List;
const int MAXSIIZE = 1000;
struct LNode
{
	int Data[MAXSIIZE];
	int Last;
};
List MakeEmpyt() {
	List PtrL;
	PtrL = (List)malloc(sizeof(LNode));
	PtrL->Last = -1;
	return PtrL;
}
int Find(int X, List PtrL) {
	int i = 0;
	while (i <= PtrL->Last && PtrL->Data[i] != X) {
		i++;
	}
	if (i > PtrL->Last)
		return -1;
	else
	{
		return i;
	}
}
void Insert(int X, int i, List PtrL) {
	int j = 0;
	if (PtrL->Last == MAXSIIZE - 1) {
		cout << "表满" << endl;
		return;
	}
	if (i<1 || i > PtrL->Last + 2) {
		cout << "位置不合法" << endl;
		return;
	}
	for (j = PtrL->Last; j >= i - 1; j--) {
		PtrL->Data[i - 1] = X;
		PtrL->Last++;
		return;
	}
}
void Delete(int i, List PtrL) {
	int j = 0;
	if (i<1 || i>PtrL->Last + 1) 
	{
		cout << "Error" << endl;
		return;
	}
	for(j = i;j <= PtrL->Last; j++)
		PtrL->Data[j - 1] = PtrL->Data[j];
	PtrL->Last--;
	return;
}
int main() {
	cout << "Hello World!" << endl;
	List PtrL = MakeEmpyt();
	if (PtrL)
		cout << "Succeful" << endl;
	Insert(1, 1, PtrL);
	Find(1, PtrL);
	Delete(1, PtrL);
	return 0;
}
