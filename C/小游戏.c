#include<iostream>  
#include<cstring>  
  
using namespace std;  
int x=0; //记录最大值   
int flag[43]; //辅助数组由题可知10 10 10 9 10 10 8 10 10这样最大的数据所能走的最大距离为43所有下标43够了  
int N[]={0,1,2,3,4,5,6,7,8}; //辅助九个动作全排列数组  
  
struct   
{  
    int pos; //此人当前所在的位置  
    int flag; //如果flag为0代表没被举 1代表被举了  
    int juren;  
    int mvflag;     //移动标志位如果没移动则为0 移动了则为1  
    int mvmax;  //移动的最大步数  
    int thrflag;  //丢标志位丢过为1没丢过则为0  
    int thrmax;  //丢的最大距离   
}People[3];   //三个人   
  
void swap(int a,int b)  
{  
    int temp=N[a];  
    N[a]=N[b];  
    N[b]=temp;  
}  
  
void judge(int a,int b,int pos)  
{  
    switch(People[0].thrflag+People[1].thrflag+People[2].thrflag) //0代表第一次丢人的人不用去判断走.1代表第二次丢 2代表第三次丢   
    {  
        case 1: if(People[a].mvflag==0)//如果背人的这个没走过且是第二次丢人  
             x=x>pos+People[a].mvmax+1+People[b].thrmax?x:pos+People[a].mvmax+1+People[b].thrmax;  //这里有个比较巧的事情   
                break;  
        case 2: if(People[a].mvflag==0)//如果背人的这个没走过且是第三次丢人   
            if(People[a].mvmax>People[a].thrmax)  
                 x=x>pos+People[a].mvmax?x:pos+People[a].mvmax;   
            if(People[b].mvflag==0)//如果被扔的人还能走则计算一下最远距离  
                x=x>pos+People[a].thrmax+People[b].mvmax?x:pos+People[a].thrmax+People[b].mvmax;  
            break;  
    }  
}  
void Permutations(int n)  
{  
    for(int i=n;i<9;i++)  
    {  
        swap(i,n);  
        int p=N[n]/3;   
        //当前动作的人0-2为第一个人的动作一次类推  
        int pos=People[p].pos;//此人当前所在位置   
        int j;  
          
        switch(N[n]%3)//根据动作的不同选择该人需要做的事 当前动作？0为移动1为举2为扔  
            {  
                case 0:   
                    if(People[p].flag||People[p].juren)break;   
                //如果被举或者举了人都不能移动直接退出  
                    x=x>pos+People[p].mvmax?x:pos+People[p].mvmax;//当前位置加上移动最大值如果大于原值则替换  
                    for(j=1;j<=People[p].mvmax;j++)//逐步往后移动   
                    {  
                    if(flag[pos+j]==0)//如果可以移动才移动   
                    {  
                        flag[pos]=0;  //原位置清0  
                        flag[pos+j]=p+1;//下一位置为该人下标+1   
                        People[p].pos=pos+j;   
                        //此人当前位置变为移动后的位置   
                        People[p].mvflag=1;   
                        //1代表移动过了  
                        Permutations(n+1);   
                        People[p].mvflag=0;//所有状态回朔  
                        flag[pos+j]=0;   
                        flag[pos]=p+1;   
                        People[p].pos=pos;   
              
                    }  
                }   
                    for(j=1;j<=People[p].mvmax;j++)//逐步往前移动    
                    {  
                        if(pos-j>0&&flag[pos-j]==0) //可以移动且大于0  
                        {  
                            flag[pos]=0;  //原位置清0  
                            flag[pos-j]=p+1;//下一位置为该人下标   
                            People[p].pos=pos-j;   
                            //此人当前位置变为移动后的位置   
                            People[p].mvflag=1;   
                            //1代表移动过了  
                            Permutations(n+1);   
                            People[p].mvflag=0;   
                            flag[pos-j]=0;//所有状态回朔   
                            flag[pos]=p+1;   
                            People[p].pos=pos;   
                          
                            }   
                        }  
                    break;  
            case 1:  
                if(People[p].flag==1)break;     
                //如果此人被举则不能举别人直接退出因为是全排列计算不会出现此人举过再举  
                if(flag[pos+1]!=0)//后面有人则先举后面的   
                {  
                    People[p].juren=flag[pos+1];  //举了这个人  
                    People[flag[pos+1]-1].flag=1 ;//被举人状态变为被举   
                    flag[pos+1]=0;//后面的人被举了之后位置清0  
                    Permutations(n+1);  
                    flag[pos+1]=People[p].juren;//回朔  
                    People[p].juren=0;     
                    People[flag[pos+1]-1].flag=0 ;  
                    People[flag[pos+1]-1].pos=pos+1; //位置复位   
                }   
                if(flag[pos-1]!=0&&pos-1>0)//原理同上举后面的人   
                {  
                    People[p].juren=flag[pos-1];  //举了这个人  
                    People[flag[pos-1]-1].flag=1 ;//被举人状态变为被举   
                    flag[pos-1]=0;//后面的人被举了之后位置清0  
                    Permutations(n+1);  
                    flag[pos-1]=People[p].juren;//回朔  
                    People[p].juren=0;     
                    People[flag[pos-1]-1].flag=0 ;  
                    People[flag[pos-1]-1].pos=pos-1; //位置复位   
                }  
                break;  
            case 2:  
                if(People[p].juren==0||People[p].flag==1)  
                    break; //如果没举人或者被别人举了则不能扔直接退出   
                x=x>pos+People[p].thrmax?x:pos+People[p].thrmax;  
                int juren=People[p].juren-1;//-1之后 才是此人操作的下标   
                judge(p,juren,pos);  //这个函数是整个裁剪的关键部分，处理之后可以让丢过人的人不用再走而得到最大距离  
                for(j=1;j<=People[p].thrmax;j++)  
                {  
                    if(flag[pos+j]==0)//丢原理和移动类似   
                    {  
                    People[juren].pos=pos+j;  //被丢人的位置变为丢到的位置 这里有一个地方没有清0就是背人标记位，从而减少了不必要的移动。  
                    People[juren].flag=0;     //被举状态复位  
                    flag[pos+j]=juren+1; //标记位置信息  
                    People[p].thrflag=1; //状态变为扔过人   
                    Permutations(n+1);   
                    People[p].thrflag=0; //回朔   
                    People[juren].flag=1;     //被举状态复位  
                    flag[pos+j]=0; //标记位置信息  
                    }  
                }  
                for(j=1;j<=People[p].thrmax;j++)  
                {  
                    if(flag[pos-j]==0&&pos-j>0)//丢原理和移动类似   
                    {  
                        People[juren].pos=pos-j;  //被丢人的位置变为丢到的位置  
                        People[juren].flag=0;     //被举状态复位  
                        flag[pos-j]=juren+1; //标记位置信息  
                        People[p].thrflag=1;   
                        Permutations(n+1);   
                        People[p].thrflag=0;   
                         //回朔   
                        People[juren].flag=1;     //被举状态复位  
                        flag[pos-j]=0; //标记位置信息  
                    }  
                }  
                break;  
            }   
        swap(i,n); //回朔   
    }  
}  
  
  
int main()  
{  
    int i,j;  
    x=0;  
    memset(flag,0,sizeof(flag));  
    memset(People,0,sizeof(People));  
      
    for(i=0;i<3;i++)  
    {  
        cin>>People[i].pos>>People[i].mvmax>>People[i].thrmax; //输入位置信息以及丢和扔的最大距离  
        flag[People[i].pos]=i+1;   
        //将位置绑定为当前人 因为0代表没人所以人下标加1   
    }  
      
    Permutations(0);//9个动作递归全排列计算  
    cout<<x<<endl;  
      
    return 0;  
}