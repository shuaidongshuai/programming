package _16;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

/*
 * Map集合：该集合存储键值值对，
 * 
 * Map
 * 	|--Hashtable：底层是哈希表数据结构，不可以存入null键null值，集合是线程同步
 * 	|--HashMap：底层是哈希表数据结构，并允许使用 null 值和 null 键,非同步
 * 	|--TreeMap：底层是二叉树数据结构，线程不同步，可以用于给map集合中的键进行排序
 * 
 * 和Set很像
 * Set底层就是使用了Map集合
 */
public class Map_1 {
	public static void main(String[] args) {
		Map<String,String> map = new HashMap<String,String>();
		//添加元素,如果出现相同的键值，那么后添加的值将覆盖以前的值，并返回以前的值
		map.put("01","zhangsan1");
		map.put("02","zhangsan2");
		map.put("03","zhangsan3");
		System.out.println(map);
		System.out.println(map.containsKey("01"));
		
		System.out.println("remove 02 :"+map.remove("02"));
		System.out.println("get 02 :"+map.get("02"));
		System.out.println(map);
		map.put("02","zhangsan2");
		
		//HashMap：允许使用 null 值和 null 键
		map.put(null, "haha");
		System.out.println("get null   "+map.get(null));//可以通过get（）方法的返回值来判断一个键是否存在
		map.put("04", null);
		System.out.println("get 04   "+map.get("04"));//这个例子除外
		
		//获取map集合中所有值
		Collection<String> coll = map.values();
		System.out.println(coll);
		
		System.out.println(map);
		
	}
}
