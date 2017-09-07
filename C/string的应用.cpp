#include <iostream>
#include <string>
using namespace std;

int main1()
{
	string s1 = "chen,ming,haha";
	
	string s2(s1,0,4);//chen		//获取角标0 之后的4个字符
	string s3(s1,5,4);//ming       //获取角标5 之后的4个字符 
	string s4(s1,4);//,ming,haha   //获取角标4 到最后  的字符串 
	
	cout<<s2<<"       "<<s3<<"    "<<s4<<endl;	
	
	
	char str[] = "chen,ming,haha";
	string s5(str,4);//获取前四个 
	cout<<s5<<endl;
	
	string s6(10,'d');//初始化为10个d 
	cout<<s6<<endl; 
}

int main2()
{
	string s1;
	
	//获取字符串，赋值给s1，以！结束		可以不止一行 
	getline(cin,s1,'!'); 
	
	cout<<s1<<endl;
	
	//都是在末尾增加字符（串） 
	s1.push_back('Q');//在末尾加Q
	 
	s1+='A'; 
	
	s1+="bbbb";
	
	int i = s1.find("23");
	
	cout<<s1<<"   i = "<<i<<endl;
 
	
	cout<<endl;	
}

int main()
{
	string s1 = "chen,ming,dong";
	
	s1.erase(0,10);//删除角标 0  -  9  的字符 
	
	cout<<s1<<endl;

	
	s1.clear();//清空 
	
	cout<<s1<<endl; 
	
}
