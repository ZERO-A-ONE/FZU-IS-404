//6-1 写出派生类构造方法（C++）
:People(id,name)
    {
    	this->sid = sid;
    	this->score = score;
//6-2 狗的继承
#include<iostream>
#include<cstring>
using namespace std;
class Animal{
   int age;
  public:
   Animal(int a){//构造函数
     age=a;
   }
   int getAge(){
     return age;
   }
};
class Dog:public Animal{//共有继承Animal基类
   char *color;
  public:
   Dog(int a,const char *c):Animal(a){
   	 color=new char[20];//创建空间
   	 strcpy(color,c);
   }
   void showInfor()
   {
     cout<<"age:"<<getAge()<<endl;
     cout<<"color:"<<color;
   }
};
//6-3 派生类使用基类的成员函数
class Animal{
	private:
		int m_nWeightBase;
		int m_nAgeBase;
	public:
		Animal(){}
		void set_weight(int nWeightBase){
			this->m_nWeightBase = nWeightBase;
		}
		int get_weight(){
			return m_nWeightBase;
		}
		void set_age(int nAgeBase){
			this->m_nAgeBase = nAgeBase;
		}
		int get_age(){
			return m_nAgeBase;
		}
};
class Cat:public Animal
{
	private:
		string m_strName;
	public:
		Cat(string str){
			m_strName = str;
		}
		void print_age(){
			cout << m_strName <<", age = "<<get_age()<<endl;
		}
};
//6-4 私有继承派生类使用基类的成员函数 
class Animal{
	private:
		int m_nWeightBase;
		int m_nAgeBase;
	public:
		Animal(){}
		void set_weight(int nWeightBase){
			this->m_nWeightBase = nWeightBase;
		}
		int get_weight(){
			return m_nWeightBase;
		}
		void set_age(int nAgeBase){
			this->m_nAgeBase = nAgeBase;
		}
		int get_age(){
			return m_nAgeBase;
		}
};
class Cat:public Animal
{
	private:
		string m_strName;
	public:
		Cat(string str){
			m_strName = str;
		}
		void set_print_age(){
			set_age(5);
			cout << m_strName << ", age = "<<get_age()<<endl;
		}
		void set_print_weight(){
			set_weight(6);
			cout << m_strName << ", weight = "<<get_weight()<<endl;
		}
};
//6-5 账户类
Account::Account(string name):userName(name){
	userName=name;
}
void Account::PrintUserName()
{
	cout << userName << endl;
}
CreditAccount::CreditAccount(string name, int credit) : Account(name), credit(credit){}
void CreditAccount::PrintInfo(){
	PrintUserName();
    cout << credit << endl;
}