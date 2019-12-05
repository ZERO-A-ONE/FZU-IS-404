#include<iostream>
#include<stdlib.h>
#define MaxData 999999
using namespace std;
typedef struct HeapStruct* MaxHeap;
struct HeapStruct {
	int* Data;
	int Size;
	int Capacity;
};
MaxHeap Create(int Maxsize) {
	MaxHeap H = new HeapStruct;
	H->Data = (int*)malloc((Maxsize + 1) * sizeof(int));
	H->Size = 0;
	H->Capacity = Maxsize;
	H->Data[0] = MaxData;
	return H;
}
void Insert(MaxHeap H, int item) {
	int i;
	if (H->Size == H->Capacity) {
		cout << "Full" << endl;
		return;
	}
	i = ++H->Size;
	for (; H->Data[i / 2] < item; i /= 2)
		H->Data[i] = H->Data[i / 2];
	H->Data[i] = item;
}
int DeletMax(MaxHeap H) {
	int Parent, Child, MaxItem, temp;
	if (H->Size == 0) {
		cout << "Empty" << endl;
	}
	MaxItem = H->Data[1];
	temp = H->Data[H->Size--];
	for (Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
		Child = Parent * 2;
		if (Child != H->Size && H->Data[Child] < H->Data[Child + 1]) {
			Child = Child + 1;
		}
		if (temp = H->Data[Child]) {
			break;
		}
		else {
			H->Data[Parent] = H->Data[Child];
		}
	}
	H->Data[Parent] = temp;
	return MaxItem;
}
int main() {
	MaxHeap H = Create(1000);
	Insert(H, 2);
	Insert(H, 10);
	Insert(H, 100);
	Insert(H, 3);
	Insert(H, 6);
	Insert(H, 8);
	cout << H->Data[1] << endl;
	return 0;
}