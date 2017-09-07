package _09;

/*前面定义过 的
 * interface Inter{
	void method();
}*/

public class 匿名内部类3 {
	public static void main(String[] args) {
		
		show(new Inter(){							//传进去一个匿名内部类
			public void method(){
				System.out.println("我是匿名内部类");
			}
		});
	}
	
	static void show(Inter in){
		in.method();
	}
	
}
