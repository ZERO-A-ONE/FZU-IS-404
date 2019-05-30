# 6-1 直角三角形

```c++
class RTriangle
{
	private :
		double a1,b1;
		public :
			RTriangle(double x,double y):a1(x),b1(y){}
			double getArea()
			{
				return 0.5*a1*b1;
			} 
			double getPerimeter()
			{
				double c1;
				c1=sqrt(a1*a1+b1*b1);
				return a1+b1+c1;
			}
};
```

# 6-2 时钟类

```c++
class Clock
{
	private :
		int hour,minute,sec;
		public:
			Clock(int h=0,int m=0,int s=0)
			{
				hour=h;
				minute=m;
				sec=s;
			}
			void showTime()
			{
				cout<<hour<<":"<<minute<<":"<<sec<<endl;
			}
};
```

# 6-3 2017final点的个数

```c++
class Point
{
	private :
		int x,y;
		static int count;
		public:
			Point(int x1=0,int y1=0):x(x1),y(y1){}
			int getX() 
			{
				return x; 
			}
			int  getY()
			{
				return y;
			} 
			static void showCount()
			{
				cout<<count<<endl;
				count++;
			}
};
int Point::count=0;
```

# 6-4 2018Final静态成员（黑名单）

```c++
int Group::blackList[N];
int Group::size;
Group::Group(){}
Group::Group(int num, bool bSign)
{
	if(bSign)
	{
	    if(size<3)
    	{
        	blackList[size] = num;
    	}
    	if(size==3)
    	{
    		for(int i = 0;i<size;i++)
    		{
    			blackList[i]=blackList[i+1];
			}
			blackList[size-1]=num;
    	}
    	if(size<3)
   		{
    		size++;
		}
	}
}
void Group::addToList(int num)
{
    if(size<3)
    {
        blackList[size] = num;
    }
    if(size==3)
    {
    	for(int i = 0;i<size;i++)
    	{
    		blackList[i]=blackList[i+1];
		}
		blackList[size-1]=num;
    }
    if(size<3)
    {
    	size++;
	}
}
void Group::removeFromList(int num)
{
    for(int i=0;i<size;i++)
    {
        if (blackList[i]==num)
        {
            if(i==size-1)
            {
                blackList[i]=0;
                size--;
            }
            else {
                for (int j = i; j < size-1; j++) {
                    blackList[j] = blackList[j+1];
                }
                size--;
            }
        }
    }
}
```

