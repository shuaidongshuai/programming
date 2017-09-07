package _12;

import javax.swing.plaf.basic.BasicInternalFrameTitlePane.MaximizeAction;

class Priority implements Runnable{
	
	public void run(){
		for(int i=0;i<10;i++){
			System.out.println(Thread.currentThread().toString());//toString() 返回该线程的字符串表示形式，包括线程名称、优先级和   线程组。
			//Thread.yield();//暂停当前正在执行的线程对象，并执行其他线程。
		}
		
		
	}
}
public class 多线程优先级 {
	public static void main(String[] args) throws InterruptedException {
		System.out.println("高优先级："+Thread.MAX_PRIORITY);
		System.out.println("默认："+Thread.NORM_PRIORITY);
		System.out.println("默认："+Thread.MIN_PRIORITY);
		
		Priority p = new Priority();
		
		
		Thread t1 = new Thread(p);
//		t1.join();
		Thread t2 = new Thread(p);

		t1.setPriority(Thread.MAX_PRIORITY);
		t1.start();
		t2.start();
		
	}
}
