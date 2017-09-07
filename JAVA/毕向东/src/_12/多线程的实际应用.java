package _12;
/*
	for(int i=0;i<10;i++)
	System.out.println("for1..........."+i);
	
		for(int i=0;i<10;i++)
	System.out.println("for1..........."+i);
	
		for(int i=0;i<10;i++)
	System.out.println("for1..........."+i);
	
	我们经常需要跑几个循环
 */
public class 多线程的实际应用 {

	public static void main(String[] args) {
		
		new Thread(){							//匿名内部类			用继承的方式
			public void run(){
			for(int i=0;i<10;i++)
				System.out.println("for1..........."+i);
			}
		}.start();
		
		Runnable r = new Runnable(){//用Runnable接口
			public void run(){
				for(int i=0;i<10;i++)
					System.out.println("for2..........."+i);
				}
		};
		new Thread(r).start();
		
		for(int i=0;i<10;i++)
			System.out.println("for3..........."+i);
	}
}
