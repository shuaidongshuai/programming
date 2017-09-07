package _09;
/*
 * 1，匿名内部类其实就是内部类的简写格式
 * 2，定义匿名内部类必须是继承一个类或者实现接口
 * 3，匿名内部类格式，new 父类或者接口{定义子类的内容}
 * 4，其实匿名内部类就是一个匿名类对象，而且这个对象有点胖。可以理解为带内容的对象
 * 5，匿名内部类中定义的方法最好不要超过3个
 */
/*
class Outer1{
	class Inner{
		void show(){
			System.out.println("这是内部类");
		}
	}
	public void function(){
		new Inner().show();
	}
}
public class 匿名内部类 {
	public static void main(String[] args) {
		new Outer1().function();
	}
}*/
//	现在我们来用匿名内部类    实现上面的代码
abstract class Abs{
	abstract void show();
}
class Outer1{
	void function(){
		//这就是匿名内部类
		new Abs(){				//这是一个没有名字的类，对象，因为没有名字，所以用的是父类的名字     （千万不要以为new的是Abs的对象，看：Abs是抽象的）					
			void show(){		//由于父类是一个抽象类，子类必须实现父类所有的方法，所以这是一个，带着方法的对象（很胖的对象）
				System.out.println("内部类");
			}
		}.show();//对象创建完了，就应该调用函数了     以前的调用就是   new Inner().show();    是不是就多了一个方法在中间
	}
}
//上面是利用父类实现的匿名内部类。。。。下面是用接口实现的内部类。。。。其实，在我看来接口也就是类的一种。
interface In{
	void show();
//	void show1();     一但方法多了之后，最好不用 匿名。。太麻烦了
//	void show2();
//	void show3();
}
class Outer2{
	void function(){
		//下面new  了几个对象
		new In(){
			public void show(){
				System.out.println("这是内部类");
			}
		}.show();
		
		new In(){
			public void show(){}
			void hehe(){
				System.out.println("呵呵");
			}
		}.hehe();
	}
	//会发现当调用两次一上  类的方法，会变得非常麻烦。。平时如果调用两次以上类的方法我们都不会使用匿名对象的。会给对象起个名字
	void function2(){
		In i = new In(){					//这是多态。。父类引用    指向    子类对象
			public void show(){
				System.out.println("匿名对象有名字了");
			}
			void hehe(){}
		};
		i.show();
		//i.hehe();			但是子类中特有的方法不能调用
	}
}

public class 匿名内部类 {
	public static void main(String[] args) {
		new Outer1().function();
		new Outer2().function();
		new Outer2().function2();
	}
}
