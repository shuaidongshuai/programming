package _12;
/*
 * 如何停止线程
 * 只有一种，，run()方法结束
 * 开启多线程运行，运行代码通常是循环结构
 * 
 * 只要控制循环，就可以让run方法结束，也就是线程结束
 */
class StopThread implements Runnable{
	private boolean f = true;
	public synchronized void run(){
		while(f){
			try {
				wait();
			} catch (InterruptedException e) {//当   线程从  wait 状态  被  interrupt 唤醒（打断wati状态），就会发生异常，但是notify这些是正常唤醒
				System.out.println(Thread.currentThread().getName()+"          Exception");
				f = false;//每次interrupt都会唤醒，但是循环一次又被  wait  所以  这里才是正真处理线程结束的操作。让线程退出循环
			}
			System.out.println(Thread.currentThread().getName()+"               runing");	//当没有异常发生时  执行这
		}
	}
}
public class 停止线程 {
	public static void main(String[] args) {
		StopThread s = new StopThread();
		Thread t1 = new Thread(s);
		Thread t2 = new Thread(s);
		t1.start();
		t2.start();
		
		for(int i=0;i<60;i++)
			System.out.println(Thread.currentThread().getName()+"    runing");
		
		t1.interrupt();// 让线程  从  wati  and  sleep 这些睡眠状态     恢复正常（唤醒线程）
		t2.interrupt();
		System.out.println("over");
	}
}
