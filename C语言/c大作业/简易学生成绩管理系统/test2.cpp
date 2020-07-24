#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
struct student
{
	int num;
	char name[20];
	float kc1;//数学 
	float kc2;//英语 
	float kc3;//c语言 
	float zf;//总分 
	float pjf;//平均分 
};
struct student cj[10];
void cjsr(struct student cj[10]);//学生成绩输入函数 
void cjtj();//学生成绩统计
void cjpx();//学生成绩排序
void cjcx();//学生成绩查询 
main()
{
  	int ch = 0;
  	while(1)
  	{
  		system("cls");
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
			case 0:
				printf("退出系统！\n");exit(0);
			case 1:
				cjsr(cj);break;//学生成绩输入函数 
			case 2:
				cjtj();break;//学生成绩统计 
    		case 3:
				cjpx();break;//学生成绩排序 
			case 4:
				cjcx();break;//学生成绩查询 
			default:
				printf("菜单选择错误！\n");
		}
		printf("按任意键继续...");
		getch();
  	}
} 
void cjsr(struct student *cj)//学生成绩输入函数 
{
	system("cls");
	FILE *fp;
	int i;
	fp=fopen("cj.txt","r");
	for(i=0;i<10;i++)
		fscanf(fp,"%d %s %f %f %f",&cj[i].num,cj[i].name,&cj[i].kc1,&cj[i].kc2,&cj[i].kc3);
	fclose(fp);
	for(i=0;i<10;i++)
	{
		cj[i].zf = cj[i].kc1 + cj[i].kc2 + cj[i].kc3;
		cj[i].pjf = cj[i].zf / 3.0;
	}
	printf("学号  姓名  数学  英语  C语言  \n");
	for(i=0;i<10;i++)
		printf("%3d %s %7.1f %7.1f %7.1f\n",cj[i].num,cj[i].name,cj[i].kc1,cj[i].kc2,cj[i].kc3);
}
void cjtj()//学生成绩统计
{
	void xstj();
	void kctj();
 	int ch = 0;
  	while(1)
  	{
  		system("cls");
     	printf("             学生成绩统计\n");
	 	printf("         -----------------------\n");
	 	printf("            1---按学生统计\n");
	 	printf("            2---按课程统计\n");
	 	printf("            0---返回\n");
	 	printf("         ---------------------\n");
	 	printf("         请选择0--2：");
  		scanf("%d",&ch);
    	switch(ch)
		{
			case 0:
				printf("返回！\n");return;
			case 1:
				xstj();break;//按学生统计 
			case 2:
				kctj();break;//按课程统计 
			default:
				printf("菜单选择错误！\n");
		}
		printf("按任意键继续...");
		getch();
  	}
}
void xstj()//按学生统计 
{
	system("cls");
	int i = 0;
	for(i=0;i<10;i++)
	{
		cj[i].zf = cj[i].kc1 + cj[i].kc2 + cj[i].kc3;
		cj[i].pjf = cj[i].zf / 3.0;
	}
	printf("学号  姓名  总分 平均分\n");
	for(i=0;i<10;i++)
		printf("%3d %s %7.1f %7.1f\n",cj[i].num, cj[i].name, cj[i].zf ,cj[i].pjf);
}	
void kctj()//按课程统计
{
	system("cls");
	int i = 0;
	float math = 0;
	float english = 0;
	float cc = 0;
	for(i=0;i<10;i++)
	{
		math += cj[i].kc1;
		english += cj[i].kc2;
		cc += cj[i].kc3;
	}
	printf("科目  总分 平均分\n");
	printf("数学 %7.1lf %7.1lf\n",math,(math/10.0));
	printf("英语 %7.1lf %7.1lf\n",english,(english/10.0));
	printf("C语言 %7.1lf %7.1lf\n",cc,(cc/10.0));
} 
void cjpx()//学生成绩排序 
{
	void xhpx();//学号排序
	void xmpx();//姓名排序 
	void math_px();//按数学成绩排序
	int ch = 0;
	while(1)
	{
		system("cls");
     	printf("             学生成绩排序\n");
	 	printf("         -----------------------\n");
	 	printf("            1---学号排序\n");
	 	printf("            2---总分排序\n");
	 	printf("            3---按数学成绩排序\n");
	 	printf("            0---返回上一级\n");
	 	printf("         ---------------------\n");
	 	printf("         请选择0--3：");
  		scanf("%d",&ch);
    	switch(ch)
		{
			case 0:
				printf("退出系统\n");return;
			case 1:
				xhpx();break;//按学生学号查询 
			case 2:
				xmpx();break;//按学生总分查询
			case 3:
				math_px();break;//按数学成绩排序
			default:
				printf("菜单选择错误！\n");
		}
		printf("按任意键继续...");
		getch();
	}
}
void xhpx()//学号排序
{
	system("cls");
	int n = 10;
	int i = 0;
	int j = 0;
	for(i = 0;i<n-1;++i)
	{
		for(j = 0;j< n-i-1;++j)
		{
			if(cj[j].num<=cj[j+1].num)
			{
				student t = cj[j];
				cj[j] = cj[j+1];
				cj[j+1] = t;
			}
		}
	}
	printf("学号  姓名  数学  英语  C语言  \n");
	for(i=0;i<10;i++)
		printf("%3d %s %7.1f %7.1f %7.1f\n",cj[i].num,cj[i].name,cj[i].kc1,cj[i].kc2,cj[i].kc3);
}
void xmpx()//总分排序 
{
	system("cls");
	int n = 10;
	int i = 0;
	int j = 0;
	for(i = 0;i<n-1;++i)
	{
		for(j = 0;j< n-i-1;++j)
		{
			if(cj[j].zf<=cj[j+1].zf)
			{
				student t = cj[j];
				cj[j] = cj[j+1];
				cj[j+1] = t;
			}
		}
	}
	printf("学号  姓名  数学  英语  C语言  总分\n");
	for(i=0;i<10;i++)
		printf("%3d %s %7.1f %7.1f %7.1f %7.1f\n",cj[i].num,cj[i].name,cj[i].kc1,cj[i].kc2,cj[i].kc3,cj[i].zf);
}
void math_px()//按数学成绩排序
{
	system("cls");
	int n = 10;
	int i = 0;
	int j = 0;
	for(i = 0;i<n-1;++i)
	{
		for(j = 0;j< n-i-1;++j)
		{
			if(cj[j].kc1<=cj[j+1].kc1)
			{
				student t = cj[j];
				cj[j] = cj[j+1];
				cj[j+1] = t;
			}
		}
	}
	printf("学号  姓名  数学  英语  C语言  \n");
	for(i=0;i<10;i++)
		printf("%3d %s %7.1f %7.1f %7.1f\n",cj[i].num,cj[i].name,cj[i].kc1,cj[i].kc2,cj[i].kc3);
} 
void cjcx()//学生成绩查询
{
	void mzcx();//按学生姓名查询
	void xhcx();//按学生学号查询 
	int ch = 0;
	while(1)
	{
		system("cls");
     	printf("             学生成绩管理\n");
	 	printf("         -----------------------\n");
	 	printf("            1---按学生学号查询\n");
	 	printf("            2---按学生姓名查询\n");
	 	printf("            0---返回上一级\n");
	 	printf("         ---------------------\n");
	 	printf("         请选择0--2：");
  		scanf("%d",&ch);
    	switch(ch)
		{
			case 0:
				printf("退出系统\n");return;
			case 1:
				xhcx();break;//按学生学号查询 
			case 2:
				mzcx();break;//按学生姓名查询
			default:
				printf("菜单选择错误！\n");
		}
		printf("按任意键继续...");
		getch();
	}
}
void mzcx()//按学生姓名查询
{
	system("cls");
	char name[20];
	printf("请输入学生姓名\n");
	scanf("%s",&name);
	int i = 0;
	for(i=0;i<10;i++)
	{
		if(name[0] == cj[i].name[0]&&name[1] == cj[i].name[1])
		{
			printf("学号  姓名  数学  英语  C语言  \n");
			printf("%3d %s %7.1f %7.1f %7.1f\n",cj[i].num,cj[i].name,cj[i].kc1,cj[i].kc2,cj[i].kc3);	
			break;
		}
	}
}
void xhcx()//按学生学号查询
{
	system("cls");
	int number = 0;
	printf("请输入学生学号\n");
	scanf("%d",&number);
	int i = 0;
	for(i=0;i<10;i++)
	{
		if(number == cj[i].num)
		{
			printf("学号  姓名  数学  英语  C语言  \n");
			printf("%3d %s %7.1f %7.1f %7.1f\n",cj[i].num,cj[i].name,cj[i].kc1,cj[i].kc2,cj[i].kc3);	
			break;
		}
	}
}


