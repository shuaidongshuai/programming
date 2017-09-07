#include<stdio.h>
#define N 13
#define M 17
int arr[N][M];
void rule(int x,int y)
{
	if (x + 1 < N && y - 3 >= 0)
	arr[x + 1][y - 3] = 1;

	if (x - 1 >= 0 && y - 2 >= 0)
	arr[x - 1][y - 2] = 1;
	
	if (x - 1 >= 0 && y + 3 < M)
	arr[x - 1][y + 3] = 1;
	
	if (x + 1 < N && y + 2 < M)
	arr[x + 1][y + 2] = 1;
}
void main()
{
	int sum = 0;
	//arr[0][4] = 1, arr[0][9] = 1, arr[0][14] = 1;
	for (int i = 4; i < M; i+=5)
	{
		arr[0][i] = 1;
	}

	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < M; i++)
		{
			if (arr[j][i] == 1)
				rule(j,i);
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (arr[i][j] == 1)
				sum += 1;
		}
	}
	printf("%d", sum);

	getchar();
}