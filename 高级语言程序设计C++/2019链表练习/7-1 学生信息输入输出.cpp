#include<iostream>
#include<string>
using namespace std;
struct Student{
	int	num;
	string	name;
	float score;
	Student *next;
}; 
void print(const Student *head)
{
	if(head != NULL)
	{
		cout<<head->num<<" "<<head->name<<" "<<head->score<<endl;
		print(head->next);
	}
}
int main()
{
	Student *head = NULL,*p,*q;
	int i = 0;
	while(1)
	{
		q = new Student;
		cin >> q->num;
		if(q->num == 0)
		{
			break;
		}
		cin >> q->name >> q->score;
		q->next = NULL;
		if(i == 0)
		{
			head = p = q;
		}	
		else
		{
			p->next = q;
			p = q;
		}
		i++; 
	}
	print(head);
	return 0;
}