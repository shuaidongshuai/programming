package _17;

import java.util.*;

public class _1_Collections {
	public static void main(String[] args) {
		List<String> list = new ArrayList<String>();
		
		list.add("bbb");
		list.add("aa");
		list.add("aa");
		list.add("dddd");
		list.add("z");
		list.add("cccc");
		System.out.println(list);
		
		Collections.sort(list);
		System.out.println(list);
		System.out.println("查找元素角标"+Collections.binarySearch(list, "z"));//查找元素角标

		Collections.sort(list,new Comparalen());//自定义比较器比较
		System.out.println(list);
		
		System.out.println(Collections.max(list));//查找最大元素   必须先有序
		System.out.println(Collections.max(list,new Comparalen()));
		
		Collections.replaceAll(list, "aa", "qq");//替换
		System.out.println(list);
		Collections.reverse(list);//集合元素反转
		System.out.println(list);
	}
}
//构建比较器
class Comparalen implements Comparator<String>{

	@Override
	public int compare(String o1, String o2) {
		return o1.length() - o2.length();
	}
	
}
