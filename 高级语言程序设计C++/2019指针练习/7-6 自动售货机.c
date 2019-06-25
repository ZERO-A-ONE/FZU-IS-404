#include"stdio.h"
struct goods
{
    int num;
    char name[20];
    int price;
    int amount;
};
int main()
{
    struct goods good[10]=
{
{1,"Table-water",1,0},
{2,"Table-water",1,0},
{3,"Table-water",1,0},
{4,"Coca-Cola",2,0},
{5,"Milk",2,0},
{6,"Beer",3,0},
{7,"Orange-Juice",3,0},
{8,"Sprite",3,0},
{9,"Oolong-Tea",4,0},
{10,"Green-Tea",4,0}
};
    int sum=0,num,change,total=0,money=0,i=0;
    while(1)
    {
        scanf("%d",&money);
        if(money==-1)
        {
            break;
        }
       sum=sum+money;
    }
    while(1)
    {
        scanf("%d",&num);
        if(num==-1)
        {
            break;
        }
        switch(num)
        {
        case 1:
            {
                total=total+good[0].price;

                good[0].amount=good[0].amount+1;
                break;
            }
        case 2:
            {
                total=total+good[1].price;

                good[1].amount=good[1].amount+1;
                break;

            }
        case 3:
            {
                total=total+good[2].price;

                good[2].amount=good[2].amount+1;
                break;
            }
             case 4:
            {
                total=total+good[3].price;

                good[3].amount=good[3].amount+1;
                break;
            }
             case 5:
            {
                total=total+good[4].price;

                good[4].amount=good[4].amount+1;
                break;
            }
             case 6:
            {
                total=total+good[5].price;

                good[5].amount=good[5].amount+1;
                break;
            }
             case 7:
            {
                total=total+good[6].price;

                good[6].amount=good[6].amount+1;
                break;
            }
             case 8:
            {
                total=total+good[7].price;

                good[7].amount=good[7].amount+1;
                break;
            }
             case 9:
            {
                total=total+good[8].price;

                good[8].amount=good[8].amount+1;
                break;
            }
             case 10:
            {
                total=total+good[9].price;

                good[9].amount=good[9].amount+1;
                break;
            }
        }


      }
      if(total>sum)
      {
          printf("Insufficient money");
      }
      else
      {
      change=sum-total;
      printf("Total:%dyuan,change:%dyuan\n",sum,change);
      for(i=0;i<10;i++)
      {
          if(good[i].amount!=0)
          {
              printf("%s:%d;",good[i].name,good[i].amount);
          }
      }
      }
}
