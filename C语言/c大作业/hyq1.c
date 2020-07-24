#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
struct student
{
	int num;
	char name[20];
	float kc1;
	float kc2;
	float kc3;
	float zf;
};
struct student cj[10];
main()
{
  void cjsr(struct student cj[10]);
  void cjtj();
  void cjpx();
  void cjcx();
  int ch;
  float tj[3]={0};
  while(1)
  	{
  		system("cls");
  		printf("             学生管理系统\n");
		printf("         ---------------------\n");
	 	printf("            1---学生成绩输入\n");
	 	printf("            2---学生成绩统计\n");
	 	printf("            3---学生成绩排序\n");
	 	printf("            4---学生成绩查询\n");
	 	printf("            0---退出\n");
	 	printf("         ---------------------\n");
	 	printf("         请选择1--4：");
 		printf("%d",&ch);
    switch(ch)
	{
		case 0:printf("退出系统！\n");exit(0);
		case 1:cjsr(cj);break;//学生成绩输入函数 
		case 2:cjtj();break;//学生成绩统计 
    	case 3:cjpx();break;//学生成绩排序 
		case 4:cjcx();break;//学生成绩查询 
		default:printf("菜单选择错误！\n");
	}
	printf("按任意键继续...");
	getch();
  	}
} 

void cjsr(struct student cj[10])//学生成绩输入函数 
{
	FILE *fp;
	int i;
	fp=fopen("cj.text","r");
	for(i=0;i<10;i++)
		fscanf(fp,"%d%s%f%f%f",&cj[i].num,cj[i].name,&cj[i].kc1,&cj[i].kc2,&cj[i].kc3);
	fclose(fp);
	    printf("学号  姓名  课程1  课程2  课程3  \n");
	for(i=0;i<10;i++)
		printf("%3d  %s %7.1f %7.1f %7.1f \n",cj[i].num,cj[i].name,cj[i].kc1,cj[i].kc2,cj[i].kc3);
}
void cjtj()//学生成绩统计
{
	
} 
	void xstj();
	void kctj();
 
  int ch;
  float tj[3]={0};
  while(1)
  {
  system("cls");
     printf("             学生管理系统\n");
	 printf("         -----------------------\n");
	 printf("            1---按学生统计\n");
	 printf("            2---按课程统计\n");
	 printf("            0---返回\n");
	 printf("         ---------------------\n");
	 printf("         请选择0--2：");
  printf("%d",&ch);
    switch(ch)
	{
	case 0:printf("返回！\n");exit(0);
	case 1:xstj();break;
	case 2:kctj();break;
	default:printf("菜单选择错误！\n");
	}
	printf("按任意键继续...");
	getch();
  }

}
void xstj()
{

}

void kctj()
{

}	

void cjpx()
{

}

void cjcx()
{

}


	
	


  
  
 
