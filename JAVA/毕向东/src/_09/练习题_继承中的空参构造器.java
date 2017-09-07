package _09;
/*
 * java中子类必须调用父类的构造函数.如果没有用super()明确指明的话,默认调用没有参数的那个构造函数
 */
class Fu{
	Fu(String a){
		System.out.println("fu  "+a);
	}
}
class Fu2{
	Fu2(){
		System.out.println("fu2");
	}
}

class Zi extends Fu{
	Zi(){
		super("dong");
		System.out.println("zi");
		//super("dong");			//还不能放在这
	}
}
class Zi2 extends Fu2{
	Zi2(){
		System.out.println("zi2");
	}
}
public class 练习题_继承中的空参构造器{
	public static void main(String[] args) {
		new Zi();
		new Zi2();
	}
}
