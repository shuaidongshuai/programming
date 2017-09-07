package _11;
/*
 * 卖票程序
 * 多个售票口   一共有100张票
 */
class Ticket extends Thread{
	private static int num = 100;
	public void run(){
			while(num>0){
				System.out.println(Thread.currentThread().getName()+" 卖出了"+num+" 号票");
				num--;//还有一点问题,当多个线程同时运行到这还没有num--;可能同时打印4个100
			}
	}
}
public class 多线程_卖票 {
	public static void main(String[] args) {
		new Ticket().start();
		new Ticket().start();
		new Ticket().start();
		new Ticket().start();		
	}
}
