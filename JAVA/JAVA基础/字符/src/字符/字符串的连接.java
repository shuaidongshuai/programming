package 字符;

// 函数  string1.concat(string2)

public class 字符串的连接 {
	public static void main(String [] args){
		String a = "hello ";
		String b = "陈明东";
		String c = a.concat(b);   //把a 和  b  连接起来		a在前b在后
		System.out.println(c);
		
		String string1 = "hello ";
		String string2 = "陈明东";
		String string3 = string1+string2;   //  由于 String 是一个重载的运算符  所以可以像 C++ 中一样进行相加
		System.out.println(string3);
	}
}
