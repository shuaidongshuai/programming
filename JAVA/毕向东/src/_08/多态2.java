package _08;

class Dog extends Animal{
	void eat(){
		System.out.println("狗吃骨头");
	}
	void Watchdog(){
		System.out.println("狗看家");
	}
}

public class 多态2 {
	public static void main(String[] args) {
		
		function(new Cat());
		function(new Dog());
	}
	
	public static void function(Animal a){
		a.eat();
		if(a instanceof Cat){//如果是猫
			((Cat) a).catchMouse();
		}
		else if(a instanceof Dog){//如果是狗
			((Dog) a).Watchdog();
		}
	}
}
