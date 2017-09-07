package _18;

import java.util.Random;

public class _Math {
	public static void main(String[] args) {
		double d1 = Math.ceil(19.2);//返回大于指定数据的最小整数
		double d2 = Math.ceil(-19.2);
		System.out.println(d1+"   "+d2);
		
		double d3 = Math.floor(12.34);//返回小于指定数据的最大整数
		double d4 = Math.floor(-12.34);
		System.out.println(d3+"   "+d4);
		
		long l1 = Math.round(12.35);//四舍五入
		long l2 = Math.round(12.55);
		System.out.println(l1+"   "+l2);
		
		double d5 = Math.pow(2, 3);//2的3次方
		System.out.println((int)d5);//强转为整数
		
		for(int i =0 ;i<3;i++)
		rand();//获取随机数
		
		//另一种获取随机数方法
		Random r = new Random();
		for(int i=0;i<3;i++){
			int d = r.nextInt(10)+1;//在 0（包括）和指定值（不包括）之间均匀分布的 int 值
			System.out.println(d);
		}
		
		String df = new java.text.DecimalFormat("#.00").format(213.43214);//保留两位小数    #.00表示保留两位 
		System.out.println(df);
		String df2 = new java.text.DecimalFormat("#.000").format(213.43214);//保留两位小数    #.00表示保留3位
		System.out.println(Double.parseDouble(df2));
	}
	public static void rand(){
//		double d = Math.random();//获取随机数（0-1之间的数，不包括1包括0）
		int d = (int)(Math.random()*10+1);
		System.out.println(d);
	}
}
