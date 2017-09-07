package 类;

class E{
	E(int a){
		System.out.println("C类的构造方法"+a);
	}
}
//子类都会掉用父类的构造方法
class F extends E{
	F(int b){
		super(20);//这一行不能注释掉，JAVA会自动插入对父类E的——无参——调用（但是父类没有无参构造方法）
		System.out.println("D类的构造方法"+b);
	}
}


public class 调用父类有参无参构造方法 {
		public static void main(String[] args) {
		// TODO Auto-generated method stub
		F d = new F
				(10);
		System.out.println( );
//		C c = new C();
	}
}
//子类的构造器中提供的参数可能只是所有参数的一部分的值，若不先调用父类的无参构造函数，则很可能有些重要的参数没有进行初始化赋值，在子类的其他方法进行操作时会出现严重的错误。
//所以有必要调用一次父类的无参构造函数。
