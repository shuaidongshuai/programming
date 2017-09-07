#include<iostream>
using namespace std;
void dong(int n,char A,char B,char C)
{
	if(n==1) cout<<A<<"移动到"<<C<<"\t";
	else{
		dong(n-1,A,C,B);		//单数先a>c双数先a>b 
		cout<<A<<"移动到"<<C<<"\t";
		dong(n-1,B,A,C); 
	} 
 } 
 int main()
 {
 	int n;
 	cin>>n;
 	dong(n,'A','B','C');
 	return 0;
 }
