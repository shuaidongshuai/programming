package _14;

import java.util.LinkedList;

/*
 * LinkedList：特有方法
 * addFirst();
 * addLast();
 * 
 * 获取元素，但是元素被删除。如果集合中没有元素，会出现异常
 * removeFirst();
 * removeLast();
 * 
 * JDK1.6出现了代替方法
 * offerFirst();在此列表的开头插入指定的元素。
 * offerLast(); 在此列表末尾插入指定的元素。
 * 
 * 
 * 获取元素，但不删除元素。如果集合中没有元素，返回null
 * peekFirst() 获取但不移除此列表的第一个元素；如果此列表为空，则返回 null。
 * peekLast() 获取但不移除此列表的最后一个元素；如果此列表为空，则返回 null。
 * 
 */
public class LinkedList_ {
	public static void main1(String[] args) {
		LinkedList link = new LinkedList();
		link.addFirst("java1");//向头部插入
		link.addFirst("java2");
		link.addFirst("java3");
		System.out.println(link);
		
		link.addLast("dong");//向尾部插入
		System.out.println(link);
		
		System.out.println(link.getFirst());//获取头部
		System.out.println(link.getLast());//获取尾部
		
		System.out.println(link.removeFirst());//获取元素，并且删除这个元素
		System.out.println(link.removeFirst());
		
		System.out.println("size = "+link.size());
	}
	public static void main(String[] args) {
		LinkedList link = new LinkedList();
		link.addFirst("java1");//向头部插入
		link.addFirst("java2");
		link.addFirst("java3");
		System.out.println(link);
		//模仿迭代器
//		while(!link.isEmpty()){//为空返回1
//			System.out.println(link.removeFirst());
//		}
		while(!link.isEmpty()){//为空返回1
			System.out.println(link.removeLast());
		}
		
	}
}
