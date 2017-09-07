#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAX 16
int getsum(int *nums, int start, int end){
    assert(nums!=NULL && start<=end);
    int sum = 0;
    int i;
    for(i = start; i<=end; i++)
        sum+=nums[i];
    return sum;
}

int test(int * nums, int start, int len, int mulcount){
    if(mulcount == 0)
        return getsum(nums, start, start+len-1);
    int m = 1;
    int midd[MAX];
    int loc = start;
    int max = 0;
    for(;loc-start<len-1;loc++){
        midd[loc] = getsum(nums,start,loc) * test(nums, loc+1, start+len-loc-1, mulcount-1);
        max = max<midd[loc] ? midd[loc]:max;
    }
    return max;
}

int main(){
	int n,k,i,a[20];
    scanf("%d%d",&n,&k);
    for(i=0;i<n;i++)
    scanf("%d",&a[i]);

    int max = test(a, 0, i, k);
    printf("%d", max);
}
