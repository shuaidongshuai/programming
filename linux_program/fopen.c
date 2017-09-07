//标准 I/O 库函数是C语言中所特有的，用于高级接口的函数，这些库函数存放在C语言的stdio.h头文件中
//EOF  在stdio.h 中定义  为  -1
#include<stdio.h>
int main()
{
	FILE *fp;									//FILE 是一种结构体
	int i;
	char a[]={'h','e','l','l','o','\n'};
	char ch;
	fp=fopen("/home/dong/dd/dong1","w");						//返回文件指针			没有文件会自动创建一个文件
	if(fp)									// 如果打开了
	{
		for(i=0;i<6;i++)
		{
			if(fputc(a[i],fp)==EOF)			// 向文件中输入一个字符			但如果这个文件里面有东西 会全被清空		
			{
				perror("write error");
				return 1;
			}
		}
		printf("write successful\n");
	}
	else{
		printf("open error");
	}
	fclose(fp);
	
	// 上面代码是进行一个   写 			下面的代码  是对上面代码的   读
	
	if((fp=fopen("/home/dong/dd/dong1","r"))==NULL)			// 以只读的方式打开 dong1
	{
		perror("open error");
		return 1;
	}
	printf("out put data in the dong1\n");
	for(i=0;i<6;i++)
	{
		if((ch=fgetc(fp))==EOF)							// 把文件中的字符 读  到  terminal
		{												// fgetc  成功调用时  返回的是读到的字符   但原型中返回值类型是  int     原因就在   EOF
			perror("fgetc error");
			return 1;
		}
		else
		{
			printf("%c",ch);
		}
	}
	printf("get successful \nplease examine dong1\n");
	fclose(fp);
	return 0;
}