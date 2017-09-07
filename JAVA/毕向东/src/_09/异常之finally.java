package _09;

public class 异常之finally {
	public static void main(String[] args) {
		int x;
		try {
			x = new div1().div(10,0);
			System.out.println("x == "+x);
		} catch (Exception e) {
			System.out.println("出现异常");
		} finally {
			System.out.println("finally");//一定执行的代码
		}

		System.out.println("over");
	}
}
