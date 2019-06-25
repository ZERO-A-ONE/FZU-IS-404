#include<iostream>
#include <stack>
using namespace std;
stack<int> mystack;
struct Node{
     int data; 
     struct Node *next; 
};
Node* create(){
    int data;
    Node *head=NULL, *p, *q;
    cin>>data;
    while(data!=-1){
        q=new Node;
        q->data=data;
        q->next=NULL;
        if(head==NULL) 
	   		head=p=q;
        else{
            	p->next = q;
            	p = p->next;
     		}
    cin>>data;
  	}
	return head;
}
void display(Node *head){
    if(head==NULL)
		return;
    cout<<head->data;
    if(head->next!=NULL){
    	cout<<' ';
    	display(head->next);
    }else 
   		cout<<endl;
}
void st(Node *head){
    if(head==NULL)
		return;
    mystack.push(head->data);
    if(head->next!=NULL){
    	st(head->next);
    }
}
int main(){
    int i;
    Node *head;
	head = create();
	st(head);
	int len = mystack.size();
	for(int i = 0;i < len;i ++)
	{
		if(i < len-1)
		{
			cout << mystack.top()<< ' ';
			mystack.pop();
		}
		else
		{
			cout << mystack.top();
			mystack.pop();
		}	
	}
  	return 0;
}

