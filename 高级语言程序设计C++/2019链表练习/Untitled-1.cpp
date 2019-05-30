# 6-1 2018Final链表(龙舟队)

```c++
Player *create(){
	Player *head=NULL;
	Player *p;
	while(1){
		Player *q=new Player;
		int a;
		cin>>a;
		if(a==-1)
		return head;
		else{
			if(a==0)
			q->drummer=false;
			else
			q->drummer=true;
		}
		cin>>q->num>>q->grade;
		if(head==NULL){
			head=q;
		}
		else if((q->drummer==true&&(head->drummer==false||head->num>q->num))||(head->drummer==false&&p->drummer==false&&q->num<head->num)){
			q->next=head;
			head=q;
		}
		else{
			int f=0;
			for(p=head;p->next!=NULL;){
			if(q->drummer==true){
				for(;p->next!=NULL;){
					if(p->next->num<q->num&&p->next->drummer==true)
						p=p->next;
					else{
						q->next=p->next;
						p->next=q;
						f=1;
						break;
					}
				}
				if(f)
				break;
				if(p->next==NULL){
					p->next=q;
					break;
				}
			}	
			else if(q->drummer==false){
				for(;p->next!=NULL;){
					if(p->next->num<q->num||p->next->drummer==true)
						p=p->next;
					else{
						q->next=p->next;
						p->next=q;
						f=1;
						break;
					}
				}
				if(f)
				break;
			}
		}
		if(p->next==NULL&&f==0)
			p->next=q;
	}
	}
} 
Player* addPlayer(Player* head, Player* q){
	Player *p=head;
	if(q->drummer==true&&(p->drummer==false||p->num>q->num)){
		q->next=p;
		return q;
	}
	if(q->drummer==false&&p->drummer==false&&q->num<p->num){
		q->next=p;
		return q;
	}
	if(q->drummer==true){
		for(;p->next!=NULL;){
			if(p->next->num<q->num&&p->next->drummer==true)
				p=p->next;
			else{
				q->next=p->next;
				p->next=q;
				return head;
			}
		}
		if(p->next==NULL){
			p->next=q;
			return head;
		}
	}
	else if(q->drummer==false){
		for(;p->next!=NULL;){
			if(p->next->num<q->num||p->next->drummer==true)
				p=p->next;
			else{
				q->next=p->next;
				p->next=q;
				return head;
			}
		}
		if(p->next==NULL){
			p->next=q;
			return head;
		}
	}
}
Player* removePlayer(Player *head, int num){
	Player *p=head;
	if(p->num==num){
		if(p->next->drummer==false){
			Player *q=p->next;
			Player *t=q;
			int h=q->num;
			int g=q->grade;
			if(p->next->drummer==false){
				for(;q->next!=NULL;){
					if(q->grade>g){
						g=q->grade;
						h=q->num;
						t=q;
					}
					else if(q->grade==g&&q->num<h){
						g=q->grade;
						h=q->num;
						t=q;
					}
					else
					q=q->next;
				}
				if(q->grade>g){
					g=q->grade;
					h=q->num;
					t=q;
				}
				else if(q->grade==g&&q->num<h){
					g=q->grade;
					h=q->num;
					t=q;
				}
				t->drummer=true;
				if(t==head->next)
				return head->next;
				for(q=head->next;q->next!=NULL;){
					if(q->next==t){
						if(t->next!=NULL)
						q->next=t->next;
						else
						q->next=NULL;
						t->next=p->next;
						return t; 
					}
					else
						q=q->next;
				}
			}
		}
		return p->next;
	}
	for(;p->next!=NULL;){
		if(p->next->num==num){
			if(p->next->next!=NULL)
				p->next=p->next->next;
			else
				p->next=NULL; 
		}
		else
			p=p->next;
	}
	return head;
}
```

# 6-2 单链表最大值

```c++
struct Node* buildLinkedList(int* arr, int n)
{
	Node *head=NULL,*p,*q;
	int i;
	 for(i=0;i<n;i++)
	 {
	 	p=(Node*)malloc(sizeof(Node));
	 	p->data=arr[i];
	 	p->next=NULL;
	 	if(head==NULL)
	 	{
	 		head=p;
		 	q=p;
		 }
		 else
		 {
		 	q->next=p;
		 	q=p;
		 }
	 }
	 return head;
 } 
struct Node* getMax(struct Node* head)
{
	Node *max=head,*q=NULL;
	if(head==NULL)
	return q;
	else
	{
		do
		{
			if(head->data>=max->data)
			{
				max=head;
			}
			head=head->next;
		}
		while(head->next!=NULL);
		if(head->data>=max->data)
		{
			max=head;
		}
	}
	return max; 
}
```

# 6-3 工作备忘录的生成（链表）

```c++
Node* add(Node *head, Node *q)
{
    if(head==NULL)
    {
        head = q;
    }
    else
    {
        if(head->start>q->start)
        {
            q->next=head;
            head=q;
        }
        else
        {
            Node *p=head;
            while(p->next!=NULL&&p->next->start<q->start)
                p=p->next;
            q->next = p->next;
            p->next = q;
        }
    }
    return head;
}
void display(Node *head,int last)
{
    if(head==NULL)
        return;
    bool sign = true;
    if(last > head->start)
        sign = false;
    if(head->next!=NULL&&head->next->start<head->end)
        sign = false;
    if(!sign)
    {
        cout<<'*';
    }
    cout<<head->name<<' '<<head->start;
    cout<<" "<<head->end<<endl;
    if(head->end>last)
    {
        last = head->end;
    }
    display(head->next,last);
}
void display(Node *head)
{
    if(head==NULL)
        return;
    return display(head,head->start-1);
}
```

