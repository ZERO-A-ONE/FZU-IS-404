//6-1 数组排序输出（函数模板）
template <class A>
void sort(A *a, int size){
	A tmp;
	for(int i = 0;i < size;i++)
	{
		cin >> a[i];
	}
	for(int i = 0;i<size-1;i++)
	{
		for(int j = i;j < size;j++)
		{
			if(a[i]>a[j])
			{
				tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}
	}
}
//6-2 使用类计算矩形的面积 
void Rectangle::setLength(int l)
{
	length=l;
}
void Rectangle::setWidth(int w)
{
	width=w;
}
int Rectangle::getArea()
{
	int area;
	area=width*length;
	return area;
}
//6-3 体育俱乐部I（构造函数）
Club::Club(string n1, int y, string n2, int wr):c(n2,wr)
{
	name=n1;
	year=y;
}
void Coach::show()
{
	cout<<name<<" "<<winRate<<"%";
}
void Club::show()
{
	cout<<name<<" "<<year<<endl;
	c.show();
}
//6-4 有序数组（类模板）
template<class T>
class MyArray{
private:
    T *data;
    int size;
public:
    MyArray(int s);
    ~MyArray();
    void sort();
    void display();
    bool check();
};
template<class T>
MyArray<T>::MyArray(int s){
        size = s;
        data = new T[size];
        for(int i=0;i<size;i++)
            cin>>data[i];
    }
template<class T>
void MyArray<T>::display(){
    for(int i=0;i<size;i++){
        cout<<data[i];
        if(i<size-1)
            cout<<" ";
    }
    cout<<endl;
}
template<class T>
void MyArray<T>::sort(){
        for(int i=0;i<size-1;i++)
            for(int j=0;j<size-i-1;j++)
                if(data[j]>data[j+1]){
                    T temp = data[j];
                    data[j] = data[j+1];
                    data[j+1] = temp;
                }
}
//6-5 2017final友元函数之全班同学的平均绩点
double averagegrade(student *stu, int count)
{
  int i,j;
  double sum1=0,sum2=0,sum;
  for(i==0;i<count;i++)
    for(j=0;stu[i].score[j]!=-1;j++)
      {
      	sum1+=stu[i].score[j]*(stu[i].grade[j]/10-5);
      	sum2+=stu[i].score[j];
      }
  if(sum2==0||sum1==0)
   return 0;
  return sum1/sum2;
}
//6-6 定义Date类 
class Date
{
	private:
		int year,month,day;
		public :
			Date(int d=1,int m=1,int y=2019)
			{
				year=y;
				month=m;
				day=d;
			}
			void display()
			{
				cout<<day<<"/"<<month<<"/"<<year<<endl;
			}
 } ;
//6-7 复数类重载加法、减法和乘法运算符
complex::complex(float r,float i)
{
	real=r;
	imag=i;
}
complex complex::operator+(const complex &op2) const
{
	complex c;
	c.imag=imag+op2.imag;
	c.real=real+op2.real;
	return c;
}
complex complex::operator-(const complex &op2) const
{
	complex c;
	c.imag=imag-op2.imag;
	c.real=real-op2.real;
	return c;
} 
complex complex::operator*(const complex &op2) const
{
	complex c;
	c.real=real*op2.real-imag*op2.imag;
	c.imag=real*op2.imag+op2.real*imag;
	return c;
}
//6-8 时间相加
Time::Time(int h,int m,int s)
{
	hours=h;
	minutes=m;
	seconds=s;
}
Time Time::operator +(Time &a)
{
	Time b;
	b.seconds=a.seconds+seconds;
	b.minutes=a.minutes+minutes;
	b.hours=a.hours+hours;
	if(b.seconds>=60)
	{
		b.seconds-=60;
		b.minutes++;
	}
	if(b.minutes>=60)
	{
		b.minutes-=60;
		b.hours++;
	}
	return b;
}
void Time::DispTime()
{
	cout<<hours<<"h:"<<minutes<<"m:"<<seconds<<"s";
}
