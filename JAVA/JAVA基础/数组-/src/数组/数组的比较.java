package 数组;
import java.util.Arrays;

// 如果两个数组长度     相同位置的元素   都一样 那么这两个数组相等

public class 数组的比较 {
	public static void main(String [] args){
		int [] a =new int [5];
		int [] b =new int [5];
		java.util.Arrays.fill(a, 1);
		java.util.Arrays.fill(b,2,4,2);// 用 2 来填充
		if(Arrays.equals(a, b))
			System.out.print("相等\n");
		else
			System.out.print("不相等\n");
		
		System.out.println(Arrays.equals(a, b));
	}
}
