package _23;

public class 理解一下String占几个字节 {
	public static void main1(String[] args) {
		String s1 = "学java";//汉字占两个字节。其他的都占一个字节
		String s2 = "abc";
		String s3 = "3";
		System.out.println(s1.length());
		System.out.println(s2.length());
		System.out.println(s3.length());
		
		byte[] buf = {1,2,8};
		int b = 10;
		buf[0] = (byte) b;
		System.out.println(buf[0]+1);
		System.out.println(buf[1]);
		System.out.println(buf[2]);
		
	}
	public static void main(String[] args) {
//		至于你说的问题，"AAA".getBytes() 这里"AAA"其实是作为String类型调用的，不是Char
//		你可以单独试一下char类型的。
		Character  a ='a';//这个
		Character  b ='啊';
		System.out.println(a.toString().getBytes().length);
		System.out.println(b.toString().getBytes().length);
//		java中有基本变量和引用变量的说法，int，char，bool ，double，short，long这些都是基本变量，
//		而Character，Integer等姿势引用变量，类似于将基本变量包装成了一个对象，所以是可以用.（点）的方式调用的，
//		里面的值也是一样的。编程传参时，基本变量的效率高些，但有些时候也使用引用变量
	}
}
