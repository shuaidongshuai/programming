void paixu(int a[],int n)
{
	int i,j,t;
	for(i=0;i<n;i++)
	{
		for(j=i;j<n;j++)
		{
			if(a[i]>a[j+1])
			{
				t=a[i];
				a[i]=a[j+1];
				a[j+1]=t;
			}
		}
	}
	for(j=0;j<10;j++)
	{
	printf("%d\t",a[j]);
}
}
