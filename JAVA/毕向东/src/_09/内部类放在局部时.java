package _09;
/*
 * 内部类定义在局部时
 * 1，不可以被成员修饰符修饰
 * 2，可以直接访问外部类中的的成员，因为还持有外部类中的引用
 * 		但是不可以访问他所在的局部中的变量，只能访问被final修饰的局部变量
 */
class Outer{
	int x = 3;
	void method(final int a){
		final int y = 4;
		class Inner{//这个类没有放在成员位置上，所以不能被成员修饰符所修饰
			void function(){
				System.out.println(x);
				System.out.println(y);//要想访问 y  定义y 的时候必须加上final
				System.out.println(a);
			}
		}
		//如果不创建Inner的对象。那么function就不会执行
		new Inner().function();
	}
	
}
public class 内部类放在局部时 {
	public static void main(String[] args) {
		Outer out = new Outer();
		out.method(10);
		out.method(20);
		
	}
}
