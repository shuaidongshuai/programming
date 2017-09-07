package _14;

import java.util.HashSet;
import java.util.Iterator;

/*
 * 还是以  创建  人的名字和年龄   
 * 
 * 				HashSet是如何保证元素唯一性的呢？
 * 				是通过元素的两个方法，hasCode和equals来完成的
 * 				如果元素的HashCode值相同，才会调用equals方法是否为true
 * 				如果元素的hashCode值不同，不会调用equals
 */
//class Person{}		这个类已经创建过
public class HashSet储存自定义对象 {
	public static void main(String[] args) {
		HashSet hs = new HashSet();
		hs.add(new Person("a",11));
		hs.add(new Person("b",12));
		hs.add(new Person("b",12));
//		hs.add(new Person("c",13));
		
		System.out.println("删除元素：b,12");
		hs.remove(new Person("b",12));
		
		Iterator it = hs.iterator();
		while(it.hasNext()){
			Person p = (Person)it.next();
			System.out.println(p.getName()+"    "+p.getAge());
		}
		
	}
}
