
#include<iostream>  
#include<iomanip>  
using namespace std;  
 
class vehicle  
{  
protected:  
	int wheels;  
	float weight;  
	
public:  
	vehicle(float wh,float we):wheels(wh),weight(we){};  
	int get_wheels(){return wheels;}  
	float get_weight(){return weight;}  
	float wheel_load(){return weight/wheels;}  
	void print()
	{  
		cout<<"weight "<<weight<<" Kg and wheels "<<wheels<<endl;  
	}
};  
 
class car:protected vehicle  
{ 
private: 
	int passenger_load;  
	
public:  
	car(float wh,float we,int pa):vehicle(wh,we),passenger_load(pa){};  
	int get_passenger(){return passenger_load;}  
	void print()
	{  
		cout<<"passenger_load "<<passenger_load<<" weight "
		<<weight<<" Kg and wheels "<<wheels<<endl;  
	}	 
};  
 
class truck:protected vehicle  
{
private:
    int passenger_load;  
    int payload;  
public:  
    truck(float wh,float we,int pa,int load):vehicle(wh,we),passenger_load(pa),payload(load){};  
    int get_passengers(){return passenger_load;}  
    float efficiency(){return payload/(payload+weight);}  
    void print()
	{  
		cout<<"passenger_load "<<passenger_load<<" weight "<<weight
		<<" Kg wheels "<<wheels<<" and efficiency "<<setiosflags(ios::fixed)
		<<setprecision(2)<<efficiency()<<setprecision(0)<<endl;  
	}
};  
  
int main()  
{  
    string type;  
    int ID,wheel,weight,passenger_load,payload,i=1;  
    cin>>type;  
    while(type!="-1")  
    {  
		cin>>ID>>wheel>>weight;  
		cout<<"The "<<i<<""; 
		if(i==1)
			cout<<"st";  
		else if(i==2)  
			cout<<"nd";  
		else if(i==3)  
			cout<<"rd";  
		else  
			cout<<"th";  
		i++;  
		cout<<" object is ";  
		if(type=="vehicle")  
		{  
			cout<<"Vehicle"<<" No. "<<ID<<": ";  
			vehicle t(wheel,weight);  
			t.print();  
		}  
		if(type=="car")  
		{  
			cin>>passenger_load;  
			cout<<"Car"<<" No. "<<ID<<": ";  
			car t(wheel,weight,passenger_load);  
			t.print();  
		}  
		if(type=="truck")  
		{  
			cin>>passenger_load>>payload;  
			cout<<"Truck"<<" No. "<<ID<<": ";  
			truck t(wheel,weight,passenger_load,payload);  
			t.print();  
		}  
		
		cin>>type;  
    }  
    
	return 0;  
}
