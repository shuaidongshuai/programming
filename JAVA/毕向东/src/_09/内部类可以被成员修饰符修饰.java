package _09;
/*
 * 2，当内部类在成员位置上，就可以被成员修饰符所修饰
 *    比如：private：将内部类所在的外部类中进行封装
 *    	   static：内部类就具备static的特性
 *    		当内部类被static修饰后，只能直接访问外部类中的static成员
 *    
 *    在外部其他类中访问static内部类的非静态成员：new Other3.Inner().method();		// 需要 new 一个Inner的对象
 *    在外部其他类中访问static内部类的静态成员	     ：Other3.Inner.show();				//不需要new 对象。。直接调用静态方法
 *    
 *    注意：当内部类定义了静态成员，该内部类必须是static
 */
class Other3{
	private static int x =3;
	
	static class Inner{
		void method(){
			System.out.println(x);//访问外部成员
		}
		static void show(){
			System.out.println("内部类");
		}
	}
}
public class 内部类可以被成员修饰符修饰 {
	public static void main(String[] args) {
		new Other3.Inner().method();
		Other3.Inner.show();
	}
}
