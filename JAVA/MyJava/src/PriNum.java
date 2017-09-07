/*
 * 判断101-200之间有多少个素数，并输出所有素数。素数又叫质数，就是除了1和它本身之外，在没有整数能被它整除的数。也就是素数只有两个因子。类名PriNum
 */
public class PriNum {
	public static void main(String[] args) {
		int count = 0;
		for(int i = 101;i<=200;i++){
			for(int j = 2;j <= Math.sqrt(i);j++){
				if(i % j == 0){
					count++;
					break;
				}
			}
		}
		System.out.println("101-200之间有"+count+"个素数");
	}
}
