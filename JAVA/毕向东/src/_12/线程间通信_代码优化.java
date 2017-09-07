package _12;
class Res2{
	private String name ;
	private String sex;
	private boolean f  = false;//false表示还没有被读取。数据为空
	
	public synchronized void set(String name,String sex){
		if(f)
			try{this.wait();}catch(Exception e){}
		this.name = name;
		this.sex = sex;
		f = true;
		this.notify();
	}
	public synchronized void out(){
		if(!f)
			try{this.wait();}catch(Exception e){}
		System.out.println(name+"---"+sex);
		f = false;
		this.notify();
	}
	
}
class Input2 implements Runnable{
	private Res2 r;
	Input2(Res2 r){
		this.r = r;
	}
	public void run(){
		int x = 0;
		while(true){
				if(x == 0)
					r.set("陈明东", "男");
				else if(x == 1)
					r.set("lili", "girl");
				else
					r.set("dong", "man");
				x = ++x%3;
		}
	}
}
class Output2 implements Runnable{
	private Res2 r;
	Output2(Res2 r){
		this.r = r;
	}
	public void run(){
		while(true)
			r.out();
	}
}
public class 线程间通信_代码优化 {
	public static void main(String[] args) {
		Res2 r = new Res2();
//		Input2 i = new Input2(r);
//		Output2 o = new Output2(r);
//		
//		new Thread(i).start();
//		new Thread(o).start();
		//简化上面几步；
		new Thread(new Input2(r)).start();
		new Thread(new Output2(r)).start();
		
	}
}
