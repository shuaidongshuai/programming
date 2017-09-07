// 【MoreWindows工作笔记3】 使用cout/pintf输出16进制，8进制，2进制数据
#include <iostream>
#include <bitset>
#include <stdlib.h>
using namespace std;
int main()
{
  printf(" 【MoreWindows工作笔记3】 使用cout/pintf输出16进制，8进制，2进制数据\n");    
  printf(" - http://blog.csdn.net/morewindows/article/details/16358511 -\n");
  printf(" -- By MoreWindows( http://blog.csdn.net/MoreWindows ) --\n\n");

  int a = 100;
  cout<<"十进制    "<<a<<endl;
  cout<<"十六进制  "<<hex<<a<<endl;
  cout<<"八进制    "<<oct<<a<<endl;
  cout<<"二进制    "<<bitset<8>(a)<<"   "<<bitset<32>(a)<<endl;  // 这里使用了bitset类来输出2进制数据	★★★★★★★★★★★★

  cout<<"--------------------------------"<<endl;

  printf("十进制    %d\n", a);
  printf("十六进制  %x\n", a);
  printf("八进制    %o\n", a);
  char binary_text[100];
  itoa(a, binary_text, 2);					//★★★★★★★★★★★★ 
  printf("二进制    %s\n", binary_text); 
  return 0;
}
