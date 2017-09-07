package _11;
/*
 * 同步代码块用的锁，是一个类
 * 同步函数用的的锁，是this（函数要被对象调用，那么函数都有一个所属对象引用，就是this）
 * 
 * 这个程序就是来验证同步函数的锁是不是this
 * 
 * 解决方案：
 * 我们知道多线程有暗转隐患。。。加上   同步函数和同步代码块可以解决
 * 
 * 但是解决问题有两个前提： 1，线程在两个或两个以上（必须同步所有的锁）
 * 						  2，用的是同一个锁
 * 
 * 当我们同时用-----同步函数_and 同步代码块-----处理同一个问题。。
 * 如果-----同步函数_and 同步代码---块锁不一样，那么会有安全隐患。
 * 如果锁一样，那么就满足   解决问题的两个前提。。就没有安全隐患
 */
class Tecket4 implements Runnable{
	private int num = 100;
	boolean flag = true;
	Object obj = new Object();
	public void run(){
		
		if(flag){
			// 用同步代码块：
			while(num>0){
				synchronized(this){//如果这用  obj  那么用的是不同的锁，结果可能为0			如果是   this  那么始终不可能出现0
					
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
	
	public synchronized void show(){
			try {Thread.sleep(10);} catch (Exception e) {}
			
			if(num>0)
			System.out.println(Thread.currentThread().getName()+"  num = "+num--);
	}
}
public class 多线程_同步函数_同步代码块 {
	public static void main(String[] args) {
		Tecket4 t = new Tecket4();
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
