package _17;

import java.util.Arrays;
import static java.util.Arrays.*;//导入的是Arrays这个类中的所有静态成员
import static java.lang.System.*;
/*
 * 当类名重名时，需要制定具体的包名
 * 当方法重名时，制定具体所属的对象或者类
 */
public class _4_静态导入 {
	public static void main(String[] args) {
		int[] arr = {3,4,1};
		
		Arrays.sort(arr);
		System.out.println(Arrays.toString(arr));
		System.out.println(Arrays.binarySearch(arr, 3));
		
		sort(arr);
		System.out.println(Arrays.toString(arr));//这个Arrays不可以省，因为Object中也有
		System.out.println(binarySearch(arr, 3));
		
		out.println("haha");//import static java.lang.System.*;
		
	}
}
