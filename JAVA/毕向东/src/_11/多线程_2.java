package _11;
/*
 * 每次运行的结果都不一样
 * 因为多个线程都获取cpu执行权，CPU执行到谁，就运行谁
 * 明确：在某个时刻只能有一个程序在运行。（多核除外）
 * 
 * static Thread currentThread();获取当前线程的对象
 * getNmae():获取线程名称
 */
class PrimeThread2 extends Thread{
//	String name;
	public PrimeThread2(String name){
//		this.name = name;
		super(name);
	}
	
	public void run(){
		for(int i=0;i<60;i++){
			System.out.println((Thread.currentThread()==this)+" "+this.getName()+" 线程在跑  "+i);//Thread.currentThread()==this
		}
	}
}

public class 多线程_2 {
	public static void main(String[] args) {
		new PrimeThread2("陈").start();
		new PrimeThread2("明").start();
		new PrimeThread2("东").start();
		
		for(int i=0 ;i<60;i++){
			System.out.println("main 线程在跑 "+i);
		}
	}
}
