package _11;
/*
 * 如何找问题：
 * 1，明确那些代码是多线程运行代码
 * 2，明确共享数据
 * 3，明确多线程运行代码中那些语句是操作了共享数据
 * 
 */
class Bank{
	private int sum;
	public synchronized void add(int n,int i){//多线程同步函数、、、、、直接在函数上加上    synchronized   
		sum+=n;
		try {
			Thread.sleep(10);
		} catch (Exception e) {
			// TODO: handle exception
		}
		System.out.println(Thread.currentThread().getName()+".."+sum+"\ti = "+i);
	}
}
class Cun implements Runnable{
	private Bank b = new Bank();
	private int x;
	public void run(){
//		for(x=0;x<3;x++){			//下面    for()循环不一样。。   这里的   x   是两个线程的共享数据	（这里也算是一个安全隐患）
//			b.add(100,x);
//		}
		for(int y=10;y<13;y++){		//  两个线程拿到的是不同的y    y不属于共享数据，，相当于 一个是   y1   一个是     y2
			b.add(100, y);
		}
	}
}
public class 多线程_同步函数 {
	public static void main(String[] args) {
		Cun c = new Cun();
		
		new Thread(c).start();
		new Thread(c).start();		
	}
}
