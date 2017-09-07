#define  _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include "Teacher.h"
using namespace std;

int main3()
{
	char* path = "C:\\Users\\37916\\Desktop\\dong.txt";
	Teacher* t1 = new Teacher("陈明东", 20);
	Teacher* t2 = new Teacher("赵丽颖", 28);
	Teacher* t3 = new Teacher("成龙", 50);
	//写文件
	FILE* fp = fopen(path, "a+");
	fwrite((void *)t1, sizeof(Teacher), 1, fp);
	fwrite((void *)t2, sizeof(Teacher), 1, fp);
	fwrite((void *)t3, sizeof(Teacher), 1, fp);

	fseek(fp, 0, SEEK_SET);


	Teacher* t = new Teacher;
	//while (!feof(fp))
	//{
	//	fread((void*)t, sizeof(Teacher), 1, fp);	//但是这个地方就非用fread不可了，和fwrite同时使用，因为我们知道大小
	//	t->show();	//会多读一次最后一个人 、、因为：是检测上一次读到EOF没有,这样就会导致多读一次
	//}	
	//上面是先检查，再读，再调用

	//这样写能解决上面的问题（下面是先读，然后在检查，最后再调用）
	fread((void*)t, sizeof(Teacher), 1, fp);
	while (!feof(fp))
	{
		t->show();
		fread((void*)t, sizeof(Teacher), 1, fp);
	}

	fclose(fp);
	system("pause");
	return 0;
}

int main2()
{
	//用c来写
	char* path = "C:\\Users\\37916\\Desktop\\hello.txt";
	char ch;
	int len = 0;

	//写文件
	FILE* fp = fopen(path, "a");
	fputc('I',fp);
	fputs(" love 陈明东\n", fp);
	fclose(fp);

	//fseek(fp, 0, SEEK_SET); //指针移动

	//读文件
	FILE* fpp = fopen(path, "r");
	
	//while (!feof(fpp))//到达文件尾时返回真值   //这样做是可以全部读出来的  第一种方法
	//{
	//	fgets(buf, 1024, fpp);
	//	printf("%s", buf);
	//}

	while (!feof(fpp))							//这样做也是可以全部读出来的  第二种方法
	{
		ch = fgetc(fpp);						
		if (ch == 'M')							//读字符还有一个好处，就是可以筛选掉不想要的字符
			continue;
		printf("%c", ch);
	}
	
	//char buf[1024];
	//while (!feof(fpp))
	//{
	//	fread(buf, 1, strlen(buf), fpp);			//如果用这个函数就必须指定长度，但是一般我们都不知道长度
	//	printf("%s", buf);
	//}
	
	fclose(fpp);
	system("pause");
	return 0;
}

int main1()
{
	char* path = "C:\\Users\\37916\\Desktop\\hello.txt";
	char ch;

	//写文件
	//ofstream fout(path);//每次都是先清空再写，默认是ofstream fout(path,ios::out)  想要追加要用 app
	ofstream fout(path,ios::app);//以追加的方式写入
	fout << "hello陈明东，Im KangKang！！" << endl;
	fout << "nice to meet you" << endl;
	fout.close();

	//读文件
	ifstream fin(path);
	while (fin.get(ch))
	{
		cout << ch;
	}
	fin.close();
	system("pause");
	return 0;
}