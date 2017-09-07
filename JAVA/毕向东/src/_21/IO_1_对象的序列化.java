package _21;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

public class IO_1_对象的序列化 {
	public static void main(String[] args) throws Exception {
		write();
		read();
	}
	public static void write() throws IOException{
		ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream("E:\\programming\\JAVA\\垃圾文件\\1.txt"));
		oos.writeObject(new Person("dong", 20,100,"China"));
		oos.writeObject(new Person("zhang",21,111,"China"));
		oos.writeObject(new Person("lisi", 22,122,"China"));
		oos.writeObject(new Person("wang", 24,133,"China"));
		oos.close();
	}
	public static void read() throws IOException, Exception{
		ObjectInputStream ois = new ObjectInputStream(new FileInputStream("E:\\programming\\JAVA\\垃圾文件\\1.txt"));//创建从指定 InputStream 读取的 ObjectInputStream
		for(int i=0;i<4;i++){
			Person p = (Person)ois.readObject();//每次read之后   自动跳向下一个Person对象
			System.out.println(p);
		}
		ois.close();
	}
}
class Person implements Serializable{
	private static final long serialVersionUID = 100L;//加了这句话再改变属性也能读取到了

	private String name;
	private int age;
	private static int a;//注意：静态不能被序列化
	private transient String country;//如果想到非静态的成员，也不序列化。就加上transient关键字
	Person(String name,int age,int a,String country){
		this.name = name;
		this.age = age;
		this.a = a;
		this.country = country;
	}
	@Override
	public String toString() {
		return name+"    "+age;
	}
}
class Person2 implements Serializable{
	private static final long serialVersionUID = 100L;

	private String name;
	private int age;
	Person2(String name,int age){
		this.name = name;
		this.age = age;
	}
	@Override
	public String toString() {
		return name+"    "+age;
	}
}