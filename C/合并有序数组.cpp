 #include<stdio.h> 
void MemeryArray(int a[], int n, int b[], int m, int c[])
{
	int i, j, k;

	i = j = k = 0;
	while (i < n && j < m)
	{
		if (a[i] < b[j])
			c[k++] = a[i++];
		else
			c[k++] = b[j++]; 
	}

	while (i < n)
		c[k++] = a[i++];

	while (j < m)
		c[k++] = b[j++];
}
int main()
{
	int a[]={2,3,5,6};
	int b[]={2,4,6,8,10};
	int c[100];
	MemeryArray(a,4,b,5,c);
	int i;
	for(i=0;i<9;i++)
	printf("%d",c[i]); 
}
