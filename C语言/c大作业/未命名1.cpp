#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#define N 100
struct student
{
	int num;
	char name[10];
	float score[4];
};
struct student stu[N];
int main()
{
	int cjsr(struct student stu[],int);//键盘输入学生成绩数据函数
	void cjxs(struct student stu[],int);//屏幕显示学生成绩数据函数
	void xrwj(struct student stu[],int);//写文件调度函数
	void xejzwj(struct student stu[],int);//写二进制文件函数
	int ch = 0;
	while(1)
  	{
  		system("cls");//清屏函数 
  		printf("             学生成绩管理系统\n");
		printf("         ---------------------\n");
	 	printf("            1---学生成绩输入\n");
	 	printf("            2---学生成绩统计\n");
	 	printf("            3---学生成绩排序\n");
	 	printf("            4---学生成绩查询\n");
	 	printf("            0---退出\n");
	 	printf("         ---------------------\n");
	 	printf("         请选择1--4：");
 		scanf("%d",&ch);
 		switch(ch)
		{
			case 0:printf("退出  系统！\n");exit(0);
			case 1:cjsr(cj);break;//学生成绩输入函数 
			case 2:sccl();break;//学生成绩统计 
    		case 3:cjpx();break;//学生成绩排序 
			case 4:scsech();break;//学生成绩查询 
			default:printf("菜单选择错误！\n");
		}	
 	}
}
void putin()
void scsech()//学生成绩查询 
{
 	int ch = 0;
	while(1)
	{
		system("cls");//清屏函数 
  		printf("             学生成绩管理系统\n");
		printf("         ---------------------\n");
	 	printf("            1---按学生学号查询\n");
	 	printf("            2---按学生姓名查询\n");
	 	printf("            0---退出\n");
	 	printf("         ---------------------\n");
	 	printf("         请选择0--2：");
	 	scanf("%d",&ch);
		switch(ch)
		{
			
		} 
	}	
}
void sccl()//学生成绩统计
{
 	int ch = 0;
	while(1)
	{
		system("cls");//清屏函数 
  		printf("             学生成绩管理系统\n");
		printf("         ---------------------\n");
	 	printf("            1---按学生学号查询\n");
	 	printf("            2---按学生姓名查询\n");
	 	printf("            0---退出\n");
	 	printf("         ---------------------\n");
	 	printf("         请选择0--2：");
	 	scanf("%d",&ch);
		switch(ch)
		{
			
		} 
	}	
}
