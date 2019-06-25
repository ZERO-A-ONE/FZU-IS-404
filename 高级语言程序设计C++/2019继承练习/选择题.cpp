//6-1 多重继承 
#include<iostream>
#include<string>
using namespace std;
class Graduate
{
	private :
		string name;
		int age;
		float score;
		char sex;
		string title;
		double wage;
		public:
			Graduate(string name,int age,char
			 sex,string title,float score,double wage)
			{
				this->name=name;
				this->age=age;
				this->sex=sex;
				this->title=title;
				this->score=score;
				this->wage=wage;
			}
			void show()
			{
				cout<<"name:"<<name<<endl;
				cout<<"age:"<<age<<endl;
				cout<<"sex:"<<sex<<endl;
				cout<<"score:"<<score<<endl;
				cout<<"title:"<<title<<endl;
				cout<<"wages:"<<wage;
			}
};
//6-2 派生类的定义和使用 
class animal
{
	public:
		void speak()
		{
			cout<<"animal language!";
		}
		
};
class Cat:public animal
{
	private:
		string name;
		public:
			Cat(string name):name(name){}
			void print_name()
			{
				cout<<"cat name: "<<name<<endl;
			}
};
//6-3 长方形派生
class Box:public Rectangle
{
	private:
		double high;
		public :
			Box(double l, double w,double high):Rectangle(l,w)
			{
				this->high=high;
			}
			double volume()
			{
				return high*area();
			}
};
//6-4 学生排名表（析构函数）
Student *t;
	for(int i=0;i<count;i++)
	{
		for(int j=i;j<count;j++)
		{
			if(pS[i]->getRank()>pS[j]->getRank())
			{	
				t=pS[i];
				pS[i]=pS[j];
				pS[j]=t;
			}
		}
	}
	for(int i=0;i<count;i++)
	{
		 delete pS[i];
	}
//6-5 学生成绩的快速录入（构造函数） 
class Student
{
	private:
		int score;
		int flag;
		public :
			static int count;
			Student(int score,int flag):flag(flag),score(score){
			count++;
			}
			Student(Student &p)
			{
				flag=p.flag;
				score=p.score+1;
				count++;
			}
			void display()
			{
				cout<<score;
				if(flag)
				{
					cout<<" Pass"<<endl;
				}
				else
				{
					cout<<" Fail"<<endl;
				}
			}
};
int Student::count=0;
//6-6 有序数组（类模板）
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
        data =new  T[size];//注意分配内存，main函数调用的时候只是动态的创建一个对象
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
//6-7 学生成绩的输入和输出（运算符重载）
class Student
{
	private:
		int score;
		string name;
		static int count;
		public:
			Student(int s=0,string n="0"):score(s),name(n){}
			friend ostream& operator<<(ostream& out,Student &c)
			{
				if(c.score>=60)
				out<<count<<". "<<c.name<<" PASS";
				else
				 out<<count<<". "<<c.name<<" FAIL";
				 count++;
				 return out;
			}
			friend istream& operator>>(istream& in,Student &c)
			{
				in>>c.name>>c.score;
				return in;
			}
};
 int  Student::count= 1;
 //6-8 数组排序输出（函数模板）
 template <class T>
void sort(T *a,int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		cin>>a[i];
	}
	T max;
	for(i=0;i<size;i++)
	{
		for(int j=i;j<size;j++)
		{
			if(a[j]<a[i])
			{
				max=a[j];
				a[j]=a[i];
				a[i]=max;
			}
		}
	}
	
}
//6-9 二维数组（海绵城市）
bool test(int a[N][N],int m,int n)
{
	int count=0;
	int b[10000]={0},i,j;
	for(i=1;i<=20;i++)
	{
		for(j=1;j<=20;j++)
		{
			if(a[i][j])
			{
				b[count]=i*10+j;
				count++;
			}
		}
	}
	int c=count;
	for(i=0;i<c;i++)
	{
		for(j=0;j<c;j++)
		{
			if(b[i]%10==b[j]/10&&b[i]/10!=b[j]%10)
			{
				b[count]=b[i]/10*10+b[j]%10;
				count++;
			}
		}
	}
	int k=m*10+n;
	for(i=0;i<count;i++)
	{
		if(k==b[i])
		return true;
	}
	return false;
}