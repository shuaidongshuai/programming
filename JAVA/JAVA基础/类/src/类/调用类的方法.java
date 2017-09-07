package 类;

class Hello{
	void sayHello(){
		System.out.println("hello dong");
	}
}

class Hello1{
	static void sayHello(){
		System.out.println("hello dong");
	}
}

//这个是抽象类
abstract class Hello2{
	static void say(){
		System.out.println("this is a abstract class");
	}
}

public class 调用类的方法 {
	public static void main(String [] args){
		//  先声明   再调用
		Hello dong = new Hello();
		dong.sayHello();
		
		Hello1.sayHello();
		
		// 可以通过抽象类名  调用其静态方法
		Hello2.say();
	}
}
