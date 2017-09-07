package _11;
/*
 * 死锁
 * 同步中嵌套同步
 */
class MyLock{
	static Object lock1 = new Object();
	static Object lock2 = new Object();
}
class Deadlock implements Runnable{
	private boolean flag = true;
	Deadlock(boolean a){
		flag = a;
	}
	public void run(){
		if(flag){
			while(true){
				synchronized(MyLock.lock1){
					System.out.println("if lock1");
					synchronized(MyLock.lock2){
						System.out.println("if lock2");
					}
				}
			}
		}
		else{
			while(true){
				synchronized(MyLock.lock2){
					System.out.println("else lock2");
					synchronized(MyLock.lock1){
						System.out.println("else lock1");
					}
				}
			}
		}
	}
}
public class 死锁 {
	public static void main(String[] args) {
		new Thread(new Deadlock(true)).start();
		new Thread(new Deadlock(false)).start();
	}
}
