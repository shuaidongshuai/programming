package _14;

import java.util.LinkedList;

/*
 * 使用LinkedList模拟一个堆栈或者队列数据结构
 */
class Queue{
	private LinkedList link;
	
	Queue(){
		link = new LinkedList();
	}
	
	public void add(Object obj){
		link.add(obj);//将指定元素添加到此列表的结尾。
	}
	
	public Object queue(){
		return link.removeFirst();
	}
	
	public Object stack(){
		return link.removeLast();
	}
	
	public boolean isNull(){
		return link.isEmpty();
	}
}

public class LinkedList_test {
	public static void main(String[] args) {
		Queue q = new Queue();
		q.add("java1");//向头部插入
		q.add("java2");
		q.add("java3");
		
		//模拟队列
//		while(!q.isNull())
//		System.out.println(q.queue());
		
		while(!q.isNull()){
			System.out.println(q.stack());
		}
		
	}
}
