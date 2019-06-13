#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

class Person {
protected:
     string name;
     int age;
public:
     Person();                  
     Person (string a, int b) : name(a), age (b){};
     void display () {cout<<name<<":"<<age<<endl;}
};

class Student : public Person{
    int ID;
    float cpp_score;
    float cpp_count;
    float cpp_grade;
public:
    void display(){cout<<ID<<" "<<name<<" "<<setiosflags(ios::fixed)<<setprecision(1)<<cpp_grade<<endl;}
    Student(string a, int b , int c ,float d ,float e) : 
    Person(a,b), ID(c) , cpp_score(d) , cpp_count(e) {cpp_grade = cpp_score * 0.9 + cpp_count * 2;}
};
int main()
{
    string name;
    int age, num,count;
    float score;
    cin>>name;
    while(name[0]!='0')
    {
        cin>> num>> age>> score >> count; 
        Student hello(name, age, num, score, count);
        hello.display();
        cin>>name;
    }


    return 0;
}