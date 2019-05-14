#include<stdio.h>
#include<string.h>
int main()
{
  char a[500001];
  gets(a);
  int l=strlen(a);
  int i,j;
  int word=0;
  int first=1;
  for(i=l-1;i>=0;i--)
  {
      if(word!=0&&a[i]==' ')
      {
          if(first==1) first=0;
          else printf(" ");
          for(j=i+1;j<=i+word;j++)
          printf("%c",a[j]);
          word=0;
      }
      else if(a[i]!=' ') word++;
  }
  if(word>0) 
  {
      if(first==0) 
          printf(" ");
      for(j=0;j<=word-1;j++)      
      printf("%c",a[j]);
  }
  return 0;
}