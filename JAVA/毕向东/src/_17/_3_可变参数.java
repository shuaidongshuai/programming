package _17;
/*
 * 可变参数：
 * 其实就是数组参数的简写形式
 * 不用每一次都手动创建数组对象
 * 
 */
public class _3_可变参数 {
	public static void main(String[] args) {
		show(3,3,4);
		show(3,3,4,3);
		show(3);
	}
	public static void show(int...arr){//可变参数
		int len = arr.length;
		while(len>0){
			System.out.print(arr[--len]);
		}
		System.out.println();
	}
	public static void show1(String s ,int...arr){//注意可变参数一定要放在最后面
		
	}
	public static void show1(int s ,String...arr){//注意可变参数一定要放在最后面
		
	}
}
