package 变量;

public class Arrays_fill对数组的填充 {
	public static void main(String[] args){
		int [] a =new int [5];
		int [] b =new int [5];
		
		// 发现 光用 Arrays.fill 不行   前面还得加上  java.util.
		java.util.Arrays.fill(a,1);   //给数组 a 填充 1
		java.util.Arrays.fill(b,2,4,20);//从b[2] 到 b[4] 用20填充
		for(int i=0;i<a.length;i++)
			System.out.println(a[i]+" ");
		for(int i=0;i<b.length;i++)
			System.out.println(b[i]+" ");
	}
}
