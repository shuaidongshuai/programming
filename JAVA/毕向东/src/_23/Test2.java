package _23;

import java.io.*;

public class Test2 {
	public static void main1(String[] args) {
		String s = "3.jpg";
		byte[] buf = new byte[1024];
		System.out.println(buf.length);
		System.out.println(s.length());
		
		buf = s.getBytes();
		
		System.out.println(buf.length);
	}
	public static void main2(String[] args)throws IOException {
		FileOutputStream os = new FileOutputStream("E:\\programming\\JAVA\\垃圾文件\\3.txt");
		FileInputStream is = new FileInputStream("E:\\programming\\JAVA\\垃圾文件\\3.txt"); 
		
		byte[] buf = new byte[1024];
		
		os.write("1".getBytes());
		os.write("hello".getBytes());
		
		is.read(buf,0,1);
		System.out.println(new String(buf,0,1));
		
		int len = buf[0]-'0';
		System.out.println(len);
	}
	public static void main(String[] args) throws IOException {
		FileOutputStream os = new FileOutputStream("E:\\programming\\JAVA\\垃圾文件\\3.txt");
		FileInputStream is = new FileInputStream("E:\\programming\\JAVA\\垃圾文件\\3.txt"); 
		String name = "123.";
//		String l = name.length() + "";
//		System.out.println(name.length());
//		os.write(l.getBytes());
//		byte[] buf = new byte[1024];
//		int len = is.read(buf,0,4);
//		System.out.println(new String(buf,0,len));
		String ss="学java";
		byte[] buff=ss.getBytes();
		int f=buff.length;
		System.out.println(f);
		char a = 'a';
	}
	public static void main3(String[] args) {
		String str = "学java";
		int n = str.getBytes().length;
		System.out.println(n);
	}
}