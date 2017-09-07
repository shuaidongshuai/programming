package 类;

class C{
	C(){
		System.out.println("C类的构造方法");
	}
}
class D extends C{
	D(){
		super();//这一行注释掉也可以，JAVA会自动插入对父类C的——无参——调用
		System.out.println("D类的构造方法");
	}
}

public class 使用super调用父类的无参构造方法 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		D d = new D();
		System.out.println( );
//		C c = new C();
	}

}
