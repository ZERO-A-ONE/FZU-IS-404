#include <stdio.h>
int main()
{
	char k,l,c,i,j;
	int n;
	scanf("%d %c",&n,&c);
	for(i=0;i<n;i++){
		for(j=0;j<2*n-1;j++){
			putchar(' ');
		}
		printf("%c\n",c);
	}
	for(i=0;i<n-1;i++){
		for(j=i;j<2*n-1;j++){
			putchar(' ');
		}
		for(k=1;k<i+2;k++){
			printf("%d",k);
		}
		for(l=k-2;l>0;l--){
			printf("%d",l);
		}
		printf("\n");
	}
	for(i=0;i<n;i++){
		printf("%c",c);	
	}
	for(k=1;k<n+1;k++){
		printf("%d",k);
	}
	for(l=n-1;l>0;l--){
		printf("%d",l);
	}
	for(i=0;i<n;i++){
		printf("%c",c);	
	}
	printf("\n");
	for(i=0;i<n-1;i++){
		for(j=0;j<n+i+1;j++){
			putchar(' ');
		}
		for(k=1;k<n-i;k++){
			printf("%d",k);
		}
		for(l=n-2-i;l>0;l--){
			printf("%d",l);
		}
		printf("\n");
	}
	for(i=0;i<n;i++){
		for(j=0;j<2*n-1;j++){
			putchar(' ');
		}
		printf("%c\n",c);
	}
	return 0;
}

            

