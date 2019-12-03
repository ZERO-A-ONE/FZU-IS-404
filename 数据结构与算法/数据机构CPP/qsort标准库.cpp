#include<iostream>
#include <stdlib.h>
using namespace std;
/*
void qsort(void *base,int nelem,int width,int (*fcmp)(const void *,const void *));【qsort ( 数组名 ，元素个数，元素占用的空间(sizeof)，比较函数) 】
argv[0] 待排序数组首地址
argv[1] 数组中待排序元素数量
argv[2] 各元素的占用空间大小
argv[3] 指向函数的指针，用于确定排序的顺序
*/
int compare(const void* a, const void* b)
{
	int* pa = (int*)a;
	int* pb = (int*)b;
	return (*pa) - (*pb);  //从小到大排序
}
int main()
{
	int a[10] = { 5, 6, 4, 3, 7, 0 ,8, 9, 2, 1 };
	qsort(a, 10, sizeof(int), compare);
	for (int i = 0; i < 10; i++)
		cout << a[i] << " " << endl;
	return 0;
}