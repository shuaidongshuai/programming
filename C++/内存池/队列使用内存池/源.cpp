#include "Queue.h"
#include <queue>
#include <vld.h>
using namespace std;

int main()
{
	Queue<int> q1;
	queue<int> q2;

	for (int i = 0; i < 22; i++)
	{
		q1.push(i);
		q2.push(i);
	}

	while (!q1.empty())
	{
		cout << q1.front() << " ";
		q1.pop();
	}

	while (!q2.empty())
	{
		cout << q2.front() << " ";
		q2.pop();
	}
	cout << endl;

	system("pause");
	return 0;
}