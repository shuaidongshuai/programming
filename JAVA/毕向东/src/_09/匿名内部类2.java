package _09;

interface Inter{
	void method();
}
/*		这就是一道题，，让你根据 Test.function().method();		补全代码			*/
public class 匿名内部类2 {
	public static void main(String[] args) {
		
		Test.function().method();	//   主要就是为了理解这句话
		
		/*这句话可以拆分成     
		 * Inter in = Test.function();
		 * in.method();					这样两句话
		 */
	}
}
class Test{
	static Inter function(){	//这是一个静态方法
		return new Inter(){		//这里返回的是一个    Inter  的 匿名子类。的一个对象
			public void method(){//匿名子类中的方法
				System.out.println("method run");
			}
		};
	}
}

