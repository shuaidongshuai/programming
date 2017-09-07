#include <fstream>
#include <iostream>
#include <string>
#include "Teacher.h"
using namespace std;

int main()
{
	char* path = "E:\\programming\\C++传智\\标准IO流\\文件读写\\TeacherProperty.txt";

	Teacher* t1 = new Teacher("陈明东", 20);
	Teacher* t2 = new Teacher("赵丽颖", 28);
	Teacher* t3 = new Teacher("成龙", 50);

	ofstream fout(path, ios::binary);//以2进制方式存储
	fout.write((char*)t1, sizeof(Teacher));
	fout.write((char*)t2, sizeof(Teacher));
	fout.write((char*)t3, sizeof(Teacher));
	fout.close();

	ifstream fin(path);
	Teacher* t = new Teacher;
	fin.read((char*)t, sizeof(Teacher));
	while (!fin.eof())
	{
		t->show();
		fin.read((char*)t, sizeof(Teacher));
	}
	fin.close();


	system("pause");
	return 0;
}