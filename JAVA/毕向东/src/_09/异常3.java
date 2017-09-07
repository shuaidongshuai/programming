package _09;
/*
 * 对多异常的处理
 * 
 * 1，声明异常时，建议声明更为具体的异常，这样处理，可以更加具体
 * 2，对方声明几个异常，就对应几个catch 块。不要定义多余的catch块
 * 		如果多个catch块中的异常出现继承关系，父类异常catch块放在最下面
 * 
 * 建议在进行catch 处理时，catch中一定要定义具体的处理方式
 * 不要简单定义一句：e.printStackTrace()
 * 也不要简单的就书写一条输出语句
 */
class Demo{
	int div(int a,int b)throws ArithmeticException,ArrayIndexOutOfBoundsException
	{
		int[] arr = new int [a];
		System.out.println(arr[4]);//数组越界始终在  除以0 之前。。如果两个同时发生  只能触发数组异常，然后这段程序就不执行了
		return a/b;
	}
}
public class 异常3 {
	public static void main(String[] args) {
		Demo d = new Demo();
		try {
			int x = d.div(5, 1);//把5改为4   或者把 0改为1
		} catch (ArithmeticException e) {
			System.out.println(e.toString());
			System.out.println("除以0 了");
		} catch (ArrayIndexOutOfBoundsException e) {
			System.out.println(e.toString());
			System.out.println("数组越界了");
		}/*
		catch(Exception e){							//不建议这么做。这样做  就不能    不能针对性的处理问题。（excepton是父类）
			System.out.println(e.toString());		//如果非要加上，也不要加在  ArithmeticException  ArrayIndexOutOfBoundsException  之前
		}*/											//这样做会导致  针对 前面两个异常的  处理方法   完全垃圾。永远执行不到他们
		System.out.println("over");
	}
}
//Arithmetic  算术    Exception  异常，例外
//ArrayIndexOutOfBoundsException数组越界异常
