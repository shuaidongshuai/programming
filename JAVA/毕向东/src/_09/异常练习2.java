package _09;
/*
 * 计算圆和矩形面积
 * circle圆....Rectangles矩形
 */
class NoValueException extends RuntimeException{
	public NoValueException(String message) {
		super(message);
	}
}
class circle{
	private double r;
	private final double PI = 3.14;
	public circle(double r){
		if(r<0)
			throw new NoValueException("Radius 小于  0");//用自定义异常抛出
			
		this.r = r;
	}
	
	void getValue(){
		System.out.println(r*r*PI);
	}
}
class Rectangles{
	private double len,wid;
	public Rectangles(double len,double wid) {
		if(len<0||wid<0)
			throw new RuntimeException("数据错误");//用Java中的RuntimeException异常
		
		this.len = len;
		this.wid = wid;
	}
	
	void getValue(){
		System.out.println(len*wid);
	}
}

public class 异常练习2 {
	public static void main(String[] args) {
		new circle(3).getValue();
		new Rectangles(1,2).getValue();
		
		new circle(-1).getValue();
//		new Rectangles(-1,2).getValue();
	}
}
