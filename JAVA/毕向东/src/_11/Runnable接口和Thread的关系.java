package _11;
/*
 * 下面我来模拟一下我们是如何使用  Runnable  来改变   Thread 里面的代码的
 * 
 * 太佩服自己了，，完全是自己想的  ，，，不过只是大致的方向。。具体的代码不是这样
 */
interface Runnable1{
	public void run();
}

class Thread1 implements Runnable1{
	public Runnable1 r ;
	Thread1(){}
	Thread1(Runnable1 r){
		this.r = r;
	}
	
	public void run(){
		System.out.println("\n本来这里面应该是不放东西的。。为了演示");
	}
	
	public void start(){
		if(r!=null)
		this.r.run();
		else
			run();
	}
}

//现在我们要来改变Thread里面的run方法
class dong implements Runnable1{
	public void run(){
		for(int x = 0;x<10;x++)
			System.out.print(x+" ");
	}
}

public class Runnable接口和Thread的关系 {
	public static void main(String[] args) {
		dong d = new dong();
		new Thread1(d).start();//这样就把    我们的代码    dong  里面  run   的代码   
		
		new Thread1().start();//不加  d   就执行 Thread1自己的run      加了d  就执行d 里面的run
	}
}
