package _11;
/*
 * 每次运行的结果都不一样
 * 因为多个线程都获取cpu执行权，CPU执行到谁，就运行谁
 * 明确：在某个时刻只能有一个程序在运行。（多核除外）
 * 
 * 
 * 
 * 创建新执行线程有两种方法。一种方法是将类声明为 Thread 的子类。该子类应重写 Thread 类的 run 方法。
 * 接下来可以分配并启动该子类的实例。例如，计算大于某一规定值的质数的线程可以写成： 
--------------------------------------------------------------------------------

     class PrimeThread extends Thread {
         long minPrime;
         PrimeThread(long minPrime) {
             this.minPrime = minPrime;
         }
 
         public void run() {
             // compute primes larger than minPrime
              . . .
         }
     }
 
--------------------------------------------------------------------------------

然后，下列代码会创建并启动一个线程： 


     PrimeThread p = new PrimeThread(143);
     p.start();
 创建线程的另一种方法是声明实现 Runnable 接口的类。该类然后实现 run 方法。然后可以分配该类的实例,
 在创建 Thread 时作为一个参数来传递并启动。采用这种风格的同一个例子如下所示： 



--------------------------------------------------------------------------------

     class PrimeRun implements Runnable {
         long minPrime;
         PrimeRun(long minPrime) {
             this.minPrime = minPrime;
         }
 
         public void run() {
             // compute primes larger than minPrime
              . . .
         }
     }
 
--------------------------------------------------------------------------------

然后，下列代码会创建并启动一个线程： 


     PrimeRun p = new PrimeRun(143);
     new Thread(p).start();
 每个线程都有一个标识名，多个线程可以同名。如果线程创建时没有指定标识名，就会为其生成一个新名称。 


 * 
 */
class PrimeThread extends Thread{
	public void run(){
		for(int i=0;i<60;i++){
			System.out.println("PrimeThread 线程在跑");
		}
	}
}

public class 多线程 {
	public static void main(String[] args) {
		PrimeThread p = new PrimeThread();
		p.start(); //		 void start() 使该线程开始执行；Java 虚拟机调用该线程的 run 方法。 
		
		for(int i=0 ;i<60;i++){
			System.out.println("main 线程在跑");
		}
	}
}
