package _08;
/*
 * 基础班学生：
 * 		学习，睡觉
 * 高级版的学生：
 * 		学习，睡觉
 * 
 * 可以将这两类事物进行抽取
 */
abstract class Student{
	public abstract void study();
	public void sleep(){
		System.out.println("躺着睡");
	}
}

class DoStudent{
	public void doSome(Student s){
		s.study();
		s.sleep();
	}
}

public class 多态的应用 {
	public static void main(String[] args) {
		DoStudent d = new DoStudent();
		d.doSome(new BaseStudent());
		d.doSome(new AdvStudent());
	}
}



class BaseStudent extends Student{
	public void study(){
		System.out.println("base study");
	}
	public void sleep(){
		System.out.println("坐着睡");
	}
}
class AdvStudent extends Student{
	public void study(){
		System.out.println("adv study");
	}
}