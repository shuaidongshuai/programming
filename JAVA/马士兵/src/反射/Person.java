package ∑¥…‰;

public class Person {
	public int i = 123;
	private String s = "dong";
	private String str = "hello";
	public int getI() {
		return i;
	}
	public void setI(int i) {
		this.i = i;
	}
	public String getS() {
		return s;
	}
	public void setS(String s) {
		this.s = s;
	}
	public String getStr() {
		return str;
	}
	static {
		System.out.println("D loaded");
	}
	public Person(){
		System.out.println("D constructed");
	}
	public Person(int i){
		System.out.println("D constructed  "+i);
	}
	private Person(String s){
		System.out.println(s);
	}
	
	public void d1(int i,String s){
		System.out.println("d1 method  "+i+s);
	}
	public void d2(){
		System.out.println("d2 method");
	}
	public static void main(String[] args) {
		System.out.println("main!!!!!"+args[0]+args[1]);
	}
}
