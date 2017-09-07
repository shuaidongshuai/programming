#include<stdio.h>
void integer(int a){
	if(a>0){
		integer(a/2);
		printf("%d",a%2);
	}
	if(a==0) printf("0");
 } 
void fraction(double a,int n){
	if(a-(int )a!=0&&n>0){
		if(n==4) printf(".");
		a*=2;
		if(a>0){
			printf("%d",(int)a);
			a-=(int)a;
		}
		fraction(a,n-1);
	}
}
int main(){
 	double n;
 	while(1){
 	printf("\n\nPlease input a number:   ");
 	scanf("%lf",&n);
 	printf("convert to binary:      ");
 	integer((int)n);
 	fraction(n-(int )n,4);
 	}
 	return 0;
 }
