package _09;
/*
 * 内部类访问规则：
 * 1，内部类可以直接访问外部类中的成员，包括私有
 * 		之所以可以直接访问外部类中的成员，是因为内部类中持有了一个外部类的引用，格式：外部类名.this
 * 2，外部类访问内部类，必须建立内部类对象
 */
class Other{
	private int x =3;
	
	class Inner{
		void method(){
			System.out.println(x);//访问外部成员
		}
		void show(){
			System.out.println("内部类");
		}
	}
	
	void method(){
		Inner i = new Inner();//访问内部类
		i.method();
	}
}
class Other2{
	private int x =1;
	
	class Inner{
		int x = 2;					//当内部类中 变量名和外部类  一样时
		void method(){
			int x = 3;
			System.out.println(x);
			System.out.println(this.x);
			System.out.println(Other2.this.x);
		}
	}
}

public class 内部类 {
	public static void main(String[] args) {
		new Other().method();
		
		Other.Inner i = new Other().new Inner();//创建内部类对象的格式
		i.show();
		
		System.out.println();
		new Other2().new Inner().method();
	}
}
