package _14;

import java.util.ArrayList;
import java.util.Iterator;

/*
 * 将自定义对象作为元素存到ArrayList集合中，并去除重复元素
 * 
 * 思路：
 * 1，对人描述，将数据封装进人对象
 * 2，定义容器，将人存入
 * 3，取出
 * 
 * List集合判断元素是否相同，依据的是元素的equals方法
 * 
 */
class Person{
	private String name ;
	private int age;
	Person(String name,int age){
		this.name = name ;
		this.age = age;
	}
	
	public int hashCode(){
		System.out.println("自动调用hashCode   "+this.name);
		return name.hashCode()+age;//hashCode是字符串的方法
	}
	
	public boolean equals(Object obj){							//在调用contains方法时，会自动调用，类中 equals方法，不从写equals就默认调用Object中的equals方法
		if(obj instanceof Person){
			Person p = (Person)obj;
			System.out.println("正在默认调用equals方法。\t "+this.name+"  调用   equals 和    "+p.name+"    比较");
			
			return this.name.equals(p.name) && this.age == p.age;//equals是字符串的equals
		}
		return false;
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
public class ArrayList_test2 {
	public static void main(String[] args) {
		ArrayList al = new ArrayList();
		al.add(new Person("陈",11));
		al.add(new Person("明",12));
		al.add(new Person("东",13));
		al.add(new Person("陈",11));
		al.add(new Person("明",12));
		
		al = singleElement(al);
		
		Iterator it = al.iterator();
		
		while(it.hasNext()){
			Person p = (Person)it.next();//it.next返回的是Object类。。。想要调用Object子类（Person类）中的特有方法（getName）必须进行强转
			System.out.println(p.getName()+"    "+p.getAge());
		}
		
	}
	public static ArrayList singleElement(ArrayList al){
		ArrayList newAl = new ArrayList();
		
		Iterator it = al.iterator();
		
		while(it.hasNext()){
			Object obj = it.next();
			if(!newAl.contains(obj)){
				newAl.add(obj);
			}
		}
		return newAl;
	}
	
	
}
