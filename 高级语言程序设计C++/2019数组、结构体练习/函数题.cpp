//6-1 数组循环右移
int ArrayShift( int a[], int n, int m )
{
	m=m%n;
	m=n-m;
	int b[10],i;
	for(i=0;i<m;i++)
	{
		b[i]=a[i];
	}
	for(i=m;i<n;i++)
	{
		a[i-m]=a[i];
	}
	for(i=0;i<m;i++)
	{
		a[n-m+i]=b[i];
	}
}
//6-2 使用函数的选择法排序
void sort( int a[], int n )
{
	int i,j,t;
	for(i=0;i<n;i++)
	{
		for(j=i;j<n;j++)
		{
			if(a[i]>a[j])
			{
				t=a[i];
				a[i]=a[j];
				a[j]=t;
			}
		 } 
	}
}
//6-4 成绩单求平均成绩（结构体）
double average ( Score a[], int n )
{
	double tmp = 0;
	for(int i = 0;i < n;i++)
	{
		tmp += a[i].score;
	}
	tmp = tmp / n;
	return tmp;
}
//6-5 歌唱比赛打分
double getScore(int *score, int total)
{
	int max = score[0];
	int min = score[0];
	double tmp = 0;
	
	for(int i=0;i<total;i++)
	{
		if(score[i] > max)
		{
			max = score[i];
		}
	}
	for(int i=0;i<total;i++)
	{
		if(score[i] < min)
		{
			min = score[i];
		}
	}
	for(int i=0;i<total;i++)
	{
		
		if(score[i] == max )
		{
			score[i] = 0;
			break;
		}
	}
	for(int i=0;i<total;i++)
	{
		if(score[i] == min )
		{
			score[i] = 0;
			break;
		}
	}
	for(int i=0;i<total;i++)
	{
		tmp += score[i];
	}
	tmp = tmp / (total - 2);
	return tmp;
}
//6-6 函数调用
int max(int a,int b)
{
	if(a<b)
	return b;
	else 
	return a;
 } 
 int min(int a,int b)
 {
 	if(a>b)
 	return b;
	else 
	return a;
 }
 int sum(int a, int b)
 {
 	return a+b;
 }
 int compute(int a, int b, int(*func)(int, int))
 {
 	return (*func)(a,b);
 }
 //6-7 两个整数的交换
 void swap (  int &a,  int &b )
{
	int t;
	t=a;
	a=b;
	b=t;
 } 
 //6-8 带默认形参值的函数
 int add(int a,int b=20,int c=30)
{
	return a+b+c;
}