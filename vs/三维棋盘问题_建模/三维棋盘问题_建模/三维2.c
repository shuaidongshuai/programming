#include<stdio.h>
#define X 6
#define Y 6
#define Z 7
int arr_3[X][Y][Z];
void rule(int x, int y, int z)
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
void main()
{
	int sum = 0;
	int i=4;
	for (int z = 0; z < Z; z++)
	{
		i = (2 * z + 1) % 5;
		for (i; i < Y; i += 5)
		{
			arr_3[0][i][z] = 1;
		}
	}

	for (int z = 0; z < Z; z++)
	{
		for (int x = 0; x < X; x++)
		{
			for (int y = 0; y < Y; y++)
			{
				if (arr_3[x][y][z] == 1)
				{
					rule(x, y, z);
				}
			}
		}
	}

	int zz[7] = { 0 };
	for (int x = 0; x < X; x++)
	{
		for (int y = 0; y < Y; y++)
		{
			for (int z = 0; z < Z; z++)
			{
				if (arr_3[x][y][z] == 1)
				{
					sum += 1;
					printf("%d %d %d\n", x, y, z);
			/*		if (z == 0)
						zz[0]++;
					if (z == 1)
						zz[1]++;
					if (z == 2)
						zz[2]++;
					if (z == 3)
						zz[3]++;
					if (z == 4)
						zz[4]++;
					if (z == 5)
						zz[5]++;
					if (z == 6)
						zz[6]++;*/
				}
			}
		}
	}
	printf("sum. = %d\n", sum);

	//for (int i = 0; i < 7; i++)
		//printf("%d\t", zz[i]);

	getchar();
}