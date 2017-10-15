#include<iostream> 
#include"CNode_s.h" 
#include"CVirtualNode_s.h" 
#include"CHashFun.h" 
#include"CConHash.h"
#include"CHashFun.h"
#include<string.h> 
#include<time.h> 

using namespace std;

void getIP(char * IP)
{
	int a = 0, b = 0, c = 0, d = 0;
	a = rand() % 256;
	b = rand() % 256;
	c = rand() % 256;
	d = rand() % 256;
	char aa[4], bb[4], cc[4], dd[4];
	itoa(a, aa, 10);
	itoa(b, bb, 10);
	itoa(c, cc, 10);
	itoa(d, dd, 10);
	strcpy(IP, aa);
	strcat(IP, ".");
	strcat(IP, bb);
	strcat(IP, ".");
	strcat(IP, cc);
	strcat(IP, ".");
	strcat(IP, dd);
}

int main()
{
	srand(time(0));
	freopen("out.txt", "r", stdin);
	/*定义hash函数*/
	CHashFun * func = new CMD5HashFun();
	/*创建一致性hash对象*/
	CConHash * conhash = new CConHash(func);

	/*定义CNode*/
	CNode_s * node1 = new CNode_s("machineA", 50, "10.3.0.201");
	CNode_s * node2 = new CNode_s("machineB", 80, "10.3.0.202");
	CNode_s * node3 = new CNode_s("machineC", 20, "10.3.0.203");
	CNode_s * node4 = new CNode_s("machineD", 100, "10.3.0.204");

	conhash->addNode_s(node1);
	conhash->addNode_s(node2);
	conhash->addNode_s(node3);
	conhash->addNode_s(node4);

	/*动态更改结点数据值*/
	//  node1->setData("99999999"); 

	int ans1, ans2, ans3, ans4;
	ans1 = ans2 = ans3 = ans4 = 0;

	char object[100];
	CNode_s * node;
	/*动态删除结点*/
	//conhash->delNode_s(node2); 
	for (int i = 0; i<30; i++)
	{
		//  getIP(object); 
		//  cout<<object<<endl; 
		cin >> object;
		node = conhash->lookupNode_s(object);
		if (node != NULL)
		{
			cout << object << "----->\t" << node->getIden() << " \t " << (char *)node->getData() << endl;
			if (strcmp(node->getIden(), "machineA") == 0) ans1++;
			if (strcmp(node->getIden(), "machineB") == 0) ans2++;
			if (strcmp(node->getIden(), "machineC") == 0) ans3++;
			if (strcmp(node->getIden(), "machineD") == 0) ans4++;
		}
	}

	cout << "Total test cases : " << ans1 + ans2 + ans3 + ans4 << endl;
	cout << "Map to MachineA : " << ans1 << endl;
	cout << "Map to MachineB : " << ans2 << endl;
	cout << "Map to MachineC : " << ans3 << endl;
	cout << "Map to MachineD : " << ans4 << endl;
	fclose(stdin);
	return 0;
}