#include <iostream>
#include <string>
using namespace std;
int** createRect(int n){
	int **matrix = new int*[n];
	for (int k = 0; k < n; k++)
		matrix[k] = new int[n];
	int circle = 0;
	int v = 1;
	int i = 0, j = 0;
	while (n - 2 * circle >= 2){
		for (j = circle; j < n - circle; j++){
			matrix[i][j] = v;
			v++;
		}
		j--; i++;
		for (i; i < n - circle; i++){
			matrix[i][j] = v;
			v++;
		}
		i--; j--;
		for (j; j >= circle; j--){
			matrix[i][j] = v;
			v++;
		}
		j++; i--;
		for (i; i > circle; i--){
			matrix[i][j] = v;
			v++;
		}
		i++; circle++;
	}
	if (n - 2 * circle == 1){
		j = circle;
		matrix[i][j] = v;
	}
	return matrix;
}
int main(){
	int n, m, x, y;
	cin >> n >> m;
	int **rect = createRect(n);
	cin >> x >> y;
	x -= 1;
	y -= 1;
	for(int i = 0; i < m; ++i){
		for(int j = 0; j < m; ++j){
			cout << rect[x + i][y + j] << ",";
		}
		cout << endl;
	}
	return 0;
}
