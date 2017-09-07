#include<stdlib.h>
#include<string>
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
const int N = 35;

struct Student {
	char name[11];
	char number[11];
	int grade1;
	int grade2;
	int grade3;
	int grade4;
	int grade5;
	int grade6;
	int sum;
	int aver;
}stu[35];
void Print();
void Account();
void SumSort(struct Student a[]);
void SubSort(struct Student a[]);
void Sort1(struct Student a[]);
void Sort2(struct Student a[]);
void output1(struct Student a[]);
void output2(struct Student a[]);

struct Student a[N], *p = a;

int main()//菜单
{
	char c;
	do {
		system("cls");//清除屏幕先前的显示内容
		cout << "  *                                                *\n" <<
			"                 学生成绩管理系统                   \n" <<
			"  *                                                *\n" <<
			"                                                    \n" <<
			"  *   1.输出文件中全部学生信息   2.分均分及总分    *\n" <<
			"      3.总分排序                 4.单科成绩筛选     \n" <<
			"  *                                                *\n" <<
			"                      0.退出系统                    \n" <<
			"  *                                                *\n" <<
			"  * -* --*--*--*--*--*--*--*--* -*\n" <<
			"\n请选择操作方式(1-4): ";

		cin >> c;

		switch (c)
		{
		case '1':Print();
			break;
		case '2':Account();
			break;
		case '3':SumSort(p);
			break;
		case '4':SubSort(p);
			break;
		case '0':break;
		default:cout << "输入错误！请重新选择!" << endl;
		}
	} while (system("pause"), c != '0');
}



void Print()
{
	ifstream inDate("F:\\2.txt", ios::in);
	string name;
	int number;
	int grade1;
	int grade2;
	int grade3;
	int grade4;
	int grade5;
	int grade6;

	cout << "  姓名    " << "学号    " << "成绩1  " << "成绩2  " << "成绩3  " << "成绩4  " << "成绩5  " << "成绩6 \n " << endl;

	while (inDate >> name >> number >> grade1 >> grade2 >> grade3 >> grade4 >> grade5 >> grade6)
	{
		cout << setw(7) << name << setw(10) << number << setw(7) << grade1 << setw(7) << grade2
			<< setw(7) << grade3 << setw(7) << grade4 << setw(7) << grade5 << setw(7) << grade6 << "\n" << endl;

	}

}

void Account()//计算平均分 
{
	ifstream inDate("F:\\2.txt", ios::in);
	string name;
	int number;
	int grade1;
	int grade2;
	int grade3;
	int grade4;
	int grade5;
	int grade6;
	int sum;//总分 
	int aver;//平均分 

	cout << "  姓名    " << "学号    " << "总分  " << "平均分 \n" << endl;

	while (inDate >> name >> number >> grade1 >> grade2 >> grade3 >> grade4 >> grade5 >> grade6)
	{
		sum = grade1 + grade2 + grade3 + grade4 + grade5 + grade6;
		aver = (grade1 + grade2 + grade3 + grade4 + grade5 + grade6) / 6;
		cout << setw(7) << name << setw(10) << number << setw(7) << sum << setw(7) << aver << "\n" << endl;

	}

}

void SumSort(struct Student a[])
{
	int i = 0;
	ifstream inDate("F:\\2.txt", ios::in);

	while (!inDate.eof())
	{
		inDate >> a[i].name >> a[i].number >> a[i].grade1 >> a[i].grade2
			>> a[i].grade3 >> a[i].grade4 >> a[i].grade5 >> a[i].grade6;
		a[i].sum = a[i].grade1 + a[i].grade2 + a[i].grade3 + a[i].grade4 + a[i].grade5 + a[i].grade6;
		a[i].aver = (a[i].grade1 + a[i].grade2 + a[i].grade3 + a[i].grade4 + a[i].grade5 + a[i].grade6) / 6;
		i++;
	}
	Sort1(p);
}

void SubSort(struct Student a[])
{
	int i = 0;
	ifstream inDate("F:\\2.txt", ios::in);

	while (!inDate.eof())
	{
		inDate >> a[i].name >> a[i].number >> a[i].grade1 >> a[i].grade2
			>> a[i].grade3 >> a[i].grade4 >> a[i].grade5 >> a[i].grade6;
		a[i].sum = a[i].grade1 + a[i].grade2 + a[i].grade3 + a[i].grade4 + a[i].grade5 + a[i].grade6;
		a[i].aver = (a[i].grade1 + a[i].grade2 + a[i].grade3 + a[i].grade4 + a[i].grade5 + a[i].grade6) / 6;
		i++;
	}
	Sort2(p);

}

