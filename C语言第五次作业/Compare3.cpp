#include<stdio.h>
int main()
{
   char bob,alice;
   scanf("%c %c",&alice,&bob);
   if(bob=='0')
   {
   scanf(" %c",&bob);
   alice=58; 
   }
   if(bob=='1')
   bob=58;
   if(bob=='K')
   bob+=1;
   if(alice=='K')
   alice+=1;
   if(bob=='Q')
   bob-=6;
   if(alice=='Q')
   alice-=6;
   if(bob=='2')
   bob+=28;
   if(alice=='2')
   alice+=28;
   if(bob=='A')
   bob+=12;
   if(alice=='A')
   alice+=12;
   if(bob>alice)
   printf("Bob win");
   if(bob==alice)
   printf("No winner");
   if(bob<alice)
   printf("Alice win");
	return 0;
 } 
