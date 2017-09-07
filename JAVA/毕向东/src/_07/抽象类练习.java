package _07;
/**
 * 经理和普通员工的抽象类练习
 * @author ☆东★
 *
 */
abstract class Employes{
	private String name;
	private String id;
	private int pay;
	
	Employes(String name,String id,int pay){//普通员工和经理，共有的属性
		this.name = name;
		this.id = id;
		this.pay  = pay;
	}
	
	public abstract void work();		//普通员工和经理工作不一样
	
	void show(){								//展现出来的 共同部分
		System.out.println("name is : "+name);
		System.out.println("id is : "+id);
		System.out.println("pay is : "+pay);
	}
}

class Manager extends Employes{
	private int bonus;
	Manager(String name,String id,int pay,int bonus){
		super( name, id, pay);
		this.bonus = bonus;
	}
	public void work(){
		System.out.println("Manager work");
	}
	public void show(){							//经理展现出来的比普通员工多一个	奖金
		super.show();
		System.out.println("bonus is : "+bonus);
	}
}

class ComEmployes extends Employes{
	ComEmployes(String name,String id,int pay){
		super(name,id,pay);
	}
	public void work(){
		System.out.println("ComEmpolyes work");
	}
}


public class 抽象类练习 {
	public static void main(String[] args) {
		Manager M = new Manager("cmd","M9870000123",100000,9999);
		ComEmployes C = new ComEmployes("dong","C70000123",9999);
		M.show();
		System.out.println();
		C.show();
	}
}
