package _11;
/*
 * 上一个程序出现一个问题：可能有重复。可能有负数
 * 原因：
 * 当多条语句在操作同一个线程共享数据时，发生的错误
 * 
 * 解决方法：
 * 
 * 同步代码块
 * synchronized(对象)
 * {	同步代码块	}
 * 
 * 当两个并发线程(thread1和thread2)访问同一个对象(syncThread)中的synchronized代码块时，
 * 在同一时刻只能有一个线程得到执行，另一个线程受阻塞，必须等待当前线程执行完这个代码块以后才能执行该代码块。
 * Thread1和thread2是互斥的，因为在执行synchronized代码块时会锁定当前的对象，
 * 只有执行完该代码块才能释放该对象锁，下一个线程才能执行并锁定该对象。
 * 
 * 好处：
 * 解决了多线程安全问题
 * 弊端：
 * 多线程要判断锁，消耗资源
 */

class Ticket3 implements Runnable{
	private int num = 100;				//这里没有static
	Object obj = new Object();
	public void run(){
		
		while(num>0){
			
			synchronized (obj) {//保证了每次进来的线程只有一个，这样既可以保证打印的顺序，又保证了没有重复，，但程序四个线程都可以执行到这里来，所以最后一定有负数
//				try {
//				Thread.sleep(10);
//			} catch (Exception e) {
//				// TODO: handle exception
//			}
				if(num>0)//这一步保证了    没有负数 
				System.out.println(Thread.currentThread().getName()+" 卖出了"+num--+" 号票");
			}
			
		}
	}
}
public class 多线程_售票3 {
	public static void main(String[] args) {
		Ticket3 t = new Ticket3();
		
		new Thread(t).start();//由于都是使用  t 这个对象，所以四个线程通用一个类     当然也不用加static了  
		new Thread(t).start();
		new Thread(t).start();
		new Thread(t).start();
	}
}
