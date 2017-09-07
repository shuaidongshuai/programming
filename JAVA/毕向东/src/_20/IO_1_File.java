package _20;

import java.io.File;

public class IO_1_File {
	public static void main(String[] args) {
		consMethod();
	}
	public static void consMethod(){
		//将1.txt封装成File对象，可以吧已有的和以出现的文件或文件夹封装成对象
	File f = new File("E:\\programming\\JAVA\\垃圾文件\\1.txt");
	
	File f2 = null;
	for(int i=0;i<3;i++)
	f2 = new File("E:\\programming\\JAVA\\垃圾文件",i+".txt");
	
	File d = new File("E:\\programming\\JAVA\\垃圾文件");
	File f3 = new File(d , "1.txt");
	
	System.out.println(f);
	System.out.println(f2);
	System.out.println(f3);
	
	}
}
