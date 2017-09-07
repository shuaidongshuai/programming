package _14;
/*
 * add 方法的参数类型是Object，以便于接收任何类型对象
 * 
 * 集合中存储的都是对象的引用（地址）
 * 
 * 什么事迭代器？
 * 其实就是集合的取出元素的方式
 * 
 */
import java.util.ArrayList;
import java.util.Iterator;

public class 集合框架 {
	public static void main1(String[] args) {
		//创建一个集合容器，使用Collection接口的子类，ArrayList
		ArrayList a1 = new ArrayList();
		//添加元素
		a1.add("java1");
		a1.add("java2");
		a1.add("java3");
		a1.add("java4");
		//打印集合
		System.out.println(a1);
		//2.获取个数，集合长度
		//System.out.println("size:"+a1.size());
		
		//3.删除元素
		a1.remove("java2");
		System.out.println(a1);
//		a1.clear();//清空容器
//		System.out.println(a1);
		
		//4.判断元素
		System.out.println("java3是否存在："+a1.contains("java3"));
		
		System.out.println("集合是否为空："+a1.isEmpty());
	}
	public static void main2(String[] args) {
		ArrayList al1 = new ArrayList();
		al1.add("java1");
		al1.add("java2");
		al1.add("java3");
		al1.add("java4");
		
		ArrayList al2 = new ArrayList();
		al2.add("java1");
		al2.add("java2");
		al2.add("java5");
		al2.add("java6");
		
		al1.retainAll(al2);//al1和al2取交集。。。retain保持
		System.out.println(al1);
		System.out.println(al2);
		
		al1.removeAll(al2);//al1 减去  al2中所有元素，（有就减，没有就不减）
		System.out.println(al1);
		System.out.println(al2);
	}
	public static void main(String[] args) {
		ArrayList al = new ArrayList();
		al.add("java1");
		al.add("java2");
		al.add("java3");
		al.add("java4");
		
//		Iterator it = al.iterator();//获取迭代器，用于取出集合中的元素
//
//		while(it.hasNext()){//boolean	hasNext() 如果仍有元素可以迭代，则返回 true。
//			System.out.println(it.next());
//		}
		for(Iterator it = al.iterator();it.hasNext();)
			System.out.println(it.next());
		
		
		
		
	}
	
}
