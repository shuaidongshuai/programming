#include <iostream>
#include <iomanip>
#include <stack>
#include <cstring>
using namespace std;

class HorseStep{
	int mx;
	int my;
public:
	static const int xf[8];
	static const int yf[8];
	int **res; 
	HorseStep(int mx = 8, int my = 8):mx(mx), my(my) {
		res = new int*[mx];
		for(int i = 0; i < mx; ++i)
			res[i] = new int[my]();
	}
	bool CheckPoint(int x, int y){
		if (x >= 0 && x < mx && y >= 0 && y < my && !res[x][y])
			return true;
		return false;
	}
	bool Origin(int x, int y, int count){
		res[x][y] = count;
		if(mx * my == count)
			return true;//find over 
		int nx, ny; //next step 
		for(int i = 0; i < 8; ++i){
			nx = x + xf[i];
			ny = y + yf[i];
			if(CheckPoint(nx, ny))
				if(Origin(nx, ny, count + 1)){
					return true;
				}
		}
		res[x][y] = 0;// recover 
		return false;
	}
	bool Start(int x = 0, int y = 0){
		for(int i = 0; i < mx; ++i)
			for(int j = 0; j < my; ++j)
				res[i][j] = 0;
		if(!Origin(x, y, 1)){
			cout<<"不存在这么一条路径"<<endl;
			return false;
		}
		return true;
	}
	void Print(){
		for(int i = 0; i < mx; ++i){
			for(int j = 0; j < my; ++j)
				cout<< setw(4) << res[i][j];
			cout<<endl;
		}
		cout<<endl;
	}
};
const int HorseStep::xf[8]{1, 2, 2, 1, -1, -2, -2, -1};
const int HorseStep::yf[8]{-2, -1, 1, 2, 2, 1, -1, -2};
/////////////////////////测试///////////////////////////
void test(){
	int x = 8, y = 8;
	HorseStep hs(x, y);
	for(int i = 0; i < x; ++i){
		for(int j = 0; j < y; ++j){
		 	hs.Start(i, j);
			hs.Print();
		}
	}
}
int main(){
	test();
    return 0;
}
