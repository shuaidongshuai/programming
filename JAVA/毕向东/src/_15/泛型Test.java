package _15;

import java.util.Comparator;
import java.util.Iterator;
import java.util.TreeSet;

public class 泛型Test {
	public static void main(String[] args) {
		TreeSet<String> ts = new TreeSet<String>(new LenComparator());
		
		ts.add("aaa");
		ts.add("dd");
		ts.add("b");
		ts.add("cccc");
		
		for(Iterator<String> it = ts.iterator();it.hasNext();){
			System.out.println(it.next());
		}
		
		System.out.println(new Integer(123));//把123这个基本类型   变成了对象。可以使用 Integer里面的方法-----
		/*   
		 *  public Integer(int value) {
        		this.value = value;}		返回的就是传进来的  int 型数据
		 */
	}
}
class LenComparator implements Comparator<String>{
	public int compare(String o1,String o2){
//		int num = new Integer(o1.length()).compareTo(new Integer(o2.length()));compareTo(Integer anotherInteger) 在数字上比较两个 Integer 对象。 
        
		int num = o1.length() - o2.length();
		
		if(num == 0)
			return o1.compareTo(o2);
		return num;
	}
}
