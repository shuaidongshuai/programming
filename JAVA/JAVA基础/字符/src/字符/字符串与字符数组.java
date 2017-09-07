package 字符;

public class 字符串与字符数组 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		char [] helloArray = {'h' , 'e' , 'l' , 'l' , 'o'};	//这是一个数组
		String helloString = new String(helloArray);		// 利用 new String 转化为字符串
		System.out.println(helloString);
		
		
		char [] hello = helloString.toCharArray();		// 利用 toCharArray()这个函数   把  helloString 这个字符串转化为 hello 这个字符数组
		for(int i=0;i<hello.length;i++){
			System.out.println(hello[i]);
		}
	}

}
