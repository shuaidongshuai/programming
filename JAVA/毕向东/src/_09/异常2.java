package _09;
/*
 * 在函数上声明异常
 * 以便于提高安全性，在编译时 提示  异常  进行处理，不处理编译失败
 */
class div1{
	int div(int a,int b)throws Exception  	//在功能上通过throws关键字声明该功能可能会出现问题
	{
		return a/b;
	}
}

public class 异常2 {
	public static void main(String[] args)/*throws Exception*/{		//可以抛  用 throws Exception（注释掉的地方）但是这样不负责任
		System.out.println("start");
		int x;
		try {														//最好的是进行处理     用：try{} catch{}进行处理
			x = new div1().div(10,0);
			System.out.println("x == "+x);
		} catch (Exception e) {
			System.out.println(e.toString());
		}
		
		System.out.println("over");
	}
}
