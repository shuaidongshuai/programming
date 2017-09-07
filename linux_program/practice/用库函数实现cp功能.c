// 使用库函数 实现文件copy  的功能
#include<stdio.h>
int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("please input a.out file1 file2");
		return 1;
	}
	else
	{
		FILE *fp1,*fp2;
		char ptr[100];				//  注意这里是字符数组
		fp1=fopen(argv[1],"r");		//以只读的 方式打开
		int size;
		size=fread(ptr,1,14,fp1);		//  14和 1 参数多少的确不太清楚   不过 14*1 就是你读的字节数
		
		fp2=fopen(argv[2],"w");
		fwrite(ptr,1,size,fp2);
	}
	return 1;
}

//根据上面的字节数  我发现 竟然 汉字 占 了 三个字节

//百度：
//占多少个字节得看你用的是什么编码集，如果是GBK和GB2312的话，确实是两个字节，
//在Windows平台上会是你预期的两个字节。但是，在Linux平台上，
//我们不设置编码集的情况下，通常默认为utf8，
//这种编码规则就不一定是几个字节了，
//2个3个可能都有的，它是变字节的。