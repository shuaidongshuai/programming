package _16;

import java.util.*;

public class map_4_test2 {
	public static void main(String[] args) {
		TreeMap<Student,String> tm = new TreeMap<Student,String>(new NameComparator());
		tm.put(new Student("a zhan",24), "wuhan");
		tm.put(new Student("b zhan",20), "beijing");
		tm.put(new Student("c zhan",22), "nanjing");
		tm.put(new Student("b zhan",27), "shanghai");
		tm.put(new Student("b zhan",20), "America");
		
		Set<Map.Entry<Student, String>> entryset = tm.entrySet();
		
		for(Iterator<Map.Entry<Student, String>> it = entryset.iterator();it.hasNext();){
			Map.Entry<Student, String> me = it.next();
			Student stu = me.getKey();
			String addr = me.getValue();
			System.out.println(stu.getName()+"   "+stu.getAge()+"    "+addr);
		}
	}
}
class NameComparator implements Comparator<Student>{
	public int compare(Student s1,Student s2){
		int num = s1.getName().compareTo(s2.getName());
		if(num == 0)
			return s1.getAge() - s2.getAge();
		return num;
	}
}
