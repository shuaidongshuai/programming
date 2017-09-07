package _05;

public class ThisµÄÓ¦ÓÃ {
	public static void main(String[] args) {
		Person p1 = new Person(31);
		Person p2 = new Person(33);
		boolean b = p1.compare(p2);
		System.out.println(b);
		
		p2.age = 31;
		b = p1.compare(p2);
		System.out.println(b);
	}
}
