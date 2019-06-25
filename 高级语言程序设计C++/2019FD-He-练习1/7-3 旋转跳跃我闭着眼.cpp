#include<iostream>
using namespace std;
int main(){
	int n,m,x,i,j;
	while(cin>>n){
	cin>>m;
	int a[n+1][m+1];
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	cin>>x;
	x%=4;
	if(x==0){
		for(i=1;i<=n;i++){
			for(j=1;j<=m;j++){
				cout<<a[i][j];
				if(j!=m)
				cout<<" ";
			}
			cout<<"\n";
		}
	}
	else if(x==1){
		for(i=1;i<=m;i++){
			for(j=n;j>=1;j--){
				cout<<a[j][i];
				if(j!=1)
				cout<<" ";
			}
			cout<<"\n";
		}
	}
	else if(x==2){
		for(i=n;i>=1;i--){
			for(j=m;j>=1;j--){
				cout<<a[i][j];
				if(j!=1)
				cout<<" ";
			}
			cout<<"\n";
		}
	}
	else if(x==3){
		for(i=m;i>=1;i--){
			for(j=1;j<=n;j++){
				cout<<a[j][i];
				if(j!=n)
				cout<<" ";
			}
			cout<<"\n";
		}
	}
}
	return 0;
}