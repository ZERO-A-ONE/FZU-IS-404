//6-1 2018final时间倒转 
Clock operator--(Clock& op) {
	int sum = 0;
	sum = op.Hour*60*60+op.Minute*60+op.Second;
	sum--;
	if(sum>=0)
	{
		int H = sum/(60*60);
		sum = sum-H*60*60;
		int M = sum/60;
		sum = sum-M*60;
		int S = sum;
		op.Hour = H;
		op.Minute = M;
		op.Second = S;
	}
	else{
		sum = 23*60*60+59*60+59;
		int H = sum/(60*60);
		sum = sum-H*60*60;
		int M = sum/60;
		sum = sum-M*60;
		int S = sum;
		op.Hour = H;
		op.Minute = M;
		op.Second = S;
	}
	return op;
}
Clock operator--(Clock& op, int) {
	Clock t = op;
	int sum = 0;
	sum = op.Hour*60*60+op.Minute*60+op.Second;
	sum--;
	if(sum>=0)
	{
		int H = sum/(60*60);
		sum = sum-H*60*60;
		int M = sum/60;
		sum = sum-M*60;
		int S = sum;
		op.Hour = H;
		op.Minute = M;
		op.Second = S;
	}
	else{
		sum = 23*60*60+59*60+59;
		int H = sum/(60*60);
		sum = sum-H*60*60;
		int M = sum/60;
		sum = sum-M*60;
		int S = sum;
		op.Hour = H;
		op.Minute = M;
		op.Second = S;
	}
	return t;
}
//6-2 2018Final链表(龙舟队) 
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
//6-3 2018Final静态成员（黑名单）
int Group::blackList[N];
int Group::size;
Group::Group(){}
Group::Group(int num, bool bSign)
{
	if(bSign)
	{
	    if(size<3)
    	{
        	blackList[size] = num;
    	}
    	if(size==3)
    	{
    		for(int i = 0;i<size;i++)
    		{
    			blackList[i]=blackList[i+1];
			}
			blackList[size-1]=num;
    	}
    	if(size<3)
   		{
    		size++;
		}
	}
}
void Group::addToList(int num)
{
    if(size<3)
    {
        blackList[size] = num;
    }
    if(size==3)
    {
    	for(int i = 0;i<size;i++)
    	{
    		blackList[i]=blackList[i+1];
		}
		blackList[size-1]=num;
    }
    if(size<3)
    {
    	size++;
	}
}
void Group::removeFromList(int num)
{
    for(int i=0;i<size;i++)
    {
        if (blackList[i]==num)
        {
            if(i==size-1)
            {
                blackList[i]=0;
                size--;
            }
            else {
                for (int j = i; j < size-1; j++) {
                    blackList[j] = blackList[j+1];
                }
                size--;
            }
        }
    }
}