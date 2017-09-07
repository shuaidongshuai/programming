package _16;

import java.util.Comparator;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

class Student implements Comparable<Student>{
	private String name;
	private int age;
	Student(String name,int age){
		this.name = name;
		this.age  = age;
	}
	
	public int compareTo(Student s){
		System.out.println("正在比较字符串大小");
		int num = this.age - s.age;
		if(num==0){
			return this.name.compareTo(s.name);
		}
		return num;
	}
	
	public int hashCode(){
		System.out.println("正在调用hashCode");
		return name.hashCode()+age*12;
	}
	
	public boolean equals(Object obj){
		if(obj instanceof Student){
			Student s = (Student)obj;
			System.out.println(s.getName()+"   正在调用equals");
			
			return this.name.equals(s.name) && this.age == s.age; 
		}
		throw new ClassCastException("类型不匹配");
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getAge() {
		return age;
	}

	public void setAge(int age) {
		this.age = age;
	}
}
public class map_3_test {
	public static void main(String[] args) {
		HashMap<Student,String> hm = new HashMap<Student,String>();
		hm.put(new Student("zhan1",20), "beijing");
		hm.put(new Student("zhan3",22), "nanjing");
		hm.put(new Student("zhan4",24), "wuhan");
		hm.put(new Student("zhan1",20), "shanghai");
		
		//第一种取出方式  keySet
		Set<Student> keyset = hm.keySet();
		System.out.println("1");
		for(Iterator<Student> it = keyset.iterator();it.hasNext();){
			System.out.println("2");
			Student stu = it.next();
			System.out.println("3");
			String addr = hm.get(stu);
			System.out.println("4");
			System.out.println(stu.getName()+"   "+stu.getAge()+"    "+addr);
		}
		
		System.out.println();
		
		//第二种方式取出
		Set<Map.Entry<Student,String>> entryset = hm.entrySet();
		for(Iterator<Map.Entry<Student,String>> it = entryset.iterator();it.hasNext();){
			Map.Entry<Student, String> me = it.next();
			Student stu = me.getKey();
			String addr = me.getValue();
			System.out.println(stu.getName()+"----"+stu.getAge()+"----"+addr);
		}
		
	}
}
