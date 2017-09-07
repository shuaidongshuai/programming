package _09;
/*
 * Exception中有一个特殊的子类异常RuntimeException  运行时异常
 * 
 * 如果在函数内抛出该异常。函数上可以不用声明
 * 
 * 如果在函数上声明了该异常，调用者可以不用进行处理（try  或者    抛   ）
 * 
 * 之所以不用在函数声明，是因为不需要让调用者处理
 * 当该异常发生，希望程序停止。因为在运行时，出现了无法继续运算的情况，希望程序终止
 * 然后我们对代码进行修改
 * 
 * 自定义异常时：如果该异常的发生，无法再继续进行运算，
 * 就让自定义异常继承RuntimeException异常 
 * 
 * 
 * 对于异常分两种：
 * 1，编译时被检测的异常
 * 2，编译时不被检测的异常（运行异常，RuntimeException以及他的子类）
 * 
 * 什么时候抛出RuntimeException异常？
 * 当出现这个异常后，整个程序就不能运行。这时用RuntimeException
 * 这个异常抛出  1，不用在函数上声明。2，不会编译出错
 */
class FuShuException2 extends RuntimeException{			//自定义异常必须继承  Exception 或者  Throwable  或者 Error
	FuShuException2(String msg){
		super(msg);
	}
}
class Demo2{
	int div(int a,int b)//throws ArithmeticException,ArrayIndexOutOfBoundsException   不用加
	{
		if(b<0){
			throw new FuShuException2("出现负数了");
		}
		if(b==0){
			throw new ArithmeticException("出现 0 了");
		}
		return a/b;
	}
}
public class RuntimeException异常 {
	public static void main(String[] args) {
		int x = new Demo2().div(10,-1);
		System.out.println("x == "+x);
		System.out.println("over");
	}
}
/**
 * 构造方法摘要 
ArithmeticException() 
          构造不带详细消息的 ArithmeticException。 
ArithmeticException(String s) 
          构造具有指定详细消息的 ArithmeticException。 
 */