void Sort1(struct Student a[])//排序函数
{
	int  i, j;
	struct Student temp;
	for (j = 0; j < N - 1; j++)
	{
		for (i = 0; i< N - 1; i++)
		{
			if (a[i].sum<a[i + 1].sum)
			{
				temp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = temp;
			}
		}
	}
	output1(p);
}

void Sort2(struct Student a[])//排序函数
{
	int  i, j;
	struct Student temp;

	for (j = 0; j < N - 1; j++)
	{
		for (i = 0; i< N - 1; i++)
		{
			if (a[i].sum<a[i + 1].sum)
			{
				temp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = temp;
			}
		}
	}
	output2(p);
}

void output1(struct Student a[])
{
	int i;
	cout << "按总成绩排名输出：\n" << endl;
	cout << " 排名  姓名  学号   成绩1  成绩2  成绩3  成绩4  成绩5  成绩6  总成绩  平均分\n " << endl;
	for (i = 0; i<N; i++)
	{
		cout << setw(3) << i + 1 << setw(7) << a[i].name << setw(10) << a[i].number << setw(7) << a[i].grade1 << setw(7) << a[i].grade2
			<< setw(7) << a[i].grade3 << setw(7) << a[i].grade4 << setw(7) << a[i].grade5 << setw(7) << a[i].grade6 << setw(7) << a[i].sum << setw(7) << a[i].aver << "\n\n";
	}
}

void output2(struct Student a[])
{
	int i, t;
	cout << "请输入要筛选的课程号：";
	cin >> t;
	cout << "成绩" << t << "在90分以上且总成绩在全班前5输出：\n" << endl;
	cout << "排名  姓名    学号   成绩1  成绩2  成绩3  成绩4  成绩5  成绩6  总成绩  平均分\n " << endl;
	if (t == 1){
		for (i = 0; i<5; i++)
		{
			if (a[i].grade1>90)
				cout << setw(3) << i + 1 << setw(7) << a[i].name << setw(10) << a[i].number << setw(7) << a[i].grade1 << setw(7) << a[i].grade2
				<< setw(7) << a[i].grade3 << setw(7) << a[i].grade4 << setw(7) << a[i].grade5 << setw(7) << a[i].grade6 << setw(7) << a[i].sum << setw(7) << a[i].aver << "\n";
		}
	}
	else if (t == 2){
		for (i = 0; i<5; i++)
		{
			if (a[i].grade2>90)
				cout << setw(3) << i + 1 << setw(7) << a[i].name << setw(10) << a[i].number << setw(7) << a[i].grade1 << setw(7) << a[i].grade2
				<< setw(7) << a[i].grade3 << setw(7) << a[i].grade4 << setw(7) << a[i].grade5 << setw(7) << a[i].grade6 << setw(7) << a[i].sum << a[i].aver << "\n";
		}
	}
	else if (t == 3){
		for (i = 0; i<5; i++)
		{
			if (a[i].grade3>90)
				cout << setw(3) << i + 1 << setw(7) << a[i].name << setw(10) << a[i].number << setw(7) << a[i].grade1 << setw(7) << a[i].grade2
				<< setw(7) << a[i].grade3 << setw(7) << a[i].grade4 << setw(7) << a[i].grade5 << setw(7) << a[i].grade6 << setw(7) << a[i].sum << a[i].aver << "\n";
		}
	}
	else if (t == 4){
		for (i = 0; i<5; i++)
		{
			if (a[i].grade4>90)
				cout << setw(3) << i + 1 << setw(7) << a[i].name << setw(10) << a[i].number << setw(7) << a[i].grade1 << setw(7) << a[i].grade2
				<< setw(7) << a[i].grade3 << setw(7) << a[i].grade4 << setw(7) << a[i].grade5 << setw(7) << a[i].grade6 << setw(7) << a[i].sum << a[i].aver << "\n";
		}
	}
	else if (t == 5){
		for (i = 0; i<5; i++)
		{
			if (a[i].grade5>90)
				cout << setw(3) << i + 1 << setw(7) << a[i].name << setw(10) << a[i].number << setw(7) << a[i].grade1 << setw(7) << a[i].grade2
				<< setw(7) << a[i].grade3 << setw(7) << a[i].grade4 << setw(7) << a[i].grade5 << setw(7) << a[i].grade6 << setw(7) << a[i].sum << a[i].aver << "\n";
		}
	}
	else if (t == 6){
		for (i = 0; i<5; i++)
		{
			if (a[i].grade6>90)
				cout << setw(3) << i + 1 << setw(7) << a[i].name << setw(10) << a[i].number << setw(7) << a[i].grade1 << setw(7) << a[i].grade2
				<< setw(7) << a[i].grade3 << setw(7) << a[i].grade4 << setw(7) << a[i].grade5 << setw(7) << a[i].grade6 << setw(7) << a[i].sum << a[i].aver << "\n";
		}
	}
	else
		cout << "输入有误！" << endl;
}

