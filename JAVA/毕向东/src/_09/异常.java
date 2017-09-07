package _09;
/*
 * 异常的由来：其实就是java对不正常情况进行描述后的对象体现。
 * 
 * 对问题的划分：一种是严重的问题，一种是非常严重的问题
 * 
 * 对于严重的，java通过error类进行描述
 * 		对于error 一般不编写针对性的代码对其处理
 * 
 * 对于非常严重的，java通过exception类进行描述
 * 		对于exception可以使用针对性的处理方式进行处理
 * 
 * 无论error或者exception都具有一些共性内容
 * 比如：不正常情况的信息，引发原因等
 * 
 * Throwable
 * 		|--Error
 * 		|--Exception
 * 
 * 
 * 2，异常的处理：
 * java提供了特有的语句进行处理
 * try
 * {
 * 		需要被检验的代码
 * }
 * catch(异常类  变量)
 * {
 * 		处理异常的代码：（处理方式）
 * }
 * finally
 * {
 * 		一定会执行的语句
 * }
 * 3，对捕获到的异常对象进行常见方法操作
 * 		String
 */
class div{
	int div(int a,int b){
		return a/b;
	}
}
public class 异常 {
	public static void main(String[] args) {
		try {
			System.out.println("start");
			int x = new div().div(10,0);
			System.out.println("x == "+x);
		} catch (Exception e) {				//就相当于Exception e = new ArithmeticException();这里是一个多态
			System.out.println("除以0啦");
			System.out.println(e.getMessage());
			System.out.println(e.toString());//异常名称，异常信息
			e.printStackTrace();//异常名称，异常信息，异常出现的位置
			//其实jvm默认的异常处理机制，就是在调用 printStackTrace();方法
			//打印异常的堆栈的跟踪信息
		}
		
		System.out.println("over");
	}
}
/*
 * String getMessage() 
          返回此 throwable 的详细消息字符串。 
          
   String toString() 
          返回此 throwable 的简短描述。 
          
   StackTraceElement[] getStackTrace() 
          提供编程访问由 printStackTrace() 输出的堆栈跟踪信息。 
*/
