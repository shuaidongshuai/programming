package 类;
//定义一个人的类
class People{
	String name;
	int age;
	People(String name,int age){
		this.name =name;
		this.age =age;
	}
	public String getName(){
		return name;
	}
	public int getAge(){
		return age;
	}
}
// 我们还需要加入性别   于是 我们添加一个子类
class Man extends People{
	public String sex;
	public  Man(String name ,int age,String sex){
		super(name ,age);
		this.sex = sex;
	}
}

public class 继承{

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Man a = new Man("陈明东",20,"男");
		System.out.println(a.getName());
		System.out.println(a.name);
		System.out.println(a.getAge());
		System.out.println(a.age);
		System.out.println(a.sex);
		
	}

}
