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
  		printf("             ѧ������ϵͳ\n");
		printf("         ---------------------\n");
	 	printf("            1---ѧ���ɼ�����\n");
	 	printf("            2---ѧ���ɼ�ͳ��\n");
	 	printf("            3---ѧ���ɼ�����\n");
	 	printf("            4---ѧ���ɼ���ѯ\n");
	 	printf("            0---�˳�\n");
	 	printf("         ---------------------\n");
	 	printf("         ��ѡ��1--4��");
 		printf("%d",&ch);
    switch(ch)
	{
		case 0:printf("�˳�ϵͳ��\n");exit(0);
		case 1:cjsr(cj);break;//ѧ���ɼ����뺯�� 
		case 2:cjtj();break;//ѧ���ɼ�ͳ�� 
    	case 3:cjpx();break;//ѧ���ɼ����� 
		case 4:cjcx();break;//ѧ���ɼ���ѯ 
		default:printf("�˵�ѡ�����\n");
	}
	printf("�����������...");
	getch();
  	}
} 

void cjsr(struct student cj[10])//ѧ���ɼ����뺯�� 
{
	FILE *fp;
	int i;
	fp=fopen("cj.text","r");
	for(i=0;i<10;i++)
		fscanf(fp,"%d%s%f%f%f",&cj[i].num,cj[i].name,&cj[i].kc1,&cj[i].kc2,&cj[i].kc3);
	fclose(fp);
	    printf("ѧ��  ����  �γ�1  �γ�2  �γ�3  \n");
	for(i=0;i<10;i++)
		printf("%3d  %s %7.1f %7.1f %7.1f \n",cj[i].num,cj[i].name,cj[i].kc1,cj[i].kc2,cj[i].kc3);
}
void cjtj()//ѧ���ɼ�ͳ��
{
	
} 
	void xstj();
	void kctj();
 
  int ch;
  float tj[3]={0};
  while(1)
  {
  system("cls");
     printf("             ѧ������ϵͳ\n");
	 printf("         -----------------------\n");
	 printf("            1---��ѧ��ͳ��\n");
	 printf("            2---���γ�ͳ��\n");
	 printf("            0---����\n");
	 printf("         ---------------------\n");
	 printf("         ��ѡ��0--2��");
  printf("%d",&ch);
    switch(ch)
	{
	case 0:printf("���أ�\n");exit(0);
	case 1:xstj();break;
	case 2:kctj();break;
	default:printf("�˵�ѡ�����\n");
	}
	printf("�����������...");
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


	
	


  
  
 
