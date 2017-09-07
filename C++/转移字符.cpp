#include <iostream>
using namespace std;

/*
目的：搞清楚java中的这一句话 
sb.append("<Mes id = \"" + MesBean.id + "\">");//我们想要加入的是  Mes id = "1"   可以用‘’ 也可以用转义字符
*/
int main()
{	 
	cout<<"dong = \"1\""<<endl;//dong = "1"
	
	cout<<"<dong = \""<<2<<"\">"<<endl;//<dong = "2">   c++中<<就相当于java中的+ 
	
}
