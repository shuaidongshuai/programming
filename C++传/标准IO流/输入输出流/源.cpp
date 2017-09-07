#include <iostream>
using namespace std;
/*
cin
cin.get();
cin.getline();
cin.ignore();
cin.peek();
cin.putback();
*/
int main7()
{
	//刚刚说了peek()和get()有区别，但是现在我们利用putback和get，，就可以组合成一个peek
	char ch;
	char buf[20];
	if (1)
	{
		//比如我们现在想要接收一个数字开头的字符串，那么可以这样做
		cin.get(ch);
		if ('0' <= ch && '9' >= ch)
		{
			cin.putback(ch);	//可以putback字符，和数字
			cin >> buf;
			cout <<"第一种方法："<< buf << endl;//这样输出，会把别人第一个字符也输出出来
		}
		//0dong
		//第一种方法：0dong
	}
	else
	{
		//还可以这样做
		ch = cin.peek();//1.先窥探是不是输入的是数字
		if ('0' <= ch && '9' >= ch)
		{
			cin >> buf;	//2.再进入到输入流
			cout << "第二种方法：" << buf << endl;//这样输出，会把别人第一个字符也输出出来
		}
		//0dong
		//第二种方法：0dong
	}
	system("pause");
	return 0;
}
int main6()
{
	char buf[20];
	//cin.getline(buf,20);//不要用这个，不然不输入完20个字符（尽管回车可以结束输入，但是效果不太好）\
							缓冲区里面没有数据，peek()函数会阻塞在那，直到缓冲区里面出现数据
	cin >> buf;//最好用空格，不然缓冲区里面就剩一个回车符，，不好看

	int a = cin.peek();		//窥探缓冲区里面第一个数据，并返回。和cin.get()的区别在于，get是直接冲缓冲区里面取出数据，peek()只是窥探

	cin.ignore(1);			//忽略一个字符，为了不重复窥探一个字符
	char i = cin.peek();
	cin.ignore(1);			//忽略一个字符

	cout << a << "   " << i << endl;

	int b = cin.peek();
	cout << b << endl;

	//	aa bc
	//	32   b		// 空格十进制ascii码是 32  
	//	99			//99是字符  c

	system("pause");
	return 0;
}

int main5()
{
	char ch;
	//while ((ch = cin.get()) != EOF)
	//{
	//	char a = cin.get();//经常我们绘碰见这样的尴尬事件，他吧回车给读进来了
	//	cout << a << endl;
	//}

	//while ((ch = cin.get()) != EOF)
	//{
	//	cin.get();		//加上这句话可以解决上面问题（但是当第二次循环的时候还会有问题，因为我们一次循环敲了两个回车  第二个回车被最上面的get给接收了）
	//	char a = cin.get();								//第二次循环，直接输出两个换行
	//	cout << a << endl;
	//}

	//while ((ch = cin.get()) != EOF)
	//{
	//	cin.get();		
	//	char a = cin.get();
	//	cout << a << endl;
	//	cin.get();		//解决办法
	//}

	//while ((ch = cin.get()) != EOF)
	//{
	//	cin.ignore(1);//新方法		忽略缓冲区的一个字符
	//	char a = cin.get();
	//	cout << a << endl;
	//	cin.ignore(1);
	//}

	char s[20];
	cin.ignore(3);//忽略3个字符
	cin.getline(s, 20);
	//	12345678
	//	45678
	cout << s << endl;

	system("pause");
	return 0;
}
int main4()
{
	char buf1[1024];
	char buf2[1024];
	cin >> buf1;
	cin.getline(buf2,1024);
	cout << buf1 << endl;
	cout << buf2 << endl;

	//aa bb cc dd
	//aa
	//	bb cc dd		//注意这里开头有一个空格，相当于把上面那个空格给拿过来了

	system("pause");
	return 0;
}
int main()
{
	char a, b;
	char c[3];
	cin.get(a);
	cin.get(b);
	cin.get(c, 3);
	
	cout << a << b << c << endl;

	cin.get(a).get(b).get(c,3);//，3是接收两个字节

	cout << a << b << c << endl;

	//	1234abcdef
	//	1234
	//	abcd
	system("pause");
	return 0;
}
int main2()
{
	char ch;
	while ((ch = cin.get())!=EOF)//遇到ctrl+z 之后结束		#define EOF     (-1)
	{
		cout << ch << endl;
	}

	system("pause");
	return 0;
}
int main1()
{
	char a[10];
	char b[10];
	char c[10];

	cin >> a;
	cin >> b >> c;

	cout << a << endl;
	cout << b << endl;
	cout << c << endl;
	//	输入：aa bb cc dd			//可以看出，遇到空格结束
//  输出：
	//	aa
	//	bb
	//	cc
	system("pause");
	return 0;
}