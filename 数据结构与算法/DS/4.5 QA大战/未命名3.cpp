#include<iostream>
#include<string>
using namespace std;
int ArryT[100000];
int People[100000];
struct P{
	int Arrynum;
	int num;
	P *Next = NULL;
};
int main(){
	int i,j,k=0;
	for(i=0;i<100000;i++){
		ArryT[i] = 0;
	}
	P *MAN[100000]; 
	int index = 1;
	while(1){
		string A="";
		int a=0;
		int b=0;
		cin>>A;
		if(A == "PUSH"){
			cin>>a>>b;
			if(ArryT[b]==0){
				P *tmp = new P;
				tmp->num = a;
				tmp->Arrynum = b;
				MAN[index] = tmp;
				ArryT[b] = index;
				index++;
			}
			else{
				P *tmp = new P;
				tmp->num = a;
				tmp->Arrynum = b;
				P *head = new P;
				head = MAN[ArryT[b]];
				while(head->Next != NULL){
					head = head->Next;
				}
				head->Next = tmp;
			}
		}
		else{
			break;
		}
	}
	
	for(i=1;i<index;i++){
		P *tmp = new P;
		tmp = MAN[i];
		while(tmp != NULL){
			cout<<tmp->num<<" ";
			tmp = tmp->Next;
		}
	}
	return 0;
}
