package _09;
/*
 * 问题：
 * 如果没有父类和接口还能创建内部类么？
 * 答：不可能没有父类，最多表面上没有父类。。。JAVA中。。任何类都是Object类的子类
 */
//现在我们不用接口   和     自己定义的父类
public class 匿名内部类4 {
	public static void main(String[] args) {
		new Object(){
			void function(){
				System.out.println("hello");
			}
		}.function();
	}
}
