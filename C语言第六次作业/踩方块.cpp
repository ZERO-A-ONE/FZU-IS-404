#include <stdio.h>
int main()
{
	int n,m,i,j,k,cnt,b,a,c[700][700];
	cnt=0;
	scanf("%d%d",&n,&m);
	for(i=0;i<m;i++){
		scanf("%d%d",&a,&b);
		for(j=0;j<n;j++){
			for(k=0;k<n;k++){
				if(j==a-1) c[j][k]++;
				if(k==b-1) c[j][k]++;
				if(j==a-1&&k==b-1) c[j][k]--;
			}
		}
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(c[i][j]%2!=0) cnt++;	
		}
	}
	printf("%d",cnt);
	return 0;
}

