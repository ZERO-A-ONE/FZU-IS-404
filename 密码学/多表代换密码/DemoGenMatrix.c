#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

//生成模26随机可逆矩阵及其逆阵的示例程序，仅供参考
//蒋启强

//函数声明
int** genA(int n);
void matrixAddRangeMod26(int** A, int n, int Li, int Lj, int r);
int mod26(int x);
int getRandomReversableMod26();
int getReverMod26(int a);
int extendEuclid(int a, int b, int* result);
void printMatrix(int** A, int n);
int getDetMod26(int** A, int n);
int** getStarMatrixMod26(int** A, int n);
int** getReverseMatrixMod26(int** A, int n);
void freeMatrix(int** A, int n);

//本例示范如何随机生成一个模26可逆矩阵及逆阵
int main() {
	int n=3;
	int** A;
	int ADet;
	int** AR;
	printf("请输入矩阵规模n(n>2):");
	scanf_s("%d", &n);
	//随机种子
	srand(time(NULL));
	//动态生成矩阵A
	A = genA(n);
	//打印输出矩阵A
	printMatrix(A, n);
	//求行列式的值
	ADet = getDetMod26(A, n);
	printf("\n行列式计算结果是：%d \n",ADet);
	//生成逆阵
	AR = getReverseMatrixMod26(A,n);
	//打印输出逆阵A
	printf("逆阵是:\n");
	printMatrix(AR, n);
	//释放内存
	freeMatrix(A,n);
	freeMatrix(AR, n);

	//测试课本例子
	int AAE[3][3] = { {11,2,19},{5,23,25},{20,7,17} };
	int** AA= (int**)malloc(sizeof(int*) * 3);
	AA[0] = AAE[0];
	AA[1] = AAE[1];
	AA[2] = AAE[2];
	//打印输出
	printf("教材例1-2用的矩阵是：\n");
	printMatrix(AA, 3);
	//求行列式值
	int AADet = getDetMod26(AA, 3);
	printf("行列式值为：%d\n逆元为：%d\n",AADet, getReverMod26(AADet));
	//求伴随矩阵
	int** AAS = getStarMatrixMod26(AA, 3);
	printf("其伴随阵是：\n");
	printMatrix(AAS, 3);
	//求逆阵
	int** AAR= getReverseMatrixMod26(AA, 3);
	printf("其逆阵是：\n");
	printMatrix(AAR, 3);
	//释放内存
	freeMatrix(AAS, 3);
	freeMatrix(AAR, 3);
	free(AA);
}

//动态生成矩阵
int** genA(int n) {
	if (n < 3)return NULL;
	//给二维数组分配空间
	int** A;
	A = (int**)malloc(sizeof(int*)*n);
	for (int i = 0; i < n; i++) {
		A[i] = (int*)malloc(sizeof(int) * n);
	}
	//给对角线置1
	for (int i = 0; i < n;i++) {
		A[i][i] = 1;
	}
	//给右上角置随机数
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			A[i][j] = rand() % 26;
	//通过初等变换，给左下角随机数
	for (int i = n - 2; i >= 0; i--) 
		for (int j = i + 1; j < n; j++) {
			//初等变换：Lj=Lj+Li*r
			matrixAddRangeMod26(A, n, i, j, rand()%25+1);
		}
	//检查对角线是否为1
	for (int i = 0; i < n; i++)
		if (A[i][i] == 1) {
			//行乘上可逆随机数
			int r = getRandomReversableMod26();
			for (int j = 0; j < n; j++)
				A[i][j] = mod26(A[i][j] * r);
		}
	return A;
}
//初等变换行相加(模26运算)：Lj=Lj+Li*r
void matrixAddRangeMod26(int** A,int n, int Li, int Lj, int r) {
	for (int i = 0; i < n; i++) 
		A[Lj][i] = mod26(A[Lj][i]+ A[Li][i]*r);	
}
//对26取模
int mod26(int x) {
	return (x % 26 + 26) % 26;
}
//获取模26随机可逆数
int getRandomReversableMod26() {
	int r = rand() % 25 + 1;
	while (getReverMod26(r) == -1)
		r++;
	return r;
}

