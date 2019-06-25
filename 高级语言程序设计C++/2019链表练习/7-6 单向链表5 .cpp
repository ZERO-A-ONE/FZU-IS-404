#include<iostream>
#include<string>
#include<stack>
using namespace std;
int score = 0;
struct Node{
	int num;
	string name;
    int score; 
    struct Node *next; 
};
Node* create();
Node *del(Node *head);
void display(Node *head);

int main()
{
	Node *head;
	head = create();
	cin >> score;
	head =del(head);
	display(head);
	return 0;
}

Node* create(){
    int num;
	string name;
    int score; 
    Node *head=NULL, *p, *q;
    cin>>num;
    while(num!=0){
    	cin>>name;
    	cin>>score;
        q=new Node;
        q->num=num;
        q->name=name;
        q->score=score;
        q->next=NULL;
        if(head==NULL) 
	   		head=p=q;
        else{
            	p->next = q;
            	p = p->next;
     		}
    cin>>num;
  	}
	return head;
}
Node *del(Node *head){
    if(head==NULL) 
		return head;
    head->next = del(head->next);
    if(head->score < score ){
    	Node *q=head;
    	head = head->next;
    	delete q;
   		}
   	return head;
}
void display(Node *head){
    if(head==NULL)
		return;
    cout<<head->num<<' '<<head->name<<' '<<head->score;
    if(head->next != NULL){
    	cout<<endl;
    	display(head->next);
   	}
}
