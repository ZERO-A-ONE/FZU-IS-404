#include<iostream>
#include<string>
using namespace std;
class student
{
	private:
		long name;
		int a;
		public:
			student(long n=0,int a1=0)
			{
				a=a1;
				name=n;
			}
			void set(long n,int a1)
			{
				a=a1;
				name=n;
			}
			friend void top(student *p,int count);
};
 void top(student *p,int count)
 {
 	int max,i,count2=0;
 	long x[100];
 	max=p[0].a;
 	for(i=1;i<count;i++)
 	{
 		if(max<p[i].a)
 		max=p[i].a;
	 }
	 for(i=0;i<count;i++)
	 {
	 	if(p[i].a==max)
	 	{
	 		x[count2]=p[i].name;
	 		count2++;
		 }
	  } 
	  for(i=0;i<count2;i++)
	  {
	  	cout<<x[i];
	  	if(i<count2-1)
		  cout<<" ";
	  }
 }
int main()
{
	student stu[100];
	long name;
	int a,count=0;
	cin>>name;
	while(name!=0)
	{
		cin>>a;
		stu[count].set(name,a);
		cin>>name;
		count++;
	 }
	 top(stu,count);
	return 0;
}
