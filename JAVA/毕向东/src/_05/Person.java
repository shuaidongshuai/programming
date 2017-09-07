package _05;

public class Person {
	int age;
	Person(int age){
		this.age = age;
	}
	
	public boolean compare(Person p){
		return this.age == p.age;
	}
}
