package _16已经可以玩了;

import java.util.*;

public class 产生随机数 {
	public static void main(String[] args) {
		Random random = new Random();
		int[] arr = {9,8,7,6};
		
		for(int i = 0;i<10;i++){
//			int r = random.nextInt(arr.length);//随机产生从0  -   5  之间的随机数
//			System.out.println(arr[r]);
			System.out.println(random.nextInt(5));
		}
	}
}
