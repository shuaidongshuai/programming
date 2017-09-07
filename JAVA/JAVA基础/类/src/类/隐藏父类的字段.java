package 类;

class A{
	public String name = "陈明东";
}
class B extends A{
	public String name = "赵小小";
	void say(){
		System.out.println(name);
		System.out.println(super.name);
	}
}

public class 隐藏父类的字段 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		B b = new B();
		b.say();
	}

}
