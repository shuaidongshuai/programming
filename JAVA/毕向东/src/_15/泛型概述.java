package _15;
/*
 * 泛型：JDK1.5版本以后出现的新特性，用于解决安全问题，是一个类型安全机制
 * 好处：
 * 		1，将运行时期出现问题ClassCastException，转移到了编译时期
 * 			方便于程序员解决问题，让运行事情问题减少，安全
 * 		2,避免了强制类型转换麻烦
 */
import java.util.ArrayList;
import java.util.Iterator;

public class 泛型概述 {
	public static void main(String[] args) {
		ArrayList<String> al = new ArrayList<String>();
		al.add("abc1");
		al.add("abc3");
		al.add("abc2");
//		al.add(4);//自动装箱  al.add(new Integer(4));
		
//		for(Iterator it = al.iterator();it.hasNext();){
//			String s = (String )it.next();
//			System.out.println(s+":"+s.length());
//		}
		for(Iterator<String> it = al.iterator();it.hasNext();){
			String s = it.next();
			System.out.println(s+":"+s.length());
		}
		
	}
}
