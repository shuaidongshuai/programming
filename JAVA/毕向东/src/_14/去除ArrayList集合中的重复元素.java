package _14;

import java.util.ArrayList;
import java.util.Iterator;

public class 去除ArrayList集合中的重复元素 {
	public static void main(String[] args) {
		ArrayList al = new ArrayList();
		
		al.add("java1");
		al.add("java2");
		al.add("java1");
		al.add("java3");
		al.add("java2");
		System.out.println(al);
		
		//在迭代时循环中next使用一次，就要用hasNext判断一次
//		Iterator it = al.iterator();
//		while(it.hasNext()){
//			System.out.println(it.next());
//		}
		
		al = singleElement(al);
		System.out.println(al);
	}
	
	public static ArrayList singleElement(ArrayList al){
		//定义一个临时容器
		ArrayList newAl = new ArrayList();
		
		Iterator it = al.iterator();//获取迭代器。用于取出元素
		
		while(it.hasNext()){
			Object obj = it.next();
			
			if(!newAl.contains(obj)){// boolean contains(Object o) 如果此列表中包含指定的元素，则返回 true 
				newAl.add(obj);
			}
		}
		return newAl;
	}
}
