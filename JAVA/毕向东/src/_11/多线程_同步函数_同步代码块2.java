package _11;
/*
 * 同步函数被静态修饰后
 * 
 * 通过验证，发现不是this   因为静态方法中不可以定义this
 * 
 * 静态进内存中没有本类对象，但是一定有该类对应的字节码文件对象
 * 类名.class  该对象的类型是Class
 * 
 * 静态的同步方法，使用的锁是该方法所在类的字节码文件对象
 */
class Tecket5 implements Runnable{
	private static int num = 100;
	boolean flag = true;
	Object obj = new Object();
	public void run(){
		
		if(flag){
			// 用同步代码块：
			while(num>0){
				synchronized(Tecket5.class){
					
					try {Thread.sleep(10);} catch (Exception e) {}
					
					if(num>0)
					System.out.println(Thread.currentThread().getName()+"  flag = "+flag+"  num = "+num--);
				}
			}
		}
		else
			while(num>0)
				show();//同步函数
	}
	
	public static synchronized void show(){
			try {Thread.sleep(10);} catch (Exception e) {}
			
			if(num>0)
			System.out.println(Thread.currentThread().getName()+"  num = "+num--);
	}
}
public class 多线程_同步函数_同步代码块2 {
	public static void main(String[] args) {
		Tecket5 t = new Tecket5();
		new Thread(t).start();
		
		try {Thread.sleep(10);} catch (Exception e) {}//暂停主程序，让线程执行同步代码块，为了用一下，同步代码块的锁
		t.flag = false;
		
		new Thread(t).start();
		/*
		 * 当除了主线程之外，有两个线程时，这两个线程，分别进入到同步代码块和同步函数
		 * 进去之后。两个线程就不冲突了，不存在强占资源问题了
		 */
	}
}
