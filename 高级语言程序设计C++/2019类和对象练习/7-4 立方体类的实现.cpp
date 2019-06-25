#include<iostream>
using namespace std;
class Box
{
	public:
	float ab;	
	void seta(float a)
	{
		ab=a;
	}
	int getvolume()
	{
		float a;
		a=ab*ab*ab;
		return a;
	}
	int getarea()
	{
		float a;
		a=ab*ab*6;
		return a;
	}
	void disp()
	{
		cout<<getvolume()<<" "<<getarea()<<endl;
	}			
};
int  main( )
{
    float ab;
    cin>>ab;
    Box  obj;
    obj.seta( ab );
    obj.getvolume( );
    obj.getarea( );
    obj.disp( );
    return 0;
}
