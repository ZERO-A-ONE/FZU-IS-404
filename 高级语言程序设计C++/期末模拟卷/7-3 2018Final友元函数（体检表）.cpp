#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
using namespace std;
class Exam{
	private:
		string num;
		int disease[10];
		int count;
	public:
		Exam(){	}
		Exam(string num):num(num){}
		string getnum()
		{
			return num;
		}
		int getcount()
		{
			return count;
		}
		void px()
		{
			sort(disease,disease+count,less<int>());
		}
		void setnum(string num)
		{
			this->num = num;
		}
		void setcount(int a)
		{
			this->count = a;
		}
		void setdisease(int a,int index)
		{
			this->disease[index] = a;
		}
		friend void print(Exam*e, int count, int *d)
		{
			for(int i = 0;i<10;i++)
			{
				int nil  = d[i];//值得关注疾病 
				for(int j=0;j<count;j++)//遍历学生 
				{
					int tmp = e[j].count;//学生疾病数 
					for(int k=0;k<tmp;k++)
					{
						if(e[j].num!= "-1"&&e[j].disease[k] == nil)
						{
							cout<<e[j].num<<' '<<nil<<endl;
							e[j].num = "-1";
							break;
						}
					}
				}
			}
		}
};
bool complare(Exam a,Exam b)
{
	return a.getnum()>b.getnum();
}
int main()
{
	Exam list[300];
	string num;
	int count = 0;//学生数 
	cin >> num;
	while(num != "0")
	{
		list[count].setnum(num);
		int nilu = 0;//疾病数 
		cin >> nilu;
		list[count].setcount(nilu);
		if(nilu > 0)//输入疾病编号 
		{
			for(int i = 0;i<nilu;i++)
			{
				int nil = 0;
				cin >> nil;
				list[count].setdisease(nil,i);
			}
			list[count].px();
		}
		if(nilu==0)
		{
			
		}
		count++;
		cin >> num;
	}
	sort(list,list+count,complare);
	int import[10] = {0};
	int impoco = 0;//值得关注的疾病数 
	int impo = 0;
	cin >> impo;//输入值得关注的疾病 
	while(impo != 0)
	{
		import[impoco] = impo;
		impoco++;
		cin>>impo;
	}
	sort(import,import+impoco,less<int>());
	print(list,count,import);
	return 0;
}