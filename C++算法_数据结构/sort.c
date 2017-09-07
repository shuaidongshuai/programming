void sort(int a[],int n)
{
	int j,i,t;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(a[j]<a[j+1])
			{
				t=a[j+1];
				a[j+1]=a[j];
				a[j]=t;
			}
		}
	}
 }  
