package _06;
class Person{
	//最先执行
	private String name = "dong";//默认初始化为   dong
	private int age;			//默认初始化为     0
	
	//最后执行
	Person(String name,int age){
		this.name = name;
		this.age  = age;
		System.out.println(name+"  "+ age);
	}
	//构造代码块-----第三执行
	{
		System.out.println(name+"  "+ age);
	}
	//第二执行
	static{
		System.out.println("这是static代码块");
	}
}
public class 构造代码块 {
	public static void main(String[] args) {
		new Person("cmd",20);
	}
}
/*	new Person("cmd",20);
 * 1，new 到了 Person.class ，所以会先找到 person.class文件加载到内存中
 * 2，执行该类中的static代码块，，给类初始化****************************************
 * 3，在堆内存中开辟空间，分配内存地址。
 * 4，在堆内存中建立对象的特有属性，并进行默认初始化*********************************
 * 5，对属性进行显示初始化*********************************************************
 * 6，对对象进行构造代码块初始化****************************************************
 * 7，对对象进行对应的构造函数初始化************************************************
 * 8，将内存地址赋给堆内存中的P变量
 */