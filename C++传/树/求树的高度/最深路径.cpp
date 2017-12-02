#include <iostream>
#include <string>
#include <vector>
#include "tree.h"
using namespace std;

void DeepPathTree(Node *node, vector<int> &v){
	if (!node || !node->left && !node->right){
		return;
	}
}

int main2(){
	int val;
	Tree root = NULL;
	//先创建一棵树 
	for (int i = 0; i<10; i++){
		val = rand() % 100;
		create(root, val);
	}
		

	cin.get();
	return 0;
}
