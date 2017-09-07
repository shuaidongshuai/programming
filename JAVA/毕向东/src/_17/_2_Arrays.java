package _17;

import java.util.*;
/*
 * static <T> List<T>  asList(T... a)   返回一个受指定数组支持的固定大小的列表。
 * 
 * 如果数组中的元素都是对象，那么变成集合时，数组中的元素就直接转成集合中的元素
 * 如果数组中的元素都是基本数据类型，那么就会将该数组作为集合中的元素存在
 */
public class _2_Arrays {
	public static void main(String[] args) {
//		int[] arr = {2,3,4};
//		System.out.println(Arrays.toString(arr));
		String[] arr = {"abc","cc","dong"};//数组中的元素都是对象
		List<String> list = Arrays.asList(arr);//把数组变成List
		/*
		 * 把数据变成List集合有什么好处
		 * 可以使用集合的思想和方法来操作数组中的元素
		 * contains
		 * get
		 * indexOf()
		 * subList();
		 * 注意：将数组变成集合，不可以使用集合的增删方法
		 * 因为数组长度是固定的
		 */
		System.out.println(list.contains("dong"));
		System.out.println(list);
		

		int[] num = {2,4,5};//数组中的都是基本数据类型
		List<int[]> lis = Arrays.asList(num);
		System.out.println(lis);
		
		Integer[] nums = {2,4,5};//自动装箱，相当于数组中的还是对象
		List<Integer> li = Arrays.asList(nums);
		System.out.println(li);
		
	}
}
