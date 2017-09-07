package _06;
/**单例设计模式：解决一个类在内存中只存在一个对象
 *
 *想要保证对象唯一。
 *1，为了避免其他程序过多创建对象，先禁止其他程序创建该类对象。
 *2，为了让其他程序访问该类对象，在类中自定义一个类
 *3，为了方便其他程序对自定义对象访问，可以对外提供一些访问方式
 *
 *具体操作：
 *1，构造函数，并私有化
 *2，在本类中创建一个该类的对象
 *3，提供一个方法，可以获取到该类对象
 */
//这个是先初始化对象，称为：饿汉式
class Signal{
	
	private Signal(){}
	
	private static Signal s = new Signal();
	
	public static Signal getSignal(){//创建一个返回值为Signal的方法
		return s;
	}
	
	//下面代码，就是来验证 ，是否在内存只能创建一个对象
	private int age;

	public int getAge() {
		return age;
	}

	public void setAge(int age) {
		this.age = age;
	}
}
//这个是、、方法被调用时才初始化，也叫作对象的延时加载，称为：懒汉式
class Signal2{

	private Signal2(){}

	private static Signal2 s = null;
	
	public static Signal2 getSignal2(){
		if(s == null)
			s = new Signal2();
		return s;
	}
}
public class 单例设计模式 {
	public static void main(String[] args) {
		
		Signal s = Signal.getSignal();
		System.out.println("age = "+s.getAge());
		
		s.setAge(20);//改变堆中，，Sighal类，对象中的	age 的值
		
		Signal s2 = Signal.getSignal();
		System.out.println("age = "+s2.getAge());//如果不是同一个对象，，那么   s2.getAge  应该和上面 s.getAge 的值一样
	}
}
