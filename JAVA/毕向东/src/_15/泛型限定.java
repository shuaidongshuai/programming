package _15;
/*
 *     ?  通配符，也可以理解为占位符
 *     泛型的限定： ? extends E:可以接受E类型或者E的子类型。有上限
 *     ? super　E 可以接收E类型或者E的子类型。有下限
 */
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Iterator;
import java.util.TreeSet;

class NameCompare implements Comparator<Person>{//比较器
	public int compare(Person p1,Person p2){
		return p1.getName().compareTo(p2.getName());
	}
}
public class 泛型限定 {
	public static void main(String[] args) {
		// ? extends E:可以接受E类型或者E的子类型。有上限
		//ArrayList(Collection<? extends E> c) 构造一个包含指定 collection 的元素的列表，这些元素是按照该 collection 的迭代器返回它们的顺序排列的。 
		ArrayList<Person> al = new ArrayList<Person>();//Person就是上限
		al.add(new Person("东"));
		
		al.add(new Students("bbb"));
		al.add(new Students("ccc"));
		al.add(new Students("aaa"));
		for(Iterator<Person> it = al.iterator();it.hasNext();){//Person就是上限
			System.out.println(it.next().getName());
		}
//		printDemo(al);
		
		
		
		//? super　E 可以接收E类型或者E的子类型。有下限
		//TreeSet(Comparator<? super E> comparator)    构造一个新的空 TreeSet，它根据指定比较器进行排序。
		TreeSet<Work> ts = new TreeSet<Work>(new NameCompare());//Work就是下限
		
		ts.add(new Work("--ccc"));
		ts.add(new Work("--aaa"));
		ts.add(new Work("--bbb"));
		
		for(Iterator<Work> it = ts.iterator();it.hasNext();){//Work就是下限
			System.out.println(it.next().getName());
		}
		
		TreeSet<Students> ts1 = new TreeSet<Students>(new NameCompare());
		
		ts1.add(new Students("++bbb"));
		ts1.add(new Students("++ccc"));
		ts1.add(new Students("++aaa"));
		
		for(Iterator<Students> it = ts1.iterator();it.hasNext();){//Work就是下限
			System.out.println(it.next().getName());
		}

		
	}
	//泛型限定：  下面这个泛型限定，只限定在了 父类为Person 或 就是Person的类
	public static void printDemo(ArrayList<? extends Person> al){
		for(Iterator<? extends Person>it = al.iterator();it.hasNext();){
			System.out.println(it.next().getName());
		}
	}
//	public static void printDemo2(TreeSet<? super Work> ts){
//		for(Iterator<? super Work> it = ts.iterator();it.hasNext()){
//			System.out.println(it.next().get);
//		}
//	}
}
class Person{
	private String name ;
	Person(String name){
		this.name = name;
	}
	public String getName(){
		return name;
	}
}
class Students extends Person{
	Students(String name) {
		super(name);
	}
}
class Work extends Person{
	Work(String name) {
		super(name);
	}
}

