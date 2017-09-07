package _09;

public class Continue_return_throw {
	public static void main(String[] args) {
		for(int i=0;i<100;i++)
		{
			System.out.println(i+" ");
			continue;
//			System.out.println(i+" ");//这句话不能存在
		}
		
		return;
//		System.out.println();//这句话也不能存在
		
		/*
		 * 还有  throw  后面也不能存在语句
		 */
	}
}