//求模26逆元,返回值为-1则没有逆元
int getReverMod26(int a) {
	int b = 0;
	int c = 0;
	c = extendEuclid(26, a, &b);
	if (c == 0) return -1;
	return b;
}

//扩展欧几里得算法
//返回值Y3,0表示返回的是ab最大公约数，1表示返回的是b在模a下的逆元
int extendEuclid(int a,int b,int* result) {
	int x[3] = { 1,0,a };
	int y[3] = { 0,1,b };
	int t[3] = { 0,0,0 };
	while (y[2]!=0 && y[2]!=1) {
		int q = x[2] / y[2];
		t[0] = x[0] - y[0] * q;
		t[1] = x[1] - y[1] * q;
		t[2] = x[2] - y[2] * q;
		x[0] = y[0];
		x[1] = y[1];
		x[2] = y[2];
		y[0] = t[0];
		y[1] = t[1];
		y[2] = t[2];
	}
	if (y[2] == 0) {
		//有公因子
		*result = x[2];
		return 0;
	}
	else{
		//ab互质
		*result = y[1];
		return 1;
	}
}

// 输出矩阵
void printMatrix(int** A, int n) {
	printf("\n");
	for (int i = 0; i < n; i++){
		printf("| ");
		for (int j = 0; j < n; j++) {
			printf("%2d ",A[i][j]);
		}
		printf("|\n");
	}
}
//求模26行列式的值，
int getDetMod26(int** A,int n) {
	int det = 0;
	int item = 0;
	if (n <= 0)return 0;
	if (n == 1) return A[0][0];
	if (n == 2) {
		det = A[0][0] * A[1][1] - A[0][1] * A[1][0];
	}
	else {
		det = 0;
		for (int i = 0; i < n; i++)
			det = det + A[0][i] * getSubDetMod26(A,n,0,i);
	}
	//返回模26结果
	return mod26(det);
}

//求模26代数余子式
int getSubDetMod26(int** A, int n,int i,int j) {
	//有效性检查
	if (i >= n || j >= n||i<0||j<0)return 0;
	//分配子行列式空间
	int** subA;
	subA = (int**)malloc(sizeof(int*) * (n-1));
	for (int i = 0; i < n-1; i++) {
		subA[i] = (int*)malloc(sizeof(int) * (n-1));
	}
	//给子行列式赋值(分四个区域)
	for (int r = 0; r < i; r++)
		for (int c=0;c<j;c++)
			subA[r][c]=A[r][c];
	for (int r = 0; r < i; r++)
		for (int c = j; c < n-1; c++)
			subA[r][c] = A[r][c+1];
	for (int r = i; r < n-1; r++)
		for (int c = 0; c < j; c++)
			subA[r][c] = A[r+1][c];
	for (int r = i; r < n-1; r++)
		for (int c = j; c < n - 1; c++)
			subA[r][c] = A[r+1][c + 1];
	//printf("代数余子式:\n");
	//printMatrix(subA, n-1);
	//计算子行列式的值
	int subADet = getDetMod26(subA, n - 1);
	//printf("代数余子式计算结果:%d\n", subADet);
	//代数余子式正负号
	if ((i + j) % 2 == 1)
		subADet = (26 - subADet)%26; //加法逆元
	//释放计算用的子行列式空间
	freeMatrix(subA,n-1);

	return subADet;
}

//求模26伴随矩阵
int** getStarMatrixMod26(int** A,int n) {
	//给伴随矩阵分配空间
	int** AStar;
	AStar = (int**)malloc(sizeof(int*) * n);
	for (int i = 0; i < n ; i++) {
		AStar[i] = (int*)malloc(sizeof(int) * n);
	}
	//给伴随矩阵元素赋值
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			AStar[j][i] = getSubDetMod26(A,n,i,j);
	return AStar;
}

//求模26逆阵
int** getReverseMatrixMod26(int** A,int n) {	
	//求A行列式的值
	int ADet = getDetMod26(A,n);
	//求逆元
	int RADet = getReverMod26(ADet);
	//求伴随矩阵
	int** AR = getStarMatrixMod26(A,n);
	//求逆阵
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			AR[i][j] = mod26(AR[i][j] * RADet);
	return AR;
}

//释放矩阵内存
void freeMatrix(int** A,int n) {
	for (int i = 0; i < n; i++)
		free(A[i]);
	free(A);
}
