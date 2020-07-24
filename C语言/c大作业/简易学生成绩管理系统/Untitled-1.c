#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
struct student
{
	int num;
	char name[20];
	float kc1;//��ѧ 
	float kc2;//Ӣ�� 
	float kc3;//c���� 
	float zf;//�ܷ� 
	float pjf;//ƽ���� 
};
struct student cj[10];
void cjsr(struct student cj[10]);//ѧ���ɼ����뺯�� 
void cjtj();//ѧ���ɼ�ͳ��
void cjpx();//ѧ���ɼ�����
void cjcx();//ѧ���ɼ���ѯ 
main()
{
  	int ch = 0;
  	while(1)
  	{
  		system("cls");
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
			case 0:
				printf("�˳�ϵͳ��\n");exit(0);
			case 1:
				cjsr(cj);break;//ѧ���ɼ����뺯�� 
			case 2:
				cjtj();break;//ѧ���ɼ�ͳ�� 
    		case 3:
				cjpx();break;//ѧ���ɼ����� 
			case 4:
				cjcx();break;//ѧ���ɼ���ѯ 
			default:
				printf("�˵�ѡ�����\n");
		}
		printf("�����������...");
		getch();
  	}
} 
void cjsr(struct student *cj)//ѧ���ɼ����뺯�� 
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
	printf("ѧ��  ����  ��ѧ  Ӣ��  C����  \n");
	for(i=0;i<10;i++)
		printf("%3d %s %7.1f %7.1f %7.1f\n",cj[i].num,cj[i].name,cj[i].kc1,cj[i].kc2,cj[i].kc3);
}
void cjtj()//ѧ���ɼ�ͳ��
{
	void xstj();
	void kctj();
 	int ch = 0;
  	while(1)
  	{
  		system("cls");
     	printf("             ѧ���ɼ�ͳ��\n");
	 	printf("         -----------------------\n");
	 	printf("            1---��ѧ��ͳ��\n");
	 	printf("            2---���γ�ͳ��\n");
	 	printf("            0---����\n");
	 	printf("         ---------------------\n");
	 	printf("         ��ѡ��0--2��");
  		scanf("%d",&ch);
    	switch(ch)
		{
			case 0:
				printf("���أ�\n");return;
			case 1:
				xstj();break;//��ѧ��ͳ�� 
			case 2:
				kctj();break;//���γ�ͳ�� 
			default:
				printf("�˵�ѡ�����\n");
		}
		printf("�����������...");
		getch();
  	}
}
void xstj()//��ѧ��ͳ�� 
{
	system("cls");
	int i = 0;
	for(i=0;i<10;i++)
	{
		cj[i].zf = cj[i].kc1 + cj[i].kc2 + cj[i].kc3;
		cj[i].pjf = cj[i].zf / 3.0;
	}
	printf("ѧ��  ����  �ܷ� ƽ����\n");
	for(i=0;i<10;i++)
		printf("%3d %s %7.1f %7.1f\n",cj[i].num, cj[i].name, cj[i].zf ,cj[i].pjf);
}	
void kctj()//���γ�ͳ��
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
	printf("��Ŀ  �ܷ� ƽ����\n");
	printf("��ѧ %7.1lf %7.1lf\n",math,(math/10.0));
	printf("Ӣ�� %7.1lf %7.1lf\n",english,(english/10.0));
	printf("C���� %7.1lf %7.1lf\n",cc,(cc/10.0));
} 
void cjpx()//ѧ���ɼ����� 
{
	void xhpx();//ѧ������
	void xmpx();//�������� 
	void math_px();//����ѧ�ɼ�����
	int ch = 0;
	while(1)
	{
		system("cls");
     	printf("             ѧ���ɼ�����\n");
	 	printf("         -----------------------\n");
	 	printf("            1---ѧ������\n");
	 	printf("            2---�ܷ�����\n");
	 	printf("            3---����ѧ�ɼ�����\n");
	 	printf("            0---������һ��\n");
	 	printf("         ---------------------\n");
	 	printf("         ��ѡ��0--3��");
  		scanf("%d",&ch);
    	switch(ch)
		{
			case 0:
				printf("�˳�ϵͳ\n");return;
			case 1:
				xhpx();break;//��ѧ��ѧ�Ų�ѯ 
			case 2:
				xmpx();break;//��ѧ���ֲܷ�ѯ
			case 3:
				math_px();break;//����ѧ�ɼ�����
			default:
				printf("�˵�ѡ�����\n");
		}
		printf("�����������...");
		getch();
	}
}
void xhpx()//ѧ������
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
	printf("ѧ��  ����  ��ѧ  Ӣ��  C����  \n");
	for(i=0;i<10;i++)
		printf("%3d %s %7.1f %7.1f %7.1f\n",cj[i].num,cj[i].name,cj[i].kc1,cj[i].kc2,cj[i].kc3);
}
void xmpx()//�ܷ����� 
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
	printf("ѧ��  ����  ��ѧ  Ӣ��  C����  �ܷ�\n");
	for(i=0;i<10;i++)
		printf("%3d %s %7.1f %7.1f %7.1f %7.1f\n",cj[i].num,cj[i].name,cj[i].kc1,cj[i].kc2,cj[i].kc3,cj[i].zf);
}
void math_px()//����ѧ�ɼ�����
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
	printf("ѧ��  ����  ��ѧ  Ӣ��  C����  \n");
	for(i=0;i<10;i++)
		printf("%3d %s %7.1f %7.1f %7.1f\n",cj[i].num,cj[i].name,cj[i].kc1,cj[i].kc2,cj[i].kc3);
} 
void cjcx()//ѧ���ɼ���ѯ
{
	void mzcx();//��ѧ��������ѯ
	void xhcx();//��ѧ��ѧ�Ų�ѯ 
	int ch = 0;
	while(1)
	{
		system("cls");
     	printf("             ѧ���ɼ�����\n");
	 	printf("         -----------------------\n");
	 	printf("            1---��ѧ��ѧ�Ų�ѯ\n");
	 	printf("            2---��ѧ��������ѯ\n");
	 	printf("            0---������һ��\n");
	 	printf("         ---------------------\n");
	 	printf("         ��ѡ��0--2��");
  		scanf("%d",&ch);
    	switch(ch)
		{
			case 0:
				printf("�˳�ϵͳ\n");return;
			case 1:
				xhcx();break;//��ѧ��ѧ�Ų�ѯ 
			case 2:
				mzcx();break;//��ѧ��������ѯ
			default:
				printf("�˵�ѡ�����\n");
		}
		printf("�����������...");
		getch();
	}
}
void mzcx()//��ѧ��������ѯ
{
	system("cls");
	char name[20];
	printf("������ѧ������\n");
	scanf("%s",&name);
	int i = 0;
	for(i=0;i<10;i++)
	{
		if(name[0] == cj[i].name[0]&&name[1] == cj[i].name[1])
		{
			printf("ѧ��  ����  ��ѧ  Ӣ��  C����  \n");
			printf("%3d %s %7.1f %7.1f %7.1f\n",cj[i].num,cj[i].name,cj[i].kc1,cj[i].kc2,cj[i].kc3);	
			break;
		}
	}
}
void xhcx()//��ѧ��ѧ�Ų�ѯ
{
	system("cls");
	int number = 0;
	printf("������ѧ��ѧ��\n");
	scanf("%d",&number);
	int i = 0;
	for(i=0;i<10;i++)
	{
		if(number == cj[i].num)
		{
			printf("ѧ��  ����  ��ѧ  Ӣ��  C����  \n");
			printf("%3d %s %7.1f %7.1f %7.1f\n",cj[i].num,cj[i].name,cj[i].kc1,cj[i].kc2,cj[i].kc3);	
			break;
		}
	}
}


