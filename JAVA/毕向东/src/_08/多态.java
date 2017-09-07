package _08;

class Animal{
	void eat(){
		System.out.println("动物吃饭");
	}
}
class Cat extends Animal{
	void eat(){
		System.out.println("猫吃饭");
	}
	void catchMouse(){
		System.out.println("猫抓老鼠");
	}
}

public class 多态 {
	public static void main(String[] args) {
		Animal A = new Cat();//类型提升：向上转型
		A.eat();//本质是猫，那就有猫的属性
		// A.catchMouse()   不能这样做了，虽然本质他是只猫，但是我们并不知道，只知道他是动物，所以不能调用猫的属性
		
		Cat C = (Cat)A;//当我们知道，它是一只猫，想要调用猫的方法。那么我们可以用强制类型转换	也叫作：向下转型
		C.catchMouse();
		
		/*向下转型是有要求的。。下面这样就不行
		 *Animal a = new Animal(); 
		 *Cat C = (Cat)a;	a 的本质不是猫，就不行强转为猫
		 */
		
	}
}
