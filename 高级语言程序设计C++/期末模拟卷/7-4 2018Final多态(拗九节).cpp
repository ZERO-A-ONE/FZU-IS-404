#include<iostream>
#include<cmath>
using namespace std;
class Group
{
	protected:
		int length;
		public:
			virtual void display()=0;
			Group(int lengt=0):length(length){}
			void set(int s)
		{
			length=s;
		}
};
class BioGroup:public Group
{
	public:
		string c;
		static int max1,max3;
		int num;
		BioGroup(string c="0",int num=0,int length=0):Group(length)
		{
			this->c=c;
			this->num=num;
		}
		virtual void display()
		{
			cout<<num<<" ";
			if(num>=2)
			{
				if(c=="C")
				cout<<"cats, ";
				if(c=="D")
				cout<<"dogs, ";
			}
			else
			{
				if(c=="C")
				cout<<"cat, ";
				if(c=="D")
				cout<<"dog, ";
			}
			cout<<length<<" ";
			if(length>=2)
			cout<<"seconds"<<endl;
			else
			cout<<"second"<<endl; 
		}
};
class ArtGroup:public Group
{
	public:
		string c;
		static int max2,max4;
		ArtGroup(string c="0",int length=0):Group(length)
		{
			this->c=c;
		}
		
		virtual void display()
		{			
				if(c=="S")
				cout<<"sing, ";
				if(c=="D")
				cout<<"dance, ";
			cout<<length<<" ";
			if(length>=2)
			cout<<"minutes"<<endl;
			else
			cout<<"minute"<<endl; 
		}
};
int BioGroup::max1=0;
int BioGroup::max3=0;
int ArtGroup::max2=0;
int ArtGroup::max4=0;
int main()
{
	Group *g[20];
	int count=0;
	char s;
	int num,length;
	string str;
	cin>>s;
	while(s!='E')
	{
		cin.get();
		switch(s)
		{
			case 'B':cin>>str>>num>>length;cin.get();g[count]=new BioGroup(str,num,length);
					if(str=="C")
					{
						if(length>BioGroup::max1) BioGroup::max1=length;g[count]->set(BioGroup::max1);count++;break;
					}
					if(str=="D")
					{
						if(length>BioGroup::max3) BioGroup::max3=length;g[count]->set(BioGroup::max3);count++;break;
					}
			case 'A':cin>>str>>length;cin.get();g[count]=new ArtGroup(str,length);
					if(str=="S")
					{
						if(length>ArtGroup::max2) ArtGroup::max2=length;g[count]->set(ArtGroup::max2);count++;break;
					 } 
					 if(str=="D")
					 {
					 	if(length>ArtGroup::max4) ArtGroup::max4=length;g[count]->set(ArtGroup::max4);count++;break;
					 }
		}
		cin>>s;
	}
	int ty;
	cin>>ty;
	while(ty!=0)
	{
		g[ty-1]->display();
		cin>>ty;
	}
	return 0;
 }
