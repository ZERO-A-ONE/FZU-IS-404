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
	int cjsr(struct student stu[],int);//��������ѧ���ɼ����ݺ���
	void cjxs(struct student stu[],int);//��Ļ��ʾѧ���ɼ����ݺ���
	void xrwj(struct student stu[],int);//д�ļ����Ⱥ���
	void xejzwj(struct student stu[],int);//д�������ļ�����
	int ch = 0;
	while(1)
  	{
  		system("cls");//�������� 
  		printf("             ѧ���ɼ�����ϵͳ\n");
		printf("         ---------------------\n");
	 	printf("            1---ѧ���ɼ�����\n");
	 	printf("            2---ѧ���ɼ�ͳ��\n");
	 	printf("            3---ѧ���ɼ�����\n");
	 	printf("            4---ѧ���ɼ���ѯ\n");
	 	printf("            0---�˳�\n");
	 	printf("         ---------------------\n");
	 	printf("         ��ѡ��1--4��");
 		scanf("%d",&ch);
 		switch(ch)
		{
			case 0:printf("�˳�  ϵͳ��\n");exit(0);
			case 1:cjsr(cj);break;//ѧ���ɼ����뺯�� 
			case 2:sccl();break;//ѧ���ɼ�ͳ�� 
    		case 3:cjpx();break;//ѧ���ɼ����� 
			case 4:scsech();break;//ѧ���ɼ���ѯ 
			default:printf("�˵�ѡ�����\n");
		}	
 	}
}
void putin()
void scsech()//ѧ���ɼ���ѯ 
{
 	int ch = 0;
	while(1)
	{
		system("cls");//�������� 
  		printf("             ѧ���ɼ�����ϵͳ\n");
		printf("         ---------------------\n");
	 	printf("            1---��ѧ��ѧ�Ų�ѯ\n");
	 	printf("            2---��ѧ��������ѯ\n");
	 	printf("            0---�˳�\n");
	 	printf("         ---------------------\n");
	 	printf("         ��ѡ��0--2��");
	 	scanf("%d",&ch);
		switch(ch)
		{
			
		} 
	}	
}
void sccl()//ѧ���ɼ�ͳ��
{
 	int ch = 0;
	while(1)
	{
		system("cls");//�������� 
  		printf("             ѧ���ɼ�����ϵͳ\n");
		printf("         ---------------------\n");
	 	printf("            1---��ѧ��ѧ�Ų�ѯ\n");
	 	printf("            2---��ѧ��������ѯ\n");
	 	printf("            0---�˳�\n");
	 	printf("         ---------------------\n");
	 	printf("         ��ѡ��0--2��");
	 	scanf("%d",&ch);
		switch(ch)
		{
			
		} 
	}	
}
