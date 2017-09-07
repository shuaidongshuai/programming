package _07;
/**
 * 这就叫做模板设计模式。
 * 
 * 什么是模板方法呢？
 * 在定义功能时，功能的一部分是确定的，但是有一部分是不确定的，而确定的部分要使用不确定的部分，
 * 那么这时就将不确定的部分暴露除去，由该类的子类去完成
 *
 * public static long currentTimeMillis()返回以毫秒为单位的当前时间。注意，当返回值的时间单位是毫秒时
 */
abstract class GetTime{
	public final void getTime(){					//加上	final  是为了 ：不让子类覆盖父类方法
		long  start = System.currentTimeMillis();
		
		runCode();
		
		long end = System.currentTimeMillis();
		
		System.out.println("\n运行时间:"+(double)(end - start)/1000);
	}
	
	public abstract void runCode();
}

class MyGetTime extends GetTime{
	public void runCode(){
		for(int i=0;i<100000;i++)
		{
			System.out.print(i+" ");
			if(i%100 == 0 )
				System.out.println();
		}
	}
}

public class 获取一段程序运行的时间 {
	public static void main(String[] args) {
		new MyGetTime().getTime();
	}
}
