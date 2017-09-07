package _09;
/*
 * 因为项目中会出现特有的问题
 * 而这些问题并未被java所描述，并封装对象
 * 所以对于这些特有的问题可以按照java对问题封装的思想
 * 将特有的问题，进行自定义的异常封装
 * 
 * 自定义异常
 * 
 * 需求：在本程序中，对于除数是负数，也是视为是错误的，是无法进行运算的
 * 那么就需要对这个问题进行自定义的描述
 * 
 * 
 * 当在函数内部出现了throw抛出异常对象，那么就必须要给对应的处理动作
 * 要么在内部try catch处理
 * 要么在函数上声明让调用者处理
 * 
 * 一般情况下，函数内出现异常，函数上需要声明，
 * 
 * 发现打印的结果中只有异常的名称，没有异常的信息
 * 因为自定义的异常并未定义信息
 * 
 * 如何自定义异常信息呢？
 * 因为父类中已经把异常信息的操作都做完了
 * 所以子类只要在构造时，将异常信息传给父类通过super
 * 那么就可以直接通过getMessage方法获取自定义的异常信息
 * 
 * 自定义异常：
 * 必须是自定义类继承Exception
 * 
 * 继承Exception的原因：
 * 异常体系有一个特点，以为异常类和异常对象都被抛出
 * 他们都具备可抛性，这个可抛性是Throwable这个体系中独有特点
 * 
 * 只有这个体系中的类和对象才可以被throws和throw操作
 * 
 */
class FuShuException extends Exception{			//自定义异常必须继承  Exception 或者  Throwable  或者 Error
	private int value;
	
	FuShuException(){
		
	}
	//如果我们想让这个自定义异常  与其他异常不一样，可以获取出异常时那个，负数
	FuShuException(String msg,int value){
		super(msg);
		this.value = value; //获取负数
	}
	public int getValue(){//返回那个负数
		return value;
		
	}
}

class Demo1{
	int div(int a,int b)throws FuShuException{
		if(b<0){
			throw new FuShuException("出现了负数的情况",b);//手动通过 throw（关键字）抛出一个自定义异常对象。  	注意是：throw  不是 throws
		}
		return a/b;
	}
}

public class 自定义异常 {
	public static void main(String[] args) {
		Demo1 d = new Demo1();
		try {
			int x = d.div(5,-10);
			System.out.println("x = "+x);
		} catch (FuShuException e) {						//如果出现异常就马上执行这一步
			System.out.println(e.toString());
			System.out.println("错误原因："+e.getMessage());
//			if(e.getValue()!=0)
			System.out.println("错误的负数是："+e.getValue());
		}
		System.out.println("over");
	}
}
/*下面是 Throwable 大致的源码
 *class Throwable
 *{
 * 	private String message;
 * 	Throwable(String message)
 * {
 * 	this.message = message;
 * }
 * 
 * public String getMessage()
 * {
 * 	return mesage;				//父类直接打印   传进来的  message 信息
 * }
 * }
 * 
 * 所以子类构造函数中只要使用   super(msg)	就可以利用父类的代码了
 */

/*
下面这个是Exception类的部分源码
public class Exception extends Throwable {

    public Exception() {
        super();																看出exception也是直接继承Throwable类
    }
    public Exception(String message) {
        super(message);															看出exception也是直接继承Throwable类
    }
 */
