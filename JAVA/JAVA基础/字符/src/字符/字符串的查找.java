package 字符;

public class 字符串的查找 {
	public static void main(String [] args){
		String string1 = "I love you I";
		String string2 = "I";
		int a = string1.indexOf(string2);//从0开始查找  love
		int b = string1.indexOf(string2,2);	//从第2找 
		System.out.println(a);
		System.out.println(b);
	}
}
