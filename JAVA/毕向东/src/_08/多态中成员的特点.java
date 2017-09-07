package _08;

class Fu{
	int n = 1;
	
	void show1(){
		System.out.println("fu_show1");
	}
	
	static void show2(){				//加了static 在加载类的时候，和类似静态绑定的
		System.out.println("fu_show2");
	}
	
}
class Zi extends Fu{
	int n = 2;
	
	void show1(){
		System.out.println("zi_show1");
	}
	
	static void show2(){
		System.out.println("zi_show2");
	}
	
}
/* 在多态中，成员函数（非静态）的特点
 * 编译时看左边 * 运行时看右边
 * 
 * 在多态中，成员变量的特点
 * 无论编译和运行，都参考左边（引用型变量所属的类）
 * 
 * 在多态中，静态成员函数的特点：
 * 无论编译和运行，都参考左边
 */
public class 多态中成员的特点 {
	public static void main(String[] args) {
		Fu f = new Zi();
		Zi z = new Zi();
		
		//下面这写都是  笔试  的考点。。比较重要
		f.show1();	//返回的是子类的方法*****************************这个容易弄错
		System.out.println(f.n);	//返回的是父类的对象
		z.show1();	//返回的是子类的方法
		System.out.println(z.n);	//返回的是子类的对象
		
		
		//由于show2是静态的，在一加载类之后就和 f 绑定了。调用方法时还是调用父类的方法。而不再看他的对象，到底属于哪个类
		f.show2();//*************************************************这个容易弄错
		z.show2();
	}
}
