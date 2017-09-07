package _14;

import java.awt.List;
import java.util.*;

/*
 * Collection
 * 		|--List;元素是有序的，元素可以重复，因为该集合体系有索引
 * 			|--ArrayList:底层的数据结构使用的是数组结构	特点：查询速度快，但是增删速度慢	线程不同步
 * 			|--LinkedList;底层使用的是链表结构	特点：查询速度慢，但是增删速度快
 * 			|--Vector:底层是数组数据结构		线程同步
 * 
 * 		|--Set;元素是无序的(存入和取出的顺序不一定一致)，元素不可以重复
 * 			|--
 * 
 * List：
 * 		特有方法：烦死可以操作角标的方法都是该体系的特有方法
 * 
 * 增：
 * 		add();
 * 		addAll();
 * 
 * 删：
 * 		remove();
 * 
 * 改：
 * 		set();
 * 
 * 查：
 * 		get();
 * 		subList(from,to);
 * 		ListItrrator();
 * 
 * List集合特有的迭代器。ListIterator是Iterator子接口
 * 
 * 在迭代时，不可以通过集合对象的方法操作集合中的元素
 * 因为会发生ConcurrentModificationException异常
 * 
 * 所以，在迭代时，只能用迭代期的方法操作元素
 */
public class ListDemo {
	public static void main1(String[] args) {
		ArrayList al = new ArrayList();
		al.add("java1");
		al.add("java2");
		al.add("java3");
		
		System.out.println(al);
		//在指定位置添加元素
		al.add(1,"java0");
		System.out.println(al);
		
		//删除指定位置元素
		al.remove(2);
		System.out.println(al);
		
		al.set(1,"java3");
		System.out.println(al);
		
		//通过角标获取元素
		System.out.println(al.get(1));
		
		//获取所有元素
		for(int x = 0; x<al.size();x++){
			System.out.println(al.get(x));
		}
		
		for(Iterator it = al.iterator();it.hasNext();){
			System.out.println(it.next());
		}
		
		//通过indexOf获取对象的位置
		System.out.println(al.indexOf("java3"));
		
		java.util.List sub = al.subList(1, 3);
		System.out.println(sub);
	}
	public static void main(String[] args) {
		//演示迭代器
		ArrayList al = new ArrayList();
		al.add("java1");
		al.add("java2");
		al.add("java3");
		
		System.out.println(al);
		//在迭代过程中，准备添加或者删除元素
		
		for(ListIterator li = al.listIterator();li.hasNext();){
			Object obj = li.next();
			if(obj.equals("java2")){
				li.add("java9");
//				li.set("java00");//不能同时操作两个
			}
			if(obj.equals("java1"))
				li.set("java00");
			
			if(obj.equals("java9"))//找不到
				li.set("java88");
		}
		
		/*for(Iterator it = al.iterator();it.hasNext();){
			Object obj = it.next();
			if(obj.equals("java2"))
//			al.add("java4");在迭代时，不可以通过集合对象的方法操作集合中的元素
				it.remove();
			System.out.println("obj  "+obj);
		}*/
		
		System.out.println(al);
		
	}
}
