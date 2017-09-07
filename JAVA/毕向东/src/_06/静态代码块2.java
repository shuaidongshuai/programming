package _06;

/**
 * 注意打印出来的顺序
 */
class StaticCode1{
	int num = 10;
	//静态代码块，给类初始化。。注意：如果要调用 属性  ，只能调用静态属性
	static{
		System.out.println("a");
	}
	//构造代码块，给对象初始化的
	{
		System.out.println("b"+this.num);
	}
	//构造函数，给对应对象初始化的
	StaticCode1(int x){
		System.out.println("c");
	}
}
public class 静态代码块2 {
	public static void main(String[] args) {
		new StaticCode1(4);
	}
}

