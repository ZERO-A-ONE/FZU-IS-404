#include<iostream>
using namespace std;
class polygon
{
	protected:
		int number;
		private:
			int side[100];
			public:
			polygon(int n=0)
			{
				number=n;
				for(int i=0;i<100;i++)
				{
					side[i]=0;
				}
			}
			void set()
			{
				int ty;
				cin>>ty;
				while(ty!=-1)
				{
					side[number]=ty;
					number++;
					cin>>ty;
				}
			}
			int bian()
			{
				int sum=0,i=0;
				while(side[i]!=0)
				{
					sum+=side[i];
					i++;
				}
				return sum;
			}
			void display()
			{
				
				cout<<number<<" "<<bian()<<endl;
			}
};
class rectangle:public polygon
{
	public :
		int height;
		int width;
		rectangle(int h=0,int w=0):height(h),width(w){}
		int bian()
		{
			int sum=0;
			sum=(height+width)*2;
			return sum;
		}
		void display()
		{
			cout<<"4 "<<bian()<<endl;
		}
};
class equal_polygon:public polygon
{
	public :
		int side_len;
		equal_polygon(int s=0)
		{
			side_len=s;
		}
		int bian(int shu)
		{
			int sum=0;
			sum=shu*side_len;
			return sum;
		}
};
int main()
{
	int n,i,ty,x,y,shu,side;
	polygon *a;
	rectangle b;
	equal_polygon c;
	cin>>n;
	for(i=0;i<n;i++)
	{
		cin>>ty;
		switch(ty)
		{
			case 0:a=new polygon ;a->set();a->display();delete a; break;
			case 1:cin>>x>>y;b=rectangle(x,y);b.display();break;
			case 2:cin>>shu>>side;c=equal_polygon(side);cout<<shu<<" "<<c.bian(shu)<<endl;
		}
	}
	return 0;
 } 
