package _13;
/*
 * byte（关键字（基本数据类型）） Byte（类（引用数据类型））
 * short						short
 * int							Integer
 * long							long
 * boolean						boolean
 * float						Float
 * double						Double
 * char							Character
 * 
 * 十进制转化成其他进制
 * toBinaryString();
 * toHexString();
 * toOctalString();
 * 
 * 
 */
public class 基本数据类型对象包装类 {
	public static void main(String[] args) {
		//获取整形类型的最大值
		//System.out.println(Integer.MAX_VALUE);
		
		//将一个字符串转成整数
		int n =Integer.parseInt("123");//把字符串转化为数字123
		System.out.println(n+3);
		Integer i = new Integer("123");
		int num = i.intValue();
		System.out.println("第二种字符转化为数字的方法"+num);
		
		
		long x = Long.parseLong("123");
		
		System.out.println(Integer.toBinaryString(-6));
		System.out.println(Integer.toHexString(60));
		
		x = Integer.parseInt("3c",16);//把16进制  3c   转化为10进制
		System.out.println(x);
		x = Integer.parseInt("110",2);// 
		System.out.println(x);
	}
}
