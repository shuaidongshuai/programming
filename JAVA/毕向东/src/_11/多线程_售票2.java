package _11;
/*
 * 创建线程的第二种方式，实现Runable接口
 * 
 * 步骤
 * 1，定义类实现Runnable接口
 * 2，覆盖Runnable接口中的run方法
 * 3，通过Thread类建立线程对象
 * 4，将Runnable接口的子类对象作为实际参数传给Thread类的构造函数
 * 5，调用Thread类的start方法开启线程并调用Runnable接口子类的run方法
 * 
 * 实现方式和继承方式有什么区别？
 * 实现方式好处：避免了单继承的局限性
 * 在定义线程时，建议使用实现方式
 * 。。。。。。。。。。。。。。。。。。接口可以实现多继承
 * 
 * 两种方式区别：（存放位置不一样）
 * 继承Thread：     线程代码存放Thread子类run方法中
 * 实现Runnable：线程代码存在接口的子类的run方法
 */
class Ticket2 implements Runnable{
	private int num = 100;				//这里没有static   
	public void run(){
			while(num>0){
//				try {
//					Thread.sleep(10);		//加了之后更能看出有负数
//				} catch (Exception e) {
//					// TODO: handle exception
//				}
				System.out.println(Thread.currentThread().getName()+" 卖出了"+num+" 号票");
				num--;
			}
	}
}
public class 多线程_售票2 {
	public static void main(String[] args) {
		Ticket2 t = new Ticket2();
		
		new Thread(t).start();//由于都是使用  t 这个对象，所以四个线程通用一个类     当然也不用加static了  
		new Thread(t).start();
		new Thread(t).start();
		new Thread(t).start();
	}
}
