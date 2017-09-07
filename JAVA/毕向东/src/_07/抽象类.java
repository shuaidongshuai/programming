package _07;
/*
 * 什么时候用抽象类：
 * 当多个类中出现相同功能，但是功能主体不一样
 * 
 * 抽象：看不懂
 * 
 * 抽象类的特点
 * 1，抽象方法一定在抽象类中。
 * 2，抽象方法和抽象类都必须被“abstract”关键字修饰
 * 3，抽象类不可以用new 创建对象，因为调用抽象方法没有意义
 * 4，如果子类只是覆盖了部分“抽象方法”，那么该子类还是一个抽象类
 * 
 * 定义抽象类的好处：
 * 可以强制让子类，覆盖，抽象方法
 * 比如：人   这个类，国家规定每个人都要学习。。那么。。你，我，他，都必须学习。。创建出来的类都必须有   学习的，方法
 * 
 * 特殊：抽象类中可以不用定义抽象方法。。。其作用就是。。不让这个类建立对象。
 */
abstract class Student{
	abstract void study();//抽象方法
	abstract void play();
	
	//如果多个类中出现相同功能，功能主体也一样，，如：每个人都要睡觉
	void sleep(){		  //这就不是抽象方法。。子类可以不用覆盖
		System.out.println("睡觉");
	}
}
class cmd extends Student{
	void study(){
		System.out.println("I like Study");
	}
	void play(){						//尽管子类中 play函数为空，但也算是覆盖了。。。所以这个类，，不再是抽象类
		
	}
}
abstract class Dong extends Student{	//必须加 abstract  因为“ 子类只是覆盖了部分抽象方法，那么该子类还是一个抽象类 ”
	void study(){
		System.out.println("我还是抽象类");
	}
}
public class 抽象类 {
	public static void main(String[] args) {
		new cmd().study();
		new cmd().sleep();
	}
}
