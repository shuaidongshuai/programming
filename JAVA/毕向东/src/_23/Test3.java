package _23;

public class Test3 {
	public static void main(String[] args) {
		String s = "http://321.234.5.5/dong";
		int a = s.indexOf("//")+2;
		int b = s.indexOf("/",a);
		System.out.println(a);
		System.out.println(b);
		
		String str = s.substring(a,b);
		String path = s.substring(b);
		System.out.println(str);
		System.out.println(path);
	}
}
