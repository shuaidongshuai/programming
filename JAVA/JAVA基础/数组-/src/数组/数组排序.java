package 数组;

import java.util.Arrays;

public class 数组排序 {

	public static void main(String[] args) {
		int [] a={5,4,2,6,7};
		int [] b={9,88,65,35};
		Arrays.sort(a, 1, 4);		//  注意  这个函数 是升序 排序		从 1 到4
		Arrays.sort(b);			//  不加参数默认 全部排序
		for(int i=0;i<a.length;i++)
			System.out.println(a[i]);
		for(int i=0;i<b.length;i++)		//  这里和 C 不一样  在 for 中 i 可以定义两次
			System.out.println(b[i]);
	}

}
