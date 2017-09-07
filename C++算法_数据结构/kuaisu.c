void kuaisu(int a[],int n)
{
	quick(a,0,n-1);
 } 
 void quick(int a[],int left,int right)
{
	int t,l,r;
	l=left;
	r=right;
	t=a[l];
	if(l<r)
	{
	while(l<r)
	{
		while((a[r]>=t)&&(l<r))
		r--;
		a[l]=a[r];
		while((a[l]<=t)&&(l<r))
		 l++;
		a[r]=a[l];
	}
	a[l]=t;					/*这里跳出循环后r=l*/ 
	quick(a,left,l-1);		/*最重要的一点：递归里的l与r不影响外面的l,r,也就是说下面的r+1中的r不受影响*/ 
	quick(a,r+1,right);		/*r+1也可以换成l+1，因为上面r=l,,递归不改变外部函数r,l的值；*/ 
}
}
