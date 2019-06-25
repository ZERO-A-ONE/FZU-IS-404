#include<iostream>
using namespace std;
struct node
{
	int num;
	node *next;
 };
node *create(int n)
{
	node *head=NULL,*p,*q;
	int num,i;
	for(i=0;i<n;i++)
	{
		q=new node;
		cin>>num;
		q->num=num;
		q->next=NULL; 
		if(head==NULL)
		{
			p=q;
			head=p;
		}
		else
		{
			p->next=q;
			p=p->next;
		}
	}
	return head;
}
node *insert(node *head,int n,int m)
{
	node *p,*q=head; 
	p=new node;
	int i;
	p->num=m;
	 for(i=0;i<n;i++)
	 {
	 	if(q->num>m)
	 	{
	 		head=p;
	 		p->next=q;
	 		break;
		 }
	 	if(q->num<=m&&q->next!=NULL&&q->next->num>=m)
	 {
	 	p->next=q->next;
	 	q->next=p;
		q=p;
		break;
	 }
	else if(q->next==NULL)
	{
		q->next=p;
		p->next=NULL;
		break;
	}
	q=q->next;
	}
	 return head;
}
void display(node *head)
{
	if(head==NULL)
	{
		return ;
	}
		cout<<head->num<<" ";
		if(head->next->next!=NULL)
		display(head->next);
}
int main()
{
	int repeat,i,n,m;
	node *head,*p;
	p=head;
	cin>>repeat;
	for(i=0;i<repeat;i++)
	{
		cin>>n;
		head=create(n);
		cin>>m;
		head=insert(head,n,m);
		cout<<"size="<<n+1<<":";
		display(head); 
		while(head->next!=NULL)
		{
			
			head=head->next; 
			p=head;
		}
		cout<<p->num;
		if(i<repeat-1)
		cout<<endl;
	}
	
	return 0;
 } 
