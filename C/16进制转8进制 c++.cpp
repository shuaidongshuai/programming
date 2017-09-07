#include <iostream>
#include <string>
using namespace std;
int arr[10000001];

int main()
{
  int n,len_str,i,j;
  string str,str2;
  cin>>n;
  while(n--)
  {
    cin>>str;
    len_str=str.length();
    str2="";

    // 十六进制转换为二进制
    for(i=0;i<len_str;++i)
    {
      switch(str[i])
      {
      case '0':str2+="0000";break;
      case '1':str2+="0001";break;
      case '2':str2+="0010";break;
      case '3':str2+="0011";break;
      case '4':str2+="0100";break;
      case '5':str2+="0101";break;
      case '6':str2+="0110";break;
      case '7':str2+="0111";break;
      case '8':str2+="1000";break;
      case '9':str2+="1001";break;
      case 'A':str2+="1010";break;
      case 'B':str2+="1011";break;
      case 'C':str2+="1100";break;
      case 'D':str2+="1101";break;
      case 'E':str2+="1110";break;
      case 'F':str2+="1111";break;
      default:break;
      }
    }
    
    // 修正位数
    if(len_str%3==1)	str2="00"+str2;
    
    else if(len_str%3==2)	str2="0"+str2;

    
    len_str=str2.length();
    // 二进制转换八进制
    j=0;
    for(i=0;i<=len_str-2;i+=3)
    {
      arr[j]=(str2[i]-'0')*4+(str2[i+1]-'0')*2+(str2[i+2]-'0');
      ++j;
    }

    for(i=0;i<j;++i)
    {
      if(i==0 && arr[i]==0)	continue;
      cout<<arr[i];
    }
    cout<<endl;

  }
  return 0;
}
