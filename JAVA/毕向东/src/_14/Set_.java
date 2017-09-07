package _14;

import java.util.HashSet;
import java.util.Iterator;

/*
 * 		|--Set;元素是无序的(存入和取出的顺序不一定一致)，元素不可以重复
 * 			|--HashSet：底层数据结构是哈希表
 * 				HashSet是如何保证元素唯一性的呢？
 * 				是通过元素的两个方法，hasCode和equals来完成的
 * 				如果元素的HashCode值相同，才会调用equals方法是否为true
 * 				如果元素的hashCode值不同，不会调用equals
 * 
 * 				注意，对于判断元素是否存在，以及删除，依赖的方法时元素的hashCode和equals方法
 * 
 * 			|--TreeSet：
 * 
 * Set集合的功能和Collection是一致的 
 * 
 */
class Demo{
	
}
class HashSetDemo{
	public int hashCode(){
		System.out.println("自定义hashCode");
		return 60;//十六进制是	3c
	}
}
public class Set_ {
	public static void main1(String[] args) {
		System.out.println(new Demo());
		System.out.println(new Demo());
		System.out.println(new HashSetDemo());
	}
	public static void main(String[] args) {
		HashSet hs = new HashSet();
		
		System.out.println(hs.add("java1"));//存入了返回  true
		System.out.println(hs.add("java1"));//没有存入返回false
		hs.add("java2");
		hs.add("java2");
		hs.add("java3");
		hs.add("java88");//Set;元素是无序的(存入和取出的顺序不一定一致)
		hs.add("java100");
		
		Iterator it = hs.iterator();
		while(it.hasNext()){
			System.out.println(it.next());
		}
		
	}
	
}
