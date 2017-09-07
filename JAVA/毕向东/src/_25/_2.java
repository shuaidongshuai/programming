package _25;

import java.util.TreeSet;

public class _2 {
	public static void main1(String[] args) {
		String str = "我我。。我要。。要要。。学学学。。编程";
		
		str = str.replaceAll("。+", "");//去掉。
		System.out.println(str);
		
		str = str.replaceAll("(.)\\1+", "$1");//删除叠词		.代表任意字符	\1代表第一组词。但是要加上转意符	$1也代表第一组词
		System.out.println(str);
	}
	public static void main2(String[] args) {
		//按从小到大的顺序排
		String ip = "192.168.1.1 2.12.45.65 10.12.45.128 010.56.87.100";
		
		ip = ip.replaceAll("(\\d+)", "00$1");
		System.out.println(ip);
		
		ip = ip.replaceAll("0+(\\d{3})","$1");//先查到一个以上0开头而且后面必须有三个整数的字符串，然后再替换为三个字符串
												//如果后面没有3个整数就拿前面的0来填，如果0都不够就不能替换
		System.out.println(ip);
		
		String[]  arr = ip.split(" ");
		
		TreeSet<String> ts = new TreeSet<String>();
		for(String s : arr){//遍历字符串
			ts.add(s);
		}
		for(String s : ts){//遍历集合
			System.out.println(s.replaceAll("0*(\\d+)", "$1"));
		}
	}
	/*
	 * 对邮件地址进行校验
	 */
	public static void main(String[] args) {
		String mail = "abc12@sina.com.cn";
		//开头为a-zA-Z0-9_一个或多个，然后是一个@，然后a-zA-Z0-9一个或多个，然后是 . ，然后是a-zA-Z一个或多个，然后是上面两步的重复
		String reg = "[a-zA-Z0-9_]+@[a-zA-Z0-9]+(\\.[a-zA-Z]+)+";//精确匹配
		reg = "\\w+@\\w+(\\.\\w+)+";//不太精确
		System.out.println(mail.matches(reg));
	}
}
