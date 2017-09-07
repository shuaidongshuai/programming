package _05;

public class 匿名对象 {
	public static void main(String[] args) {
		Car c = new Car();
		c.run();

		new Car().run();//这个就叫做  匿名对象
		
		// 以上两种方法调用类的 方法。效果一样
		new Car().color = "a";//毫无作用

		show(c);//把c 传入方法里面。在方法里面改变的颜色，也是c 改变的颜色
		c.run();//颜色也变成了 红色
		
		show(new Car());//这样做也可以（体现了：匿名对象可以作为实参使用）
	}
	
	public static void show(Car c){
		c.color = "红色";
		c.run();
	}
}
/*当对象的方法只调用一次时，可以使用匿名对象。
 *当对一个对象的多个成员调用时，必须给对象起个名字
 * */
