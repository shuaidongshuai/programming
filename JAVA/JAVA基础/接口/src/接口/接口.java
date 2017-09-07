package 接口;

public class 接口 {
	public static void main(String[] args) {
		new Dilei().fly();
		new Dilei().run();
		new Plane().fly();
		new Plane().run();
}
	
}

interface Aa{
	void fly();
	void run();
}

class Dilei implements Aa{

	@Override
	public void fly() {
		// TODO Auto-generated method stub
		System.out.println("地雷不会飞");
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		System.out.println("地雷不会跑");
	}
	
}
class Plane implements Aa{

	@Override
	public void fly() {
		// TODO Auto-generated method stub
		System.out.println("飞机会飞");
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		System.out.println("飞机会跑");
	}
	
}