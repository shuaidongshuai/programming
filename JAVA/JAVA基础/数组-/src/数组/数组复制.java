package 数组;


public class 数组复制 {
	public static void main(String [] args){
		int [] a ={1,2,3,4,5};
		int [] b={11,12,13,14,15};
		//将数组b 的值复制到 a 中
		System.arraycopy(b, 1, a, 2, 3);	// 把 b[1]开始后 3个长度     复制到     以  a[2]开始  的后三个长度中
		System.out.println("复制之后的值");
		for(int i=0;i<a.length;i++){
			System.out.println(a[i]);
		}
	}
}
