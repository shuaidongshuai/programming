package _15;

import java.util.Comparator;
import java.util.Iterator;
import java.util.TreeSet;

/*
 * 练习：按照字符串长度排序
 * 字符串本身具备比较性，但是他的比较方式不是所需要的。
 * 
 * 这是就只能使用比较器
 */
class StringLengthComparator implements Comparator{
	public int compare(Object o1,Object o2){
		Student s1 = (Student)o1;
		Student s2 = (Student)o2;
		
		/*if(s1.getName().length()>s2.getName().length())
			return 1;
		if(s1.getName().length() == s2.getName().length())
			return 0;*/
		int num = s1.getName().length() - s2.getName().length();
		
		if(num==0){
//			return s1.getName().compareTo(s2.getName());
			int n =  s1.getName().compareTo(s2.getName());
			
			if(n==0)
				return s1.getAge() - s2.getAge();
			
			return n;
		}
		return num;
	}
}
public class TreeSet3练习 {
	public static void main(String[] args) {
		TreeSet ts = new TreeSet(new StringLengthComparator());
		
		ts.add(new Student("陈aaaaa",2));
		ts.add(new Student("陈aaaaa",1));
		ts.add(new Student("陈bbbb",3));
		ts.add(new Student("陈ccc",4));
		ts.add(new Student("陈ddddddd",5));
		for(Iterator it = ts.iterator();it.hasNext();){
			Student s = (Student)it.next();
			System.out.println(s.getName()+"    "+s.getAge());
		}
	}
}
