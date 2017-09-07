package 接口;

//定义接口A

//接口就像是c语言中的.h头文件中的  函数声明
interface InterfaceA{
	final int sum1 = 20;//final 定义后的的变量只能被赋值一次，第二次赋值会出错
	int getValue();
}
//定义接口B
interface InterfaceB{
	void say();
}
//定义类，来实现接口
class InterfaceTest implements InterfaceA,InterfaceB{
	public int getValue(){
		System.out.println("实现接口A\tgetValue的方法");
		return 0;
	}
	public void say(){
		System.out.println("实现接口B\t的say方法");
	}
	
}

public class 接口的实现 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		InterfaceTest obj = new InterfaceTest();
		obj.getValue();
		obj.say();
	}

}
