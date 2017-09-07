#include<iostream>
#include<cmath>
using namespace std;

int main()
{
    int N;
    char c;
    cin >> N >> c;
    int k = sqrt((N + 1) / 2);//他设的是 上半部分的行数 
    for (int i = 1; i <= k; i++)
    { 
        for (int j = 1; j < i; j++)
          cout << " ";

        for (int j = 2*(k - i) + 1; j >= 1; j--)
          cout << c;

        cout << endl;
    }
    for (int i = 1; i <= k - 1; i++)
    {
        for (int j = 1; j <= k - i - 1; j++)
        {
          cout << " ";
        }
        for (int j = 1; j <= 2 * i + 1; j++)
        {
          cout << c;
        }
        cout << endl;
    }
    cout << N + 1 - 2 * k*k << endl;
    return 0;
}
