#include <iostream>
#include <cstring>
using namespace std;

//求平均数，向上取整 
int main() 
{
	int arr[] = {4,4,3};
	int n = sizeof(arr)/sizeof(arr[0]); 
	double res = (double)(arr[0] + arr[1] + arr[2]) / n;
	int res2 = (arr[0] + arr[1] + arr[2]) / n;
	
	cout<<res<<endl;
	cout<<res2<<endl;
    
    ////////////上面不管咋弄，感觉都会有误差，除非自己把误差考虑进去，但是下面有一种好方法//////////////////
    int res3 = (arr[0] + arr[1] + arr[2] + n - 1) / n;
    cout<<res3<<endl;
    
    double i = 5.546375;
    printf("%.5f\n",i);//四舍五入的话   .5f   自动四舍五入 
    
    return 0;
}

