//一、友元介绍
//我们知道，类的成员函数可以访问同类的其他成员函数，包括公有、私有和保护成员。而类的外部函数只能访问类的公有成员。
//
//友元是一种允许非类成员函数访问类的非公有成员的一种机制。
//可以把一个函数指定为类的友元，也可以把整个类指定为另一个类的友元。
//友元函数
//友元类
//二、友元函数
//友元函数在类作用域外定义，但它需要在类体中进行说明
//为了与该类的成员函数加以区别，定义的方式是在类中用关键字friend说明该函数，格式如下：
//friend  类型 友元函数名(参数表);
//友元的作用在于提高程序的运行效率
//友元函数注意事项：
//1、友元函数不是类的成员函数，在函数体中访问对象的成员，必须用对象名加运算符“.”加对象成员名。但友元函数可以访问类中的所有成员（公有的、私有的、保护的），一般函数只能访问类中的公有成员。
//2、友元函数不受类中的访问权限关键字限制，可以把它放在类的公有、私有、保护部分，但结果一样。
//3、某类的友元函数的作用域并非该类作用域。如果该友元函数是另一类的成员函数，则其作用域为另一类的作用域，否则与一般函数相同。
//4、友元函数破坏了面向对象程序设计类的封装性，所以友元函数如不是必须使用，则尽可能少用。或者用其他手段保证封装性。

#include <math.h>
#include <iostream>
using namespace std;
class Point
{
    friend double Distance(const Point &p1, const Point &p2);
public:
    Point(int x, int y);
private:
    int x_;
    int y_;
};
Point::Point(int x, int y) : x_(x), y_(y)
{
}
double Distance(const Point &p1, const Point &p2)
{
    double dx = p1.x_ - p2.x_;
    double dy = p1.y_ - p2.y_;
    return sqrt(dx * dx + dy * dy);
}
int main(void)
{
    Point p1(3, 4);
    Point p2(6, 9);
    cout << Distance(p1, p2) << endl;
    return 0;
}
//程序中Distance 是Point类的友元函数，可以访问类的私有数据成员。

//三、友元类
//如果某类B的成员函数会频繁的存取另一个类A的数据成员, 而A的数据成员的Private/Protectd限制造成B存取的麻烦, B只能通过A的Public的成员函数进行间接存取
//把B做成A类的友元类,即A类向B类开放其Private/Protectd内容, 让B直接存取
//友元类：一个类可以作另一个类的友元
//友元类的所有成员函数都是另一个类的友元函数
//友元类的声明：
//friend class 类名;
//友元类注意事项：
//1、友元关系是单向的
//2、友元关系不能被传递
//3、友元关系不能被继承 


//将TeleController 类作为Television类的友元类，这样TeleController 类的成员函数就都可以访问Television类的所有成员，包括私有。 

