//6-1 计算正方体体积与表面积
class Box{
	private:
		float a,volume,area;
	public:
		Box(float x):a(x){a=x;}
		Box(){}
		void seta(float a2)
		{
			a=a2;
		}
		void getarea(){
			area=6*a*a;
		}
		void getvolume(){
			volume=a*a*a;
		}
		void disp()
		{
			cout<<volume<<' '<<area<<endl;
			
		}
};

//6-2 奇偶分离排序
bool compare(int a,int b)
{
	return a>b;
}
void sort_array(int* a)
{
	int js[10];
	int os[10];
	int j=0;
	int k=0;
	for(int i = 0;i<10;i++)
	{
		if((a[i]%2)!=0)
		{
			js[j] = a[i];
			j++;
		}
	}
	sort(js,js+j,compare);
	for(int i = 0;i<10;i++)
	{
		if((a[i]%2)==0)
		{
			os[k] = a[i];
			k++;
		}
	}
	sort(os,os+k);
	if(k==0)
	{
		for(int i=0;i<j;i++)
		{
			if(i < j-1)
			{
				cout << js[i]<<' ';
			}
			if(i == j-1)
			{
				cout << js[i];
			}
		}		
	}
	else
	{
		for(int i=0;i<j;i++)
		{
			cout << js[i]<<' ';
		}
	}
	for(int i=0;i<k;i++)
	{
		if(i < k-1)
		{
			cout << os[i]<<' ';
		}
		if(i == k-1)
		{
			cout << os[i];
		}
	}
}
//6-3 学生最高i分 
void max(STU* arr)
 {
 	float max = arr[0]->score;
 	for(int i = 0;i < 5;i++)
 	{
 		if(arr[i]->score>=max)
 		{
 			max = arr[i]->score;
		 }
	 }
	for(int i = 0;i < 5;i++)
 	{
 		if(arr[i]->score==max)
 		{
 			cout<<arr[i]->num<< ' ' << arr[i]->score<<endl;
	 	}
 }
}
//6-4 运算符重载（三进制混合四则运算）
#include<string>
#include<cmath>
#include<cstdio>
#include<cstdlib> 
#include<sstream>
char *myitoa(long num,char *str,long radix) 
{  
	/* 索引表 */ 
	char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
	long unum; /* 中间变量 */ 
	int i=0,j,k; 
	/* 确定unum的值 */ 
	if(radix==10&&num<0) /* 十进制负数 */ 
	{ 
		unum=(unsigned)-num; 
		str[i++]='-'; 
	} 
	else unum=(unsigned)num; /* 其它情况 */ 
	/* 逆序 */ 
	do  
	{ 
		str[i++]=index[unum%(unsigned)radix]; 
		unum/=radix; 
	}while(unum); 
	str[i]='\0'; 
	/* 转换 */ 
	if(str[0]=='-') k=1; /* 十进制负数 */ 
	else k=0; 
	/* 将原来的“/2”改为“/2.0”，保证当num在16~255之间，radix等于16时，也能得到正确结果 */ 
	char temp; 
	for(j=k;j<=(i-k-1)/2.0;j++) 
	{ 
		temp=str[j]; 
		str[j]=str[i-j-1]; 
		str[i-j-1]=temp; 
	} 
	return str; 
} 
class Ter{
	private:
		string source;
		long tree;
		long ten;
		long tensize;
		long treesize;
		int flag;//flag输出进制数0为3，1为10 
	public:
		Ter(){
			source = "0";
			ten = 0;
			tree = 0;
			tensize = 0;
			treesize = 0;
			flag=0; 
		}
		Ter(string a,int b){
			source = a;
			flag=b;
			ten = 0;
			tree = 0;
			tensize = 0;
			treesize = 0;
			long len = source.length();
			long tmp = 0;
			for(int i = len-1;i > -1;i--)
			{
				tree = tree+(long)((source[i]-48)*pow(10.0,tmp));
				tmp++;
			}
			treesize = tmp;
			tmp = 0;
			for(int i = len-1;i > -1;i--)
			{
				ten = ten+(long)((source[i]-48)*pow(3.0,tmp));
				tmp++;
			}
			long tentmp = ten;
			while(tentmp)
			{
				tentmp/=10;
				tensize++;
			}
		}
		void star()
		{
			ten = 0;
			tree = 0;
			tensize = 0;
			treesize = 0;
			flag = 0;
			long len = source.length();
			long tmp = 0;
			for(int i = len-1;i > -1;i--)
			{
				tree = tree+(long)((source[i]-48)*pow(10.0,tmp));
				tmp++;
			}
			treesize = tmp;
			tmp = 0;
			for(int i = len-1;i > -1;i--)
			{
				ten = ten+(long)((source[i]-48)*pow(3.0,tmp));
				tmp++;
			}
			long tentmp = ten;
			while(tentmp)
			{
				tentmp/=10;
				tensize++;
			}
		}
		long showtree(){
			return tree;
		}
		long showten(){
			return ten;
		}
		long showtensize(){
			return tensize;
		}
		long showtreesize(){
			return treesize;
		}
		Ter operator+(const Ter& ter1)
		{
			long tmp = this->ten + ter1.ten;
			char s[1000];
			string b;
			myitoa(tmp,s,3);
			b = s;
			Ter re(b,ter1.flag);
			return re; 
		}
		Ter operator*(const Ter& ter1)
		{
			long tmp = this->ten * ter1.ten;
			char s[1000];
			string b;
			myitoa(tmp,s,3);
			b = s;
			Ter re(b,this->flag);
			return re; 
		}
		Ter operator/(int b)
		{
			long tmp = this->ten / b;
			char s[1000];
			string c;
			myitoa(tmp,s,10);
			c = s;
			Ter re(c,1);
			return re; 
		}
		friend Ter operator/(const int b, Ter obj)
		{
			long tmp = b / obj.ten;
			char s[1000];
			string c;
			myitoa(tmp,s,10);
			c = s;
			Ter re(c,1);
			return re; 
		} 
		friend istream &operator>>( istream  &input, Ter &D )
      	{ 
         	input >> D.source;
         	D.star();
         	return input;            
      	}
		friend ostream &operator<<( ostream &output, const Ter &D )
      	{ 
      		if(D.flag == 0)
      		{
      			output <<D.tree;
         		return output;
			}
			if(D.flag == 1)
			{
				output <<D.ten;
         		return output;
			}         
      	}
};
//6-5 2017Final 乐观的中考生
Task* getBatch(int m){
 	int ID;//任务编号
    int key;//任务优先级
    int load;//任务持续时间
    cin >> key;
    Task *head=NULL,*p,*q;
    for(int i = 0;i < m;i++)
    {
    	cin >> ID;
    	cin >> load;
    	q = new Task;
    	q->ID = ID;
    	q->key = key;
    	q->load = load;
    	q->next = NULL;
    	if(head == NULL)head=p=q;
    	else{
    		p->next = q;
    		p = p->next;
		}
	}
	return head;
 }
