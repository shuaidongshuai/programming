package _12;
/*
 *现在有两个生产者两个消费者，进行线程间通信
 * 
 * 这道题难就难在不是两个线程。。除了主线程有4个线程
 * 
 */
class Resource{
	private String name;
	private boolean flag = false;
	
	public synchronized void set(String name){
		while(flag)//注意这里不是  if 目的：让被唤醒的线程再一次判断标记
			try {
				wait();
			} catch (Exception e) {
			}
		this.name = name;
		System.out.println(Thread.currentThread().getName()+"...生产..."+this.name);
		flag = true;
		notifyAll();//注意是全部唤醒。。如果不是全部唤醒，很有可能就是唤醒  己方的线程。导致对方线程始终起不来。最终导致：全部线程睡眠
	}
	public synchronized void out(){
		while(!flag)//注意这里不是  if 目的：让被唤醒的线程再一次判断标记
			try {
				wait();
			} catch (Exception e) {
			}
		System.out.println(Thread.currentThread().getName()+"...消费*****"+this.name);
		flag = false;
		notifyAll();
	}
}
class Producer implements Runnable{
	private int num = 1;
	private Resource r;
	Producer(Resource r){
		this.r = r;
	}
	public void run(){
		while(true)
			r.set("商品("+(num++)+")");
	}
}
class Consumer implements Runnable{
	private Resource r;
	Consumer(Resource r){
		this.r = r;
	}
	public void run(){
		while(true)
			r.out();
	}
}
public class 线程间通信_练习 {
	public static void main(String[] args) {
		Resource r = new Resource();
		
		Producer p = new Producer(r);
		Consumer c = new Consumer(r);
		
		new Thread(p).start();;
		new Thread(p).start();;
		new Thread(c).start();;
		new Thread(c).start();;
		
		
	}
}
