package _07;

public class 子父变量的特点 {
	public static void main(String[] args) {
		Zi z = new Zi();
		//在子类中可以调用父类的属性
		System.out.println(z.s1);
		System.out.println(z.s2);
		z.show();
	}
}

class Fu{
	String s1 = "父类";
	int age = 20;
}

class Zi extends Fu{
	String s2 = "子类";
	int age = 10;
	public void show(){
		System.out.println(super.age+"  "+age);
	}
}