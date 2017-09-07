package _12;
/*
 * JDK1.5中提供了   Lock
 * synchronized 转换成实现 Lock 操作
 * 
 * 新方法Lock
 * 
 * Lock lock = new ReentrantLock();
 * Condition condition_pro = lock.newCondition();
 * Condition condition_con = lock.newCondition();
 * 
 * lock.lock();
 * 
 * condition_pro.await();//本线程等待
 * condition_con.signal();//唤醒对方线程
 * 
 * lock.unlock();
 */
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class Resource2{
	private String name;
	private boolean flag = false;
	
	private Lock lock = new ReentrantLock();
	private Condition condition_pro = lock.newCondition();
	private Condition condition_con = lock.newCondition();
	
	public void set(String name){
		lock.lock();
		try {
			while(flag)
				condition_pro.await();//本线程等待
			this.name = name;
			System.out.println(Thread.currentThread().getName()+"...生产.."+this.name);
			flag = true;
			condition_con.signal();//唤醒对方线程
		} catch(InterruptedException e){
			System.out.println("出错");
		}finally {
			lock.unlock();
		}


	}
	public void out(){
		lock.lock();
		try {
			while(!flag)
				condition_con.await();
		System.out.println(Thread.currentThread().getName()+"...消费******"+this.name);
		flag = false;
		condition_pro.signal();
		} catch(InterruptedException e){
			System.out.println("出错");
		}finally {
			lock.unlock();
		}
	}
}
class Producer2 implements Runnable{
	private int num = 1;
	private Resource2 r;
	Producer2(Resource2 r){
		this.r = r;
	}
	public void run(){
		while(num<60)
			r.set("商品("+(num++)+")");
	}
}
class Consumer2 implements Runnable{
	private int num = 1;
	private Resource2 r;
	Consumer2(Resource2 r){
		this.r = r;
	}
	public void run(){
		while(num++<60)
			r.out();
	}
}
public class 线程通信_练习_lock替代同步 {
	public static void main(String[] args) {
		Resource2 r = new Resource2();
		
		Producer2 p = new Producer2(r);
		Consumer2 c = new Consumer2(r);
		
		new Thread(p).start();;
		new Thread(p).start();;
		new Thread(c).start();;
		new Thread(c).start();;
		
		
	}
}
