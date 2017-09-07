#include<stdio.h>
#define X 6
#define Z 7
#define Y 6
int arr_3[X][Z][Y];
void rule1(int x,int y,int z)
{
	if (x + 1 < X && y + 2 < Y)
	arr_3[x + 1][y + 2][z] = 1;

	if (x + 1 < X && y - 3 >= 0)
	arr_3[x + 1][y - 3][z] = 1;

	if (x - 1 >= 0 && y - 2 >= 0)
	arr_3[x - 1][y - 2][z] = 1;

	if (x - 1 >= 0 && y + 3 < Y)
	arr_3[x - 1][y + 3][z] = 1;
}
void rule2(int x, int y, int z)
{
	if (x + 1 < X && z + 2 < Z)
		arr_3[x + 1][y][z + 2] = 1;

	if (x + 1 < X && z - 3 >= 0)
		arr_3[x + 1][y][z - 3] = 1;

	if (x - 1 >= 0 && z - 2 >= 0)
		arr_3[x - 1][y][z - 2] = 1;

	if (x - 1 >= 0 && z + 3 < Z)
		arr_3[x - 1][y][z + 3] = 1;
}
void rule3(int x, int y, int z)
{
	if (y + 1 < Y && z + 2 < Z)
		arr_3[x][y + 1][z + 2] = 1;

	if (y + 1 < Y && z - 3 >= 0)
		arr_3[x][y + 1][z - 3] = 1;

	if (y - 1 >= 0 && z - 2 >= 0)
		arr_3[x][y - 1][z - 2] = 1;

	if (y - 1 >= 0 && z + 3 < Z)
		arr_3[x][y - 1][z + 3] = 1;
}
void main1()
{
	int sum = 0;
	for (int i = 4; i < Y; i+=5 )
	{
		arr_3[0][0][i] = 1;
	}

	for (int x = 0; x < X; x++)
	{
		for (int z = 0; z < Z; z++)
		{
			for (int y = 0; y < Y; y++)
			{
				if (arr_3[x][y][z] == 1)
				{
					rule1(x, y, z);
					rule2(x, y, z);
					rule3(x, y, z);
				}
			}
		}
	}

	for (int x = 0; x < X; x++)
	{
		for (int y = 0; y < Y; y++)
		{
			for (int z = 0; z < Z; z++)
			{
				if (arr_3[x][y][z] == 1)
					sum += 1;
			}
		}
	}
	printf("sum = %d", sum);
	getchar();
}
