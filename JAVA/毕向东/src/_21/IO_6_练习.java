package _21;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Collections;
import java.util.Comparator;
import java.util.Set;
import java.util.TreeSet;
/*
 * 练习：
 * 从键盘输入   如：chen,43,43,54
 * 计算总分，并排序，并写入到txt文件中
 */
class Student implements Comparable<Student>{//使学生类自己带有排序功能
	private String name ;
	private int ma,cn,en,sum;
	
	public Student(String name, int ma, int cn, int en) {
		this.name = name;
		this.ma = ma;
		this.cn = cn;
		this.en = en;
		this.sum = ma + cn + en ;
	}
	
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((name == null) ? 0 : name.hashCode());
		result = prime * result + sum;
		return result;
	}

	public boolean equals(Object obj) {
		if(obj instanceof Student)
			throw new ClassCastException();
		Student s = (Student)obj;
		
		return this.name.equals(s.name) && this.sum == s.sum;
	}

	public int compareTo(Student o) {
		int num = new Integer(this.sum).compareTo(o.sum);
		if(num == 0)
			return this.name.compareTo(o.name);
		return num;
	}

	@Override
	public String toString() {
		return name+"  "+ma+"   "+cn+"   "+en;
	}
	public int getSum(){
		return sum;
	}
}
class StudentInfoTool{
	public static Set<Student> getStudents()throws IOException{
		return getStudents(null);
	}
	//返回一个带有Student 的集合
	public static Set<Student> getStudents(Comparator<Student> cmp) throws IOException{//使用比较器
		BufferedReader bufr = new BufferedReader(new InputStreamReader(System.in));//重键盘输入
		
		String line = null;
		
		Set<Student> stus = null;
		if(cmp==null)
			stus = new TreeSet<Student>();
		else
			stus = new TreeSet<Student>(cmp);//建立TreeSet集合		并且  使用比较器
		
		while((line = bufr.readLine())!=null){
			if(line.equals("over"))
				break;
			String[] info = line.split(",");//分割 ，
			
			Student stu = new Student(info[0],Integer.parseInt(info[1]),//把分割成的4份     作为参数传给Student
					Integer.parseInt(info[2]),
					Integer.parseInt(info[3]));
			
			stus.add(stu);//把学生对象，传给 TreeSet
		}
		bufr.close();
		return stus;//返回TreeSet这个集合对象
	}
	public static void write2File(Set<Student> stus) throws IOException{
		BufferedWriter bufw = new BufferedWriter(new FileWriter("E:\\programming\\JAVA\\垃圾文件\\学生成绩.txt"));
		
		for(Student stu : stus){
			bufw.write(stu.toString()+"\t");
			bufw.write("总分："+stu.getSum()+"");
			bufw.newLine();
			bufw.flush();
		}
		bufw.close();
	}
}
public class IO_6_练习 {
	public static void main(String[] args) throws IOException {
		Comparator cmp = Collections.reverseOrder();//创建一个   比较器（和原集合 排序相反的比较器）
		
		Set<Student> stus = StudentInfoTool.getStudents(cmp);
		StudentInfoTool.write2File(stus);
	}
}
/*
chen,32,34,45
dong,12,43,65
ming,32,53,53
haha,21,43,65
hell,34,65,76
over
*/
