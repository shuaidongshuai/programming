#include <iostream>
#include <random>
#include <ctime>
using namespace std;
#if 0
//rand随机的范围是 0 - 32767 
#define N 100000
int test(){
	srand(time(0));
	int num;
	for(int i = 0; i < N; ++i){
		num = rand();
		if(num > 32760)
			cout<<num<<endl;
	}
	return 0;
} 
#endif

//c++11提供的<random>实现了随机数库 https://www.cnblogs.com/byhj/p/4149467.html
#define N 0x7fffffff
int main(){
	default_random_engine e;//或者直接在这里改变种子 e(10) 
	e.seed(time(0)); //设置新的种子
    for (size_t i = 0; i < 10; ++i) //生成十个随机数 
       cout << e() << endl; 
    cout << "Min random:" << e.min() << endl; //输出该随机数引擎序列的范围 
    cout << "Max random:" << e.max() << endl; 
    return 0;
}
