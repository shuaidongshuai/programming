package _15;

import java.util.Iterator;
import java.util.TreeSet;

/*
 * Set：无序，不可以重复元素
 * 	|--HashSet：数据结构是哈希。线程是非同步的
 * 		|--保证元素唯一性的原理，判断元素的hashCode值是否相同
 * 		|--如果相同，还会继续判断元素的equals方法，是否为true
 * 	|--TreeSet:可以对Set集合中的元素进行排序
 * 			   底层数据结构是二叉树
 * 			 保证元素唯一性的依据：compareTo方法 return 0；
 * 			
 * 			TreeSet排序的第一种方式，让元素自身具备比较性
 * 			元素需要实现Comparable接口，覆盖compareTo方法
 * 			这种方式也成为元素的自然循序
 * 
 * 			TreeSet的第二种排序方式
 * 			当元素自身不具备比较性时，或者具备的比较性不是所需要的
 * 			这时就需要让集合自身具备计较性
 * 			在集合初始化时，就有了比较方式
 * 
 * 记住，排序时，当主要条件相同时，一定要判断次要条件
 */
public class TreeSet_ {
	public static void main1(String[] args) {
		TreeSet ts = new TreeSet();
		
		ts.add("aaa");
		ts.add("bbb");
		ts.add("abc");
		ts.add("aab");
		
		for(Iterator it = ts.iterator();it.hasNext();){
			System.out.println(it.next());
		}
	}
	
	public static void main(String[] args) {
		TreeSet ts = new TreeSet();
		
		ts.add(new Student("陈4",22));
		ts.add(new Student("陈1",22));
		ts.add(new Student("陈4",23));
		ts.add(new Student("陈3",24));
		ts.add(new Student("陈5",43));
		for(Iterator it = ts.iterator();it.hasNext();){
			Student s = (Student)it.next();
			System.out.println(s.getName()+"    "+s.getAge());
		}
	}
}
class Student implements Comparable{//该接口强制让学生具备比较性
	private String name;
	private int age;
	
	Student(String name,int age){
		this.name = name ;
		this.age = age ;
	}
	
	public int compareTo(Object obj){				//重写  接口 方法，，使之比较年龄排序
		if(!(obj instanceof Student))
			throw new RuntimeException("不是学生对象");
		Student s = (Student)obj;
		
		//System.out.println(this.name+"..."+this.age+"......compare......."+s.name+"..."+s.age);
		
		if(this.age > s.age ){
			return 1;
		}
		if(this.age == s.age)
			return this.name.compareTo(s.name);//名字按自然循序排序
		return -1;
		
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
