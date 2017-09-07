package _08;

public class ToString {
	public static void main(String[] args) {
		Demo d = new Demo();
		Class c = d.getClass();
		
		System.out.println(c.getName());
		System.out.println(Integer.toHexString(d.hashCode()));
		
		System.out.println(d.toString());
	}
}
