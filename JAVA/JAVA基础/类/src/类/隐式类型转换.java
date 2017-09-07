package 类;

// static用来修饰类中的变量或方法，成为静态变量，静态方法
// 静态变量对于所有的类对象共享同一个内存空间
// 
public class 隐式类型转换 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Cat myCat = new Cat();		
		Cat.testClass();
		Animal.testClass();
		System.out.println( );
		//Cat.testInstance();	//Cat 只能调用类中有 static 的方法
		myCat.testClass();		// Cat 的对象可以调用 类中的一切
		myCat.testInstance();
		
		System.out.println( );
		
		Animal myAnimal = myCat;
		Animal.testClass();//Animal 只能调用 类中有static 的方法
		//从下面可以看出  只是隐式类型转换了  子类中的 static 部分  
		// static 是在程序执行时,类的字节码文件就加载到内存中去的
		// 没有 static 就不能加载到内存中去，需要操作对象进行加载
		myAnimal.testClass();//从这可以看出隐藏了父类的   	类方法
		// 方法重写的地方   不能转换，，如果方法没有重写就可以完全转换为Animal类
		myAnimal.testInstance();
		
		System.out.println( );
		
		Animal mytest = new Animal();
		mytest.testClass();
		mytest.testInstance();
	}
}
//创建一个 父类
class Animal{
	public static void testClass(){//对这个static方法  只能父类自己用，重命名子类方法不改变
		System.out.println("Animal中的类方法");
	}
	public void testInstance(){	// 对这个方进行重命名时，子类的方法也会改变
		System.out.println("Animal中的实例方法");
	}
}
//创建一个子类
class Cat extends Animal{
	public static void testClass(){//不能算是对父类的重写，他根本访问不到父类static的方法
	System.out.println("Cat 中类的方法");
	}
	// 下面这个方法   叫做               父类的重写
	public void testInstance(){
		System.out.println("Cat中类的实例方法");
	}
}
