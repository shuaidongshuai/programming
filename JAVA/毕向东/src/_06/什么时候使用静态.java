package _06;
/**
 *静态修饰的内容有”成员变量”和“函数”
 *什么时候定义静态变量（类变量）？
 *答：当对象中出现共享数据时
 *
 *什么时候定义静态函数呢？
 *答：当功能内部没有访问到 非静态数据（对象的特有数据）
 *那么该功能可以定义为静态的
 */
/*将方法都静态后可以方便使用，但是该类还是可以被其他程序建立对象
 * 为了更加严谨，强制让该类不能建立对象
 * 可以通过将构造函数私有化
 */
class Dong{
	String name = "陈明东";
	
	private Dong(){}//将构造函数私有化，使这个类不能创建对象
	
	public void showdong(){								//这里不能用 static 
		System.out.println("这里有一个人叫"+name);
	}
	public static void show(){							//这里就可以用static
		System.out.println("这里有一个人不知道叫什么");
		showw();										//这个方法只有加了 static 才能被 调用  。 如果showw没有加static 在编译的时候根本就不存在这个方法
	}
	
	
	public static void showw(){
		System.out.println("hello");
	}
}
/**
 * 为什么第一个方法不能用static ？
 * 答 ： 如果用了static  在编译的时候就会提前编译，放在内存中。不会等到 创建对象时才放在堆中。。当然编译的时候还没有 name 这个属性所以不能调用 name
 * 		第二个方法里面没有用到  “对象的特有数据” 也就可以加 static
 * 如果想要在含有 static 的方法中使用 “对象的特有数据” 就可以在这个特有数据前  加上 static 放这个类属性 在编译的时候就放入内存
 */
public class 什么时候使用静态 {
	public static void main(String[] args) {
		/*Dong d = new Dong(); 私有化之后不能创建对象
		d.showdong();*/
		
		Dong.show();//这就是使用静态的好处。可以不用创建对象。而且不是匿名对象，是根本就没有对象。直接调用类中的static 方法
	}
}
