package _05;

public class Car{
	//描述颜色
	String color = "red";						// color 就是局部变量
	//描述轮胎的个数
	int num = 4;
	//运行行为（方法）
	void run(){
		System.out.println("颜色："+color+"\n轮胎数："+num);
	}
	
	//接口 Source->Generate Getters and Setters
	public String getColor() {
		return color;
	}
	public void setColor(String color) {
		this.color = color;
	}
	public int getNum() {
		return num;
	}
	public void setNum(int num) {
		this.num = num;
	}
	
}