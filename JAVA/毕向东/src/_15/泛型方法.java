package _15;
/*
 * 泛型类定义的泛型，在整个类中有效，如果被方法使用，
 * 那么泛型类的对象明确要操作的具体类型后，所有要操作的类型就已经固定了
 * 
 * 为了让不同方法可以操作不同类型，而且类型还不确定
 * 那么可以将泛型定义在方法上
 * 
 * 特殊：
 * 静态方法不可以访问类上定义的泛型
 * 如果静态方法操作的引用数据类型不去定，可以将泛型定义在方法上
 */
class Demo{
	public <T> void show(T t){
		System.out.println(t);
	}
	//泛型类中也可以有，泛型方法
	public <Q> void print(Q q){
		System.out.println(q);
	}
	
	public static <W> void method(W w){
		System.out.println(w);
	}
	
}
public class 泛型方法 {

	public static void main(String[] args) {
		Demo d = new Demo();
		d.show("haha");
		d.show(123);
		d.show(new Integer(123));
		
		d.print("dong");
		d.print(123);
		
		d.method("hahahahahaha");
		
	}

}
