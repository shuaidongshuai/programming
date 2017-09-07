package _12;
/*
 * Input向  Res 里面写数据，Output往Res里面读数据
 * 
 * 注意：1，两个线程都必须同时同步，不能只同步一个
 *       2，两个线程必须用同一个锁（同一个类对象）
 *       
 *  wait;
 *  notify();
 *  notifyAll();
 *  都使用在同步中，因为要持有监视器（锁）的线程操作
 *  所以要使用在同步中，因为只有同步才有锁
 *  
 *  为什么这些操作线程的方法要定义在Object中？
 *  因为：这些方法在操作同步中线程时，都必须要标识他们所操作线程的锁
 *  只有同一个锁上的被等待线程，可以被同一个锁上的notefy唤醒
 *  不可以对不同锁中的线程唤醒
 *  
 *  也就是说，等待和唤醒必须是同一个锁
 *  
 *  而锁可以是任意对象，所以可以被任意对象调用的方法定义在Object类中
 */
class Res{
	public String name ;
	public String sex;
	public boolean f  = false;//false表示还没有被读取。数据为空
}
class Input implements Runnable{
	private Res r;
	Input(Res r){
		this.r = r;
	}
	public void run(){
		int x = 0;
		while(true){
			synchronized(Input.class){
				if(r.f)
					try{Input.class.wait();} catch(Exception e){}
				if(x == 0){
					r.name = "dong";
					r.sex = "man";
				}
				else{
					r.name = "丽丽";
					r.sex = "女";
				}
				r.f = true;
				Input.class.notify();
				x = (x+1)%2;
			}
		}
	}
}
class Output implements Runnable{
	private Res r;
	Output(Res r){
		this.r = r;
	}
	public void run(){
		while(true){
			synchronized(Input.class){
				if(!r.f)
					try{Input.class.wait();} catch(Exception e){}
				System.out.println(r.name+"    "+r.sex);
				r.f = false;
				Input.class.notify();
			}
		}
	}
}
public class 线程间通信 {
	public static void main(String[] args) {
		Res r = new Res();
		Input i = new Input(r);
		Output o = new Output(r);
		
		new Thread(i).start();
		new Thread(o).start();
		
	}
}
