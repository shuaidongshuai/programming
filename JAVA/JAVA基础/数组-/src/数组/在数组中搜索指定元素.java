/**
 * 
 */
package 数组;

/**
 * @author ☆东★
 *
 */
import java.util.Arrays;
public class 在数组中搜索指定元素 {
	public static void main(String[] args) {
		int [] a={100,34,66,7,75,6,};
		int num1=Arrays.binarySearch(a,0,5,34);
		int num2=Arrays.binarySearch(a,1,4,100);
		System.out.println("num1 = "+num1);
		System.out.println("num2 = "+num2);
	}

}
