#include <typeinfo>
#include <cassert>
#include <iostream> 
using namespace std;

struct B {} b, c;

struct D : B {} d;

int main() {
    const std::type_info& tb = typeid(b); 
    const std::type_info& tc = typeid(c); 
    const std::type_info& td = typeid(d);
    assert(tb == tc);   // b和c具有相同的类型
    assert(&tb == &tc); // tb和tc引用的是相同的对象
    assert(tb != td);   // 虽然D是B的子类，但是b和d的类型却不同
    assert(&tb != &td); // tb和td引用的是不同的对象
    
    cout<<tb.name()<<endl;
    cout<<tc.name()<<endl;
    cout<<td.name()<<endl;
}
