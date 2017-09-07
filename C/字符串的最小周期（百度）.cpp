#include <stdio.h>
#include <string.h>
int main()
{
 char word[100];int ok=0;
 scanf("%s",word);
 int l=strlen(word);
 for (int i=1; i<=l; ++i)//周期必是1到l,若为1，即是常数串
 {
  if (l%i==0)//最小周期必是长度的约数			这一步非常重要   
  {
   int ok=1;
   for (int j=i; j<l; ++j)
   {
//word[j]为第二周期的第一个字符,word[j%i]是前一个周期的第一个字符(因为
//j=i;j%i=0;j每加1,j%i也加1,直到最后一组word[j]都等于word[j%i],则i为周期
    if (word[j%i]!=word[j])//个人认为j-1亦可 
     {
      ok=0;
      break;
     }
   }
   if (ok) 
   {
    printf("%d\n",i);
    break;// this is the least cycle 
   }
  }
  else 
   continue;
 }
 return 0;
}
