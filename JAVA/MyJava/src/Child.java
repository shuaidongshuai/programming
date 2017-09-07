import java.util.Random;

class Father{
	public int x = 100;
	public Father(){
		System.out.println("super's x = "+x);
		age();
	}
	
	{
		x = 50;
	}
	public void age(){
		System.out.println("nothing");
	}
}
public class Child extends Father{
	static{
		System.out.println("child static");
	}
	private int n = 20;
	
	{
		n = 30;
	}
	public int x = 200;
	public Child(){
		System.out.println("child constructor body:" + n);
	}
	public void age(){
		System.out.println("age = "+n);
	}
	public void printX(){
		System.out.println("x = "+x);
	}
	public static void main(String[] args) {
		new Child().printX();
	}
}