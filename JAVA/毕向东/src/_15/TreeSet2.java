package _15;

import java.util.Comparator;
import java.util.Iterator;
import java.util.TreeSet;

/* TreeSet的第二种排序方式:
 * 
 * 当元素自身不具备比较性，或者具备的比较性不是所需要的
 * 这时需要让容器自身具备比较性
 * 定义类比较器，将比较器对象作为参数传递给TreeSet集合的构造函数
 *  
 * 当两种排序都存在时，以比较器为主
 * 
 * 定义一个类，实现Comparator接口，覆盖compare方法
 * 
 */
public class TreeSet2 {
	public static void main(String[] args) {
		TreeSet ts = new TreeSet(new MyCompare());
		
		ts.add(new Student("陈1",22));
		ts.add(new Student("陈1",23));
		ts.add(new Student("陈5",43));
		ts.add(new Student("陈4",22));
		for(Iterator it = ts.iterator();it.hasNext();){
			Student s = (Student)it.next();
			System.out.println(s.getName()+"    "+s.getAge());
		}
	}
}
class MyCompare implements Comparator{
	public int compare(Object o1,Object o2){
		Student s1 = (Student)o1;
		Student s2 = (Student)o2;
		
		int num = s1.getName().compareTo(s2.getName());//字符串自然顺序比较
		
		if(num==0){
			return s1.getAge()-s2.getAge();
		}
		return num;
	}
}
