#include<iostream>
using namespace std;
struct Node{
     int data; 
     struct Node *next; 
};
void removeAll(Node *head){
      if(head!=NULL){
              removeAll(head->next);
             delete head;
        }
}
Node* create(){
       int data;
        Node *head=NULL, *p, *q;
        cin>>data;
        while(data!=-1){
            q=new Node;
            q->data=data;
            q->next=NULL;
       if(head==NULL) head=p=q;
          else{
                       p->next = q;
            p = p->next;
        }
      cin>>data;
   }
  return head;
}
Node *del(Node *head){ 
     if(head==NULL) return head;
     head->next = del(head->next);
     if(head->data %2==1){
      Node *q=head;
      head = head->next;
      delete q;
    }
    return head;
}
void display(Node *head){
    if(head==NULL)return;
    cout<<head->data;
    if(head->next!=NULL){
     cout<<' ';
     display(head->next);
    }else cout<<endl;
}
int main(){
    int i, repeat;
    Node *head;
    cin>>repeat;
    for(i=0; i<repeat;i++){
    head = create();
    head = del(head);
    display(head);
    removeAll(head);
    }
   return 0;
}
