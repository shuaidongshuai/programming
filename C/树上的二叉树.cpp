#include<stdio.h>
 #include<stdlib.h>
 typedef struct node
 {
     char elem;
     struct node * lchild;
     struct node * rchild;
 }Node;
 typedef Node  * bitree;
 void creattree(bitree &t)
 {
     char i;
     printf("ÇëÊäÈëÊıÖµ\n");
     scanf("%c",&i);getchar();
     if(i==' ') t=NULL;
     else
     {
         t=(bitree)malloc(sizeof(Node));
         t->elem=i;
         creattree(t->lchild);
         creattree(t->rchild);
     }
 }
 void bianli(bitree t)
 {
     if(t)
     {
         if(t->elem)
         printf("%c\t",t->elem);
         bianli(t->lchild);
         bianli(t->rchild);
     }
 }
int main()
 {
     bitree h;
     creattree(h);
     bianli(h);
 } 