void display(Task *head, int m){
 	Task *index = head;
 	int point = 0;
 	while(index){
 		point++;
 		if(point==3){
 			cout << index->ID<<" "<<index->key<<" "<<index->load<<endl;
		 }
		 index = index->next;
	 }
	 if(point < 3)
	 {
	 	cout<<"OK"<<endl;
	 }
 }
Task* addBatch(Task *head, Task *h){
 	if(head==NULL){
    head = h;
    return head; //加上这句。
    }
	 else{
		if(head->key >= h->key)//新任务优先级最高（key最小） 
		{
			Task *index = h;
			while(h->next){
 				h=h->next;
	 		}
	 		h->next = head;
	 		return index;
		}
		if(head->key < h->key)
		{
			Task *aa = head;
			{
				while(aa->next)
				{
					aa=aa->next;//取现有任务最低优先级 
				}
				if(aa->key <= h->key )//新任务优先级最高（key最大） 
				{  
					aa->next =  h;
					return head;
				}
				if(aa->key > h->key)//新任务处于中间优先级 
				{
					Task *bb =head;
					while(1)//取出插入节点位置 
					{
						if(bb->next->key >= h->key){
							break;
						}
						bb = bb->next; 
					}
					Task *p = bb->next;
					Task *q = h;
					while(q->next)//取到新任务末端 
					{
						q = q->next;
					}
					bb->next = h;
					q->next = p;
					return head;
				}
			}
		}	
	 }	
}
Task* dell1(Task *head,int ID)
{
	if(head==NULL)return head;
	head->next = dell1(head->next,ID);
	if(head->ID == ID)
	{
		Task *q=head;
		head = head->next;
		delete q;
	 } 
	 return head;
}
Task* dell(Task *head,int line[],int number){
	for(int i = 0;i < number;i++)
	{
		int ID = line[i];
		head = dell1(head,ID);
	}
	return head;
}
Task* study(Task*head, int mi, int ma, int load){
	Task *index = head;
	int line[10000];//待删除ID列表 
	int number = 0;
	while(index)
	{
		if(index->load >= mi && index->load <= ma)
		{
			load = load - index->load;
			if(load < 0 )
			{
				break;
			}
			line[number] = index->ID;
			number++;
		}
		index = index->next;
	}
	for(int i = 0;i < number;i++)
	{
		int ID = line[i];
	}
	head = dell(head,line,number);
	return head;
}