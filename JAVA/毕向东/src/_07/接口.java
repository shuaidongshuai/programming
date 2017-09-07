package _07;
/*
 * 接口中所有的方法与变量都默认是 public 的，在接口中可以不写出来。但是实现接口的方法权限不能低于接口的方法权限
 * 
 * 接口的作用：
 * 就是拓展子类的功能
 */
abstract class Student1{
	public abstract void study();//每个学生都必须学习
}
//但一个学生不一定都，抽烟，喝酒，所以他们就是接口类
interface Smoking{
	void Smoke();
}
interface Drinking{
	void Drink();
}

class Wang extends Student1 implements Smoking,Drinking{
	public void study(){}								//作为一个学生必须学习
	public void Smoke(){}								//王同学有自己的行为  如：抽烟
	public void Drink(){}								//王同学有自己的行为  如：喝酒
}
class Li extends Student1 implements Drinking{
	public void study(){}								//作为一个学生必须学习
	public void Drink(){}								//李同学有自己的行为  如：喝酒
}

public class 接口 {

}
