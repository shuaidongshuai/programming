package _13;
/*
 * JDK1.5版本后的新特性
 * 
 */
public class 基本数据类型对象包装类新特性 {
	public static void main(String[] args) {
//		Integer x = new Integer("123");
//		Integer y = new Integer("123");
//		
//		System.out.println(x==y);//指向的。对象不同
//		System.out.println(x.equals(y));
		
		Integer x = 4;//自动装箱（new Integer(4)）
		x = x + 2;//x+2；x进行了自动拆箱，变成了int类型，和2进行加法运算，再将和自动装箱赋给x
		
		Integer m = 128;
		Integer n = 128;
		System.out.println(m==n);
		Integer a = 127;
		Integer b = 127;
		System.out.println(a==b);//结果为true。因为a和b指向了同一个Integer
									//因为当数值在byte范围内时，对于新特性，如果该数值已经纯在，则不会再开辟新空间
		
	}
}
