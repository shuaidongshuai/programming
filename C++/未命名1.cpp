#include <iostream>
#include <unordered_set>
#include <string>
using namespace std;

int main(){
    int i;
    int* pn = (int*)calloc(10, sizeof(int));
    for(i = 0;i < 10;i++)
        printf("%d", pn[i]);
    printf("\n");
    free(pn);
    return 0;
}

