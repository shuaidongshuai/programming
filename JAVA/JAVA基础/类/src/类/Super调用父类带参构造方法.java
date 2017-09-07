package 类;

class User{
	public String name ;
	public int age;
	public User(String name,int age){//定义一个带参数的构造方法
		this.name = name;
		this.age = age;
	}
}
class Tom extends User{
	public String password;
	public Tom(String name,int age,String passwd){
		super(name,age);
		this.password = passwd;
	}
	void dong(){
		System.out.println(super.name+"\n"+super.age+"\n"+password);
	}
}

public class Super调用父类带参构造方法 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Tom man = new Tom("chen",20,"123456");
		man.dong();
	}

}
