#include<iostream>
using namespace std;
class Complex{
   double real,image;
  public:
   Complex()
   {
     real=0;
     image=0;
   }
   void get(double r,double i)
   {
     real=r;
     image=i;
   }
   void fan()
   {
     real=-real;
     image=-image;
   }
   void Print()
   {
     cout<<"("<<real<<", "<<image<<")"<<endl;
   }
   friend void jiao(Complex ob1,Complex ob2)
   {
     cout<<"("<<ob1.real+ob2.real<<", "<<ob1.image+ob2.image<<")"<<endl;
   }
};
int main(void)
{
  double c11,c12,c21,c22;
  cin>>c11>>c12>>c21>>c22;
  Complex ob1,ob2;
  ob1.get(c11,c12);
  ob2.get(c21,c22);
  jiao(ob1,ob2);
  ob2.fan();
  jiao(ob1,ob2);
  ob2.fan();
  ob2.Print();
}