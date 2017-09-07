#include "Queue.h"
#include <queue>
#include <vld.h>
using namespace std;

int main()
{
	Queue<int> q1;//默认大小是5

	for (int i = 0; i < 5; i++)
	{
		q1.push(i);
		cout << "push:" << i << endl;
	}
	while (!q1.empty())
	{
		cout << q1.front() << " ";
		q1.pop();
	}
	cout << endl;

	for (int i = 0; i < 11; i++)
	{
		q1.push(i);
		cout << "push:" << i << endl;
	}
	while (!q1.empty())
	{
		cout << q1.front() << " ";
		q1.pop();
	}
	cout << endl;

	system("pause");
	return 0;
}