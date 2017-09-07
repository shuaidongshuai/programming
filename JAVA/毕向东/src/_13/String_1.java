package _13;
/*
 * 字符串最大的特点：一旦被初始化就不可以被改变
 */
public class String_1 {
	public static void main(String[] args) {
		
		String s1 = "abc";//s1是一个类类型变量，“abc”是一个对象
		String s2 = new String("abc");
		//s1   s2   的区别？
		//S1在内存中一个对象
		//S2在内存中两个对象
		String s3 = "abc";
		System.out.println(s1==s2);
		System.out.println(s1==s3);
		
	}
}
