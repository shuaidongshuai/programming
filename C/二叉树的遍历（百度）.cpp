#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
typedef struct _NODE
{
    int value;
    struct _NODE *left;
    struct _NODE *right;
    
    _NODE(int value) : value(value), left(NULL),  right(NULL) {};
}NODE, *PTRNODE;
void insert(PTRNODE &root, int value)
{
    if(root == NULL)
        root = new NODE(value);
    else
    {   
        if(value < root->value)
            insert(root->left, value);
        else if(value > root->value)
            insert(root->right, value);
        else
            cout << "duplicated value" << endl;
    }
}
void preOrder(PTRNODE root)
{
     if(root != NULL)
     {
         cout << root->value << "->";
         preOrder(root->left);
         preOrder(root->right);
     }
}
void inOrder(PTRNODE root)
{
     if(root != NULL)
     {
         inOrder(root->left);
         cout << root->value << "->";
         inOrder(root->right);
     }
}
void postOrder(PTRNODE root)
{
     if(root != NULL)
     {
         inOrder(root->left);
         inOrder(root->right);
         cout << root->value << "->";
     }
}
void clear(PTRNODE &root)
{    
     if(root != NULL)
     {
         clear(root->left);
         clear(root->right);
         
         delete root;
         root = NULL;
     }
}
void _search(PTRNODE root, int searchVal)
{
   if(root == NULL)
   {
       cout << "not find... " << endl;
       return;
   }
   
   if(searchVal < root->value)
       _search(root->left, searchVal);
   else if(searchVal > root->value)
       _search(root->right, searchVal);
   else
       cout << "find... " << endl;
}
int main(int argc, char *argv[])
{
    PTRNODE root = NULL;
    srand(time(NULL));
    cout << "init is: " << endl;
    for(int i=0; i<10; i++)
    {
        int value = rand() % 100;
        cout << value << " ";
        
        insert(root, value);
    }
    
    cout << endl;
    
    cout << "pre order result is: " << endl;
    preOrder(root);
    cout << endl;
    
    cout << "in order result is: " << endl;
    inOrder(root);
    cout << endl;
    
    cout << "post order result is: " << endl;
    postOrder(root);
    cout << endl;
    
    cout << "please input a search value: ";
    int searchVal;
    cin >> searchVal;
    _search(root, searchVal);
    
    clear(root);
    
    system("PAUSE");
    return EXIT_SUCCESS;
}

