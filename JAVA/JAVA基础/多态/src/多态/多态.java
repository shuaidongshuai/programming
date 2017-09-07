package 多态;

public class 多态 {
	
	void test(Animal h){
		h.move();
	}
	
	public static void main(String[] args){
		//1
		Animal a = new Human();		//这种就叫多态
		a.move();
		//2
		new Human().move();
		//3
		Animal b = new Human();	//这种也是多态
		new 多态().test(b);
		//4
		new 多态().test(new Human());// 这种也是多态
		//上面4种调用形式
		System.out.println();
		
		new 多态().test(new Monkey());
		System.out.println( );
		
		Monkey c = new Monkey();
		Animal d = new Animal();
		new 多态().test(d);
		d.move();
		d = (Animal) c;// 强制类型转化  把猴子当成动物，，但对象会变成猴子 	类对象
		d.move();
		
		
	}
}

class Animal{
	void move(){
		System.out.println("动物行走");
	}
}

class Human extends Animal{
	void move(){
		System.out.println("人行走");
	}
}

class Monkey extends Animal{
	void move(){
		System.out.println("猴子走");
	}
}
