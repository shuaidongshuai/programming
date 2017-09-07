package _06;
/**
 * 静态代码块
 * 格式：
 * static
 * {
 * 		静态代码块中的执行语句
 * }
 * 特点：随着类的加载而执行，只执行一次
 * 用于给类初始化的
 */
class StaticCode{
	public static void show(){
		System.out.println("haha");
	}
	
	static{
		System.out.println("c");
	}
}
public class 静态代码块 {
	static{
		System.out.println("a");
	}
	
	public static void main(String[] args) {
//		new StaticCode();
//		new StaticCode();//两个 new StaticCode    但是 static代码块只执行一次
//		System.out.println("over");
		
		StaticCode.show();//调用方法时也自动调用 static代码块
		
	}
	
	static{
		System.out.println("b");
	}
	
}
